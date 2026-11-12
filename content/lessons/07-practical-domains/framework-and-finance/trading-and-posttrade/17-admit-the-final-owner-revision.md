<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/17-admit-the-final-owner-revision.md

PURPOSE:
Admit a revision before publishing a new event

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Admit a revision before publishing a new event

## A revision is an observation identity

Readers use a revision to distinguish earlier and later owner state. Wrapping the counter from its maximum back to zero can make a changed session resemble an old observation. The workspace must therefore reserve publication capacity before changing orders, positions or evidence.

The execution path checks exact replay first because it publishes nothing. It then requires an available workspace revision for a new event. Cancellation follows the same distinction: acknowledging an already-cancelled order does not consume a revision, while a new cancellation needs capacity in both the order and workspace.

## Read the decision boundary

~~~c
/* Inside the Framework owner, after exact-replay handling: */
if (workspace->revision == UINT64_MAX)
    return UMI_STATUS_CAPACITY_EXCEEDED;
~~~

This is a source-reading fragment from the private owner implementation. The installed-SDK laboratory cannot and should not write workspace->revision because its workspace type is opaque. Product clients handle the returned status and retain evidence. Regression tests include the real implementation to inject this otherwise impractical boundary.

## Design the important cases

- The last available revision accepts one complete new change.
- A later unseen event refuses publication and preserves the owner.
- An exact retained replay still succeeds at the maximum revision.
- Conflicting reuse of an identity still reports a conflict.
- Repeated cancellation does not consume another revision.

## Exercise and answer

Why not reset the counter when capacity is exhausted? Resetting inside the same session breaks the relationship between identity and state. A new session needs an explicit lifecycle and evidence boundary. Silently rewriting the counter is not recovery.

## Keep the scope honest

These changes guard execution publication and cancellation. They do not prove that every other workspace command has identical revision admission. Review each mutation path and its return contract before extending the rule; a source change in one function is not qualification of the entire trading product.

## Use the complete laboratory

[Read the source, owner commands and expected results](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). In an offline checkout, open labs/framework/order-lifecycle/README.md. Build and runtime qualification remains unexecuted for this authored continuation.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/17-admit-the-final-owner-revision.html)
