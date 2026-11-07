<!--
Umicom Bits2Banking
File: content/lessons/09-treasury-tms-calypso/introduction-to-treasury-management-systems/03-follow-evidence-through-a-payment.md

PURPOSE:
  Present "Follow evidence through a payment" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow evidence through a payment

A payment instruction, an approval and a completed transfer describe different events. This lab continues the existing treasury introduction using its equipment-payment example. You will build a small evidence table before considering a software implementation.

Source to open: `Umicom-Bits2Banking/content/lessons/09-treasury-tms-calypso/03-how-a-treasury-management-system-helps.md`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath 'content\lessons\09-treasury-tms-calypso\03-how-a-treasury-management-system-helps.md'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' 'content/lessons/09-treasury-tms-calypso/03-how-a-treasury-management-system-helps.md'
```

## Understand the idea

A status is a named stage in a workflow. Evidence explains why a record entered that stage. In the existing example, PAY-0042 represents a planned £900 equipment payment. An approval records an authorised decision; a sent instruction records a communication; settlement needs appropriate external evidence. Reconciliation compares related records and investigates differences. A stable identifier lets later observations refer to the same payment without creating a new obligation every time a message is received.

```text
PAY-0042
Draft -> Approved -> Sent -> confirmation reviewed -> Settled
                        |
                        +-> rejection recorded -> investigation
Duplicate observation: same evidence identity; not a second payment.
```

## Work through the lab

1. Read the existing source lesson and copy the payment identity, amount, currency and due date into a practice table. Add a payee and destination using invented classroom values only.
2. Create rows for Draft, Approved, Sent and Settled. For each row, write what event would justify entering it, who or what supplied the observation, and which earlier record it references.
3. Add a bank rejection after Sent. Keep the rejection reason and time. Do not replace it with Settled simply because a user clicked an approval button. Then add a duplicate copy of the same confirmation and decide how you would recognise that it is the same observation.
4. Write a proposed interface contract in plain language: accept a payment identity and new evidence, validate the allowed transition, preserve prior history, and return the resulting state or a specific refusal. Check the current Framework service before implementing a competing workflow in an application.

## Expected result

Your table should never claim settlement from approval alone. It should retain the rejected or duplicated observation in the investigation record while keeping the business state consistent. This is a teaching workflow, not a claim about a particular bank's integration protocol.

## If the result differs

If two rows disagree, compare identity, amount, currency, timing and the source of each observation. Do not resolve the conflict by deleting the inconvenient row. A missing confirmation is an unknown outcome until the relevant evidence is obtained.

## Explain it yourself

The application times out after sending a payment. Should it create a new payment identity and resend immediately?

<details>
<summary>Worked explanation</summary>

Not without investigating the original outcome and the provider's retry contract. The first instruction may already have been accepted. Stable identity, explicit unknown status and reconciliation help avoid an accidental duplicate.

</details>

## Use the idea in Umicom

The domain model and transition rules belong in shared Framework services; a Bank or TMS screen should present those states and collect authorised actions. This lesson extends the existing treasury material and makes no claim that a real bank transfer was performed.

[HTML edition](../../../courses/introduction-to-treasury-management-systems/lessons/03-follow-evidence-through-a-payment.html)

[Terminal and editor setup guide](../../learning-c/terminal-to-visual-studio.md)

[Previous lesson](02-status-approval-and-evidence.md) · [Course contents](index.md)
