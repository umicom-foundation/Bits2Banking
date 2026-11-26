<!--
Umicom Bits2Banking
File: content/simple-steps/apply/learning-rabbitmq.md

PURPOSE:
Give learners an additional practical case for Learning RabbitMQ and Message Queues.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Sketch a queue for work and a queue for review

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A local practice plan has a report job destined for a worker and an invalid job destined for manual review after its status is known.

1. Draw the worker queue and a separate local review queue. Use the course’s routing and acknowledgement lessons to label their purpose.
2. Trace one valid job to a recorded result and one invalid job to a review entry, before acknowledging each respective delivery.

**Check your result.** The trace contains one accepted report and one review entry. Both acknowledgements follow their recorded outcomes.

[Step-by-step course guide](../course-guides/learning-rabbitmq.md) · [Full course](../../courses/learning-rabbitmq/index.html) · [Small projects by course](index.md) · [First practice case](../practice/learning-rabbitmq.md)
