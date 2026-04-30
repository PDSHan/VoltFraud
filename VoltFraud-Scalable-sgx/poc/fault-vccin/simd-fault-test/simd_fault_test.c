#define _GNU_SOURCE
#include <immintrin.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/ioctl.h>

#include "DCbias.h"

int configure_for_vddq(int repeat,
                       int ch,
                       float prep_volt,
                       float prep_width,
                       float fault_volt,
                       float falut_width,
                       float delay);


typedef struct {
    int retries;
    double freq;
    double volt_prep;
    double width_prep;
    double volt_fault;
    double width_fault;
    int index;
} fault_params;

typedef struct {
    uint32_t seed;
} rng_t;

static uint32_t xorshift32(rng_t *rng)
{
    uint32_t x = rng->seed;
    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;
    rng->seed = x;
    return x;
}

static void init_data(uint32_t *a, uint32_t *b, uint32_t *c, size_t n, uint32_t seed)
{
    rng_t rng = {seed};
    for (size_t i = 0; i < n; i++) {
        a[i] = xorshift32(&rng);
        b[i] = xorshift32(&rng) | 1u;
        c[i] = xorshift32(&rng);
    }
}

static void simd_step_avx2(const uint32_t *a, const uint32_t *b, uint32_t *c, size_t n)
{
    const __m256i mask = _mm256_set1_epi32(0x00FF00FFu);
    const __m256i bias = _mm256_set1_epi32(0x9E3779B9u);
    const __m256i shift_amt = _mm256_set1_epi32(5);

    size_t i = 0;
    for (; i + 8 <= n; i += 8) {
        __m256i va = _mm256_loadu_si256((const __m256i *)&a[i]);
        __m256i vb = _mm256_loadu_si256((const __m256i *)&b[i]);
        __m256i vc = _mm256_loadu_si256((const __m256i *)&c[i]);

        // A mixed instruction sequence: add/xor/mul/shift/and/or.
        __m256i vm = _mm256_mullo_epi32(va, vb);
        __m256i vx = _mm256_xor_si256(va, vb);
        __m256i vs = _mm256_sllv_epi32(vx, shift_amt);
        __m256i va1 = _mm256_add_epi32(vm, vc);
        __m256i va2 = _mm256_add_epi32(va1, bias);
        __m256i vmasked = _mm256_and_si256(vs, mask);
        __m256i vr = _mm256_or_si256(va2, vmasked);

        _mm256_storeu_si256((__m256i *)&c[i], vr);
    }

    for (; i < n; i++) {
        uint32_t vm = a[i] * b[i];
        uint32_t vx = a[i] ^ b[i];
        uint32_t vs = vx << 5;
        uint32_t va1 = vm + c[i];
        uint32_t va2 = va1 + 0x9E3779B9u;
        uint32_t vmasked = vs & 0x00FF00FFu;
        c[i] = va2 | vmasked;
    }
}

static int check_mismatch(const uint32_t *simd, const uint32_t *ref, size_t n, size_t round)
{
    for (size_t i = 0; i < n; i++) {
        if (simd[i] != ref[i]) {
            uint32_t diff = simd[i] ^ ref[i];
            printf("[FAULT] round=%zu idx=%zu simd=0x%08" PRIx32 " ref=0x%08" PRIx32 " diff=0x%08" PRIx32 "\n",
                   round,
                   i,
                   simd[i],
                   ref[i],
                   diff);
            return 1;
        }
    }
    return 0;
}

