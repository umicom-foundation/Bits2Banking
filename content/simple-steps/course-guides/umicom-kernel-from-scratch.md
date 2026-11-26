<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/umicom-kernel-from-scratch.md

PURPOSE:
Provide practical first steps and a result to check for Umicom Kernel from Scratch.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Umicom Kernel from Scratch

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Follow the first-boot guest instructions. Record the image identity and the final boot marker from the emulator. [Understand your first boot](../../courses/umicom-kernel-from-scratch/lessons/understand-your-first-boot.html)
2. Open the native types and bounded console source. Find which length controls the read. [Read a native kernel without booting it](../../courses/umicom-kernel-from-scratch/lessons/01-native-kernel-and-host-models.html)
3. Use the supplied parser lab to compare a complete input with a truncated one and record the results separately. [A byte span is not a string](../../courses/umicom-kernel-from-scratch/lessons/02-bounded-input.html)

**Check your result.** The recorded guest output reaches the expected marker. The parser lab rejects a truncated input while keeping the earlier state.

[Hands-on boot workshop](../boot-media/index.md) · [Kernel RISC-V console](../boot-media/kernel-riscv-console.md) · [Kernel diagnostic ISO](../boot-media/kernel-diagnostic-iso.md)

[Continue in the full course](../../courses/umicom-kernel-from-scratch/index.html) · [All course guides](index.md)
