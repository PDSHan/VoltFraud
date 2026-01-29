
app：     文件格式 elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64 
    1004:	48 83 ec 08          	sub    $0x8,%rsp
    1008:	48 8b 05 d9 3f 00 00 	mov    0x3fd9(%rip),%rax        # 4fe8 <__gmon_start__@Base>
    100f:	48 85 c0             	test   %rax,%rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   *%rax
    1016:	48 83 c4 08          	add    $0x8,%rsp
    101a:	c3                   	ret    

Disassembly of section .plt:

0000000000001020 <.plt>:
    1020:	ff 35 82 3e 00 00    	push   0x3e82(%rip)        # 4ea8 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	f2 ff 25 83 3e 00 00 	bnd jmp *0x3e83(%rip)        # 4eb0 <_GLOBAL_OFFSET_TABLE_+0x10>
    102d:	0f 1f 00             	nopl   (%rax)
    1030:	f3 0f 1e fa          	endbr64 
    1034:	68 00 00 00 00       	push   $0x0
    1039:	f2 e9 e1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    103f:	90                   	nop
    1040:	f3 0f 1e fa          	endbr64 
    1044:	68 01 00 00 00       	push   $0x1
    1049:	f2 e9 d1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    104f:	90                   	nop
    1050:	f3 0f 1e fa          	endbr64 
    1054:	68 02 00 00 00       	push   $0x2
    1059:	f2 e9 c1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    105f:	90                   	nop
    1060:	f3 0f 1e fa          	endbr64 
    1064:	68 03 00 00 00       	push   $0x3
    1069:	f2 e9 b1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    106f:	90                   	nop
    1070:	f3 0f 1e fa          	endbr64 
    1074:	68 04 00 00 00       	push   $0x4
    1079:	f2 e9 a1 ff ff ff    	bnd jmp 1020 <_init+0x20>
    107f:	90                   	nop
    1080:	f3 0f 1e fa          	endbr64 
    1084:	68 05 00 00 00       	push   $0x5
    1089:	f2 e9 91 ff ff ff    	bnd jmp 1020 <_init+0x20>
    108f:	90                   	nop
    1090:	f3 0f 1e fa          	endbr64 
    1094:	68 06 00 00 00       	push   $0x6
    1099:	f2 e9 81 ff ff ff    	bnd jmp 1020 <_init+0x20>
    109f:	90                   	nop
    10a0:	f3 0f 1e fa          	endbr64 
    10a4:	68 07 00 00 00       	push   $0x7
    10a9:	f2 e9 71 ff ff ff    	bnd jmp 1020 <_init+0x20>
    10af:	90                   	nop
    10b0:	f3 0f 1e fa          	endbr64 
    10b4:	68 08 00 00 00       	push   $0x8
    10b9:	f2 e9 61 ff ff ff    	bnd jmp 1020 <_init+0x20>
    10bf:	90                   	nop
    10c0:	f3 0f 1e fa          	endbr64 
    10c4:	68 09 00 00 00       	push   $0x9
    10c9:	f2 e9 51 ff ff ff    	bnd jmp 1020 <_init+0x20>
    10cf:	90                   	nop
    10d0:	f3 0f 1e fa          	endbr64 
    10d4:	68 0a 00 00 00       	push   $0xa
    10d9:	f2 e9 41 ff ff ff    	bnd jmp 1020 <_init+0x20>
    10df:	90                   	nop
    10e0:	f3 0f 1e fa          	endbr64 
    10e4:	68 0b 00 00 00       	push   $0xb
    10e9:	f2 e9 31 ff ff ff    	bnd jmp 1020 <_init+0x20>
    10ef:	90                   	nop
    10f0:	f3 0f 1e fa          	endbr64 
    10f4:	68 0c 00 00 00       	push   $0xc
    10f9:	f2 e9 21 ff ff ff    	bnd jmp 1020 <_init+0x20>
    10ff:	90                   	nop
    1100:	f3 0f 1e fa          	endbr64 
    1104:	68 0d 00 00 00       	push   $0xd
    1109:	f2 e9 11 ff ff ff    	bnd jmp 1020 <_init+0x20>
    110f:	90                   	nop
    1110:	f3 0f 1e fa          	endbr64 
    1114:	68 0e 00 00 00       	push   $0xe
    1119:	f2 e9 01 ff ff ff    	bnd jmp 1020 <_init+0x20>
    111f:	90                   	nop
    1120:	f3 0f 1e fa          	endbr64 
    1124:	68 0f 00 00 00       	push   $0xf
    1129:	f2 e9 f1 fe ff ff    	bnd jmp 1020 <_init+0x20>
    112f:	90                   	nop
    1130:	f3 0f 1e fa          	endbr64 
    1134:	68 10 00 00 00       	push   $0x10
    1139:	f2 e9 e1 fe ff ff    	bnd jmp 1020 <_init+0x20>
    113f:	90                   	nop
    1140:	f3 0f 1e fa          	endbr64 
    1144:	68 11 00 00 00       	push   $0x11
    1149:	f2 e9 d1 fe ff ff    	bnd jmp 1020 <_init+0x20>
    114f:	90                   	nop
    1150:	f3 0f 1e fa          	endbr64 
    1154:	68 12 00 00 00       	push   $0x12
    1159:	f2 e9 c1 fe ff ff    	bnd jmp 1020 <_init+0x20>
    115f:	90                   	nop
    1160:	f3 0f 1e fa          	endbr64 
    1164:	68 13 00 00 00       	push   $0x13
    1169:	f2 e9 b1 fe ff ff    	bnd jmp 1020 <_init+0x20>
    116f:	90                   	nop
    1170:	f3 0f 1e fa          	endbr64 
    1174:	68 14 00 00 00       	push   $0x14
    1179:	f2 e9 a1 fe ff ff    	bnd jmp 1020 <_init+0x20>
    117f:	90                   	nop
    1180:	f3 0f 1e fa          	endbr64 
    1184:	68 15 00 00 00       	push   $0x15
    1189:	f2 e9 91 fe ff ff    	bnd jmp 1020 <_init+0x20>
    118f:	90                   	nop
    1190:	f3 0f 1e fa          	endbr64 
    1194:	68 16 00 00 00       	push   $0x16
    1199:	f2 e9 81 fe ff ff    	bnd jmp 1020 <_init+0x20>
    119f:	90                   	nop
    11a0:	f3 0f 1e fa          	endbr64 
    11a4:	68 17 00 00 00       	push   $0x17
    11a9:	f2 e9 71 fe ff ff    	bnd jmp 1020 <_init+0x20>
    11af:	90                   	nop
    11b0:	f3 0f 1e fa          	endbr64 
    11b4:	68 18 00 00 00       	push   $0x18
    11b9:	f2 e9 61 fe ff ff    	bnd jmp 1020 <_init+0x20>
    11bf:	90                   	nop
    11c0:	f3 0f 1e fa          	endbr64 
    11c4:	68 19 00 00 00       	push   $0x19
    11c9:	f2 e9 51 fe ff ff    	bnd jmp 1020 <_init+0x20>
    11cf:	90                   	nop
    11d0:	f3 0f 1e fa          	endbr64 
    11d4:	68 1a 00 00 00       	push   $0x1a
    11d9:	f2 e9 41 fe ff ff    	bnd jmp 1020 <_init+0x20>
    11df:	90                   	nop
    11e0:	f3 0f 1e fa          	endbr64 
    11e4:	68 1b 00 00 00       	push   $0x1b
    11e9:	f2 e9 31 fe ff ff    	bnd jmp 1020 <_init+0x20>
    11ef:	90                   	nop
    11f0:	f3 0f 1e fa          	endbr64 
    11f4:	68 1c 00 00 00       	push   $0x1c
    11f9:	f2 e9 21 fe ff ff    	bnd jmp 1020 <_init+0x20>
    11ff:	90                   	nop
    1200:	f3 0f 1e fa          	endbr64 
    1204:	68 1d 00 00 00       	push   $0x1d
    1209:	f2 e9 11 fe ff ff    	bnd jmp 1020 <_init+0x20>
    120f:	90                   	nop
    1210:	f3 0f 1e fa          	endbr64 
    1214:	68 1e 00 00 00       	push   $0x1e
    1219:	f2 e9 01 fe ff ff    	bnd jmp 1020 <_init+0x20>
    121f:	90                   	nop
    1220:	f3 0f 1e fa          	endbr64 
    1224:	68 1f 00 00 00       	push   $0x1f
    1229:	f2 e9 f1 fd ff ff    	bnd jmp 1020 <_init+0x20>
    122f:	90                   	nop
    1230:	f3 0f 1e fa          	endbr64 
    1234:	68 20 00 00 00       	push   $0x20
    1239:	f2 e9 e1 fd ff ff    	bnd jmp 1020 <_init+0x20>
    123f:	90                   	nop
    1240:	f3 0f 1e fa          	endbr64 
    1244:	68 21 00 00 00       	push   $0x21
    1249:	f2 e9 d1 fd ff ff    	bnd jmp 1020 <_init+0x20>
    124f:	90                   	nop
    1250:	f3 0f 1e fa          	endbr64 
    1254:	68 22 00 00 00       	push   $0x22
    1259:	f2 e9 c1 fd ff ff    	bnd jmp 1020 <_init+0x20>
    125f:	90                   	nop
    1260:	f3 0f 1e fa          	endbr64 
    1264:	68 23 00 00 00       	push   $0x23
    1269:	f2 e9 b1 fd ff ff    	bnd jmp 1020 <_init+0x20>
    126f:	90                   	nop

Disassembly of section .plt.got:

0000000000001270 <__cxa_finalize@plt>:
    1270:	f3 0f 1e fa          	endbr64 
    1274:	f2 ff 25 7d 3d 00 00 	bnd jmp *0x3d7d(%rip)        # 4ff8 <__cxa_finalize@GLIBC_2.2.5>
    127b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .plt.sec:

