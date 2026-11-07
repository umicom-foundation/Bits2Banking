<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-java/04-check-a-ledger-invariant.md

PURPOSE:
  Present "Check a ledger invariant" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a ledger invariant

An invariant is a rule expected to remain true while a program works. The Java ledger example checks one such rule: total debits equal total credits. We will find what that check proves and what additional validation it needs.

Source to open: `Umicom-Bits2Banking/content/labs/java-ledger/LedgerDemo.java`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath 'content\labs\java-ledger\LedgerDemo.java'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' 'content/labs/java-ledger/LedgerDemo.java'
```

## Understand the idea

A Posting record groups an account name, debit and credit. BigDecimal represents decimal values with explicit precision and scale; adding values produces another value. IsBalanced accumulates both sides and uses compareTo so numerical equality does not depend on whether a value was written as 25.1 or 25.10. Arithmetic balance is only one part of a valid journal.

```text
postings → sum debit / sum credit → numerical equality
                  ↑
       account and currency admission are separate checks
```

## Work through the lab

1. Read the two postings in main. Write debit and credit columns on paper and add them independently.
2. Change only one credit in your paper example from 25.10 to 25.09. Compute the difference before predicting the result.
3. Consider an empty list, two negative matching amounts, and an unknown account name. Follow IsBalanced to see which cases it can reject.
4. Write a validation checklist for a future adapter: recognised accounts, one currency or an explicit conversion, permitted signs, nonempty journal and balanced totals. Keep this separate from the simple addition rule.

## Expected result

The supplied example balances at 25.10 on each side. The changed-credit example does not. The addition loop alone can accept an empty list because both totals begin at zero.

## If the result differs

If a learner uses binary floating-point for decimal money, small representation differences may confuse comparisons. Retain BigDecimal and inspect how input values are constructed. A balanced result still requires business validation.

## Explain it yourself

Could two equal but incorrectly assigned amounts pass IsBalanced?

<details>
<summary>Worked explanation</summary>

Yes. Equal totals do not prove the right accounts were used, that a payment occurred, or that an entry was authorised. Tests should cover each rule independently and then the full posting workflow.

</details>

## Use the idea in Umicom

Record inputs, expected outputs and refusal cases before extending the example. Reusable production behaviour belongs in Umicom Framework; applications translate user actions and show the service result. A traced example explains a contract. It does not establish that every application using a similar idea has been integrated or tested.

[HTML edition](../../../courses/learning-java/lessons/04-check-a-ledger-invariant.html)

[Terminal and editor setup guide](../../learning-c/terminal-to-visual-studio.md)

[Previous lesson](03-values-methods-and-checks.md) · [Course contents](index.md)

[Next lesson: Compare a decimal value and its representation](05-compare-value-and-representation.md)
