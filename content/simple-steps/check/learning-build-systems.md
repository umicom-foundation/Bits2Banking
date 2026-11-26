<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-build-systems.md

PURPOSE:
Give learners an additional practical case for Learning Build Systems.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check what rebuilds after two different changes

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

An exercise target compiles counter.c to counter.o and then links an executable. The documentation file is outside that target's dependency graph.

1. Change only the documentation file and record whether compiling or linking is requested by the build.
2. In a separate up-to-date fixture, change counter.c and read the next compile and link entries.

**Check your result.** The documentation edit schedules neither step. The source edit recompiles counter.o and relinks its executable.

[Step-by-step course guide](../course-guides/learning-build-systems.md) · [Full course](../../courses/learning-build-systems/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-build-systems.md)