0000000000001280 <putchar@plt>:
    1280:	f3 0f 1e fa          	endbr64 
    1284:	f2 ff 25 2d 3c 00 00 	bnd jmp *0x3c2d(%rip)        # 4eb8 <putchar@GLIBC_2.2.5>
    128b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001290 <puts@plt>:
    1290:	f3 0f 1e fa          	endbr64 
    1294:	f2 ff 25 25 3c 00 00 	bnd jmp *0x3c25(%rip)        # 4ec0 <puts@GLIBC_2.2.5>
    129b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000012a0 <strtod@plt>:
    12a0:	f3 0f 1e fa          	endbr64 
    12a4:	f2 ff 25 1d 3c 00 00 	bnd jmp *0x3c1d(%rip)        # 4ec8 <strtod@GLIBC_2.2.5>
    12ab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000012b0 <atof@plt>:
    12b0:	f3 0f 1e fa          	endbr64 
    12b4:	f2 ff 25 15 3c 00 00 	bnd jmp *0x3c15(%rip)        # 4ed0 <atof@GLIBC_2.2.5>
    12bb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000012c0 <clock_gettime@plt>:
    12c0:	f3 0f 1e fa          	endbr64 
    12c4:	f2 ff 25 0d 3c 00 00 	bnd jmp *0x3c0d(%rip)        # 4ed8 <clock_gettime@GLIBC_2.17>
    12cb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000012d0 <write@plt>:
    12d0:	f3 0f 1e fa          	endbr64 
    12d4:	f2 ff 25 05 3c 00 00 	bnd jmp *0x3c05(%rip)        # 4ee0 <write@GLIBC_2.2.5>
    12db:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000012e0 <sgx_destroy_enclave@plt>:
    12e0:	f3 0f 1e fa          	endbr64 
    12e4:	f2 ff 25 fd 3b 00 00 	bnd jmp *0x3bfd(%rip)        # 4ee8 <sgx_destroy_enclave@Base>
    12eb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000012f0 <fclose@plt>:
    12f0:	f3 0f 1e fa          	endbr64 
    12f4:	f2 ff 25 f5 3b 00 00 	bnd jmp *0x3bf5(%rip)        # 4ef0 <fclose@GLIBC_2.2.5>
    12fb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001300 <strlen@plt>:
    1300:	f3 0f 1e fa          	endbr64 
    1304:	f2 ff 25 ed 3b 00 00 	bnd jmp *0x3bed(%rip)        # 4ef8 <strlen@GLIBC_2.2.5>
    130b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001310 <__stack_chk_fail@plt>:
    1310:	f3 0f 1e fa          	endbr64 
    1314:	f2 ff 25 e5 3b 00 00 	bnd jmp *0x3be5(%rip)        # 4f00 <__stack_chk_fail@GLIBC_2.4>
    131b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001320 <system@plt>:
    1320:	f3 0f 1e fa          	endbr64 
    1324:	f2 ff 25 dd 3b 00 00 	bnd jmp *0x3bdd(%rip)        # 4f08 <system@GLIBC_2.2.5>
    132b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001330 <printf@plt>:
    1330:	f3 0f 1e fa          	endbr64 
    1334:	f2 ff 25 d5 3b 00 00 	bnd jmp *0x3bd5(%rip)        # 4f10 <printf@GLIBC_2.2.5>
    133b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001340 <pclose@plt>:
    1340:	f3 0f 1e fa          	endbr64 
    1344:	f2 ff 25 cd 3b 00 00 	bnd jmp *0x3bcd(%rip)        # 4f18 <pclose@GLIBC_2.2.5>
    134b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001350 <snprintf@plt>:
    1350:	f3 0f 1e fa          	endbr64 
    1354:	f2 ff 25 c5 3b 00 00 	bnd jmp *0x3bc5(%rip)        # 4f20 <snprintf@GLIBC_2.2.5>
    135b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001360 <dup@plt>:
    1360:	f3 0f 1e fa          	endbr64 
    1364:	f2 ff 25 bd 3b 00 00 	bnd jmp *0x3bbd(%rip)        # 4f28 <dup@GLIBC_2.2.5>
    136b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001370 <__assert_fail@plt>:
    1370:	f3 0f 1e fa          	endbr64 
    1374:	f2 ff 25 b5 3b 00 00 	bnd jmp *0x3bb5(%rip)        # 4f30 <__assert_fail@GLIBC_2.2.5>
    137b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001380 <fputs@plt>:
    1380:	f3 0f 1e fa          	endbr64 
    1384:	f2 ff 25 ad 3b 00 00 	bnd jmp *0x3bad(%rip)        # 4f38 <fputs@GLIBC_2.2.5>
    138b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001390 <ioctl@plt>:
    1390:	f3 0f 1e fa          	endbr64 
    1394:	f2 ff 25 a5 3b 00 00 	bnd jmp *0x3ba5(%rip)        # 4f40 <ioctl@GLIBC_2.2.5>
    139b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000013a0 <close@plt>:
    13a0:	f3 0f 1e fa          	endbr64 
    13a4:	f2 ff 25 9d 3b 00 00 	bnd jmp *0x3b9d(%rip)        # 4f48 <close@GLIBC_2.2.5>
    13ab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000013b0 <sched_setaffinity@plt>:
    13b0:	f3 0f 1e fa          	endbr64 
    13b4:	f2 ff 25 95 3b 00 00 	bnd jmp *0x3b95(%rip)        # 4f50 <sched_setaffinity@GLIBC_2.3.4>
    13bb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000013c0 <memcmp@plt>:
    13c0:	f3 0f 1e fa          	endbr64 
    13c4:	f2 ff 25 8d 3b 00 00 	bnd jmp *0x3b8d(%rip)        # 4f58 <memcmp@GLIBC_2.2.5>
    13cb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000013d0 <fgets@plt>:
    13d0:	f3 0f 1e fa          	endbr64 
    13d4:	f2 ff 25 85 3b 00 00 	bnd jmp *0x3b85(%rip)        # 4f60 <fgets@GLIBC_2.2.5>
    13db:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000013e0 <fprintf@plt>:
    13e0:	f3 0f 1e fa          	endbr64 
    13e4:	f2 ff 25 7d 3b 00 00 	bnd jmp *0x3b7d(%rip)        # 4f68 <fprintf@GLIBC_2.2.5>
    13eb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000013f0 <sgx_ecall@plt>:
    13f0:	f3 0f 1e fa          	endbr64 
    13f4:	f2 ff 25 75 3b 00 00 	bnd jmp *0x3b75(%rip)        # 4f70 <sgx_ecall@Base>
    13fb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001400 <fdopen@plt>:
    1400:	f3 0f 1e fa          	endbr64 
    1404:	f2 ff 25 6d 3b 00 00 	bnd jmp *0x3b6d(%rip)        # 4f78 <fdopen@GLIBC_2.2.5>
    140b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001410 <open@plt>:
    1410:	f3 0f 1e fa          	endbr64 
    1414:	f2 ff 25 65 3b 00 00 	bnd jmp *0x3b65(%rip)        # 4f80 <open@GLIBC_2.2.5>
    141b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001420 <popen@plt>:
    1420:	f3 0f 1e fa          	endbr64 
    1424:	f2 ff 25 5d 3b 00 00 	bnd jmp *0x3b5d(%rip)        # 4f88 <popen@GLIBC_2.2.5>
    142b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001430 <perror@plt>:
    1430:	f3 0f 1e fa          	endbr64 
    1434:	f2 ff 25 55 3b 00 00 	bnd jmp *0x3b55(%rip)        # 4f90 <perror@GLIBC_2.2.5>
    143b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001440 <sysconf@plt>:
    1440:	f3 0f 1e fa          	endbr64 
    1444:	f2 ff 25 4d 3b 00 00 	bnd jmp *0x3b4d(%rip)        # 4f98 <sysconf@GLIBC_2.2.5>
    144b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001450 <atoi@plt>:
    1450:	f3 0f 1e fa          	endbr64 
    1454:	f2 ff 25 45 3b 00 00 	bnd jmp *0x3b45(%rip)        # 4fa0 <atoi@GLIBC_2.2.5>
    145b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001460 <sprintf@plt>:
    1460:	f3 0f 1e fa          	endbr64 
    1464:	f2 ff 25 3d 3b 00 00 	bnd jmp *0x3b3d(%rip)        # 4fa8 <sprintf@GLIBC_2.2.5>
    146b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001470 <exit@plt>:
    1470:	f3 0f 1e fa          	endbr64 
    1474:	f2 ff 25 35 3b 00 00 	bnd jmp *0x3b35(%rip)        # 4fb0 <exit@GLIBC_2.2.5>
    147b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001480 <sched_getaffinity@plt>:
    1480:	f3 0f 1e fa          	endbr64 
    1484:	f2 ff 25 2d 3b 00 00 	bnd jmp *0x3b2d(%rip)        # 4fb8 <sched_getaffinity@GLIBC_2.3.4>
    148b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000001490 <sleep@plt>:
    1490:	f3 0f 1e fa          	endbr64 
    1494:	f2 ff 25 25 3b 00 00 	bnd jmp *0x3b25(%rip)        # 4fc0 <sleep@GLIBC_2.2.5>
    149b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000014a0 <sgx_create_enclave@plt>:
    14a0:	f3 0f 1e fa          	endbr64 
    14a4:	f2 ff 25 1d 3b 00 00 	bnd jmp *0x3b1d(%rip)        # 4fc8 <sgx_create_enclave@Base>
    14ab:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

00000000000014b0 <usleep@plt>:
    14b0:	f3 0f 1e fa          	endbr64 
    14b4:	f2 ff 25 15 3b 00 00 	bnd jmp *0x3b15(%rip)        # 4fd0 <usleep@GLIBC_2.2.5>
    14bb:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

Disassembly of section .text:

00000000000014c0 <_start>:
    14c0:	f3 0f 1e fa          	endbr64 
    14c4:	31 ed                	xor    %ebp,%ebp
    14c6:	49 89 d1             	mov    %rdx,%r9
    14c9:	5e                   	pop    %rsi
    14ca:	48 89 e2             	mov    %rsp,%rdx
    14cd:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
    14d1:	50                   	push   %rax
    14d2:	54                   	push   %rsp
    14d3:	45 31 c0             	xor    %r8d,%r8d
    14d6:	31 c9                	xor    %ecx,%ecx
    14d8:	48 8d 3d 73 01 00 00 	lea    0x173(%rip),%rdi        # 1652 <main>
    14df:	ff 15 f3 3a 00 00    	call   *0x3af3(%rip)        # 4fd8 <__libc_start_main@GLIBC_2.34>
    14e5:	f4                   	hlt    
    14e6:	66 2e 0f 1f 84 00 00 	cs nopw 0x0(%rax,%rax,1)
    14ed:	00 00 00 

00000000000014f0 <deregister_tm_clones>:
    14f0:	48 8d 3d 21 3b 00 00 	lea    0x3b21(%rip),%rdi        # 5018 <__TMC_END__>
    14f7:	48 8d 05 1a 3b 00 00 	lea    0x3b1a(%rip),%rax        # 5018 <__TMC_END__>
    14fe:	48 39 f8             	cmp    %rdi,%rax
    1501:	74 15                	je     1518 <deregister_tm_clones+0x28>
    1503:	48 8b 05 d6 3a 00 00 	mov    0x3ad6(%rip),%rax        # 4fe0 <_ITM_deregisterTMCloneTable@Base>
    150a:	48 85 c0             	test   %rax,%rax
    150d:	74 09                	je     1518 <deregister_tm_clones+0x28>
    150f:	ff e0                	jmp    *%rax
    1511:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
    1518:	c3                   	ret    
    1519:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001520 <register_tm_clones>:
    1520:	48 8d 3d f1 3a 00 00 	lea    0x3af1(%rip),%rdi        # 5018 <__TMC_END__>
    1527:	48 8d 35 ea 3a 00 00 	lea    0x3aea(%rip),%rsi        # 5018 <__TMC_END__>
    152e:	48 29 fe             	sub    %rdi,%rsi
    1531:	48 89 f0             	mov    %rsi,%rax
    1534:	48 c1 ee 3f          	shr    $0x3f,%rsi
    1538:	48 c1 f8 03          	sar    $0x3,%rax
    153c:	48 01 c6             	add    %rax,%rsi
    153f:	48 d1 fe             	sar    %rsi
    1542:	74 14                	je     1558 <register_tm_clones+0x38>
    1544:	48 8b 05 a5 3a 00 00 	mov    0x3aa5(%rip),%rax        # 4ff0 <_ITM_registerTMCloneTable@Base>
    154b:	48 85 c0             	test   %rax,%rax
    154e:	74 08                	je     1558 <register_tm_clones+0x38>
    1550:	ff e0                	jmp    *%rax
    1552:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)
    1558:	c3                   	ret    
    1559:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

0000000000001560 <__do_global_dtors_aux>:
    1560:	f3 0f 1e fa          	endbr64 
    1564:	80 3d bd 3a 00 00 00 	cmpb   $0x0,0x3abd(%rip)        # 5028 <completed.0>
    156b:	75 2b                	jne    1598 <__do_global_dtors_aux+0x38>
    156d:	55                   	push   %rbp
    156e:	48 83 3d 82 3a 00 00 	cmpq   $0x0,0x3a82(%rip)        # 4ff8 <__cxa_finalize@GLIBC_2.2.5>
    1575:	00 
    1576:	48 89 e5             	mov    %rsp,%rbp
    1579:	74 0c                	je     1587 <__do_global_dtors_aux+0x27>
    157b:	48 8b 3d 86 3a 00 00 	mov    0x3a86(%rip),%rdi        # 5008 <__dso_handle>
    1582:	e8 e9 fc ff ff       	call   1270 <__cxa_finalize@plt>
    1587:	e8 64 ff ff ff       	call   14f0 <deregister_tm_clones>
    158c:	c6 05 95 3a 00 00 01 	movb   $0x1,0x3a95(%rip)        # 5028 <completed.0>
    1593:	5d                   	pop    %rbp
    1594:	c3                   	ret    
    1595:	0f 1f 00             	nopl   (%rax)
    1598:	c3                   	ret    
    1599:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)

00000000000015a0 <frame_dummy>:
    15a0:	f3 0f 1e fa          	endbr64 
    15a4:	e9 77 ff ff ff       	jmp    1520 <register_tm_clones>

00000000000015a9 <ocall_print_string>:
    15a9:	f3 0f 1e fa          	endbr64 
    15ad:	55                   	push   %rbp
    15ae:	48 89 e5             	mov    %rsp,%rbp
    15b1:	48 83 ec 10          	sub    $0x10,%rsp
    15b5:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    15b9:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    15bd:	48 89 c6             	mov    %rax,%rsi
    15c0:	48 8d 05 59 1a 00 00 	lea    0x1a59(%rip),%rax        # 3020 <_IO_stdin_used+0x20>
    15c7:	48 89 c7             	mov    %rax,%rdi
    15ca:	b8 00 00 00 00       	mov    $0x0,%eax
    15cf:	e8 5c fd ff ff       	call   1330 <printf@plt>
    15d4:	90                   	nop
    15d5:	c9                   	leave  
    15d6:	c3                   	ret    

00000000000015d7 <my_round>:
    15d7:	f3 0f 1e fa          	endbr64 
    15db:	55                   	push   %rbp
    15dc:	48 89 e5             	mov    %rsp,%rbp
    15df:	f3 0f 11 45 fc       	movss  %xmm0,-0x4(%rbp)
    15e4:	66 0f ef c0          	pxor   %xmm0,%xmm0
    15e8:	0f 2f 45 fc          	comiss -0x4(%rbp),%xmm0
    15ec:	76 1c                	jbe    160a <my_round+0x33>
    15ee:	66 0f ef c0          	pxor   %xmm0,%xmm0
    15f2:	f3 0f 5a 45 fc       	cvtss2sd -0x4(%rbp),%xmm0
    15f7:	f2 0f 10 0d b9 1d 00 	movsd  0x1db9(%rip),%xmm1        # 33b8 <result_exp+0x378>
    15fe:	00 
    15ff:	f2 0f 5c c1          	subsd  %xmm1,%xmm0
    1603:	f2 48 0f 2c c0       	cvttsd2si %xmm0,%rax
    1608:	eb 1a                	jmp    1624 <my_round+0x4d>
    160a:	66 0f ef c9          	pxor   %xmm1,%xmm1
    160e:	f3 0f 5a 4d fc       	cvtss2sd -0x4(%rbp),%xmm1
    1613:	f2 0f 10 05 9d 1d 00 	movsd  0x1d9d(%rip),%xmm0        # 33b8 <result_exp+0x378>
    161a:	00 
    161b:	f2 0f 58 c1          	addsd  %xmm1,%xmm0
    161f:	f2 48 0f 2c c0       	cvttsd2si %xmm0,%rax
    1624:	5d                   	pop    %rbp
    1625:	c3                   	ret    

0000000000001626 <fault_handler>:
    1626:	f3 0f 1e fa          	endbr64 
    162a:	55                   	push   %rbp
    162b:	48 89 e5             	mov    %rsp,%rbp
    162e:	89 7d fc             	mov    %edi,-0x4(%rbp)
    1631:	48 8d 05 f8 39 00 00 	lea    0x39f8(%rip),%rax        # 5030 <fault_fired>
    1638:	8b 00                	mov    (%rax),%eax
    163a:	48 8d 05 ef 39 00 00 	lea    0x39ef(%rip),%rax        # 5030 <fault_fired>
    1641:	8b 00                	mov    (%rax),%eax
    1643:	8d 50 01             	lea    0x1(%rax),%edx
    1646:	48 8d 05 e3 39 00 00 	lea    0x39e3(%rip),%rax        # 5030 <fault_fired>
    164d:	89 10                	mov    %edx,(%rax)
    164f:	90                   	nop
    1650:	5d                   	pop    %rbp
    1651:	c3                   	ret    

