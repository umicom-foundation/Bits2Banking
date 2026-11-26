<!--
Umicom Bits2Banking
File: content/simple-steps/check/learning-rabbitmq.md

PURPOSE:
Give learners an additional practical case for Learning RabbitMQ and Message Queues.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check an acquisition just before and at its deadline

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A deterministic local worker acquired message 42 with deadline 120. Both test traces begin with the same acquired state.

1. Use the lease deadline lesson to trace an ownership check at clock value 119 without advancing the fixture elsewhere.
2. Reset the fixture and check ownership at clock value 120. Record which outcomes allow the work item to stay current.

**Check your result.** The check at 119 finds the ticket current. At 120 it is expired and the trace accepts no operation based on the expired ownership.

[Step-by-step course guide](../course-guides/learning-rabbitmq.md) · [Full course](../../courses/learning-rabbitmq/index.html) · [Acceptance checks by course](index.md) · [First practice case](../practice/learning-rabbitmq.md)
