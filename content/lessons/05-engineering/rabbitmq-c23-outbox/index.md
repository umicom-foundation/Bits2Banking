<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/rabbitmq-c23-outbox/index.md

PURPOSE:
Follow one durable message from a synthetic ledger, distinguish publisher evidence from consumer evidence and practise a redelivery workflow.

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

# RabbitMQ Outbox Practice in C23

[Learning pathways](../../../start/connected-learning.md)

Follow one durable message from a synthetic ledger, distinguish publisher evidence from consumer evidence and practise a redelivery workflow.

Start with the invented data and trace the steps on paper. Optional compiler, SDK and adapter steps are for your own practice environment. The C state model has no broker, SDK, or network dependency. The practical discussion assumes AMQP 0-9-1.

## Lessons in order

- [Save the ledger entry and its outbox record together](01-save-the-ledger-and-outbox-together.md)
- [Match publisher confirmations and returned messages](02-match-confirmations-and-returns.md)
- [Commit the consumer effect before acknowledging delivery](03-commit-the-effect-before-acknowledging.md)

## Continue in another course

- [Applied native courses](../../../start/applied-native-courses.md)
- [Learning RabbitMQ and Message Queues](../../../courses/learning-rabbitmq/index.html)
- [MySQL Ledger Practice in C23](../../../courses/mysql-c23-ledger/index.html)

[Learning pathways](../../../start/connected-learning.md)
