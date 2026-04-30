# VoltFraud: Voltage Fault Injection Against Intel SGX Through Voltage Loop Control

## Introduction
Modern processors regulate on-chip supply rails with a voltage control loop. The loop observes the sensed voltage and adjusts the regulator output to compensate for load variation and delivery loss.

VoltFraud targets the integrity of that sensing path. By injecting an additional voltage into the voltage sense circuit, an attacker can bias the sensed value seen by the control loop. The regulator then compensates in the wrong direction and introduces controllable voltage faults on the target rail.

This repository contains the VoltFraud implementation together with proof-of-concept attacks for both client SGX and Scalable SGX platforms.

## Key Properties
1. **Broad attack coverage**  
    The attack affects components powered by the targeted voltage domain, including CPU cores, memory-related logic, and I/O or system-agent subsystems depending on the platform.
2. **Fine-grained control**  
    The sensing path can be influenced at millivolt scale, which enables controlled fault injection rather than coarse undervolting.
3. **Practical deployment**  
    The setup does not rely on chip decapsulation or proprietary debug interfaces. The experiments are built around external voltage injection and software-controlled triggering.

## Experimental Platforms

| Platform | CPU | Mainboard | TEE |
|---|---|---|---|
| Desktop | Intel Core i3-10305 | Asus Prime H410M-F | Client SGX |
| Server | Intel Xeon Scalable 6330 | ASRock SPC621D8U-2T | Scalable SGX |

VoltFraud targets the platform power-delivery feedback path rather than a single microarchitectural block. Because of that, the technique is expected to generalize to other systems that expose a similar voltage feedback mechanism.

## Repository Layout

```text
.
├── README.md
├── remote-reset-scalable-sgx.py
├── remote-reset-sgx.py
├── VoltFraud-sgx
│   ├── lib
│   └── poc
│       ├── fault-core
│       │   ├── mul
│       │   ├── sgx-crt-rsa
│       │   └── sgx-sm4
│       ├── fault-io
│       │   ├── memory-access
│       │   └── sgx-memory-access
│       └── fault-mc
│           ├── memory-access
│           └── sgx-memory-access
└── VoltFraud-Scalable-sgx
     ├── lib
     └── poc
          ├── fault-vccin
          │   ├── mul
          │   └── simd-fault-test
          ├── fault-vccio
          │   └── memory-access
          ├── fault-vccsa
          │   └── memory-access
          └── fault-vddq
                ├── memory-access
                ├── sgx-Digital-Signature
                └── sgx-memory-access
```

## Top-Level Files
- `remote-reset-sgx.py`: remote reset helper for the client SGX platform.
- `remote-reset-scalable-sgx.py`: remote reset helper for the Scalable SGX platform.

## Client SGX Tree

`VoltFraud-sgx/` contains the desktop or client SGX implementation.

- `lib/`: hardware control code for voltage injection, triggering, and DC power control.
- `poc/fault-core/`: experiments targeting the core-related voltage rail.
- `poc/fault-mc/`: experiments targeting the memory-controller path.
- `poc/fault-io/`: experiments targeting the I/O-related path.

Representative proof-of-concept directories:

- `VoltFraud-sgx/poc/fault-core/mul`: core-domain arithmetic fault experiments.
- `VoltFraud-sgx/poc/fault-core/sgx-crt-rsa`: RSA fault attack in an SGX enclave.
- `VoltFraud-sgx/poc/fault-core/sgx-sm4`: SM4 fault experiments in an SGX enclave.
- `VoltFraud-sgx/poc/fault-mc/memory-access`: memory-controller fault experiment without SGX.
- `VoltFraud-sgx/poc/fault-mc/sgx-memory-access`: memory-controller fault experiment with SGX.
- `VoltFraud-sgx/poc/fault-io/memory-access`: I/O-path memory access experiment.
- `VoltFraud-sgx/poc/fault-io/sgx-memory-access`: I/O-path SGX memory access experiment.

## Scalable SGX Tree

`VoltFraud-Scalable-sgx/` contains the server or Scalable SGX implementation.

- `lib/`: control utilities for the external voltage setup.
- `poc/fault-vccin/`: experiments on the VCCIN-related rail.
- `poc/fault-vccio/`: experiments on the VCCIO-related rail.
- `poc/fault-vccsa/`: experiments on the VCCSA-related rail.
- `poc/fault-vddq/`: experiments on the VDDQ-related rail.

Representative proof-of-concept directories:

- `VoltFraud-Scalable-sgx/poc/fault-vccin/mul`: server-side multiplication fault experiment.
- `VoltFraud-Scalable-sgx/poc/fault-vccin/simd-fault-test`: SIMD-oriented fault test.
- `VoltFraud-Scalable-sgx/poc/fault-vccio/memory-access`: VCCIO memory-access experiment.
- `VoltFraud-Scalable-sgx/poc/fault-vccsa/memory-access`: VCCSA memory-access experiment.
- `VoltFraud-Scalable-sgx/poc/fault-vddq/memory-access`: VDDQ memory-access experiment.
- `VoltFraud-Scalable-sgx/poc/fault-vddq/sgx-Digital-Signature`: digital-signature fault experiment in SGX.
- `VoltFraud-Scalable-sgx/poc/fault-vddq/sgx-memory-access`: SGX memory-access fault experiment.

## Quick Start

Choose a proof-of-concept directory, build it, and run it from inside that directory.

Client SGX example:

```bash
cd VoltFraud-sgx/poc/fault-core/sgx-crt-rsa
make
sudo ./run.sh 10 3.8GHz 0.023 0.023 0.000010 0.01 0.0610 0.000050 0
```

```bash
cd VoltFraud-Scalable-sgx/poc/fault-vddq/sgx-memory-access
make
./simd_fault_test 10 0.8GHz 0.12000.1200 0.1200 0.002745 0.2850 0.000050 0
```

## Notes
- Many experiment directories contain generated binaries, logs, and enclave build artifacts alongside source files.
- Build and runtime requirements depend on the selected proof-of-concept, including SGX SDK availability, hardware trigger setup, and external power-control access.
