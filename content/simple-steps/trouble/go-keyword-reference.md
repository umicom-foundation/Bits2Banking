<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/go-keyword-reference.md

PURPOSE:
Give learners an additional practical case for Go Keywords for Beginners.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Spot the last value from a closed channel

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local Go exercise buffers 8 and 13 on an integer channel, then closes it.

1. Read from the channel three times and capture both the value and the receive flag each time.
2. Use the receive flag to decide which reads should count as work.

**Check your result.** The reads are 8 with true, 13 with true, and 0 with false. Exactly two reads count as work.

[Step-by-step course guide](../course-guides/go-keyword-reference.md) · [Full course](../../courses/go-keyword-reference/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/go-keyword-reference.md)
