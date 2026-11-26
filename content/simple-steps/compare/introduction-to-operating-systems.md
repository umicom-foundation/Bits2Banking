<!--
Umicom Bits2Banking
File: content/simple-steps/compare/introduction-to-operating-systems.md

PURPOSE:
Give learners an additional practical case for Introduction to Operating Systems.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare polling with one completion notification

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A device exercise supplies two timelines. In one timeline a CPU checks five times before seeing ready. In the other the device sends one ready notification after completing the same work.

1. Count the CPU reads in the polling trace and the ready notifications in the other trace.
2. Write down when the application can first receive the finished data in each timeline.

**Check your result.** The polling trace includes five checks. The notification trace includes one completion notification. Both make the data available only after the device is ready.

[Step-by-step course guide](../course-guides/introduction-to-operating-systems.md) · [Full course](../../courses/introduction-to-operating-systems/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/introduction-to-operating-systems.md)
