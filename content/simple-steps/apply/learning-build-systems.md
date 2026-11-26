<!--
Umicom Bits2Banking
File: content/simple-steps/apply/learning-build-systems.md

PURPOSE:
Give learners an additional practical case for Learning Build Systems.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Build two tools from a shared object

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A stopwatch tool and a report tool both use time_format.o. Each tool also has a separate main object.

1. Draw a graph with the shared time_format.o producer and one executable target for each tool.
2. List the object inputs for both link steps and count how many times the shared object needs to be compiled for that build configuration.

**Check your result.** The graph has one producer for time_format.o and two link targets. Each link uses the shared object and its respective main object.

[Step-by-step course guide](../course-guides/learning-build-systems.md) · [Full course](../../courses/learning-build-systems/index.html) · [Small projects by course](index.md) · [First practice case](../practice/learning-build-systems.md)
