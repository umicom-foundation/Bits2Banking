<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-data-structures.md

PURPOSE:
Give learners an additional practical case for Learning Data Structures.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check when an empty queue means the work is finished

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice producer and consumer share an empty queue. One fixture marks the producer active and the other marks all production finished.

1. Read once from the empty queue in the active fixture and record the consumer's next state.
2. Read in the finished fixture and record whether the consumer can close its work.

**Check your result.** The active fixture reports that the consumer should wait. The finished fixture reports that there is no remaining work.

[Step-by-step course guide](../course-guides/learning-data-structures.md) · [Full course](../../courses/learning-data-structures/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-data-structures.md)
