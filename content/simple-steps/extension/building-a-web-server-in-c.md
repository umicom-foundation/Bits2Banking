<!--
Umicom Bits2Banking
File: content/simple-steps/extension/building-a-web-server-in-c.md

PURPOSE:
Give learners an additional practical case for Building a Web Server in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare the headers and body for HEAD

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

An offline trace represents a 200 response with the five-byte text ready. The router has explicit GET and HEAD entries for this path.

1. Use Recognise complete requests and honest results to write the Content-Length for each response.
2. Record the bytes sent after the header separator for each method.

**Check your result.** Both responses have Content-Length 5. GET carries ready after the separator. HEAD carries zero body bytes.

[Step-by-step course guide](../course-guides/building-a-web-server-in-c.md) · [Full course](../../courses/building-a-web-server-in-c/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/building-a-web-server-in-c.md)
