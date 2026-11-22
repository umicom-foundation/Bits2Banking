<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/multikernel-systems/09-separate-firmware-inventory-from-hart-entry.md

PURPOSE:
Teach how to keep firmware facts and observed Kernel entry in separate fields.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material.
-->

# Separate firmware inventory from hart entry

<p class="umicom-course-artwork"><span class="umicom-brand-mark"><img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom" width="180"></span> <a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="30"></a></p>

[Course contents](index.md) · [Previous lesson](08-qualify-a-bootable-release-in-stages.md)

A **hart** is a RISC-V hardware thread. Firmware describes harts in a device tree. The Kernel records a separate fact when a hart reaches its C startup code.

| Test profile | Firmware description for ID 1 | Kernel entry evidence for ID 1 |
| --- | --- | --- |
| One-hart QEMU | The checked tree did not describe it | No C entry record |
| Two-hart QEMU | The checked tree described it as enabled | No C entry record |

Hart 0 has an observed entry in both cases.

1. In the Umicom Kernel source, find **UmicomKernelHardwareHartRead** in **hardware_catalogue.h**. Write down the fields used for the two columns.
2. Find **hardware.hart-evidence** in **hardware_validation.c**. Predict the **other-firmware-enabled** value for each test profile. Explain why **other-c-entry** remains unobserved in both.
3. Compare an available tree without the requested ID to an unavailable tree. Record the two firmware states separately.
4. Draw two firmware entries with IDs 0 and 4096. Find the second record by its ID. Explain why 4096 cannot be used as a position in a table with two entries.

Write an acceptance check for actually starting a second hart. Ask the secondary code to report its own identifier and startup attempt. Check independent stack ownership and message exchange in separate tests. Keep per-hart memory locality separate as well.

When reproducing the two QEMU profiles, record the tool version, image digest and hart count with the observations. [Umicom Kernel hardware discovery](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/HARDWARE_DISCOVERY.md)
