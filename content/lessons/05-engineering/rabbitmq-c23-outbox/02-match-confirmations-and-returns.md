<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/rabbitmq-c23-outbox/02-match-confirmations-and-returns.md

PURPOSE:
Track what happened to the specific outgoing event before marking its durable outbox row as sent.

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

# Match publisher confirmations and returned messages

[Course contents](index.md) · [Previous · Save the ledger entry and its outbox record together](01-save-the-ledger-and-outbox-together.md) · [Next · Commit the consumer effect before acknowledging delivery](03-commit-the-effect-before-acknowledging.md) · [Browser edition](../../../courses/rabbitmq-c23-outbox/lessons/02-match-confirmations-and-returns.html)

Track what happened to the specific outgoing event before marking its durable outbox row as sent.

## Decide which outcomes qualify

AMQP 0-9-1 publisher confirms say how the broker handled a publication from the publisher’s perspective. Publishing with mandatory routing lets the broker return an unroutable message. A returned mandatory message can also receive a confirm. RabbitMQ sends the return before its confirm, so account for both pieces of evidence for a single publication.

```c
return ledger_committed && evidence == SEND_CONFIRMED_ROUTABLE;
```

- Unknown after a disconnect. Leave the event pending for controlled retry.
- Negative acknowledgement. Keep the failure available for retry handling.
- Mandatory return. Record that no route accepted it and keep the row unsent.
- Positive confirm paired with the known routing outcome. Mark the committed row as sent.

## Inspect the same predicate in Assembly

Using Intel syntax, EAX contains the committed flag and EDX contains the result enum. The lab labels SEND_CONFIRMED_ROUTABLE as 3. The two comparisons produce booleans in CL and AL. The final AND writes the result in AL. This is a hand trace of the predicate.

```asm
test eax, eax
setne cl
cmp edx, 3
sete al
and al, cl
```

## Optional native practice

From the Bits2Banking checkout, open a Windows UCRT64 toolchain session. In PowerShell with the C23 compiler already on your path, compile the supplied files. Expect exit code 0 and the line shown below when you run the resulting training program. If the compiler is missing, use the paper trace first.

```powershell
Set-Location labs/native/service-practice/rabbitmq-outbox
gcc -std=c23 -Wall -Wextra -Werror main.c -o rabbitmq-outbox-rules.exe
.\rabbitmq-outbox-rules.exe
```

```text
outbox evidence checks ready
```

- [Read the complete native lab source](../../../labs/native/service-practice/rabbitmq-outbox/main.c)
- [RabbitMQ publishers and routing returns](https://www.rabbitmq.com/docs/publishers)

## Continue in another course

- [Applied native courses](../../../start/applied-native-courses.md)
- [Learning RabbitMQ and Message Queues](../../../courses/learning-rabbitmq/index.html)
- [MySQL Ledger Practice in C23](../../../courses/mysql-c23-ledger/index.html)

[Course contents](index.md) · [Previous · Save the ledger entry and its outbox record together](01-save-the-ledger-and-outbox-together.md) · [Next · Commit the consumer effect before acknowledging delivery](03-commit-the-effect-before-acknowledging.md) · [Browser edition](../../../courses/rabbitmq-c23-outbox/lessons/02-match-confirmations-and-returns.html)
