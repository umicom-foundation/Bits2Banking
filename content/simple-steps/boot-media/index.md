<!--
Umicom Bits2Banking
File: content/simple-steps/boot-media/index.md

PURPOSE:
Choose and qualify the correct Umicom Kernel or Umicom OS boot medium.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

# Umicom Kernel and Umicom OS boot media

Start with a virtual machine and keep the source files, output and captures in a folder you own. Each step identifies the artifact it produces and the claim its checks can support.

1. [Choose the target](choose-a-target.md). Match the project, processor, firmware and medium.
2. [Boot Umicom Kernel in RISC-V QEMU](kernel-riscv-console.md). Try the system and recovery consoles without attaching a disk.
3. [Build the Kernel x64 UEFI diagnostic](kernel-uefi-preflight.md). Identify the ELF and the EFI application that contains it.
4. [Create the Kernel diagnostic ISO](kernel-diagnostic-iso.md). Trace the EFI file through a FAT image and optical boot catalogue.
5. [Build and verify an OS Foundation bundle](os-foundation-bundle.md). Prepare the Linux kernel and initial filesystem.
6. [Boot the OS bundle directly](os-direct-boot.md). Compare normal and forced recovery results for the same bundle.
7. [Create an OS optical image](os-optical-iso.md). Produce the ISO in Linux and compare the three embedded payloads.
8. [Check a virtual optical boot](os-optical-vm.md). Match the declared firmware, exact ISO and serial evidence.
9. [Make an OS UEFI disk-image file](os-uefi-disk-image.md). Follow the EFI loader, kernel, archive and menu into a GPT partition.
10. [Rehearse a verified transfer](inspect-and-copy.md). Use two regular files before discussing USB devices.
11. [Decide whether a physical target is ready](physical-readiness.md). List the evidence still needed for a specific computer and medium.
12. [Review the evidence in C](evidence-lab.md). Run a small C23 exercise that distinguishes structural, virtual boot and hardware claims.

You can stop after any step. Keep the result from that step and choose the next one that fits your target. A developer with only a Windows computer can do the Kernel virtual console lesson, file-copy exercise and C evidence lab.

[Kernel course guide](../course-guides/umicom-kernel-from-scratch.md) · [OS course guide](../course-guides/umicom-os-from-scratch.md) · [Learning in Simple Steps](../index.md)
