<!--
Umicom Bits2Banking
File: content/simple-steps/extension/learning-spring-framework.md

PURPOSE:
Give learners an additional practical case for Learning Spring Framework.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Match a route and a request method

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local practice controller is configured to return a room summary on GET /rooms.

1. Use the route lesson to write a test or trace that sends GET /rooms and checks for the text Room summary.
2. Send or trace POST /rooms in the same fixture and count entries into the GET handler.

**Check your result.** The GET check observes Room summary. The POST request never enters the GET handler, whose total invocation count is one.

[Step-by-step course guide](../course-guides/learning-spring-framework.md) · [Full course](../../courses/learning-spring-framework/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/learning-spring-framework.md)
