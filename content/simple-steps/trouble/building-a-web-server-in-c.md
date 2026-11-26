<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/building-a-web-server-in-c.md

PURPOSE:
Give learners an additional practical case for Building a Web Server in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Wait for the rest of one request

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

In an offline HTTP framing trace, the headers declare a four-byte POST body, and the first receive supplies only the letters ab after the header separator.

1. Use Recognise complete requests and honest results to record how many body bytes are missing and which status applies.
2. Append cd in the trace and record when the complete body becomes eligible for the next processing step.

**Check your result.** The first receive is UMI_STATUS_BUSY with dispatch still pending. The assembled request then contains the exact four-byte body abcd.

[Step-by-step course guide](../course-guides/building-a-web-server-in-c.md) · [Full course](../../courses/building-a-web-server-in-c/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/building-a-web-server-in-c.md)
