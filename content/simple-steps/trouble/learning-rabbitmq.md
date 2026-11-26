<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-rabbitmq.md

PURPOSE:
Give learners an additional practical case for Learning RabbitMQ and Message Queues.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Find a routing key that misses its queue

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice direct exchange has a queue binding named venue.report. A message is published with key venue.reports.

1. Compare the two text keys in the routes lesson. Mark the exact point at which the last character differs.
2. Use the queue’s exact binding for the next paper trace. Keep both published keys in the observation sheet.

**Check your result.** The first key selects no listed binding. venue.report selects the one intended queue.

[Step-by-step course guide](../course-guides/learning-rabbitmq.md) · [Full course](../../courses/learning-rabbitmq/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-rabbitmq.md)
