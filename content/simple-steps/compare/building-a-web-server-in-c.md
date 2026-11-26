<!--
Umicom Bits2Banking
File: content/simple-steps/compare/building-a-web-server-in-c.md

PURPOSE:
Give learners an additional practical case for Building a Web Server in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a textual port with its published number

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

The Framework loopback demo receives 01024 as one port choice and 01023 as another. Read the parser on paper and leave sockets closed.

1. Trace the decimal accumulator character by character for both choices.
2. Apply the accepted range at the end. Give the published output variable a starting value of 8765 in each trace.

**Check your result.** 01024 passes and publishes port 1024. 01023 is below the minimum and leaves the output at 8765.

[Step-by-step course guide](../course-guides/building-a-web-server-in-c.md) · [Full course](../../courses/building-a-web-server-in-c/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/building-a-web-server-in-c.md)
