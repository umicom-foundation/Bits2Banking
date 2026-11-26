<!--
Umicom Bits2Banking
File: content/wiki/boot-media.md

PURPOSE:
Link an installer contributor to the media decision, native implementation and verification steps.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# OS and Kernel boot media

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Start by choosing the product. The standalone Umicom Kernel has its own artifact and machine contract. The current Umicom OS Foundation preview uses a Linux kernel and a small initial filesystem. Each choice has its own build, inspection and boot evidence.

1. Follow the [Setup Centre user guide](../umicom/setup-centre-boot-planning.md). Choose a specific product, target machine and output. Write down the expected artifact before you run a producer.
2. Use the [boot media steps](../simple-steps/boot-media/index.md) to find the matching artifact producer or review. Record the exact image digest and what its inspection actually checked.
3. If you change the Windows wizard, follow the [contributor workshop](../contributing/setup-centre/index.md). Keep the portable selection decision in Framework. Use the adapter for control state and visible handoffs.
4. Record the outcome for the exact boot profile. A diagnostic ISO file, a serial capture from a VM and a completed installation each answer a different question.

**Example.** You request a RISC-V Kernel guest. First check which type of ELF the QEMU board expects. If a report refers to a different file or architecture, keep that observation separate and inspect the correct artifact rather than editing the report.

[Verify a prebuilt RISC-V launch kit](../simple-steps/boot-media/verify-kernel-launch-kit.md) to check the system and recovery files before using the standalone QEMU guide.

[Contributor wiki](index.md)
