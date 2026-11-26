<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/rabbitmq-c23-outbox.md

PURPOSE:
Provide practical first steps and a result to check for RabbitMQ Outbox Practice in C23.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# RabbitMQ Outbox Practice in C23

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Draw a ledger row and its outbox record in the same database change. Mark what is available after a crash. [Save the ledger entry and its outbox record together](../../courses/rabbitmq-c23-outbox/lessons/01-save-the-ledger-and-outbox-together.html)
2. Trace one acknowledged publish and one returned message. Record which evidence the publisher can accept. [Match publisher confirmations and returned messages](../../courses/rabbitmq-c23-outbox/lessons/02-match-confirmations-and-returns.html)
3. Use the consumer exercise to place the durable commit before acknowledgement, then trace a repeat delivery. [Commit the consumer effect before acknowledging delivery](../../courses/rabbitmq-c23-outbox/lessons/03-commit-the-effect-before-acknowledging.html)

**Check your result.** One delivery produces one committed effect. The repeated delivery can be acknowledged without posting a second effect.

[Continue in the full course](../../courses/rabbitmq-c23-outbox/index.html) · [All course guides](index.md)
