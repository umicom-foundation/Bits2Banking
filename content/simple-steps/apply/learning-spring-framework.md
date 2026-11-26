<!--
Umicom Bits2Banking
File: content/simple-steps/apply/learning-spring-framework.md

PURPOSE:
Give learners an additional practical case for Learning Spring Framework.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep course selection rules out of a request handler

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A scratch portal needs GET /open-rooms to report the number of open rooms. The training data marks Gallery and Elm as open and Ash as closed.

1. Use the request lesson to draw the controller mapping, and use the supplied service pattern to place the open-room counting rule behind one service call.
2. Trace the three records through that service before the handler formats its count. Check that the handler never reads the room list directly.

**Check your result.** The service counts two open rooms. The short handler returns Open rooms 2.

[Step-by-step course guide](../course-guides/learning-spring-framework.md) · [Full course](../../courses/learning-spring-framework/index.html) · [Small projects by course](index.md) · [First practice case](../practice/learning-spring-framework.md)
