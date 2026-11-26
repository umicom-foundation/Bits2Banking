<!--
Umicom Bits2Banking
File: content/simple-steps/extension/learning-build-systems.md

PURPOSE:
Give learners an additional practical case for Learning Build Systems.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Give a generated header an explicit build dependency

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice compiler step includes generated settings.h. On a clean build the file is produced by a separate generator step.

1. Add a build dependency from the consuming object to the generated header and record the generator as its producer.
2. Build a clean exercise copy and read the order of the two actions in the build output.

**Check your result.** The generator writes settings.h before the compiler builds the consuming object.

[Step-by-step course guide](../course-guides/learning-build-systems.md) · [Full course](../../courses/learning-build-systems/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/learning-build-systems.md)
