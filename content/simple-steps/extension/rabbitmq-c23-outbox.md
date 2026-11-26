<!--
Umicom Bits2Banking
File: content/simple-steps/extension/rabbitmq-c23-outbox.md

PURPOSE:
Give learners an additional practical case for RabbitMQ Outbox Practice in C23.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Record one message that needs a later retry

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fictional outbox stores R12 and R13. The course publisher confirms only R12.

1. Place the two identities and their observations in a table. Write which record is still awaiting an accepted publish result.
2. Replay the observation for R13 with a successful confirmation and compare both states before and after.

**Check your result.** R12 stays confirmed. Only R13 changes when matching confirmation arrives.

[Step-by-step course guide](../course-guides/rabbitmq-c23-outbox.md) · [Full course](../../courses/rabbitmq-c23-outbox/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/rabbitmq-c23-outbox.md)
