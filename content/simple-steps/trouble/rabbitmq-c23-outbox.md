<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/rabbitmq-c23-outbox.md

PURPOSE:
Give learners an additional practical case for RabbitMQ Outbox Practice in C23.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find an acknowledgement before the effect is saved

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A paper trace acknowledges a synthetic record and then shows its database write failing.

1. Put acknowledgement and commit on separate timeline rows. Mark the durable evidence available when acknowledgement occurs.
2. Trace the course’s commit-first order using the same fictional message.

**Check your result.** The first timeline can lose the accepted effect. The corrected timeline has a durable commit before acknowledgement.

[Step-by-step course guide](../course-guides/rabbitmq-c23-outbox.md) · [Full course](../../courses/rabbitmq-c23-outbox/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/rabbitmq-c23-outbox.md)
