<!--
Umicom Bits2Banking
File: content/simple-steps/practice/rabbitmq-c23-outbox.md

PURPOSE:
Give learners an additional practical case for RabbitMQ Outbox Practice in C23.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Place a record before an acknowledgement

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fictional message M9 carries one requested ledger effect.

1. Draw four rows for received, saved, committed and acknowledged. Add a failure between received and committed.
2. Trace a later redelivery of M9. Check the durable effect count and whether the sequence can acknowledge the retry.

**Check your result.** The acknowledgement belongs after the committed effect. The duplicate identity can be checked before a second effect is saved.

[Step-by-step course guide](../course-guides/rabbitmq-c23-outbox.md) · [Full course](../../courses/rabbitmq-c23-outbox/index.html) · [Practice by course](index.md)