0000000000001652 <main>:
    1652:	f3 0f 1e fa          	endbr64 
    1656:	55                   	push   %rbp
    1657:	48 89 e5             	mov    %rsp,%rbp
    165a:	48 81 ec b0 08 00 00 	sub    $0x8b0,%rsp
    1661:	89 bd 5c f7 ff ff    	mov    %edi,-0x8a4(%rbp)
    1667:	48 89 b5 50 f7 ff ff 	mov    %rsi,-0x8b0(%rbp)
    166e:	c7 45 84 02 00 00 00 	movl   $0x2,-0x7c(%rbp)
    1675:	c7 45 ec ff ff ff ff 	movl   $0xffffffff,-0x14(%rbp)
    167c:	c7 45 e8 ff ff ff ff 	movl   $0xffffffff,-0x18(%rbp)
    1683:	ba b6 01 00 00       	mov    $0x1b6,%edx
    1688:	be 41 02 00 00       	mov    $0x241,%esi
    168d:	48 8d 05 ac 1a 00 00 	lea    0x1aac(%rip),%rax        # 3140 <result_exp+0x100>
    1694:	48 89 c7             	mov    %rax,%rdi
    1697:	b8 00 00 00 00       	mov    $0x0,%eax
    169c:	e8 6f fd ff ff       	call   1410 <open@plt>
    16a1:	89 45 e8             	mov    %eax,-0x18(%rbp)
    16a4:	83 7d e8 ff          	cmpl   $0xffffffff,-0x18(%rbp)
    16a8:	75 0a                	jne    16b4 <main+0x62>
    16aa:	bf 01 00 00 00       	mov    $0x1,%edi
    16af:	e8 bc fd ff ff       	call   1470 <exit@plt>
    16b4:	48 8d 85 00 ff ff ff 	lea    -0x100(%rbp),%rax
    16bb:	48 89 c6             	mov    %rax,%rsi
    16be:	b8 00 00 00 00       	mov    $0x0,%eax
    16c3:	ba 10 00 00 00       	mov    $0x10,%edx
    16c8:	48 89 f7             	mov    %rsi,%rdi
    16cb:	48 89 d1             	mov    %rdx,%rcx
    16ce:	f3 48 ab             	rep stos %rax,%es:(%rdi)
    16d1:	48 c7 45 e0 01 00 00 	movq   $0x1,-0x20(%rbp)
    16d8:	00 
    16d9:	48 81 7d e0 ff 03 00 	cmpq   $0x3ff,-0x20(%rbp)
    16e0:	00 
    16e1:	77 49                	ja     172c <main+0xda>
    16e3:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    16e7:	48 c1 e8 06          	shr    $0x6,%rax
    16eb:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
    16f2:	00 
    16f3:	48 8d 8d 00 ff ff ff 	lea    -0x100(%rbp),%rcx
    16fa:	48 01 ca             	add    %rcx,%rdx
    16fd:	48 8b 32             	mov    (%rdx),%rsi
    1700:	48 8b 55 e0          	mov    -0x20(%rbp),%rdx
    1704:	83 e2 3f             	and    $0x3f,%edx
    1707:	bf 01 00 00 00       	mov    $0x1,%edi
    170c:	89 d1                	mov    %edx,%ecx
    170e:	48 d3 e7             	shl    %cl,%rdi
    1711:	48 89 fa             	mov    %rdi,%rdx
    1714:	48 8d 0c c5 00 00 00 	lea    0x0(,%rax,8),%rcx
    171b:	00 
    171c:	48 8d 85 00 ff ff ff 	lea    -0x100(%rbp),%rax
    1723:	48 01 c8             	add    %rcx,%rax
    1726:	48 09 f2             	or     %rsi,%rdx
    1729:	48 89 10             	mov    %rdx,(%rax)
    172c:	48 8d 85 00 ff ff ff 	lea    -0x100(%rbp),%rax
    1733:	48 89 c2             	mov    %rax,%rdx
    1736:	be 80 00 00 00       	mov    $0x80,%esi
    173b:	bf 00 00 00 00       	mov    $0x0,%edi
    1740:	e8 6b fc ff ff       	call   13b0 <sched_setaffinity@plt>
    1745:	b8 00 00 00 00       	mov    $0x0,%eax
    174a:	e8 22 0d 00 00       	call   2471 <print_affinity>
    174f:	48 c7 85 00 fb ff ff 	movq   $0x0,-0x500(%rbp)
    1756:	00 00 00 00 
    175a:	48 c7 85 08 fb ff ff 	movq   $0x0,-0x4f8(%rbp)
    1761:	00 00 00 00 
    1765:	48 8d 95 10 fb ff ff 	lea    -0x4f0(%rbp),%rdx
    176c:	b8 00 00 00 00       	mov    $0x0,%eax
    1771:	b9 7e 00 00 00       	mov    $0x7e,%ecx
    1776:	48 89 d7             	mov    %rdx,%rdi
    1779:	f3 48 ab             	rep stos %rax,%es:(%rdi)
    177c:	c7 45 dc 00 00 00 00 	movl   $0x0,-0x24(%rbp)
    1783:	c7 45 d8 00 00 00 00 	movl   $0x0,-0x28(%rbp)
    178a:	c7 85 fc fa ff ff 00 	movl   $0x0,-0x504(%rbp)
    1791:	00 00 00 
    1794:	48 c7 85 f0 fa ff ff 	movq   $0x0,-0x510(%rbp)
    179b:	00 00 00 00 
    179f:	48 c7 85 f0 f9 ff ff 	movq   $0x0,-0x610(%rbp)
    17a6:	00 00 00 00 
    17aa:	48 c7 85 f8 f9 ff ff 	movq   $0x0,-0x608(%rbp)
    17b1:	00 00 00 00 
    17b5:	48 c7 85 00 fa ff ff 	movq   $0x0,-0x600(%rbp)
    17bc:	00 00 00 00 
    17c0:	48 c7 85 08 fa ff ff 	movq   $0x0,-0x5f8(%rbp)
    17c7:	00 00 00 00 
    17cb:	48 c7 85 10 fa ff ff 	movq   $0x0,-0x5f0(%rbp)
    17d2:	00 00 00 00 
    17d6:	48 c7 85 18 fa ff ff 	movq   $0x0,-0x5e8(%rbp)
    17dd:	00 00 00 00 
    17e1:	48 c7 85 20 fa ff ff 	movq   $0x0,-0x5e0(%rbp)
    17e8:	00 00 00 00 
    17ec:	48 c7 85 28 fa ff ff 	movq   $0x0,-0x5d8(%rbp)
    17f3:	00 00 00 00 
    17f7:	48 c7 85 30 fa ff ff 	movq   $0x0,-0x5d0(%rbp)
    17fe:	00 00 00 00 
    1802:	48 c7 85 38 fa ff ff 	movq   $0x0,-0x5c8(%rbp)
    1809:	00 00 00 00 
    180d:	48 c7 85 40 fa ff ff 	movq   $0x0,-0x5c0(%rbp)
    1814:	00 00 00 00 
    1818:	48 c7 85 48 fa ff ff 	movq   $0x0,-0x5b8(%rbp)
    181f:	00 00 00 00 
    1823:	48 c7 85 50 fa ff ff 	movq   $0x0,-0x5b0(%rbp)
    182a:	00 00 00 00 
    182e:	48 c7 85 58 fa ff ff 	movq   $0x0,-0x5a8(%rbp)
    1835:	00 00 00 00 
    1839:	48 c7 85 60 fa ff ff 	movq   $0x0,-0x5a0(%rbp)
    1840:	00 00 00 00 
    1844:	48 c7 85 68 fa ff ff 	movq   $0x0,-0x598(%rbp)
    184b:	00 00 00 00 
    184f:	48 c7 85 70 fa ff ff 	movq   $0x0,-0x590(%rbp)
    1856:	00 00 00 00 
    185a:	48 c7 85 78 fa ff ff 	movq   $0x0,-0x588(%rbp)
    1861:	00 00 00 00 
    1865:	48 c7 85 80 fa ff ff 	movq   $0x0,-0x580(%rbp)
    186c:	00 00 00 00 
    1870:	48 c7 85 88 fa ff ff 	movq   $0x0,-0x578(%rbp)
    1877:	00 00 00 00 
    187b:	48 c7 85 90 fa ff ff 	movq   $0x0,-0x570(%rbp)
    1882:	00 00 00 00 
    1886:	48 c7 85 98 fa ff ff 	movq   $0x0,-0x568(%rbp)
    188d:	00 00 00 00 
    1891:	48 c7 85 a0 fa ff ff 	movq   $0x0,-0x560(%rbp)
    1898:	00 00 00 00 
    189c:	48 c7 85 a8 fa ff ff 	movq   $0x0,-0x558(%rbp)
    18a3:	00 00 00 00 
    18a7:	48 c7 85 b0 fa ff ff 	movq   $0x0,-0x550(%rbp)
    18ae:	00 00 00 00 
    18b2:	48 c7 85 b8 fa ff ff 	movq   $0x0,-0x548(%rbp)
    18b9:	00 00 00 00 
    18bd:	48 c7 85 c0 fa ff ff 	movq   $0x0,-0x540(%rbp)
    18c4:	00 00 00 00 
    18c8:	48 c7 85 c8 fa ff ff 	movq   $0x0,-0x538(%rbp)
    18cf:	00 00 00 00 
    18d3:	48 c7 85 d0 fa ff ff 	movq   $0x0,-0x530(%rbp)
    18da:	00 00 00 00 
    18de:	48 c7 85 d8 fa ff ff 	movq   $0x0,-0x528(%rbp)
    18e5:	00 00 00 00 
    18e9:	48 c7 85 e0 fa ff ff 	movq   $0x0,-0x520(%rbp)
    18f0:	00 00 00 00 
    18f4:	48 c7 85 e8 fa ff ff 	movq   $0x0,-0x518(%rbp)
    18fb:	00 00 00 00 
    18ff:	48 8d 05 2a 37 00 00 	lea    0x372a(%rip),%rax        # 5030 <fault_fired>
    1906:	c7 00 00 00 00 00    	movl   $0x0,(%rax)
    190c:	48 8d 05 37 18 00 00 	lea    0x1837(%rip),%rax        # 314a <result_exp+0x10a>
    1913:	48 89 c7             	mov    %rax,%rdi
    1916:	b8 00 00 00 00       	mov    $0x0,%eax
    191b:	e8 10 fa ff ff       	call   1330 <printf@plt>
    1920:	48 8d 8d f0 fa ff ff 	lea    -0x510(%rbp),%rcx
    1927:	48 8d 95 fc fa ff ff 	lea    -0x504(%rbp),%rdx
    192e:	48 8d 85 00 fb ff ff 	lea    -0x500(%rbp),%rax
    1935:	41 b9 00 00 00 00    	mov    $0x0,%r9d
    193b:	49 89 c8             	mov    %rcx,%r8
    193e:	48 89 d1             	mov    %rdx,%rcx
    1941:	48 89 c2             	mov    %rax,%rdx
    1944:	be 01 00 00 00       	mov    $0x1,%esi
    1949:	48 8d 05 0f 18 00 00 	lea    0x180f(%rip),%rax        # 315f <result_exp+0x11f>
    1950:	48 89 c7             	mov    %rax,%rdi
    1953:	e8 48 fb ff ff       	call   14a0 <sgx_create_enclave@plt>
    1958:	89 c2                	mov    %eax,%edx
    195a:	48 8d 05 af 36 00 00 	lea    0x36af(%rip),%rax        # 5010 <sgx_ret>
    1961:	89 10                	mov    %edx,(%rax)
    1963:	48 8d 05 a6 36 00 00 	lea    0x36a6(%rip),%rax        # 5010 <sgx_ret>
    196a:	8b 00                	mov    (%rax),%eax
    196c:	85 c0                	test   %eax,%eax
    196e:	74 1f                	je     198f <main+0x33d>
    1970:	48 8d 05 99 36 00 00 	lea    0x3699(%rip),%rax        # 5010 <sgx_ret>
    1977:	8b 00                	mov    (%rax),%eax
    1979:	89 c6                	mov    %eax,%esi
    197b:	48 8d 05 ef 17 00 00 	lea    0x17ef(%rip),%rax        # 3171 <result_exp+0x131>
    1982:	48 89 c7             	mov    %rax,%rdi
    1985:	b8 00 00 00 00       	mov    $0x0,%eax
    198a:	e8 a1 f9 ff ff       	call   1330 <printf@plt>
    198f:	c7 45 d4 00 00 00 00 	movl   $0x0,-0x2c(%rbp)
    1996:	48 8b 85 50 f7 ff ff 	mov    -0x8b0(%rbp),%rax
    199d:	48 8b 00             	mov    (%rax),%rax
    19a0:	48 89 45 c8          	mov    %rax,-0x38(%rbp)
    19a4:	83 bd 5c f7 ff ff 09 	cmpl   $0x9,-0x8a4(%rbp)
    19ab:	74 25                	je     19d2 <main+0x380>
    19ad:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    19b1:	48 89 c6             	mov    %rax,%rsi
    19b4:	48 8d 05 d5 17 00 00 	lea    0x17d5(%rip),%rax        # 3190 <result_exp+0x150>
    19bb:	48 89 c7             	mov    %rax,%rdi
    19be:	b8 00 00 00 00       	mov    $0x0,%eax
    19c3:	e8 68 f9 ff ff       	call   1330 <printf@plt>
    19c8:	bf ff ff ff ff       	mov    $0xffffffff,%edi
    19cd:	e8 9e fa ff ff       	call   1470 <exit@plt>
    19d2:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    19d9:	48 8d 15 24 18 00 00 	lea    0x1824(%rip),%rdx        # 3204 <result_exp+0x1c4>
    19e0:	be 00 02 00 00       	mov    $0x200,%esi
    19e5:	48 89 c7             	mov    %rax,%rdi
    19e8:	b8 00 00 00 00       	mov    $0x0,%eax
    19ed:	e8 5e f9 ff ff       	call   1350 <snprintf@plt>
    19f2:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    19f9:	48 89 c7             	mov    %rax,%rdi
    19fc:	e8 ff f8 ff ff       	call   1300 <strlen@plt>
    1a01:	48 89 c2             	mov    %rax,%rdx
    1a04:	48 8d 8d f0 f7 ff ff 	lea    -0x810(%rbp),%rcx
    1a0b:	8b 45 e8             	mov    -0x18(%rbp),%eax
    1a0e:	48 89 ce             	mov    %rcx,%rsi
    1a11:	89 c7                	mov    %eax,%edi
    1a13:	e8 b8 f8 ff ff       	call   12d0 <write@plt>
    1a18:	c6 85 ef f7 ff ff 00 	movb   $0x0,-0x811(%rbp)
    1a1f:	48 8b 85 f0 fa ff ff 	mov    -0x510(%rbp),%rax
    1a26:	48 8d 95 ef f7 ff ff 	lea    -0x811(%rbp),%rdx
    1a2d:	48 89 d6             	mov    %rdx,%rsi
    1a30:	48 89 c7             	mov    %rax,%rdi
    1a33:	e8 73 08 00 00       	call   22ab <rsa_init_ecall>
    1a38:	89 c2                	mov    %eax,%edx
    1a3a:	48 8d 05 cf 35 00 00 	lea    0x35cf(%rip),%rax        # 5010 <sgx_ret>
    1a41:	89 10                	mov    %edx,(%rax)
    1a43:	48 8d 05 c6 35 00 00 	lea    0x35c6(%rip),%rax        # 5010 <sgx_ret>
    1a4a:	8b 00                	mov    (%rax),%eax
    1a4c:	85 c0                	test   %eax,%eax
    1a4e:	74 51                	je     1aa1 <main+0x44f>
    1a50:	48 8d 05 b9 35 00 00 	lea    0x35b9(%rip),%rax        # 5010 <sgx_ret>
    1a57:	8b 10                	mov    (%rax),%edx
    1a59:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    1a60:	89 d1                	mov    %edx,%ecx
    1a62:	48 8d 15 08 17 00 00 	lea    0x1708(%rip),%rdx        # 3171 <result_exp+0x131>
    1a69:	be 00 02 00 00       	mov    $0x200,%esi
    1a6e:	48 89 c7             	mov    %rax,%rdi
    1a71:	b8 00 00 00 00       	mov    $0x0,%eax
    1a76:	e8 d5 f8 ff ff       	call   1350 <snprintf@plt>
    1a7b:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    1a82:	48 89 c7             	mov    %rax,%rdi
    1a85:	e8 76 f8 ff ff       	call   1300 <strlen@plt>
    1a8a:	48 89 c2             	mov    %rax,%rdx
    1a8d:	48 8d 8d f0 f7 ff ff 	lea    -0x810(%rbp),%rcx
    1a94:	8b 45 e8             	mov    -0x18(%rbp),%eax
    1a97:	48 89 ce             	mov    %rcx,%rsi
    1a9a:	89 c7                	mov    %eax,%edi
    1a9c:	e8 2f f8 ff ff       	call   12d0 <write@plt>
    1aa1:	0f b6 85 ef f7 ff ff 	movzbl -0x811(%rbp),%eax
    1aa8:	3c 01                	cmp    $0x1,%al
    1aaa:	74 4b                	je     1af7 <main+0x4a5>
    1aac:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    1ab3:	48 8d 15 57 17 00 00 	lea    0x1757(%rip),%rdx        # 3211 <result_exp+0x1d1>
    1aba:	be 00 02 00 00       	mov    $0x200,%esi
    1abf:	48 89 c7             	mov    %rax,%rdi
    1ac2:	b8 00 00 00 00       	mov    $0x0,%eax
    1ac7:	e8 84 f8 ff ff       	call   1350 <snprintf@plt>
    1acc:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    1ad3:	48 89 c7             	mov    %rax,%rdi
    1ad6:	e8 25 f8 ff ff       	call   1300 <strlen@plt>
    1adb:	48 89 c2             	mov    %rax,%rdx
    1ade:	48 8d 8d f0 f7 ff ff 	lea    -0x810(%rbp),%rcx
    1ae5:	8b 45 e8             	mov    -0x18(%rbp),%eax
    1ae8:	48 89 ce             	mov    %rcx,%rsi
    1aeb:	89 c7                	mov    %eax,%edi
    1aed:	e8 de f7 ff ff       	call   12d0 <write@plt>
    1af2:	e9 5a 06 00 00       	jmp    2151 <main+0xaff>
    1af7:	48 8b 85 50 f7 ff ff 	mov    -0x8b0(%rbp),%rax
    1afe:	48 83 c0 08          	add    $0x8,%rax
    1b02:	48 8b 00             	mov    (%rax),%rax
    1b05:	48 89 c7             	mov    %rax,%rdi
    1b08:	e8 43 f9 ff ff       	call   1450 <atoi@plt>
    1b0d:	89 45 c4             	mov    %eax,-0x3c(%rbp)
    1b10:	48 8b 85 50 f7 ff ff 	mov    -0x8b0(%rbp),%rax
    1b17:	48 83 c0 10          	add    $0x10,%rax
    1b1b:	48 8b 00             	mov    (%rax),%rax
    1b1e:	48 89 c7             	mov    %rax,%rdi
    1b21:	e8 a4 0a 00 00       	call   25ca <set_freq>
    1b26:	48 8b 85 50 f7 ff ff 	mov    -0x8b0(%rbp),%rax
    1b2d:	48 83 c0 10          	add    $0x10,%rax
    1b31:	48 8b 00             	mov    (%rax),%rax
    1b34:	48 8d 95 e0 f7 ff ff 	lea    -0x820(%rbp),%rdx
    1b3b:	48 89 d6             	mov    %rdx,%rsi
    1b3e:	48 89 c7             	mov    %rax,%rdi
    1b41:	e8 5a f7 ff ff       	call   12a0 <strtod@plt>
    1b46:	66 48 0f 7e c0       	movq   %xmm0,%rax
    1b4b:	48 89 45 b8          	mov    %rax,-0x48(%rbp)
    1b4f:	48 8b 85 50 f7 ff ff 	mov    -0x8b0(%rbp),%rax
    1b56:	48 83 c0 18          	add    $0x18,%rax
    1b5a:	48 8b 00             	mov    (%rax),%rax
    1b5d:	48 89 c7             	mov    %rax,%rdi
    1b60:	e8 4b f7 ff ff       	call   12b0 <atof@plt>
    1b65:	66 48 0f 7e c0       	movq   %xmm0,%rax
    1b6a:	48 89 45 b0          	mov    %rax,-0x50(%rbp)
    1b6e:	48 8b 85 50 f7 ff ff 	mov    -0x8b0(%rbp),%rax
    1b75:	48 83 c0 20          	add    $0x20,%rax
    1b79:	48 8b 00             	mov    (%rax),%rax
    1b7c:	48 89 c7             	mov    %rax,%rdi
    1b7f:	e8 2c f7 ff ff       	call   12b0 <atof@plt>
    1b84:	66 48 0f 7e c0       	movq   %xmm0,%rax
    1b89:	48 89 45 a8          	mov    %rax,-0x58(%rbp)
    1b8d:	48 8b 85 50 f7 ff ff 	mov    -0x8b0(%rbp),%rax
    1b94:	48 83 c0 28          	add    $0x28,%rax
    1b98:	48 8b 00             	mov    (%rax),%rax
    1b9b:	48 89 c7             	mov    %rax,%rdi
    1b9e:	e8 0d f7 ff ff       	call   12b0 <atof@plt>
    1ba3:	66 48 0f 7e c0       	movq   %xmm0,%rax
    1ba8:	48 89 45 a0          	mov    %rax,-0x60(%rbp)
    1bac:	48 8b 85 50 f7 ff ff 	mov    -0x8b0(%rbp),%rax
    1bb3:	48 83 c0 30          	add    $0x30,%rax
    1bb7:	48 8b 00             	mov    (%rax),%rax
    1bba:	48 89 c7             	mov    %rax,%rdi
    1bbd:	e8 ee f6 ff ff       	call   12b0 <atof@plt>
    1bc2:	66 48 0f 7e c0       	movq   %xmm0,%rax
    1bc7:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    1bcb:	48 8b 85 50 f7 ff ff 	mov    -0x8b0(%rbp),%rax
    1bd2:	48 83 c0 38          	add    $0x38,%rax
    1bd6:	48 8b 00             	mov    (%rax),%rax
    1bd9:	48 89 c7             	mov    %rax,%rdi
    1bdc:	e8 cf f6 ff ff       	call   12b0 <atof@plt>
    1be1:	66 48 0f 7e c0       	movq   %xmm0,%rax
    1be6:	48 89 45 98          	mov    %rax,-0x68(%rbp)
    1bea:	48 8b 85 50 f7 ff ff 	mov    -0x8b0(%rbp),%rax
    1bf1:	48 83 c0 40          	add    $0x40,%rax
    1bf5:	48 8b 00             	mov    (%rax),%rax
    1bf8:	48 89 c7             	mov    %rax,%rdi
    1bfb:	e8 b0 f6 ff ff       	call   12b0 <atof@plt>
    1c00:	66 48 0f 7e c0       	movq   %xmm0,%rax
    1c05:	48 89 45 90          	mov    %rax,-0x70(%rbp)
    1c09:	b8 00 00 00 00       	mov    $0x0,%eax
    1c0e:	e8 a8 0d 00 00       	call   29bb <close_BNC_Arb>
    1c13:	66 0f ef ed          	pxor   %xmm5,%xmm5
    1c17:	f2 0f 5a 6d b0       	cvtsd2ss -0x50(%rbp),%xmm5
    1c1c:	66 0f 7e e8          	movd   %xmm5,%eax
    1c20:	66 0f ef e4          	pxor   %xmm4,%xmm4
    1c24:	66 0f ef db          	pxor   %xmm3,%xmm3
    1c28:	66 0f ef d2          	pxor   %xmm2,%xmm2
    1c2c:	66 0f ef c9          	pxor   %xmm1,%xmm1
    1c30:	66 0f 6e c0          	movd   %eax,%xmm0
    1c34:	be 01 00 00 00       	mov    $0x1,%esi
    1c39:	bf 01 00 00 00       	mov    $0x1,%edi
    1c3e:	e8 47 0b 00 00       	call   278a <configure_glitch_with_delay>
    1c43:	b8 00 00 00 00       	mov    $0x0,%eax
    1c48:	e8 32 0d 00 00       	call   297f <start_DCpower_type1>
    1c4d:	48 c7 85 d8 f7 ff ff 	movq   $0x0,-0x828(%rbp)
    1c54:	00 00 00 00 
    1c58:	48 c7 85 b0 f7 ff ff 	movq   $0x0,-0x850(%rbp)
    1c5f:	00 00 00 00 
    1c63:	48 c7 85 b8 f7 ff ff 	movq   $0x0,-0x848(%rbp)
    1c6a:	00 00 00 00 
    1c6e:	48 c7 85 c0 f7 ff ff 	movq   $0x0,-0x840(%rbp)
    1c75:	00 00 00 00 
    1c79:	48 c7 85 c8 f7 ff ff 	movq   $0x0,-0x838(%rbp)
    1c80:	00 00 00 00 
    1c84:	48 c7 85 d0 f7 ff ff 	movq   $0x0,-0x830(%rbp)
    1c8b:	00 00 00 00 
    1c8f:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%rbp)
    1c96:	e9 1c 04 00 00       	jmp    20b7 <main+0xa65>
    1c9b:	f2 0f 10 4d f8       	movsd  -0x8(%rbp),%xmm1
    1ca0:	f2 0f 10 05 18 17 00 	movsd  0x1718(%rip),%xmm0        # 33c0 <result_exp+0x380>
    1ca7:	00 
    1ca8:	f2 0f 58 c1          	addsd  %xmm1,%xmm0
    1cac:	f2 0f 11 45 f8       	movsd  %xmm0,-0x8(%rbp)
    1cb1:	f2 0f 10 5d 90       	movsd  -0x70(%rbp),%xmm3
    1cb6:	f2 0f 10 55 98       	movsd  -0x68(%rbp),%xmm2
    1cbb:	f2 0f 10 4d f8       	movsd  -0x8(%rbp),%xmm1
    1cc0:	f2 0f 10 45 a0       	movsd  -0x60(%rbp),%xmm0
    1cc5:	48 8b 55 a8          	mov    -0x58(%rbp),%rdx
    1cc9:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    1cd0:	66 0f 28 e3          	movapd %xmm3,%xmm4
    1cd4:	66 0f 28 da          	movapd %xmm2,%xmm3
    1cd8:	66 0f 28 d1          	movapd %xmm1,%xmm2
    1cdc:	66 0f 28 c8          	movapd %xmm0,%xmm1
    1ce0:	66 48 0f 6e c2       	movq   %rdx,%xmm0
    1ce5:	48 8d 15 44 15 00 00 	lea    0x1544(%rip),%rdx        # 3230 <result_exp+0x1f0>
    1cec:	be 00 02 00 00       	mov    $0x200,%esi
    1cf1:	48 89 c7             	mov    %rax,%rdi
    1cf4:	b8 05 00 00 00       	mov    $0x5,%eax
    1cf9:	e8 52 f6 ff ff       	call   1350 <snprintf@plt>
    1cfe:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    1d05:	48 89 c7             	mov    %rax,%rdi
    1d08:	e8 f3 f5 ff ff       	call   1300 <strlen@plt>
    1d0d:	48 89 c2             	mov    %rax,%rdx
    1d10:	48 8d 8d f0 f7 ff ff 	lea    -0x810(%rbp),%rcx
    1d17:	8b 45 e8             	mov    -0x18(%rbp),%eax
    1d1a:	48 89 ce             	mov    %rcx,%rsi
    1d1d:	89 c7                	mov    %eax,%edi
    1d1f:	e8 ac f5 ff ff       	call   12d0 <write@plt>
    1d24:	66 0f ef db          	pxor   %xmm3,%xmm3
    1d28:	f2 0f 5a 5d 90       	cvtsd2ss -0x70(%rbp),%xmm3
    1d2d:	66 0f ef d2          	pxor   %xmm2,%xmm2
    1d31:	f2 0f 5a 55 98       	cvtsd2ss -0x68(%rbp),%xmm2
    1d36:	66 0f ef c9          	pxor   %xmm1,%xmm1
    1d3a:	f2 0f 5a 4d f8       	cvtsd2ss -0x8(%rbp),%xmm1
    1d3f:	66 0f ef c0          	pxor   %xmm0,%xmm0
    1d43:	f2 0f 5a 45 a0       	cvtsd2ss -0x60(%rbp),%xmm0
    1d48:	66 0f ef f6          	pxor   %xmm6,%xmm6
    1d4c:	f2 0f 5a 75 a8       	cvtsd2ss -0x58(%rbp),%xmm6
    1d51:	66 0f 7e f0          	movd   %xmm6,%eax
    1d55:	0f 28 e3             	movaps %xmm3,%xmm4
    1d58:	0f 28 da             	movaps %xmm2,%xmm3
    1d5b:	0f 28 d1             	movaps %xmm1,%xmm2
    1d5e:	0f 28 c8             	movaps %xmm0,%xmm1
    1d61:	66 0f 6e c0          	movd   %eax,%xmm0
    1d65:	be 01 00 00 00       	mov    $0x1,%esi
    1d6a:	bf 01 00 00 00       	mov    $0x1,%edi
    1d6f:	e8 16 0a 00 00       	call   278a <configure_glitch_with_delay>
    1d74:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%rbp)
    1d7b:	e9 13 03 00 00       	jmp    2093 <main+0xa41>
    1d80:	be 02 01 00 00       	mov    $0x102,%esi
    1d85:	48 8d 05 f2 14 00 00 	lea    0x14f2(%rip),%rax        # 327e <result_exp+0x23e>
    1d8c:	48 89 c7             	mov    %rax,%rdi
    1d8f:	b8 00 00 00 00       	mov    $0x0,%eax
    1d94:	e8 77 f6 ff ff       	call   1410 <open@plt>
    1d99:	89 45 ec             	mov    %eax,-0x14(%rbp)
    1d9c:	83 7d ec ff          	cmpl   $0xffffffff,-0x14(%rbp)
    1da0:	75 50                	jne    1df2 <main+0x7a0>
    1da2:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    1da9:	48 8d 15 e0 14 00 00 	lea    0x14e0(%rip),%rdx        # 3290 <result_exp+0x250>
    1db0:	be 00 02 00 00       	mov    $0x200,%esi
    1db5:	48 89 c7             	mov    %rax,%rdi
    1db8:	b8 00 00 00 00       	mov    $0x0,%eax
    1dbd:	e8 8e f5 ff ff       	call   1350 <snprintf@plt>
    1dc2:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    1dc9:	48 89 c7             	mov    %rax,%rdi
    1dcc:	e8 2f f5 ff ff       	call   1300 <strlen@plt>
    1dd1:	48 89 c2             	mov    %rax,%rdx
    1dd4:	48 8d 8d f0 f7 ff ff 	lea    -0x810(%rbp),%rcx
    1ddb:	8b 45 e8             	mov    -0x18(%rbp),%eax
    1dde:	48 89 ce             	mov    %rcx,%rsi
    1de1:	89 c7                	mov    %eax,%edi
    1de3:	e8 e8 f4 ff ff       	call   12d0 <write@plt>
    1de8:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    1ded:	e9 22 04 00 00       	jmp    2214 <main+0xbc2>
    1df2:	48 8d 55 84          	lea    -0x7c(%rbp),%rdx
    1df6:	8b 45 ec             	mov    -0x14(%rbp),%eax
    1df9:	be 17 54 00 00       	mov    $0x5417,%esi
    1dfe:	89 c7                	mov    %eax,%edi
    1e00:	b8 00 00 00 00       	mov    $0x0,%eax
    1e05:	e8 86 f5 ff ff       	call   1390 <ioctl@plt>
    1e0a:	f2 0f 10 45 b8       	movsd  -0x48(%rbp),%xmm0
    1e0f:	48 8b 05 b2 15 00 00 	mov    0x15b2(%rip),%rax        # 33c8 <result_exp+0x388>
    1e16:	66 0f 28 c8          	movapd %xmm0,%xmm1
    1e1a:	66 48 0f 6e c0       	movq   %rax,%xmm0
    1e1f:	e8 63 08 00 00       	call   2687 <delay_us>
    1e24:	48 8d 85 80 f7 ff ff 	lea    -0x880(%rbp),%rax
    1e2b:	48 89 c6             	mov    %rax,%rsi
    1e2e:	bf 01 00 00 00       	mov    $0x1,%edi
    1e33:	e8 88 f4 ff ff       	call   12c0 <clock_gettime@plt>
    1e38:	48 8b 85 f0 fa ff ff 	mov    -0x510(%rbp),%rax
    1e3f:	48 8d 95 f0 f9 ff ff 	lea    -0x610(%rbp),%rdx
    1e46:	48 8d b5 ef f7 ff ff 	lea    -0x811(%rbp),%rsi
    1e4d:	b9 e8 03 00 00       	mov    $0x3e8,%ecx
    1e52:	48 89 c7             	mov    %rax,%rdi
    1e55:	e8 ea 03 00 00       	call   2244 <rsa_dec_ecall>
    1e5a:	89 c2                	mov    %eax,%edx
    1e5c:	48 8d 05 ad 31 00 00 	lea    0x31ad(%rip),%rax        # 5010 <sgx_ret>
    1e63:	89 10                	mov    %edx,(%rax)
    1e65:	48 8d 85 70 f7 ff ff 	lea    -0x890(%rbp),%rax
    1e6c:	48 89 c6             	mov    %rax,%rsi
    1e6f:	bf 01 00 00 00       	mov    $0x1,%edi
    1e74:	e8 47 f4 ff ff       	call   12c0 <clock_gettime@plt>
    1e79:	48 8d 05 90 31 00 00 	lea    0x3190(%rip),%rax        # 5010 <sgx_ret>
    1e80:	8b 00                	mov    (%rax),%eax
    1e82:	85 c0                	test   %eax,%eax
    1e84:	74 5b                	je     1ee1 <main+0x88f>
    1e86:	48 8d 05 83 31 00 00 	lea    0x3183(%rip),%rax        # 5010 <sgx_ret>
    1e8d:	8b 10                	mov    (%rax),%edx
    1e8f:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    1e96:	89 d1                	mov    %edx,%ecx
    1e98:	48 8d 15 21 14 00 00 	lea    0x1421(%rip),%rdx        # 32c0 <result_exp+0x280>
    1e9f:	be 00 02 00 00       	mov    $0x200,%esi
    1ea4:	48 89 c7             	mov    %rax,%rdi
    1ea7:	b8 00 00 00 00       	mov    $0x0,%eax
    1eac:	e8 9f f4 ff ff       	call   1350 <snprintf@plt>
    1eb1:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    1eb8:	48 89 c7             	mov    %rax,%rdi
    1ebb:	e8 40 f4 ff ff       	call   1300 <strlen@plt>
    1ec0:	48 89 c2             	mov    %rax,%rdx
    1ec3:	48 8d 8d f0 f7 ff ff 	lea    -0x810(%rbp),%rcx
    1eca:	8b 45 e8             	mov    -0x18(%rbp),%eax
    1ecd:	48 89 ce             	mov    %rcx,%rsi
    1ed0:	89 c7                	mov    %eax,%edi
    1ed2:	e8 f9 f3 ff ff       	call   12d0 <write@plt>
    1ed7:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    1edc:	e9 33 03 00 00       	jmp    2214 <main+0xbc2>
    1ee1:	8b 45 ec             	mov    -0x14(%rbp),%eax
    1ee4:	89 c7                	mov    %eax,%edi
    1ee6:	e8 b5 f4 ff ff       	call   13a0 <close@plt>
    1eeb:	48 8d 85 f0 f9 ff ff 	lea    -0x610(%rbp),%rax
    1ef2:	ba 00 01 00 00       	mov    $0x100,%edx
    1ef7:	48 8d 0d 42 11 00 00 	lea    0x1142(%rip),%rcx        # 3040 <result_exp>
    1efe:	48 89 ce             	mov    %rcx,%rsi
    1f01:	48 89 c7             	mov    %rax,%rdi
    1f04:	e8 b7 f4 ff ff       	call   13c0 <memcmp@plt>
    1f09:	85 c0                	test   %eax,%eax
    1f0b:	0f 84 0e 01 00 00    	je     201f <main+0x9cd>
    1f11:	8b 55 f0             	mov    -0x10(%rbp),%edx
    1f14:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    1f1b:	89 d1                	mov    %edx,%ecx
    1f1d:	48 8d 15 c0 13 00 00 	lea    0x13c0(%rip),%rdx        # 32e4 <result_exp+0x2a4>
    1f24:	be 00 02 00 00       	mov    $0x200,%esi
    1f29:	48 89 c7             	mov    %rax,%rdi
    1f2c:	b8 00 00 00 00       	mov    $0x0,%eax
    1f31:	e8 1a f4 ff ff       	call   1350 <snprintf@plt>
    1f36:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    1f3d:	48 89 c7             	mov    %rax,%rdi
    1f40:	e8 bb f3 ff ff       	call   1300 <strlen@plt>
    1f45:	48 89 c2             	mov    %rax,%rdx
    1f48:	48 8d 8d f0 f7 ff ff 	lea    -0x810(%rbp),%rcx
    1f4f:	8b 45 e8             	mov    -0x18(%rbp),%eax
    1f52:	48 89 ce             	mov    %rcx,%rsi
    1f55:	89 c7                	mov    %eax,%edi
    1f57:	e8 74 f3 ff ff       	call   12d0 <write@plt>
    1f5c:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    1f63:	48 8d 15 96 13 00 00 	lea    0x1396(%rip),%rdx        # 3300 <result_exp+0x2c0>
    1f6a:	be 00 02 00 00       	mov    $0x200,%esi
    1f6f:	48 89 c7             	mov    %rax,%rdi
    1f72:	b8 00 00 00 00       	mov    $0x0,%eax
    1f77:	e8 d4 f3 ff ff       	call   1350 <snprintf@plt>
    1f7c:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    1f83:	48 89 c7             	mov    %rax,%rdi
    1f86:	e8 75 f3 ff ff       	call   1300 <strlen@plt>
    1f8b:	48 89 c2             	mov    %rax,%rdx
    1f8e:	48 8d 8d f0 f7 ff ff 	lea    -0x810(%rbp),%rcx
    1f95:	8b 45 e8             	mov    -0x18(%rbp),%eax
    1f98:	48 89 ce             	mov    %rcx,%rsi
    1f9b:	89 c7                	mov    %eax,%edi
    1f9d:	e8 2e f3 ff ff       	call   12d0 <write@plt>
    1fa2:	8b 45 e8             	mov    -0x18(%rbp),%eax
    1fa5:	89 c7                	mov    %eax,%edi
    1fa7:	e8 c1 03 00 00       	call   236d <log_sensors_output>
    1fac:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%rbp)
    1fb3:	eb 5c                	jmp    2011 <main+0x9bf>
    1fb5:	8b 45 f4             	mov    -0xc(%rbp),%eax
    1fb8:	48 98                	cltq   
    1fba:	0f b6 84 05 f0 f9 ff 	movzbl -0x610(%rbp,%rax,1),%eax
    1fc1:	ff 
    1fc2:	0f b6 d0             	movzbl %al,%edx
    1fc5:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    1fcc:	89 d1                	mov    %edx,%ecx
    1fce:	48 8d 15 4c 13 00 00 	lea    0x134c(%rip),%rdx        # 3321 <result_exp+0x2e1>
    1fd5:	be 00 02 00 00       	mov    $0x200,%esi
    1fda:	48 89 c7             	mov    %rax,%rdi
    1fdd:	b8 00 00 00 00       	mov    $0x0,%eax
    1fe2:	e8 69 f3 ff ff       	call   1350 <snprintf@plt>
    1fe7:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    1fee:	48 89 c7             	mov    %rax,%rdi
    1ff1:	e8 0a f3 ff ff       	call   1300 <strlen@plt>
    1ff6:	48 89 c2             	mov    %rax,%rdx
    1ff9:	48 8d 8d f0 f7 ff ff 	lea    -0x810(%rbp),%rcx
    2000:	8b 45 e8             	mov    -0x18(%rbp),%eax
    2003:	48 89 ce             	mov    %rcx,%rsi
    2006:	89 c7                	mov    %eax,%edi
    2008:	e8 c3 f2 ff ff       	call   12d0 <write@plt>
    200d:	83 45 f4 01          	addl   $0x1,-0xc(%rbp)
    2011:	81 7d f4 ff 00 00 00 	cmpl   $0xff,-0xc(%rbp)
    2018:	7e 9b                	jle    1fb5 <main+0x963>
    201a:	e9 80 00 00 00       	jmp    209f <main+0xa4d>
    201f:	bf 20 4e 00 00       	mov    $0x4e20,%edi
    2024:	e8 87 f4 ff ff       	call   14b0 <usleep@plt>
    2029:	48 8b 85 70 f7 ff ff 	mov    -0x890(%rbp),%rax
    2030:	48 8b 95 80 f7 ff ff 	mov    -0x880(%rbp),%rdx
    2037:	48 29 d0             	sub    %rdx,%rax
    203a:	66 0f ef c9          	pxor   %xmm1,%xmm1
    203e:	f2 48 0f 2a c8       	cvtsi2sd %rax,%xmm1
    2043:	48 8b 85 78 f7 ff ff 	mov    -0x888(%rbp),%rax
    204a:	48 8b 95 88 f7 ff ff 	mov    -0x878(%rbp),%rdx
    2051:	48 29 d0             	sub    %rdx,%rax
    2054:	66 0f ef c0          	pxor   %xmm0,%xmm0
    2058:	f2 48 0f 2a c0       	cvtsi2sd %rax,%xmm0
    205d:	f2 0f 10 15 6b 13 00 	movsd  0x136b(%rip),%xmm2        # 33d0 <result_exp+0x390>
    2064:	00 
    2065:	f2 0f 5e c2          	divsd  %xmm2,%xmm0
    2069:	f2 0f 58 c1          	addsd  %xmm1,%xmm0
    206d:	f2 0f 11 45 88       	movsd  %xmm0,-0x78(%rbp)
    2072:	48 8b 45 88          	mov    -0x78(%rbp),%rax
    2076:	66 48 0f 6e c0       	movq   %rax,%xmm0
    207b:	48 8d 05 ae 12 00 00 	lea    0x12ae(%rip),%rax        # 3330 <result_exp+0x2f0>
    2082:	48 89 c7             	mov    %rax,%rdi
    2085:	b8 01 00 00 00       	mov    $0x1,%eax
    208a:	e8 a1 f2 ff ff       	call   1330 <printf@plt>
    208f:	83 45 f0 01          	addl   $0x1,-0x10(%rbp)
    2093:	8b 45 f0             	mov    -0x10(%rbp),%eax
    2096:	3b 45 c4             	cmp    -0x3c(%rbp),%eax
    2099:	0f 82 e1 fc ff ff    	jb     1d80 <main+0x72e>
    209f:	bf 40 42 0f 00       	mov    $0xf4240,%edi
    20a4:	e8 07 f4 ff ff       	call   14b0 <usleep@plt>
    20a9:	b8 00 00 00 00       	mov    $0x0,%eax
    20ae:	e8 08 09 00 00       	call   29bb <close_BNC_Arb>
    20b3:	83 45 f4 01          	addl   $0x1,-0xc(%rbp)
    20b7:	81 7d f4 c7 00 00 00 	cmpl   $0xc7,-0xc(%rbp)
    20be:	0f 8e d7 fb ff ff    	jle    1c9b <main+0x649>
    20c4:	48 8b 85 f0 fa ff ff 	mov    -0x510(%rbp),%rax
    20cb:	48 8d 95 ef f7 ff ff 	lea    -0x811(%rbp),%rdx
    20d2:	48 89 d6             	mov    %rdx,%rsi
    20d5:	48 89 c7             	mov    %rax,%rdi
    20d8:	e8 20 02 00 00       	call   22fd <rsa_clean_ecall>
    20dd:	89 c2                	mov    %eax,%edx
    20df:	48 8d 05 2a 2f 00 00 	lea    0x2f2a(%rip),%rax        # 5010 <sgx_ret>
    20e6:	89 10                	mov    %edx,(%rax)
    20e8:	48 8d 05 21 2f 00 00 	lea    0x2f21(%rip),%rax        # 5010 <sgx_ret>
    20ef:	8b 00                	mov    (%rax),%eax
    20f1:	85 c0                	test   %eax,%eax
    20f3:	74 5b                	je     2150 <main+0xafe>
    20f5:	48 8d 05 14 2f 00 00 	lea    0x2f14(%rip),%rax        # 5010 <sgx_ret>
    20fc:	8b 10                	mov    (%rax),%edx
    20fe:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    2105:	89 d1                	mov    %edx,%ecx
    2107:	48 8d 15 4a 12 00 00 	lea    0x124a(%rip),%rdx        # 3358 <result_exp+0x318>
    210e:	be 00 02 00 00       	mov    $0x200,%esi
    2113:	48 89 c7             	mov    %rax,%rdi
    2116:	b8 00 00 00 00       	mov    $0x0,%eax
    211b:	e8 30 f2 ff ff       	call   1350 <snprintf@plt>
    2120:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    2127:	48 89 c7             	mov    %rax,%rdi
    212a:	e8 d1 f1 ff ff       	call   1300 <strlen@plt>
    212f:	48 89 c2             	mov    %rax,%rdx
    2132:	48 8d 8d f0 f7 ff ff 	lea    -0x810(%rbp),%rcx
    2139:	8b 45 e8             	mov    -0x18(%rbp),%eax
    213c:	48 89 ce             	mov    %rcx,%rsi
    213f:	89 c7                	mov    %eax,%edi
    2141:	e8 8a f1 ff ff       	call   12d0 <write@plt>
    2146:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
    214b:	e9 c4 00 00 00       	jmp    2214 <main+0xbc2>
    2150:	90                   	nop
    2151:	48 8b 85 f0 fa ff ff 	mov    -0x510(%rbp),%rax
    2158:	48 89 c7             	mov    %rax,%rdi
    215b:	e8 80 f1 ff ff       	call   12e0 <sgx_destroy_enclave@plt>
    2160:	89 c2                	mov    %eax,%edx
    2162:	48 8d 05 a7 2e 00 00 	lea    0x2ea7(%rip),%rax        # 5010 <sgx_ret>
    2169:	89 10                	mov    %edx,(%rax)
    216b:	48 8d 05 9e 2e 00 00 	lea    0x2e9e(%rip),%rax        # 5010 <sgx_ret>
    2172:	8b 00                	mov    (%rax),%eax
    2174:	85 c0                	test   %eax,%eax
    2176:	74 51                	je     21c9 <main+0xb77>
    2178:	48 8d 05 91 2e 00 00 	lea    0x2e91(%rip),%rax        # 5010 <sgx_ret>
    217f:	8b 10                	mov    (%rax),%edx
    2181:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    2188:	89 d1                	mov    %edx,%ecx
    218a:	48 8d 15 ef 11 00 00 	lea    0x11ef(%rip),%rdx        # 3380 <result_exp+0x340>
    2191:	be 04 00 00 00       	mov    $0x4,%esi
    2196:	48 89 c7             	mov    %rax,%rdi
    2199:	b8 00 00 00 00       	mov    $0x0,%eax
    219e:	e8 ad f1 ff ff       	call   1350 <snprintf@plt>
    21a3:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    21aa:	48 89 c7             	mov    %rax,%rdi
    21ad:	e8 4e f1 ff ff       	call   1300 <strlen@plt>
    21b2:	48 89 c2             	mov    %rax,%rdx
    21b5:	48 8d 8d f0 f7 ff ff 	lea    -0x810(%rbp),%rcx
    21bc:	8b 45 e8             	mov    -0x18(%rbp),%eax
    21bf:	48 89 ce             	mov    %rcx,%rsi
    21c2:	89 c7                	mov    %eax,%edi
    21c4:	e8 07 f1 ff ff       	call   12d0 <write@plt>
    21c9:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    21d0:	48 8d 15 d2 11 00 00 	lea    0x11d2(%rip),%rdx        # 33a9 <result_exp+0x369>
    21d7:	be 00 02 00 00       	mov    $0x200,%esi
    21dc:	48 89 c7             	mov    %rax,%rdi
    21df:	b8 00 00 00 00       	mov    $0x0,%eax
    21e4:	e8 67 f1 ff ff       	call   1350 <snprintf@plt>
    21e9:	48 8d 85 f0 f7 ff ff 	lea    -0x810(%rbp),%rax
    21f0:	48 89 c7             	mov    %rax,%rdi
    21f3:	e8 08 f1 ff ff       	call   1300 <strlen@plt>
    21f8:	48 89 c2             	mov    %rax,%rdx
    21fb:	48 8d 8d f0 f7 ff ff 	lea    -0x810(%rbp),%rcx
    2202:	8b 45 e8             	mov    -0x18(%rbp),%eax
    2205:	48 89 ce             	mov    %rcx,%rsi
    2208:	89 c7                	mov    %eax,%edi
    220a:	e8 c1 f0 ff ff       	call   12d0 <write@plt>
    220f:	b8 00 00 00 00       	mov    $0x0,%eax
    2214:	c9                   	leave  
    2215:	c3                   	ret    

