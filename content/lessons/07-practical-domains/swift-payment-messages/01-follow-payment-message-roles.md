<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/swift-payment-messages/01-follow-payment-message-roles.md

PURPOSE:
Identify who sends the instruction, status and statement in a fictional cross-border flow.

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

# Follow the Payment and Message Roles

[Course contents](index.md) · [Next lesson · Normalize Message Evidence for Review](02-normalize-message-evidence.md)

Identify who sends the instruction, status and statement in a fictional cross-border flow.

## Follow the story before the XML

Imagine that Cedar Bank receives a request from one of its fictional customers to send USD 125.00 to a customer of Birch Bank. Cedar's processing system records an instruction. A messaging network can carry that instruction to a financial institution involved in the transfer. Settlement is the completion of the transfer of funds according to the relevant arrangement. Reconciliation compares an independent record of what happened with the instruction your system recorded.

Swift provides financial messaging services. ISO 20022 defines standardized message models. Swift's Cross-Border Payments and Reporting Plus usage guidelines, known as CBPR+, specify how selected ISO 20022 messages are used for that market practice.

## Classify the evidence

- pacs.008 is a financial-institution-to-financial-institution customer credit transfer message family. It can carry a customer credit transfer instruction.
- pacs.002 is a financial-institution-to-financial-institution payment status report family. Interpret a status code in the relevant profile and correlate the referenced instruction.
- camt.053 is a statement message family used in cash management reporting. A matched entry can support reconciliation under your own accounting rules.

Legacy training material may refer to MT 103, the historical Swift MT customer credit transfer message. A mapping needs the actual message version and profile, exact field semantics and trusted migration rules. The examples use the family identifiers alone, so start with the official catalogue and Swift usage guide when comparing specific schemas.

## Trace the classroom sequence

1. Write P-201, USD and 12,500 cents on one card. Label it instruction.
2. Write P-201 and accepted on another card. Label it the local interpretation of status. Keep the instruction recorded as accepted pending reconciliation.
3. Add a matched statement record for P-201 and 12,500 cents. Identify this as a separate piece of evidence. If the amount is 12,499, place the case in review.

- [Swift ISO 20022 standards and CBPR+ usage guidelines](https://www.swift.com/iso-20022-standards)
- [ISO 20022 message catalogue](https://www.iso20022.org/iso-20022-message-definitions)
- [Swift payments instruction scope and migration roadmap](https://www.swift.com/sites/default/files/files/cbpr-phase2_roadmap_detailed.pdf)

[Browser edition](../../../courses/swift-payment-messages/lessons/01-follow-payment-message-roles.html)

