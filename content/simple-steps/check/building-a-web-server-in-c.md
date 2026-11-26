<!--
Umicom Bits2Banking
File: content/simple-steps/check/building-a-web-server-in-c.md

PURPOSE:
Give learners an additional practical case for Building a Web Server in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check that parsing publishes only a complete request

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Trace two offline POST requests that each have one Host header and declare a three-byte body. The first body has bytes 41 00 42. The second is truncated to bytes 41 00.

1. Use the owned-storage lesson to trace the length check before testing the stored bytes. Start the output object with an earlier valid request in each case.
2. Write the acceptance status and the body observation that the caller may use after the operation.

**Check your result.** The three-byte message is admitted and stores A, zero, B in order with body length three. The truncated case is refused and leaves the earlier request intact.

[Step-by-step course guide](../course-guides/building-a-web-server-in-c.md) · [Full course](../../courses/building-a-web-server-in-c/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/building-a-web-server-in-c.md)