0000000000002216 <encl_ocall_print_string>:
    2216:	f3 0f 1e fa          	endbr64 
    221a:	55                   	push   %rbp
    221b:	48 89 e5             	mov    %rsp,%rbp
    221e:	48 83 ec 20          	sub    $0x20,%rsp
    2222:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    2226:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    222a:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    222e:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2232:	48 8b 00             	mov    (%rax),%rax
    2235:	48 89 c7             	mov    %rax,%rdi
    2238:	e8 6c f3 ff ff       	call   15a9 <ocall_print_string>
    223d:	b8 00 00 00 00       	mov    $0x0,%eax
    2242:	c9                   	leave  
    2243:	c3                   	ret    

0000000000002244 <rsa_dec_ecall>:
    2244:	f3 0f 1e fa          	endbr64 
    2248:	55                   	push   %rbp
    2249:	48 89 e5             	mov    %rsp,%rbp
    224c:	48 83 ec 50          	sub    $0x50,%rsp
    2250:	48 89 7d c8          	mov    %rdi,-0x38(%rbp)
    2254:	48 89 75 c0          	mov    %rsi,-0x40(%rbp)
    2258:	48 89 55 b8          	mov    %rdx,-0x48(%rbp)
    225c:	89 4d b4             	mov    %ecx,-0x4c(%rbp)
    225f:	48 8b 45 b8          	mov    -0x48(%rbp),%rax
    2263:	48 89 45 e8          	mov    %rax,-0x18(%rbp)
    2267:	8b 45 b4             	mov    -0x4c(%rbp),%eax
    226a:	89 45 f0             	mov    %eax,-0x10(%rbp)
    226d:	48 8d 55 e0          	lea    -0x20(%rbp),%rdx
    2271:	48 8b 45 c8          	mov    -0x38(%rbp),%rax
    2275:	48 89 d1             	mov    %rdx,%rcx
    2278:	48 8d 15 11 2a 00 00 	lea    0x2a11(%rip),%rdx        # 4c90 <ocall_table_encl>
    227f:	be 00 00 00 00       	mov    $0x0,%esi
    2284:	48 89 c7             	mov    %rax,%rdi
    2287:	e8 64 f1 ff ff       	call   13f0 <sgx_ecall@plt>
    228c:	89 45 dc             	mov    %eax,-0x24(%rbp)
    228f:	83 7d dc 00          	cmpl   $0x0,-0x24(%rbp)
    2293:	75 11                	jne    22a6 <rsa_dec_ecall+0x62>
    2295:	48 83 7d c0 00       	cmpq   $0x0,-0x40(%rbp)
    229a:	74 0a                	je     22a6 <rsa_dec_ecall+0x62>
    229c:	0f b6 55 e0          	movzbl -0x20(%rbp),%edx
    22a0:	48 8b 45 c0          	mov    -0x40(%rbp),%rax
    22a4:	88 10                	mov    %dl,(%rax)
    22a6:	8b 45 dc             	mov    -0x24(%rbp),%eax
    22a9:	c9                   	leave  
    22aa:	c3                   	ret    

