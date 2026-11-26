<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/umicom-os-from-scratch.md

PURPOSE:
Provide practical first steps and a result to check for Umicom OS from Scratch.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Umicom OS from Scratch

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Find the startup entry and service configuration parser listed in the lesson. Mark where parsing ends and launch begins. [A system has several layers](../../courses/umicom-os-from-scratch/lessons/01-system-boundaries.html)
2. Build the hosted parser exercise. Check the displayed order of storage and display. [Build one real OS component](../../courses/umicom-os-from-scratch/lessons/02-build-the-parser.html)
3. Try the lesson’s invalid dependency example and check that the previous complete plan survives. [Plan startup before executing it](../../courses/umicom-os-from-scratch/lessons/03-service-dependencies.html)

**Check your result.** The service plan lists storage before the service that depends on it, and rejects an invalid plan before launch.

[Hands-on boot workshop](../boot-media/index.md) · [Foundation optical ISO](../boot-media/os-optical-iso.md) · [Foundation UEFI disk image](../boot-media/os-uefi-disk-image.md)

[Continue in the full course](../../courses/umicom-os-from-scratch/index.html) · [All course guides](index.md)
