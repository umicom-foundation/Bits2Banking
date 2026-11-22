<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/multikernel-systems/index.md

PURPOSE:
Guide beginning systems developers through execution domains and multikernel experiments.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material.
-->

# Multikernel systems and workload isolation

<p class="umicom-course-artwork"><span class="umicom-brand-mark"><img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom" width="180"></span> <a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="30"></a></p>

Learn how a system can run work in a process, a virtual machine or a native kernel instance. Follow one small request across an ownership boundary, handle a restart and decide what evidence would justify adding another kernel. The practical C23 exercise runs on a desktop host and requires CMake, Ninja and a suitable compiler.

1. [Choose an execution boundary](01-choose-an-execution-boundary.md).
2. [Tell startup from readiness](02-tell-startup-from-readiness.md).
3. [Design a small control message](03-design-a-small-control-message.md).
4. [Track buffer ownership](04-track-buffer-ownership.md).
5. [Recover a domain without losing evidence](05-recover-a-domain-without-losing-evidence.md).
6. [Qualify a kernel experiment](06-qualify-a-kernel-experiment.md).
7. [Check a core-owned memory range](07-check-a-core-owned-memory-range.md).
8. [Qualify a bootable release in stages](08-qualify-a-bootable-release-in-stages.md).
9. [Separate firmware inventory from hart entry](09-separate-firmware-inventory-from-hart-entry.md).


You should be able to read a small C program and explain what an operating system kernel does. Review [Learning C](../../../courses/learning-c/index.html) and [Introduction to Operating Systems](../../../courses/introduction-to-operating-systems/index.html) as needed. For the native implementation side, continue with [Umicom Kernel from Scratch](../../../courses/umicom-kernel-from-scratch/index.html).

Keep the complete Bits2Banking repository and select [the offline pack](../../../../learning-packs/multikernel-systems.json) to study in the Studio learning catalogue. The practical exercise covers host-side framing and validation. The recovery and multi-hart stages are source-reading and experiment-design exercises.
