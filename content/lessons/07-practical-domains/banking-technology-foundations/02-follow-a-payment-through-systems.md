<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/banking-technology-foundations/02-follow-a-payment-through-systems.md

PURPOSE:
Map what happens after a person asks to send money and which system owns each result.

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

# Follow an instruction from entry to settlement

[Course contents](index.md) · [Previous · Read an account, its ledger and its holds](01-read-a-bank-account.md) · [Next · Reconcile amounts by reference and currency](03-reconcile-with-stable-identities.md) · [Browser edition](../../../courses/banking-technology-foundations/lessons/02-follow-a-payment-through-systems.html)

Map what happens after a person asks to send money and which system owns each result.

## Trace the roles

A payment instruction says who should pay, who should receive and how much. The sending system may validate and record the request before a clearing step exchanges and checks payment information. Settlement is the discharge of the obligations by transferring funds under the system’s rules. The confirmation or statement provides evidence to compare with the original instruction.

```text
REQUEST received
CHECK fields and permissions for this system
RECORD a local reference and status
EXCHANGE instruction through the selected route
RECONCILE the returned evidence
```

The real arrangement depends on the payment system. For example, Fedwire Funds is a real-time gross settlement system. A request accepted by a local training screen does not prove the external transfer settled.

## Try a paper test

Label local reference P71 as accepted. Leave the clearing and settlement boxes blank. If someone asks whether it settled, answer “we have no settlement evidence yet.” A small native TMS status panel can show the most recent evidence alongside the request.

- [BIS glossary of payments and settlement](https://www.bis.org/committees/cpmi/glossary)
- [Federal Reserve description of Fedwire Funds](https://www.federalreserve.gov/paymentsystems/fedfunds_about.htm)

## Continue in another course

- [Bookkeeping from Your First Entry](../../../courses/bookkeeping-from-first-entry/index.html)
- [Build a Banking Application in C](../../../courses/build-a-bank-application-in-c/index.html)
- [Open Banking account access](../../../courses/open-banking-account-access/index.html)
- [Swift payment messages](../../../courses/swift-payment-messages/index.html)

[Course contents](index.md) · [Previous · Read an account, its ledger and its holds](01-read-a-bank-account.md) · [Next · Reconcile amounts by reference and currency](03-reconcile-with-stable-identities.md) · [Browser edition](../../../courses/banking-technology-foundations/lessons/02-follow-a-payment-through-systems.html)
