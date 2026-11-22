<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/banking-technology-foundations/01-read-a-bank-account.md

PURPOSE:
Use one pocket-money example to distinguish a recorded balance from money available to spend.

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

# Read an account, its ledger and its holds

[Course contents](index.md) · [Next · Follow an instruction from entry to settlement](02-follow-a-payment-through-systems.md) · [Browser edition](../../../courses/banking-technology-foundations/lessons/01-read-a-bank-account.html)

Use one pocket-money example to distinguish a recorded balance from money available to spend.

## Start with a small record

A bank account is a named record of amounts. A ledger records the events that change those amounts. A hold reserves part of a balance for a possible payment. In this exercise a posted credit increases your savings and a new hold reduces what is available.

- Opening balance 3,000 cents.
- Posted credit 600 cents brings the ledger balance to 3,600.
- An active hold of 900 leaves 2,700 cents available.
- Removing the hold restores the available amount to 3,600 while the ledger balance stays at 3,600.

## Try the rule in FreeBASIC

```freebasic
Dim As LongInt posted = 3600
Dim As LongInt held = 900
Print LTrim(Str(posted - held))
```

Copy the three lines to `available.bas` in a practice folder. Use `fbc available.bas` with FreeBASIC installed. The numerical output is 2700. This teaching rule models one hold against one balance in the same currency.

## Check it yourself

Change the hold to 500. The available balance is 3,100 cents. If a form shows only 3,600, ask which balance it intends to display. Build the two labels into a synthetic Umicom Bank account view.

## Continue in another course

- [Bookkeeping from Your First Entry](../../../courses/bookkeeping-from-first-entry/index.html)
- [Build a Banking Application in C](../../../courses/build-a-bank-application-in-c/index.html)
- [Open Banking account access](../../../courses/open-banking-account-access/index.html)
- [Swift payment messages](../../../courses/swift-payment-messages/index.html)

[Course contents](index.md) · [Next · Follow an instruction from entry to settlement](02-follow-a-payment-through-systems.md) · [Browser edition](../../../courses/banking-technology-foundations/lessons/01-read-a-bank-account.html)
