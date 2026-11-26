<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/multikernel-systems.md

PURPOSE:
Provide practical first steps and a result to check for Multikernel systems and workload isolation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Multikernel systems and workload isolation

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Choose an editor and an image worker. Write what needs to stay available if each one stops. [Choose an execution boundary](../../courses/multikernel-systems/lessons/01-choose-an-execution-boundary.html)
2. Draw one row for worker generation 7 and one for generation 8. Mark the replacement as starting. [Tell startup from readiness](../../courses/multikernel-systems/lessons/02-tell-startup-from-readiness.html)
3. Trace a late reply from the old worker through the control-message check, then record the signal that makes the current worker ready. [Design a small control message](../../courses/multikernel-systems/lessons/03-design-a-small-control-message.html)

**Check your result.** A reply from generation 7 leaves generation 8 in its starting state. Readiness comes from the current worker.

[Continue in the full course](../../courses/multikernel-systems/index.html) · [All course guides](index.md)
