#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include <openssl/bn.h>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/obj_mac.h>
#include <openssl/sha.h>

#define MSG_LEN_LEGACY (4096 * 128)
#define SIG_HEX_LEN 128
#define SIG_BUF_LEN 129

static int hex_nibble(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

static int hex_to_bytes(const char *hex, size_t hex_len, unsigned char *out, size_t out_len)
{
    if (hex_len != out_len * 2) return -1;
    for (size_t i = 0; i < out_len; i++) {
        int hi = hex_nibble(hex[2 * i]);
        int lo = hex_nibble(hex[2 * i + 1]);
        if (hi < 0 || lo < 0) return -1;
        out[i] = (unsigned char)((hi << 4) | lo);
    }
    return 0;
}

static int build_pubkey_from_fixed_priv(EC_KEY **out_key)
{
    // Keep same private key words as enclave Sign().
    const uint32_t fixedPriv[8] = {
        0x12345678u, 0x9ABCDEF0u, 0x13572468u, 0x24681357u,
        0x11111111u, 0x22222222u, 0x33333333u, 0x44444444u
    };

    EC_KEY *ec = NULL;
    BIGNUM *priv = NULL;
    EC_POINT *pub = NULL;
    BN_CTX *ctx = NULL;
    unsigned char priv_be[32];

    ec = EC_KEY_new_by_curve_name(NID_X9_62_prime256v1);
    if (!ec) goto fail;

    // IPP big numbers use 32-bit limbs in little-endian word order.
    // Convert to a single big-endian 32-byte scalar for OpenSSL.
    for (int i = 0; i < 8; i++) {
        uint32_t w = fixedPriv[7 - i];
        priv_be[i * 4 + 0] = (unsigned char)((w >> 24) & 0xFF);
        priv_be[i * 4 + 1] = (unsigned char)((w >> 16) & 0xFF);
        priv_be[i * 4 + 2] = (unsigned char)((w >> 8) & 0xFF);
        priv_be[i * 4 + 3] = (unsigned char)(w & 0xFF);
    }

    priv = BN_bin2bn(priv_be, sizeof(priv_be), NULL);
    if (!priv) goto fail;
    if (EC_KEY_set_private_key(ec, priv) != 1) goto fail;

    pub = EC_POINT_new(EC_KEY_get0_group(ec));
    ctx = BN_CTX_new();
    if (!pub || !ctx) goto fail;

    if (EC_POINT_mul(EC_KEY_get0_group(ec), pub, priv, NULL, NULL, ctx) != 1) goto fail;
    if (EC_KEY_set_public_key(ec, pub) != 1) goto fail;

    *out_key = ec;
    BN_free(priv);
    EC_POINT_free(pub);
    BN_CTX_free(ctx);
    return 0;

fail:
    BN_free(priv);
    EC_POINT_free(pub);
    BN_CTX_free(ctx);
    EC_KEY_free(ec);
    return -1;
}

int main(void)
{
    FILE *fp = fopen("../fault_output.bin", "rb");
    if (!fp) {
        perror("fopen ../fault_output.bin");
        return 1;
    }

    if (fseek(fp, 0, SEEK_END) != 0) {
        perror("fseek");
        fclose(fp);
        return 1;
    }
    long fsize = ftell(fp);
    if (fsize < SIG_BUF_LEN) {
        printf("invalid file size: %ld\n", fsize);
        fclose(fp);
        return 1;
    }

    if (fsize == (MSG_LEN_LEGACY + 64)) {
        printf("detected legacy format (message + 64-byte hash), not message + 129-byte signature hex\n");
        printf("please regenerate ../fault_output.bin with current enclave Sign path enabled\n");
        fclose(fp);
        return 1;
    }
    if (fseek(fp, 0, SEEK_SET) != 0) {
        perror("fseek");
        fclose(fp);
        return 1;
    }

    size_t msg_len = (size_t)fsize - SIG_BUF_LEN;
    unsigned char *msg = (unsigned char *)malloc(msg_len);
    char sig_hex[SIG_BUF_LEN];
    unsigned char sig_r[32], sig_s[32];
    unsigned char full_hash[SHA512_DIGEST_LENGTH];
    unsigned char digest32[32];
    int rc = 1;

    if (!msg) {
        perror("malloc msg");
        fclose(fp);
        return 1;
    }

    if (fread(msg, 1, msg_len, fp) != msg_len) {
        printf("failed to read message section\n");
        goto out;
    }
    if (fread(sig_hex, 1, SIG_BUF_LEN, fp) != SIG_BUF_LEN) {
        printf("failed to read signature section\n");
        goto out;
    }
    fclose(fp);
    fp = NULL;

    // Be tolerant if producer omitted trailing '\0'.
    sig_hex[SIG_HEX_LEN] = '\0';

    if (hex_to_bytes(sig_hex, 64, sig_r, sizeof(sig_r)) != 0 ||
        hex_to_bytes(sig_hex + 64, 64, sig_s, sizeof(sig_s)) != 0) {
        printf("invalid signature hex format\n");
        goto out;
    }

    SHA512(msg, msg_len, full_hash);
    memcpy(digest32, full_hash, sizeof(digest32));

    ECDSA_SIG *sig = ECDSA_SIG_new();
    EC_KEY *pubkey = NULL;
    BIGNUM *r = BN_bin2bn(sig_r, sizeof(sig_r), NULL);
    BIGNUM *s = BN_bin2bn(sig_s, sizeof(sig_s), NULL);
    if (!sig || !r || !s) {
        printf("failed to create signature components\n");
        ECDSA_SIG_free(sig);
        BN_free(r);
        BN_free(s);
        goto out;
    }

    if (ECDSA_SIG_set0(sig, r, s) != 1) {
        printf("failed to set ECDSA_SIG\n");
        ECDSA_SIG_free(sig);
        BN_free(r);
        BN_free(s);
        goto out;
    }

    if (build_pubkey_from_fixed_priv(&pubkey) != 0) {
        printf("failed to derive public key from fixed private key\n");
        ECDSA_SIG_free(sig);
        goto out;
    }

    int verify_ok = ECDSA_do_verify(digest32, sizeof(digest32), sig, pubkey);
    if (verify_ok == 1) {
        printf("signature verification passed\n");

        const uint64_t expected_v = 1000000ULL;
        size_t tampered = 0;
        size_t blocks = msg_len / 64;
        for (size_t off = 0; off + 64 <= msg_len; off += 64) {
            uint64_t block_tail = 0;
            memcpy(&block_tail, msg + off + 56, sizeof(block_tail));
            if (block_tail != expected_v) {
                printf("tampered block idx=%zu off=%zu low8B=%llu\n",
                       off / 64,
                       off,
                       (unsigned long long)block_tail);
                tampered++;
            }
        }
        if (msg_len % 64 != 0) {
            printf("warning: message length %zu is not a multiple of 64 bytes\n", msg_len);
        }
        printf("scan done: blocks=%zu, tampered=%zu\n", blocks, tampered);

        rc = 0;
    } else if (verify_ok == 0) {
        printf("signature verification failed\n");
    } else {
        printf("signature verification error\n");
    }

    EC_KEY_free(pubkey);
    ECDSA_SIG_free(sig);

out:
    if (fp) fclose(fp);
    free(msg);
    return rc;
}