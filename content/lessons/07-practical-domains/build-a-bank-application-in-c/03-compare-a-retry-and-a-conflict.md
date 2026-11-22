<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/build-a-bank-application-in-c/03-compare-a-retry-and-a-conflict.md

PURPOSE:
Use the original request fields to distinguish an identical repeat from a collision.

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

# Compare a retry with a changed request

[Course contents](index.md) · [Previous · Build one checked posting](02-build-a-checked-posting.md) · [Next · Design a durable journal and statement view](04-design-a-durable-statement.md) · [Browser edition](../../../courses/build-a-bank-application-in-c/lessons/03-compare-a-retry-and-a-conflict.html)

Use the original request fields to distinguish an identical repeat from a collision.

## Read the four calls

- New 71, amount 600, from 0 to 1 gives an applied result.
- Repeat 71 with the same fields gives duplicate.
- Repeat 71 with amount 650 gives conflict.
- Use new 72 with amount 2,401 from the remaining 2,400 and get insufficient.

Idempotency means repeating the agreed operation has the same intended effect as performing it once. This example accepts only one posting per reference. It never overwrites the previously posted amount in response to a changed request.

## Compare the field rule in D

```d
bool sameTransfer(ulong oldId, long oldCents, ulong newId, long newCents)
{
    return oldId == newId && oldCents == newCents;
}
```

This small D comparison illustrates identity and amount. The full native C route also compares the source and destination account. Add those two fields if you extend the D exercise.

## Check after a refusal

Read the accepted row and both balances after the four calls. They remain unchanged after the first posting. Add a synthetic test that changes the destination while using the same reference. Its result is a conflict when the new account pair is otherwise admissible. The two-account example can model this by swapping the source and destination.

## Continue in another course

- [Banking Technology Foundations](../../../courses/banking-technology-foundations/index.html)
- [Bookkeeping from Your First Entry](../../../courses/bookkeeping-from-first-entry/index.html)
- [Open Banking account access](../../../courses/open-banking-account-access/index.html)
- [Swift payment messages](../../../courses/swift-payment-messages/index.html)
- [Umicom development workflow](../../../umicom/development-path.md)

[Course contents](index.md) · [Previous · Build one checked posting](02-build-a-checked-posting.md) · [Next · Design a durable journal and statement view](04-design-a-durable-statement.md) · [Browser edition](../../../courses/build-a-bank-application-in-c/lessons/03-compare-a-retry-and-a-conflict.html)
