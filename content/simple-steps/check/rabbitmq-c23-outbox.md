<!--
Umicom Bits2Banking
File: content/simple-steps/check/rabbitmq-c23-outbox.md

PURPOSE:
Give learners an additional practical case for RabbitMQ Outbox Practice in C23.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check an initial delivery and replay

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fake accepted event M18 enters the durable consumer first, then arrives once more with the same identity.

1. Trace both attempts through the lesson’s duplicate-control rule. Record each observed delivery independently.
2. Count accepted durable effects after the original and after the replay.

**Check your result.** The trace reports one durable effect both before and after the replay, with two observed deliveries.

[Step-by-step course guide](../course-guides/rabbitmq-c23-outbox.md) · [Full course](../../courses/rabbitmq-c23-outbox/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/rabbitmq-c23-outbox.md)
