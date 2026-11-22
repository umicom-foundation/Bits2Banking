<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/swift-payment-messages/02-normalize-message-evidence.md

PURPOSE:
Link local evidence by a known reference, currency and amount before changing a payment view.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom Foundation" width="220">
</picture>

# Normalize Message Evidence for Review

[Course contents](index.md) · [Previous lesson · Follow the Payment and Message Roles](01-follow-payment-message-roles.md) · [Next lesson · Apply Payment Evidence in C23](03-apply-payment-evidence-in-c.md)

Link local evidence by a known reference, currency and amount before changing a payment view.

## Read three local records

These compact records belong to the classroom application. ISO 20022 schemas have their own envelopes, versions and element names. The references below represent an adapter's local correlation result. A status report may refer to the original instruction without carrying the amount in its own payload.

~~~text
instruction    | P-201 | USD | 12500 | recorded
status-report  | P-201 | USD | 12500 | accepted in this exercise
statement-match| P-201 | USD | 12500 | reconciled evidence
~~~

A version-aware adapter can preserve the original message identity, validated profile and correlation reference, then hand a smaller candidate to an internal service. The service evaluates it consistently whether the source was a sample file or an approved provider. Carry currency everywhere you compare a monetary amount.

## Practise the hand-off

1. Draw boxes for message receipt, business status and settlement review. Write the rule that connects each pair.
2. Repeat the status-report row. Keep the same instruction and view status.
3. Replace P-201 with P-202 on the statement. Record an unmatched case. In a real review console, preserve both source identities and avoid assigning the other receipt to P-201.

## Relate the workshop to Umicom Bank

The Bank application's ledger has its own debit and credit records. Its payment review can expose a pending reconciliation state. A TMS cash view can show matched cash evidence separately from a deal confirmation. For FpML deal terms, follow the treasury course.

- [FpML for Treasury and Trade Confirmation](../../../courses/fpml-for-treasury/index.html)
- [Bookkeeping from First Entry](../../../courses/bookkeeping-from-first-entry/index.html)
- [Swift ISO 20022 standards and CBPR+ usage guidelines](https://www.swift.com/iso-20022-standards)

[Browser edition](../../../courses/swift-payment-messages/lessons/02-normalize-message-evidence.html)