00000000000022ab <rsa_init_ecall>:
    22ab:	f3 0f 1e fa          	endbr64 
    22af:	55                   	push   %rbp
    22b0:	48 89 e5             	mov    %rsp,%rbp
    22b3:	48 83 ec 20          	sub    $0x20,%rsp
    22b7:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    22bb:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
    22bf:	48 8d 55 fb          	lea    -0x5(%rbp),%rdx
    22c3:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    22c7:	48 89 d1             	mov    %rdx,%rcx
    22ca:	48 8d 15 bf 29 00 00 	lea    0x29bf(%rip),%rdx        # 4c90 <ocall_table_encl>
    22d1:	be 01 00 00 00       	mov    $0x1,%esi
    22d6:	48 89 c7             	mov    %rax,%rdi
    22d9:	e8 12 f1 ff ff       	call   13f0 <sgx_ecall@plt>
    22de:	89 45 fc             	mov    %eax,-0x4(%rbp)
    22e1:	83 7d fc 00          	cmpl   $0x0,-0x4(%rbp)
    22e5:	75 11                	jne    22f8 <rsa_init_ecall+0x4d>
    22e7:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
    22ec:	74 0a                	je     22f8 <rsa_init_ecall+0x4d>
    22ee:	0f b6 55 fb          	movzbl -0x5(%rbp),%edx
    22f2:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    22f6:	88 10                	mov    %dl,(%rax)
    22f8:	8b 45 fc             	mov    -0x4(%rbp),%eax
    22fb:	c9                   	leave  
    22fc:	c3                   	ret    

