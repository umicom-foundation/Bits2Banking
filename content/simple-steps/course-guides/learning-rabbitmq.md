<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/learning-rabbitmq.md

PURPOSE:
Provide practical first steps and a result to check for Learning RabbitMQ and Message Queues.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Learning RabbitMQ and Message Queues

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Draw an interface, a queue and a worker. Show where the worker records the result of a request. [Understand messages, queues and consumers](../../courses/learning-rabbitmq/lessons/01-messages-producers-and-consumers.html)
2. Open the local message-retry lab. Follow the two record calls with the key `export-7`. [Understand messages, queues and consumers](../../courses/learning-rabbitmq/lessons/01-messages-producers-and-consumers.html)
3. Build and run the local C example using the lesson's SDK commands. Record its retry and lease results. [Understand messages, queues and consumers](../../courses/learning-rabbitmq/lessons/01-messages-producers-and-consumers.html)

**Check your result.** The repeated key leaves `report prepared` as the result, and the lease is owned at 119 and expired at 120.

[Continue in the full course](../../courses/learning-rabbitmq/index.html) · [All course guides](index.md)
