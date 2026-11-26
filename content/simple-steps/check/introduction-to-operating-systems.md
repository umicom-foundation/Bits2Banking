<!--
Umicom Bits2Banking
File: content/simple-steps/check/introduction-to-operating-systems.md

PURPOSE:
Give learners an additional practical case for Introduction to Operating Systems.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check which process owns a private region

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A paper operating-system model gives task A an address range from 100 through 109. The fixture grants task B no access to that region.

1. Request address 106 on behalf of task A and record the simulated permission result.
2. Make the same request on behalf of task B and record the independent result.

**Check your result.** Task A's read request is permitted. Task B's read request is refused by the model's ownership rule.

[Step-by-step course guide](../course-guides/introduction-to-operating-systems.md) · [Full course](../../courses/introduction-to-operating-systems/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/introduction-to-operating-systems.md)