00000000000022fd <rsa_clean_ecall>:
    22fd:	f3 0f 1e fa          	endbr64 
    2301:	55                   	push   %rbp
    2302:	48 89 e5             	mov    %rsp,%rbp
    2305:	48 83 ec 20          	sub    $0x20,%rsp
    2309:	48 89 7d e8          	mov    %rdi,-0x18(%rbp)
    230d:	48 89 75 e0          	mov    %rsi,-0x20(%rbp)
    2311:	48 8d 55 fb          	lea    -0x5(%rbp),%rdx
    2315:	48 8b 45 e8          	mov    -0x18(%rbp),%rax
    2319:	48 89 d1             	mov    %rdx,%rcx
    231c:	48 8d 15 6d 29 00 00 	lea    0x296d(%rip),%rdx        # 4c90 <ocall_table_encl>
    2323:	be 02 00 00 00       	mov    $0x2,%esi
    2328:	48 89 c7             	mov    %rax,%rdi
    232b:	e8 c0 f0 ff ff       	call   13f0 <sgx_ecall@plt>
    2330:	89 45 fc             	mov    %eax,-0x4(%rbp)
    2333:	83 7d fc 00          	cmpl   $0x0,-0x4(%rbp)
    2337:	75 11                	jne    234a <rsa_clean_ecall+0x4d>
    2339:	48 83 7d e0 00       	cmpq   $0x0,-0x20(%rbp)
    233e:	74 0a                	je     234a <rsa_clean_ecall+0x4d>
    2340:	0f b6 55 fb          	movzbl -0x5(%rbp),%edx
    2344:	48 8b 45 e0          	mov    -0x20(%rbp),%rax
    2348:	88 10                	mov    %dl,(%rax)
    234a:	8b 45 fc             	mov    -0x4(%rbp),%eax
    234d:	c9                   	leave  
    234e:	c3                   	ret    

000000000000234f <rdtsc>:
    234f:	55                   	push   %rbp
    2350:	48 89 e5             	mov    %rsp,%rbp
    2353:	0f 31                	rdtsc  
    2355:	89 45 f8             	mov    %eax,-0x8(%rbp)
    2358:	89 55 fc             	mov    %edx,-0x4(%rbp)
    235b:	8b 45 fc             	mov    -0x4(%rbp),%eax
    235e:	48 c1 e0 20          	shl    $0x20,%rax
    2362:	48 89 c2             	mov    %rax,%rdx
    2365:	8b 45 f8             	mov    -0x8(%rbp),%eax
    2368:	48 09 d0             	or     %rdx,%rax
    236b:	5d                   	pop    %rbp
    236c:	c3                   	ret    

