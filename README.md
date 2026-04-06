# VoltFraud: Voltage Fault injection attacks against Intel SGX using the voltage loop control

## Introduction
Modern processors use a voltage loop to regulate the supply voltage of the target hardware. The loop monitors the sensed voltage through a voltage sense circuit and adjusts the voltage regulator to compensate for fluctuations and power delivery losses.

VoltFraud exploits the lack of integrity protection on the sensed voltage. By injecting an additional voltage into the voltage sense circuit, an attacker can manipulate the sensed voltage and mislead the voltage loop. The regulator then adjusts the hardware voltage in the opposite direction, unintentionally introducing voltage faults.

This repository contains the implementation of VoltFraud and the proof-of-concept attacks used in the paper. The code supports both client SGX and server SGX (Scalable SGX) platforms.

## Key Features
1. **Broad Attack Surface**
VoltFraud targets the processor’s voltage loop and therefore affects a wide range of on-chip components. The attack can influence most hardware modules powered by the shared voltage domain, including CPU cores, memory controllers, I/O subsystems, and the system agent.
2. **Millivolt-Level Voltage Control**
Benefiting from the high-precision differential amplification used in the voltage sense circuit, VoltFraud can manipulate the hardware voltage with millivolt-level granularity, enabling fine-grained and controlled voltage fault injection.
3. **Low Deployment Complexity**
VoltFraud requires neither chip decapsulation nor reverse engineering of proprietary interfaces. The attack can be implemented by simply connecting an external power supply to the resistor divider in the voltage sense circuit to inject an additional voltage.

## Experimental Setup

VoltFraud is evaluated on two representative Intel platforms, including both a desktop-class system and a server-class system. The configurations of the experimental platforms are summarized below.

| Platform | CPU | Mainboard | TEE |
|---|---|---|---|
| Desktop | Intel Core i3-10305 | Asus Prime H410M-F | Client SGX |
| Server | Intel Xeon Scalable 6330 | ASRock SPC621D8U-2T | Scalable SGX |

VoltFraud exploits a vulnerability in the processor’s **power delivery architecture**, specifically the feedback mechanism used by the voltage loop. Because this mechanism belongs to the platform’s power regulation infrastructure rather than the processor microarchitecture, the attack is largely independent of specific microarchitectural designs.Therefore, VoltFraud is expected to be applicable to other processor platforms that employ similar voltage feedback mechanisms. We plan to evaluate additional platforms in future work.


## Repository Structure
```
/
├── remote-reset-sgx.py
├── remote-reset-scalable-sgx.py
├── VoltFraud-sgx
│   ├── lib
│   └── poc
│       ├── fault-vcccin
│       ├── fault-mc
│       └── fault-sa
└── VoltFraud-Scalable-sgx
    ├── lib
    └── poc
        ├── fault-vccin
        ├── fault-vccio
        ├── fault-vccsa
        └── fault-vddq
```
- **remote-reset-sgx.py** – remotely control script for the desktop platform.
- **remote-reset-scalable-sgx.py** – remotely control script for the server platform.
### VoltFraud-sgx
Implementation and proof-of-concept attacks for **client SGX platforms**.

- `lib/` – hardware control libraries for voltage manipulation.  
- `poc/` – proof-of-concept fault injection attacks.

### VoltFraud-Scalable-sgx
Implementation and experiments for **server SGX (Scalable SGX)** platforms.

- `lib/` – voltage control utilities.  
- `poc/` – fault injection experiments targeting different voltage rails.

## Quick Start
Navigate to the target experiment directory, compile the code, and run the experiment:

```bash
cd VoltFraud-sgx/poc/fault-vcccin/sgx-crt-rsa
make
sudo ./run.sh 10 3.8GHz 0.030 0.795 0.01 0.000010 0
```
