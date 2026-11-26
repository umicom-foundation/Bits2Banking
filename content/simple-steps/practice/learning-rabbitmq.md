<!--
Umicom Bits2Banking
File: content/simple-steps/practice/learning-rabbitmq.md

PURPOSE:
Give learners an additional practical case for Learning RabbitMQ and Message Queues.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep deliveries and effects separate

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A disposable queue exercise has one practice message M27. The local consumer receives it twice.

1. Record each delivery attempt under the same message ID. Write the acceptance condition before acknowledging.
2. Use the lesson’s local examples or a paper trace. Mark whether one or two independent effects should be saved.

**Check your result.** Two deliveries can be recorded for M27. One durable accepted effect remains when duplicate processing is prevented.

[Step-by-step course guide](../course-guides/learning-rabbitmq.md) · [Full course](../../courses/learning-rabbitmq/index.html) · [Practice by course](index.md)
