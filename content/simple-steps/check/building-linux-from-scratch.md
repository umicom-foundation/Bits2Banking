<!--
Umicom Bits2Banking
File: content/simple-steps/check/building-linux-from-scratch.md

PURPOSE:
Give learners an additional practical case for Building Linux from Scratch Using C Code.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a guest root before starting the VM

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Two paper guest root trees contain the listed training application and its libraries. The educational kernel boot plan asks to launch /init. Only the first tree includes /init.

1. Locate the first user-space path in the boot plan. Check for that exact path in both printed target root trees.
2. Record whether each tree meets that preflight condition before any virtual launch.

**Check your result.** The first tree passes the /init presence check. The second reports missing /init and fails preflight.

[Step-by-step course guide](../course-guides/building-linux-from-scratch.md) · [Full course](../../courses/building-linux-from-scratch/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/building-linux-from-scratch.md)
