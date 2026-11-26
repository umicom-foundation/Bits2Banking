<!--
Umicom Bits2Banking
File: content/simple-steps/compare/learning-rabbitmq.md

PURPOSE:
Give learners an additional practical case for Learning RabbitMQ and Message Queues.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare retrying a job with holding it for review

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A fictional report worker can face a temporary local file read error or a record that violates its format rule.

1. Use the recovery lesson to map the first outcome to one planned retry and the second to a review record for this exercise.
2. Write down what remains visible for each job and when a worker can record a completed effect.

**Check your result.** The read error schedules one retry and records no completed effect. The invalid record creates one review entry and no completed effect.

[Step-by-step course guide](../course-guides/learning-rabbitmq.md) · [Full course](../../courses/learning-rabbitmq/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/learning-rabbitmq.md)
