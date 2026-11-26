<!--
Umicom Bits2Banking
File: content/simple-steps/apply/building-a-web-server-in-c.md

PURPOSE:
Give learners an additional practical case for Building a Web Server in C.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Document who owns a local demo service

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A class needs a paper runbook for the Framework loopback demo that says which object owns the routes and when each is released.

1. Draw the service with its route handlers, the server that borrows it and the access policy value borrowed at the request gate.
2. Write the startup and shutdown sequence as a handoff card. Include what happens to the borrowed objects while one request is handled.

**Check your result.** The service, routes and access policy are alive before serving. Serving finishes before releasing the server, and the service remains alive until then.

[Step-by-step course guide](../course-guides/building-a-web-server-in-c.md) · [Full course](../../courses/building-a-web-server-in-c/index.html) · [Small projects by course](index.md) · [First practice case](../practice/building-a-web-server-in-c.md)
