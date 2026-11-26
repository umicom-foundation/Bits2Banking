<!--
Umicom Bits2Banking
File: content/simple-steps/apply/building-linux-from-scratch.md

PURPOSE:
Give learners an additional practical case for Building Linux from Scratch Using C Code.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Sketch a starter root filesystem

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A future disposable Linux VM should start a small practice application and provide a configuration file for it. You are preparing a paper build plan.

1. Draw separate boxes for the compiled kernel, the toolchain sysroot and the guest root filesystem. Under the guest root list a program, its expected libraries and one configuration file.
2. Add the boot order through the first user-space process. Mark which machine builds the files and which environment would run them.

**Check your result.** The plan shows firmware, loader, kernel and first user-space process in order. It lists the application, libraries and configuration in the guest filesystem and target build inputs in the sysroot.

[Step-by-step course guide](../course-guides/building-linux-from-scratch.md) · [Full course](../../courses/building-linux-from-scratch/index.html) · [Small projects by course](index.md) · [First practice case](../practice/building-linux-from-scratch.md)
