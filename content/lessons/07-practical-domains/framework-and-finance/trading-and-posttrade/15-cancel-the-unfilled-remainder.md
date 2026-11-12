<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/15-cancel-the-unfilled-remainder.md

PURPOSE:
Cancel the remainder while preserving completed fills

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Cancel the remainder while preserving completed fills

## Cancellation does not reverse a fill

A two-unit request with one unit already filled still has a one-unit position after cancellation. Cancellation ends the remaining local order lifecycle. Erasing the fill quantity or position would rewrite history and hide exposure. The shared UmiOrderCancel operation changes only order status and revision.

## Follow the cancel scenario

- Accept a synthetic two-unit limit order.
- Retain one one-unit execution and observe the position.
- Cancel the selected order through the workspace.
- Repeat cancellation and replay the original fill; neither publishes another change.
- Submit a new fill identity and observe refusal for the cancelled order.

The workspace and local broker both delegate the transition to the canonical order-state service. The workspace additionally owns its own revision and selection. A partial position remains visible because cancellation does not remove prior execution evidence or recalculate that position to zero.

## Use the owner command

~~~c
UmiStatus status = umi_trading_workspace_cancel_selected_order(workspace);
/* Keep prior fills and positions. Read the resulting owner state. */
~~~

The default laboratory view retains the selected cancelled order, so repeating the command succeeds without a new revision. An open-orders filter may remove the order from that view and clear its selection. A later selected-order command can then return NOT_FOUND. That result describes the current selection; it does not undo or invalidate the earlier cancellation.

## Exercise and answer

Should a live broker client mark an order cancelled immediately after sending a network request? This local value helper does not establish that acknowledgement. A live adapter needs its own command and provider-response lifecycle. The lesson makes no claim that local cancellation confirms exchange cancellation.

## Read the evidence

Inspect order_state.c and the workspace command, then compare the cancel regression fixture. It checks partial fills, repeated calls, invalid states and revision limits. The test source is authored coverage; only an owner run against identified binaries supplies a result.

## Use the complete laboratory

[Read the source, owner commands and expected results](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). In an offline checkout, open labs/framework/order-lifecycle/README.md. Build and runtime qualification remains unexecuted for this authored continuation.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/15-cancel-the-unfilled-remainder.html)
