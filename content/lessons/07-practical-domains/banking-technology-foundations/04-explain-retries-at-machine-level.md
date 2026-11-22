<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/banking-technology-foundations/04-explain-retries-at-machine-level.md

PURPOSE:
Read how C and an x86-64 register comparison can express the same small decision.

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

# Keep a payment retry from changing the balance twice

[Course contents](index.md) · [Previous · Reconcile amounts by reference and currency](03-reconcile-with-stable-identities.md) · [Browser edition](../../../courses/banking-technology-foundations/lessons/04-explain-retries-at-machine-level.html)

Read how C and an x86-64 register comparison can express the same small decision.

## Use one identity throughout a retry

When a response is lost, senders may repeat a request with its original reference. The receiver can return the accepted result it already recorded if the identity and normalized request agree. A conflict needs a separate result and review. A reply merely saying “received” can be insufficient evidence of completion.

```text
FIND prior accepted row with request reference
IF none: validate and consider posting
IF found and fields equal: return original result
IF found and fields differ: report conflict
```

## Read two machine instructions

In the following x86-64 Intel-syntax excerpt, registers are small fast storage locations. Assume RAX and RDX already hold the prior and requested amounts after the other fields were checked. This is a teaching fragment inside a larger routine.

```asm
cmp rax, rdx
jne amount_conflict
```

The CPU compares the two stored numbers. Its conditional jump goes to the mismatch path when their bits represent different amounts. The surrounding C program owns the rows, capacity, identity and result.

## Try it

Trace requests P71 with 600 twice, then P71 with 650. The results are first submission, same replay, conflict. Follow the bank application course to see these decisions tested against the same checked ledger.

- [Build a Banking Application in C](../../../courses/build-a-bank-application-in-c/index.html)
- [Learning x86 Assembly](../../../courses/learning-x86-assembly/index.html)

## Continue in another course

- [Bookkeeping from Your First Entry](../../../courses/bookkeeping-from-first-entry/index.html)
- [Build a Banking Application in C](../../../courses/build-a-bank-application-in-c/index.html)
- [Open Banking account access](../../../courses/open-banking-account-access/index.html)
- [Swift payment messages](../../../courses/swift-payment-messages/index.html)

[Course contents](index.md) · [Previous · Reconcile amounts by reference and currency](03-reconcile-with-stable-identities.md) · [Browser edition](../../../courses/banking-technology-foundations/lessons/04-explain-retries-at-machine-level.html)