int main(int argc, char **argv)
{
    if (!__builtin_cpu_supports("avx2")) {
        fprintf(stderr, "AVX2 not supported on this CPU.\n");
        return 2;
    }

    const char *program = argv[0];
    if (argc != 9) {
        printf("Need 8 args: %s <iterations> <frequency> <DC_pre_volt> <volt_prep> <width_prep> <volt_fault> <width_fault> <index>\n",
               program);
        return -1;
    }

    fault_params params;
    params.retries = atoi(argv[1]);
    set_freq(argv[2]);
    char *endptr;
    params.freq = strtod(argv[2], &endptr);
    double DC_pre_volt = atof(argv[3]);
    params.volt_prep = atof(argv[4]);
    params.width_prep = atof(argv[5]);
    params.volt_fault = atof(argv[6]);
    params.width_fault = atof(argv[7]);
    params.index = atoi(argv[8]);

    cpu_set_t my_set;
    CPU_ZERO(&my_set);
    CPU_SET(1, &my_set);
    sched_setaffinity(0, sizeof(cpu_set_t), &my_set);
    print_affinity();

    int ch = 1;
    double delay_start = (double)params.index;
    close_BNC_Arb(ch);
    configure_for_vddq(1,1,DC_pre_volt,0,0,0,0);
    start_DCpower_type1(ch);

    size_t rounds = (size_t)params.retries;
    size_t n = 1 << 15; // 32768 elements, 128 KiB per array
    if (n == 0) {
        fprintf(stderr, "Element count must be > 0\n");
        return 2;
    }

    size_t bytes = n * sizeof(uint32_t);
    size_t aligned_bytes = (bytes + 31u) & ~((size_t)31u);

    uint32_t *a = (uint32_t *)aligned_alloc(32, aligned_bytes);
    uint32_t *b = (uint32_t *)aligned_alloc(32, aligned_bytes);
    uint32_t *base_c = (uint32_t *)aligned_alloc(32, aligned_bytes);
    uint32_t *run1_c = (uint32_t *)aligned_alloc(32, aligned_bytes);
    uint32_t *run2_c = (uint32_t *)aligned_alloc(32, aligned_bytes);

    if (!a || !b || !base_c || !run1_c || !run2_c) {
        fprintf(stderr, "Allocation failed\n");
        free(a);
        free(b);
        free(base_c);
        free(run1_c);
        free(run2_c);
        return 2;
    }

    double volt_fault = params.volt_fault;
    size_t faults = 0;
    rng_t seed_rng = {0x12345678u};
    int DTR = TIOCM_DTR;
    const size_t chain_repeats = 5000;

    for(int i=0; i<100; i++) {
        volt_fault = volt_fault + 0.005;
        configure_for_vddq(1, 1, params.volt_prep, params.width_prep, volt_fault, params.width_fault, params.index);
        for (size_t r = 1; r <= rounds; r++) {
            uint32_t round_seed = xorshift32(&seed_rng) ^ (uint32_t)r;
            init_data(a, b, base_c, n, round_seed);

            memcpy(run1_c, base_c, n * sizeof(uint32_t));
            memcpy(run2_c, base_c, n * sizeof(uint32_t));

            int fd_trigger = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
            if (fd_trigger == -1) {
                perror("Trigger serial: could not open /dev/ttyS0");
                faults++;
                break;
            }
            if (ioctl(fd_trigger, TIOCMBIC, &DTR) == -1) {
                perror("Trigger serial: ioctl TIOCMBIC failed");
                close(fd_trigger);
                faults++;
                break;
            }

            int fault_in_round = 0;
            for (size_t k = 0; k < chain_repeats; k++) {
                simd_step_avx2(a, b, run1_c, n);
                simd_step_avx2(a, b, run2_c, n);
                if (check_mismatch(run1_c, run2_c, n, r)) {
                    faults++;
                    fault_in_round = 1;
                    break;
                }
            }
            // Adjacent repeated execution on identical random operands.

            close(fd_trigger);

            if (fault_in_round) {
                break;
            }

            if ((r % 1000) == 0) {
                printf("[INFO] completed rounds: %zu (chain_repeats=%zu)\n", r, chain_repeats);
            }
        }
        close_BNC_Arb(1);
        msleep(1000);
    }
    

    if (faults == 0) {
        printf("[OK] no mismatch detected in %zu rounds (n=%zu).\n", rounds, n);
    } else {
        printf("[SUMMARY] mismatches detected: %zu\n", faults);
    }

    free(a);
    free(b);
    free(base_c);
    free(run1_c);
    free(run2_c);
    return faults ? 1 : 0;
    
}
