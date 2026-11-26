<!--
Umicom Bits2Banking
File: content/simple-steps/apply/rabbitmq-c23-outbox.md

PURPOSE:
Give learners an additional practical case for RabbitMQ Outbox Practice in C23.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Document a replay of one practice event

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fictional outbox has one event for an accepted payment. The sender sees a temporary failure before a later successful confirmation.

1. Write the event ID, durable record and both observations. Follow the publisher and consumer traces in the course.
2. Produce a short report of how many publish observations occurred and how many effects were accepted.

**Check your result.** There are two publish observations for one retained event. The exercise accepts one durable payment effect.

[Step-by-step course guide](../course-guides/rabbitmq-c23-outbox.md) · [Full course](../../courses/rabbitmq-c23-outbox/index.html) · [Small projects by course](index.md) · [First practice case](../practice/rabbitmq-c23-outbox.md)
