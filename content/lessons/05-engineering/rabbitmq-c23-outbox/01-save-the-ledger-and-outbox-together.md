<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/rabbitmq-c23-outbox/01-save-the-ledger-and-outbox-together.md

PURPOSE:
Use a durable send-intent record to bridge the gap between a local commit and a broker publish.

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

# Save the ledger entry and its outbox record together

[Course contents](index.md) · [Next · Match publisher confirmations and returned messages](02-match-confirmations-and-returns.md) · [Browser edition](../../../courses/rabbitmq-c23-outbox/lessons/01-save-the-ledger-and-outbox-together.html)

Use a durable send-intent record to bridge the gap between a local commit and a broker publish.

## Trace one record through a crash

A transaction groups database changes. Commit makes the group durable. An outbox is a database table of messages that still need delivery. Save entry E-42 and its outbox event OUT-42 inside the same database transaction. The relay reads only committed outbox rows.

```text
begin transaction
  insert training ledger entry E-42
  insert outbox event OUT-42 with state pending
commit
relay reads pending OUT-42
```

If the transaction rolls back, neither row is visible to the relay. If the process crashes after commit and before publish, the row remains pending for the next relay. Paper-check both cases before wiring the actual database.

A publisher is the process that sends a message to an exchange. RabbitMQ routes a published message to queues using bindings. The relay preserves OUT-42 as the stable event identifier. The broker delivery tag is channel-scoped protocol evidence and serves a different purpose.

- [RabbitMQ consumer acknowledgements and publisher confirms](https://www.rabbitmq.com/docs/confirms)
- [SQL Statement Reconciliation](../../../courses/sql-statement-reconciliation/index.html)

## Continue in another course

- [Applied native courses](../../../start/applied-native-courses.md)
- [Learning RabbitMQ and Message Queues](../../../courses/learning-rabbitmq/index.html)
- [MySQL Ledger Practice in C23](../../../courses/mysql-c23-ledger/index.html)

[Course contents](index.md) · [Next · Match publisher confirmations and returned messages](02-match-confirmations-and-returns.md) · [Browser edition](../../../courses/rabbitmq-c23-outbox/lessons/01-save-the-ledger-and-outbox-together.html)