000000000000236d <log_sensors_output>:
    236d:	f3 0f 1e fa          	endbr64 
    2371:	55                   	push   %rbp
    2372:	48 89 e5             	mov    %rsp,%rbp
    2375:	48 81 ec 30 01 00 00 	sub    $0x130,%rsp
    237c:	89 bd dc fe ff ff    	mov    %edi,-0x124(%rbp)
    2382:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    2389:	00 00 
    238b:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    238f:	31 c0                	xor    %eax,%eax
    2391:	48 8d 05 40 10 00 00 	lea    0x1040(%rip),%rax        # 33d8 <result_exp+0x398>
    2398:	48 89 c6             	mov    %rax,%rsi
    239b:	48 8d 05 38 10 00 00 	lea    0x1038(%rip),%rax        # 33da <result_exp+0x39a>
    23a2:	48 89 c7             	mov    %rax,%rdi
    23a5:	e8 76 f0 ff ff       	call   1420 <popen@plt>
    23aa:	48 89 85 e0 fe ff ff 	mov    %rax,-0x120(%rbp)
    23b1:	48 83 bd e0 fe ff ff 	cmpq   $0x0,-0x120(%rbp)
    23b8:	00 
    23b9:	0f 84 9b 00 00 00    	je     245a <log_sensors_output+0xed>
    23bf:	8b 85 dc fe ff ff    	mov    -0x124(%rbp),%eax
    23c5:	89 c7                	mov    %eax,%edi
    23c7:	e8 94 ef ff ff       	call   1360 <dup@plt>
    23cc:	89 c2                	mov    %eax,%edx
    23ce:	48 8d 05 0d 10 00 00 	lea    0x100d(%rip),%rax        # 33e2 <result_exp+0x3a2>
    23d5:	48 89 c6             	mov    %rax,%rsi
    23d8:	89 d7                	mov    %edx,%edi
    23da:	e8 21 f0 ff ff       	call   1400 <fdopen@plt>
    23df:	48 89 85 e8 fe ff ff 	mov    %rax,-0x118(%rbp)
    23e6:	48 83 bd e8 fe ff ff 	cmpq   $0x0,-0x118(%rbp)
    23ed:	00 
    23ee:	75 2a                	jne    241a <log_sensors_output+0xad>
    23f0:	48 8b 85 e0 fe ff ff 	mov    -0x120(%rbp),%rax
    23f7:	48 89 c7             	mov    %rax,%rdi
    23fa:	e8 41 ef ff ff       	call   1340 <pclose@plt>
    23ff:	eb 5a                	jmp    245b <log_sensors_output+0xee>
    2401:	48 8b 95 e8 fe ff ff 	mov    -0x118(%rbp),%rdx
    2408:	48 8d 85 f0 fe ff ff 	lea    -0x110(%rbp),%rax
    240f:	48 89 d6             	mov    %rdx,%rsi
    2412:	48 89 c7             	mov    %rax,%rdi
    2415:	e8 66 ef ff ff       	call   1380 <fputs@plt>
    241a:	48 8b 95 e0 fe ff ff 	mov    -0x120(%rbp),%rdx
    2421:	48 8d 85 f0 fe ff ff 	lea    -0x110(%rbp),%rax
    2428:	be 00 01 00 00       	mov    $0x100,%esi
    242d:	48 89 c7             	mov    %rax,%rdi
    2430:	e8 9b ef ff ff       	call   13d0 <fgets@plt>
    2435:	48 85 c0             	test   %rax,%rax
    2438:	75 c7                	jne    2401 <log_sensors_output+0x94>
    243a:	48 8b 85 e8 fe ff ff 	mov    -0x118(%rbp),%rax
    2441:	48 89 c7             	mov    %rax,%rdi
    2444:	e8 a7 ee ff ff       	call   12f0 <fclose@plt>
    2449:	48 8b 85 e0 fe ff ff 	mov    -0x120(%rbp),%rax
    2450:	48 89 c7             	mov    %rax,%rdi
    2453:	e8 e8 ee ff ff       	call   1340 <pclose@plt>
    2458:	eb 01                	jmp    245b <log_sensors_output+0xee>
    245a:	90                   	nop
    245b:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    245f:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    2466:	00 00 
    2468:	74 05                	je     246f <log_sensors_output+0x102>
    246a:	e8 a1 ee ff ff       	call   1310 <__stack_chk_fail@plt>
    246f:	c9                   	leave  
    2470:	c3                   	ret    

0000000000002471 <print_affinity>:
    2471:	f3 0f 1e fa          	endbr64 
    2475:	55                   	push   %rbp
    2476:	48 89 e5             	mov    %rsp,%rbp
    2479:	48 81 ec b0 00 00 00 	sub    $0xb0,%rsp
    2480:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    2487:	00 00 
    2489:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    248d:	31 c0                	xor    %eax,%eax
    248f:	48 8d 85 70 ff ff ff 	lea    -0x90(%rbp),%rax
    2496:	48 89 c2             	mov    %rax,%rdx
    2499:	be 80 00 00 00       	mov    $0x80,%esi
    249e:	bf 00 00 00 00       	mov    $0x0,%edi
    24a3:	e8 d8 ef ff ff       	call   1480 <sched_getaffinity@plt>
    24a8:	83 f8 ff             	cmp    $0xffffffff,%eax
    24ab:	75 37                	jne    24e4 <print_affinity+0x73>
    24ad:	48 8d 05 30 0f 00 00 	lea    0xf30(%rip),%rax        # 33e4 <result_exp+0x3a4>
    24b4:	48 89 c7             	mov    %rax,%rdi
    24b7:	e8 74 ef ff ff       	call   1430 <perror@plt>
    24bc:	48 8d 05 2d 11 00 00 	lea    0x112d(%rip),%rax        # 35f0 <__PRETTY_FUNCTION__.0>
    24c3:	48 89 c1             	mov    %rax,%rcx
    24c6:	ba 2a 00 00 00       	mov    $0x2a,%edx
    24cb:	48 8d 05 24 0f 00 00 	lea    0xf24(%rip),%rax        # 33f6 <result_exp+0x3b6>
    24d2:	48 89 c6             	mov    %rax,%rsi
    24d5:	48 8d 05 23 0f 00 00 	lea    0xf23(%rip),%rax        # 33ff <result_exp+0x3bf>
    24dc:	48 89 c7             	mov    %rax,%rdi
    24df:	e8 8c ee ff ff       	call   1370 <__assert_fail@plt>
    24e4:	bf 54 00 00 00       	mov    $0x54,%edi
    24e9:	e8 52 ef ff ff       	call   1440 <sysconf@plt>
    24ee:	48 89 85 60 ff ff ff 	mov    %rax,-0xa0(%rbp)
    24f5:	48 8d 05 05 0f 00 00 	lea    0xf05(%rip),%rax        # 3401 <result_exp+0x3c1>
    24fc:	48 89 c7             	mov    %rax,%rdi
    24ff:	b8 00 00 00 00       	mov    $0x0,%eax
    2504:	e8 27 ee ff ff       	call   1330 <printf@plt>
    2509:	48 c7 85 58 ff ff ff 	movq   $0x0,-0xa8(%rbp)
    2510:	00 00 00 00 
    2514:	eb 7f                	jmp    2595 <print_affinity+0x124>
    2516:	48 8b 85 58 ff ff ff 	mov    -0xa8(%rbp),%rax
    251d:	48 89 85 68 ff ff ff 	mov    %rax,-0x98(%rbp)
    2524:	48 81 bd 68 ff ff ff 	cmpq   $0x3ff,-0x98(%rbp)
    252b:	ff 03 00 00 
    252f:	77 41                	ja     2572 <print_affinity+0x101>
    2531:	48 8b 85 68 ff ff ff 	mov    -0x98(%rbp),%rax
    2538:	48 c1 e8 06          	shr    $0x6,%rax
    253c:	48 8d 14 c5 00 00 00 	lea    0x0(,%rax,8),%rdx
    2543:	00 
    2544:	48 8d 85 70 ff ff ff 	lea    -0x90(%rbp),%rax
    254b:	48 01 d0             	add    %rdx,%rax
    254e:	48 8b 10             	mov    (%rax),%rdx
    2551:	48 8b 85 68 ff ff ff 	mov    -0x98(%rbp),%rax
    2558:	83 e0 3f             	and    $0x3f,%eax
    255b:	89 c1                	mov    %eax,%ecx
    255d:	48 d3 ea             	shr    %cl,%rdx
    2560:	48 89 d0             	mov    %rdx,%rax
    2563:	83 e0 01             	and    $0x1,%eax
    2566:	48 85 c0             	test   %rax,%rax
    2569:	74 07                	je     2572 <print_affinity+0x101>
    256b:	b8 01 00 00 00       	mov    $0x1,%eax
    2570:	eb 05                	jmp    2577 <print_affinity+0x106>
    2572:	b8 00 00 00 00       	mov    $0x0,%eax
    2577:	89 c6                	mov    %eax,%esi
    2579:	48 8d 05 96 0e 00 00 	lea    0xe96(%rip),%rax        # 3416 <result_exp+0x3d6>
    2580:	48 89 c7             	mov    %rax,%rdi
    2583:	b8 00 00 00 00       	mov    $0x0,%eax
    2588:	e8 a3 ed ff ff       	call   1330 <printf@plt>
    258d:	48 83 85 58 ff ff ff 	addq   $0x1,-0xa8(%rbp)
    2594:	01 
    2595:	48 8b 85 58 ff ff ff 	mov    -0xa8(%rbp),%rax
    259c:	48 3b 85 60 ff ff ff 	cmp    -0xa0(%rbp),%rax
    25a3:	0f 8c 6d ff ff ff    	jl     2516 <print_affinity+0xa5>
    25a9:	bf 0a 00 00 00       	mov    $0xa,%edi
    25ae:	e8 cd ec ff ff       	call   1280 <putchar@plt>
    25b3:	90                   	nop
    25b4:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    25b8:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    25bf:	00 00 
    25c1:	74 05                	je     25c8 <print_affinity+0x157>
    25c3:	e8 48 ed ff ff       	call   1310 <__stack_chk_fail@plt>
    25c8:	c9                   	leave  
    25c9:	c3                   	ret    

00000000000025ca <set_freq>:
    25ca:	f3 0f 1e fa          	endbr64 
    25ce:	55                   	push   %rbp
    25cf:	48 89 e5             	mov    %rsp,%rbp
    25d2:	48 81 ec e0 00 00 00 	sub    $0xe0,%rsp
    25d9:	48 89 bd 28 ff ff ff 	mov    %rdi,-0xd8(%rbp)
    25e0:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    25e7:	00 00 
    25e9:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    25ed:	31 c0                	xor    %eax,%eax
    25ef:	48 8b 95 28 ff ff ff 	mov    -0xd8(%rbp),%rdx
    25f6:	48 8d 85 30 ff ff ff 	lea    -0xd0(%rbp),%rax
    25fd:	48 8d 0d 1c 0e 00 00 	lea    0xe1c(%rip),%rcx        # 3420 <result_exp+0x3e0>
    2604:	48 89 ce             	mov    %rcx,%rsi
    2607:	48 89 c7             	mov    %rax,%rdi
    260a:	b8 00 00 00 00       	mov    $0x0,%eax
    260f:	e8 4c ee ff ff       	call   1460 <sprintf@plt>
    2614:	48 8d 85 30 ff ff ff 	lea    -0xd0(%rbp),%rax
    261b:	48 89 c7             	mov    %rax,%rdi
    261e:	e8 fd ec ff ff       	call   1320 <system@plt>
    2623:	48 8b 95 28 ff ff ff 	mov    -0xd8(%rbp),%rdx
    262a:	48 8d 85 30 ff ff ff 	lea    -0xd0(%rbp),%rax
    2631:	48 8d 0d 10 0e 00 00 	lea    0xe10(%rip),%rcx        # 3448 <result_exp+0x408>
    2638:	48 89 ce             	mov    %rcx,%rsi
    263b:	48 89 c7             	mov    %rax,%rdi
    263e:	b8 00 00 00 00       	mov    $0x0,%eax
    2643:	e8 18 ee ff ff       	call   1460 <sprintf@plt>
    2648:	48 8d 85 30 ff ff ff 	lea    -0xd0(%rbp),%rax
    264f:	48 89 c7             	mov    %rax,%rdi
    2652:	e8 c9 ec ff ff       	call   1320 <system@plt>
    2657:	bf 02 00 00 00       	mov    $0x2,%edi
    265c:	e8 2f ee ff ff       	call   1490 <sleep@plt>
    2661:	48 8d 05 04 0e 00 00 	lea    0xe04(%rip),%rax        # 346c <result_exp+0x42c>
    2668:	48 89 c7             	mov    %rax,%rdi
    266b:	e8 b0 ec ff ff       	call   1320 <system@plt>
    2670:	90                   	nop
    2671:	48 8b 45 f8          	mov    -0x8(%rbp),%rax
    2675:	64 48 2b 04 25 28 00 	sub    %fs:0x28,%rax
    267c:	00 00 
    267e:	74 05                	je     2685 <set_freq+0xbb>
    2680:	e8 8b ec ff ff       	call   1310 <__stack_chk_fail@plt>
    2685:	c9                   	leave  
    2686:	c3                   	ret    

0000000000002687 <delay_us>:
    2687:	f3 0f 1e fa          	endbr64 
    268b:	55                   	push   %rbp
    268c:	48 89 e5             	mov    %rsp,%rbp
    268f:	48 83 ec 20          	sub    $0x20,%rsp
    2693:	f2 0f 11 45 e8       	movsd  %xmm0,-0x18(%rbp)
    2698:	f2 0f 11 4d e0       	movsd  %xmm1,-0x20(%rbp)
    269d:	f2 0f 10 45 e8       	movsd  -0x18(%rbp),%xmm0
    26a2:	66 0f 28 c8          	movapd %xmm0,%xmm1
    26a6:	f2 0f 59 4d e0       	mulsd  -0x20(%rbp),%xmm1
    26ab:	f2 0f 10 05 4d 0f 00 	movsd  0xf4d(%rip),%xmm0        # 3600 <__PRETTY_FUNCTION__.0+0x10>
    26b2:	00 
    26b3:	f2 0f 59 c1          	mulsd  %xmm1,%xmm0
    26b7:	66 0f 2f 05 49 0f 00 	comisd 0xf49(%rip),%xmm0        # 3608 <__PRETTY_FUNCTION__.0+0x18>
    26be:	00 
    26bf:	73 0b                	jae    26cc <delay_us+0x45>
    26c1:	f2 48 0f 2c c0       	cvttsd2si %xmm0,%rax
    26c6:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
    26ca:	eb 23                	jmp    26ef <delay_us+0x68>
    26cc:	f2 0f 10 0d 34 0f 00 	movsd  0xf34(%rip),%xmm1        # 3608 <__PRETTY_FUNCTION__.0+0x18>
    26d3:	00 
    26d4:	f2 0f 5c c1          	subsd  %xmm1,%xmm0
    26d8:	f2 48 0f 2c c0       	cvttsd2si %xmm0,%rax
    26dd:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
    26e1:	48 b8 00 00 00 00 00 	movabs $0x8000000000000000,%rax
    26e8:	00 00 80 
    26eb:	48 31 45 f0          	xor    %rax,-0x10(%rbp)
    26ef:	48 8b 45 f0          	mov    -0x10(%rbp),%rax
    26f3:	48 89 45 f0          	mov    %rax,-0x10(%rbp)
    26f7:	b8 00 00 00 00       	mov    $0x0,%eax
    26fc:	e8 4e fc ff ff       	call   234f <rdtsc>
    2701:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    2705:	90                   	nop
    2706:	b8 00 00 00 00       	mov    $0x0,%eax
    270b:	e8 3f fc ff ff       	call   234f <rdtsc>
    2710:	48 2b 45 f8          	sub    -0x8(%rbp),%rax
    2714:	48 39 45 f0          	cmp    %rax,-0x10(%rbp)
    2718:	77 ec                	ja     2706 <delay_us+0x7f>
    271a:	90                   	nop
    271b:	90                   	nop
    271c:	c9                   	leave  
    271d:	c3                   	ret    

