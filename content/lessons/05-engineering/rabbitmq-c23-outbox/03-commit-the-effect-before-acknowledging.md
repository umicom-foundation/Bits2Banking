<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/rabbitmq-c23-outbox/03-commit-the-effect-before-acknowledging.md

PURPOSE:
Measure the effect of receiving OUT-42 twice and let durable state determine whether work already applied.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom">
</picture>

# Commit the consumer effect before acknowledging delivery

[Course contents](index.md) · [Previous · Match publisher confirmations and returned messages](02-match-confirmations-and-returns.md) · [Browser edition](../../../courses/rabbitmq-c23-outbox/lessons/03-commit-the-effect-before-acknowledging.html)

Measure the effect of receiving OUT-42 twice and let durable state determine whether work already applied.

## Follow a small replay scenario

The consumer records the stable event ID in a durable uniqueness table and applies the training effect in the same transaction. After commit, it acknowledges this delivery on the receiving channel. Use the result of the uniqueness check to distinguish a known replay from a new effect.

```text
delivery OUT-42 -> commit event ID and effect -> crash before acknowledging
redelivery OUT-42 -> see committed event ID -> avoid repeating effect -> acknowledge
```

Trace a second failure, this time before commit. The receipt has no committed effect or event marker. It may be handled as new when the next delivery arrives. The acknowledge attempt and the record of business work remain distinct.

## Apply this to Umicom Bank and TMS

Use one synthetic statement event and an independent expected total. Verify a pre-commit failure, a post-commit failure, a routing failure and successful replay. Keep the native predicate local during the exercise. Use the existing Framework reliability exercises before qualifying an actual relay.

- [RabbitMQ consumer acknowledgements and publisher confirms](https://www.rabbitmq.com/docs/confirms)
- [RabbitMQ consumers](https://www.rabbitmq.com/docs/consumers)
- [Learning RabbitMQ and Message Queues](../../../courses/learning-rabbitmq/index.html)

## Continue in another course

- [Applied native courses](../../../start/applied-native-courses.md)
- [Learning RabbitMQ and Message Queues](../../../courses/learning-rabbitmq/index.html)
- [MySQL Ledger Practice in C23](../../../courses/mysql-c23-ledger/index.html)

[Course contents](index.md) · [Previous · Match publisher confirmations and returned messages](02-match-confirmations-and-returns.md) · [Browser edition](../../../courses/rabbitmq-c23-outbox/lessons/03-commit-the-effect-before-acknowledging.html)
