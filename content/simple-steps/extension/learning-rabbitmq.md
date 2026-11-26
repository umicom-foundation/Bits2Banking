<!--
Umicom Bits2Banking
File: content/simple-steps/extension/learning-rabbitmq.md

PURPOSE:
Give learners an additional practical case for Learning RabbitMQ and Message Queues.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Keep separate tickets for two messages

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice worker owns message 41 and message 42 at the same time. Each work item has a copy of its own current ticket.

1. Use the delivery-ticket lesson to put each message number and generation into its corresponding work item.
2. Trace a release using the ticket for 41. Then check the ownership of 42 using the second ticket.

**Check your result.** Message 41 is released. The check for message 42 still finds it owned by the worker.

[Step-by-step course guide](../course-guides/learning-rabbitmq.md) · [Full course](../../courses/learning-rabbitmq/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/learning-rabbitmq.md)