000000000000271e <func_error>:
    271e:	f3 0f 1e fa          	endbr64 
    2722:	55                   	push   %rbp
    2723:	48 89 e5             	mov    %rsp,%rbp
    2726:	48 83 ec 10          	sub    $0x10,%rsp
    272a:	48 89 7d f8          	mov    %rdi,-0x8(%rbp)
    272e:	48 8b 05 eb 28 00 00 	mov    0x28eb(%rip),%rax        # 5020 <stderr@GLIBC_2.2.5>
    2735:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
    2739:	48 8d 0d 49 0d 00 00 	lea    0xd49(%rip),%rcx        # 3489 <result_exp+0x449>
    2740:	48 89 ce             	mov    %rcx,%rsi
    2743:	48 89 c7             	mov    %rax,%rdi
    2746:	b8 00 00 00 00       	mov    $0x0,%eax
    274b:	e8 90 ec ff ff       	call   13e0 <fprintf@plt>
    2750:	bf ff ff ff ff       	mov    $0xffffffff,%edi
    2755:	e8 16 ed ff ff       	call   1470 <exit@plt>

000000000000275a <float2int>:
    275a:	f3 0f 1e fa          	endbr64 
    275e:	55                   	push   %rbp
    275f:	48 89 e5             	mov    %rsp,%rbp
    2762:	f3 0f 11 45 fc       	movss  %xmm0,-0x4(%rbp)
    2767:	f3 0f 10 4d fc       	movss  -0x4(%rbp),%xmm1
    276c:	f3 0f 10 05 9c 0e 00 	movss  0xe9c(%rip),%xmm0        # 3610 <__PRETTY_FUNCTION__.0+0x20>
    2773:	00 
    2774:	f3 0f 59 c8          	mulss  %xmm0,%xmm1
    2778:	f3 0f 10 05 94 0e 00 	movss  0xe94(%rip),%xmm0        # 3614 <__PRETTY_FUNCTION__.0+0x24>
    277f:	00 
    2780:	f3 0f 58 c1          	addss  %xmm1,%xmm0
    2784:	f3 0f 2c c0          	cvttss2si %xmm0,%eax
    2788:	5d                   	pop    %rbp
    2789:	c3                   	ret    

000000000000278a <configure_glitch_with_delay>:
    278a:	f3 0f 1e fa          	endbr64 
    278e:	55                   	push   %rbp
    278f:	48 89 e5             	mov    %rsp,%rbp
    2792:	48 81 ec 40 01 00 00 	sub    $0x140,%rsp
    2799:	89 bd dc fe ff ff    	mov    %edi,-0x124(%rbp)
    279f:	89 b5 d8 fe ff ff    	mov    %esi,-0x128(%rbp)
    27a5:	f3 0f 11 85 d4 fe ff 	movss  %xmm0,-0x12c(%rbp)
    27ac:	ff 
    27ad:	f3 0f 11 8d d0 fe ff 	movss  %xmm1,-0x130(%rbp)
    27b4:	ff 
    27b5:	f3 0f 11 95 cc fe ff 	movss  %xmm2,-0x134(%rbp)
    27bc:	ff 
    27bd:	f3 0f 11 9d c8 fe ff 	movss  %xmm3,-0x138(%rbp)
    27c4:	ff 
    27c5:	f3 0f 11 a5 c4 fe ff 	movss  %xmm4,-0x13c(%rbp)
    27cc:	ff 
    27cd:	64 48 8b 04 25 28 00 	mov    %fs:0x28,%rax
    27d4:	00 00 
    27d6:	48 89 45 f8          	mov    %rax,-0x8(%rbp)
    27da:	31 c0                	xor    %eax,%eax
    27dc:	8b 85 d8 fe ff ff    	mov    -0x128(%rbp),%eax
    27e2:	89 05 80 28 00 00    	mov    %eax,0x2880(%rip)        # 5068 <channel>
    27e8:	8b 85 cc fe ff ff    	mov    -0x134(%rbp),%eax
    27ee:	66 0f 6e c0          	movd   %eax,%xmm0
    27f2:	e8 63 ff ff ff       	call   275a <float2int>
    27f7:	85 c0                	test   %eax,%eax
    27f9:	75 7d                	jne    2878 <configure_glitch_with_delay+0xee>
    27fb:	66 0f ef c0          	pxor   %xmm0,%xmm0
    27ff:	f3 0f 5a 85 d4 fe ff 	cvtss2sd -0x12c(%rbp),%xmm0
    2806:	ff 
    2807:	f2 0f 10 0d 09 0e 00 	movsd  0xe09(%rip),%xmm1        # 3618 <__PRETTY_FUNCTION__.0+0x28>
    280e:	00 
    280f:	f2 0f 5e c1          	divsd  %xmm1,%xmm0
    2813:	f2 0f 5a c0          	cvtsd2ss %xmm0,%xmm0
    2817:	f3 0f 11 85 e8 fe ff 	movss  %xmm0,-0x118(%rbp)
    281e:	ff 
    281f:	66 0f ef ed          	pxor   %xmm5,%xmm5
    2823:	f3 0f 5a ad e8 fe ff 	cvtss2sd -0x118(%rbp),%xmm5
    282a:	ff 
    282b:	66 48 0f 7e ea       	movq   %xmm5,%rdx
    2830:	48 8d 85 f0 fe ff ff 	lea    -0x110(%rbp),%rax
    2837:	66 48 0f 6e c2       	movq   %rdx,%xmm0
    283c:	48 8d 15 4d 0c 00 00 	lea    0xc4d(%rip),%rdx        # 3490 <result_exp+0x450>
    2843:	be 00 01 00 00       	mov    $0x100,%esi
    2848:	48 89 c7             	mov    %rax,%rdi
    284b:	b8 01 00 00 00       	mov    $0x1,%eax
    2850:	e8 fb ea ff ff       	call   1350 <snprintf@plt>
    2855:	48 8d 85 f0 fe ff ff 	lea    -0x110(%rbp),%rax
    285c:	48 89 c7             	mov    %rax,%rdi
    285f:	e8 2c ea ff ff       	call   1290 <puts@plt>
    2864:	48 8d 85 f0 fe ff ff 	lea    -0x110(%rbp),%rax
    286b:	48 89 c7             	mov    %rax,%rdi
    286e:	e8 ad ea ff ff       	call   1320 <system@plt>
    2873:	e9 ec 00 00 00       	jmp    2964 <configure_glitch_with_delay+0x1da>
    2878:	66 0f ef c0          	pxor   %xmm0,%xmm0
    287c:	f3 0f 5a 85 d4 fe ff 	cvtss2sd -0x12c(%rbp),%xmm0
    2883:	ff 
    2884:	f2 0f 10 0d 8c 0d 00 	movsd  0xd8c(%rip),%xmm1        # 3618 <__PRETTY_FUNCTION__.0+0x28>
    288b:	00 
    288c:	f2 0f 5e c1          	divsd  %xmm1,%xmm0
    2890:	f2 0f 5a c0          	cvtsd2ss %xmm0,%xmm0
    2894:	f3 0f 11 85 e8 fe ff 	movss  %xmm0,-0x118(%rbp)
    289b:	ff 
    289c:	66 0f ef c0          	pxor   %xmm0,%xmm0
    28a0:	f3 0f 5a 85 cc fe ff 	cvtss2sd -0x134(%rbp),%xmm0
    28a7:	ff 
    28a8:	f2 0f 10 0d 68 0d 00 	movsd  0xd68(%rip),%xmm1        # 3618 <__PRETTY_FUNCTION__.0+0x28>
    28af:	00 
    28b0:	f2 0f 5e c1          	divsd  %xmm1,%xmm0
    28b4:	f2 0f 5a c0          	cvtsd2ss %xmm0,%xmm0
    28b8:	f3 0f 11 85 ec fe ff 	movss  %xmm0,-0x114(%rbp)
    28bf:	ff 
    28c0:	f3 0f 10 85 d0 fe ff 	movss  -0x130(%rbp),%xmm0
    28c7:	ff 
    28c8:	f3 0f 58 85 c4 fe ff 	addss  -0x13c(%rbp),%xmm0
    28cf:	ff 
    28d0:	f3 0f 11 85 d0 fe ff 	movss  %xmm0,-0x130(%rbp)
    28d7:	ff 
    28d8:	66 0f ef d2          	pxor   %xmm2,%xmm2
    28dc:	f3 0f 5a 95 c8 fe ff 	cvtss2sd -0x138(%rbp),%xmm2
    28e3:	ff 
    28e4:	66 0f ef c9          	pxor   %xmm1,%xmm1
    28e8:	f3 0f 5a 8d ec fe ff 	cvtss2sd -0x114(%rbp),%xmm1
    28ef:	ff 
    28f0:	66 0f ef c0          	pxor   %xmm0,%xmm0
    28f4:	f3 0f 5a 85 d0 fe ff 	cvtss2sd -0x130(%rbp),%xmm0
    28fb:	ff 
    28fc:	66 0f ef f6          	pxor   %xmm6,%xmm6
    2900:	f3 0f 5a b5 e8 fe ff 	cvtss2sd -0x118(%rbp),%xmm6
    2907:	ff 
    2908:	66 48 0f 7e f1       	movq   %xmm6,%rcx
    290d:	8b 95 dc fe ff ff    	mov    -0x124(%rbp),%edx
    2913:	48 8d 85 f0 fe ff ff 	lea    -0x110(%rbp),%rax
    291a:	66 0f 28 da          	movapd %xmm2,%xmm3
    291e:	66 0f 28 d1          	movapd %xmm1,%xmm2
    2922:	66 0f 28 c8          	movapd %xmm0,%xmm1
    2926:	66 48 0f 6e c1       	movq   %rcx,%xmm0
    292b:	89 d1                	mov    %edx,%ecx
    292d:	48 8d 15 a4 0b 00 00 	lea    0xba4(%rip),%rdx        # 34d8 <result_exp+0x498>
    2934:	be 00 01 00 00       	mov    $0x100,%esi
    2939:	48 89 c7             	mov    %rax,%rdi
    293c:	b8 04 00 00 00       	mov    $0x4,%eax
    2941:	e8 0a ea ff ff       	call   1350 <snprintf@plt>
    2946:	48 8d 85 f0 fe ff ff 	lea    -0x110(%rbp),%rax
    294d:	48 89 c7             	mov    %rax,%rdi
    2950:	e8 3b e9 ff ff       	call   1290 <puts@plt>
    2955:	48 8d 85 f0 fe ff ff 	lea    -0x110(%rbp),%rax
    295c:	48 89 c7             	mov    %rax,%rdi
    295f:	e8 bc e9 ff ff       	call   1320 <system@plt>
    2964:	b8 00 00 00 00       	mov    $0x0,%eax
    2969:	48 8b 55 f8          	mov    -0x8(%rbp),%rdx
    296d:	64 48 2b 14 25 28 00 	sub    %fs:0x28,%rdx
    2974:	00 00 
    2976:	74 05                	je     297d <configure_glitch_with_delay+0x1f3>
    2978:	e8 93 e9 ff ff       	call   1310 <__stack_chk_fail@plt>
    297d:	c9                   	leave  
    297e:	c3                   	ret    

000000000000297f <start_DCpower_type1>:
    297f:	f3 0f 1e fa          	endbr64 
    2983:	55                   	push   %rbp
    2984:	48 89 e5             	mov    %rsp,%rbp
    2987:	48 8d 05 a2 0b 00 00 	lea    0xba2(%rip),%rax        # 3530 <result_exp+0x4f0>
    298e:	48 89 c7             	mov    %rax,%rdi
    2991:	e8 8a e9 ff ff       	call   1320 <system@plt>
    2996:	b8 00 00 00 00       	mov    $0x0,%eax
    299b:	5d                   	pop    %rbp
    299c:	c3                   	ret    

000000000000299d <end_DCpower_type1>:
    299d:	f3 0f 1e fa          	endbr64 
    29a1:	55                   	push   %rbp
    29a2:	48 89 e5             	mov    %rsp,%rbp
    29a5:	48 8d 05 c4 0b 00 00 	lea    0xbc4(%rip),%rax        # 3570 <result_exp+0x530>
    29ac:	48 89 c7             	mov    %rax,%rdi
    29af:	e8 6c e9 ff ff       	call   1320 <system@plt>
    29b4:	b8 00 00 00 00       	mov    $0x0,%eax
    29b9:	5d                   	pop    %rbp
    29ba:	c3                   	ret    

00000000000029bb <close_BNC_Arb>:
    29bb:	f3 0f 1e fa          	endbr64 
    29bf:	55                   	push   %rbp
    29c0:	48 89 e5             	mov    %rsp,%rbp
    29c3:	48 8d 05 e6 0b 00 00 	lea    0xbe6(%rip),%rax        # 35b0 <result_exp+0x570>
    29ca:	48 89 c7             	mov    %rax,%rdi
    29cd:	e8 4e e9 ff ff       	call   1320 <system@plt>
    29d2:	b8 00 00 00 00       	mov    $0x0,%eax
    29d7:	5d                   	pop    %rbp
    29d8:	c3                   	ret    

Disassembly of section .fini:

00000000000029dc <_fini>:
    29dc:	f3 0f 1e fa          	endbr64 
    29e0:	48 83 ec 08          	sub    $0x8,%rsp
    29e4:	48 83 c4 08          	add    $0x8,%rsp
    29e8:	c3                   	ret    
