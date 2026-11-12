<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/14-replay-without-new-economics.md

PURPOSE:
Replay an execution without adding its economics twice

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Replay an execution without adding its economics twice

## A repeated message can be normal

A sender may retry because it did not observe an acknowledgement. The receiver cannot conclude that every repeated message represents a new trade. The workspace first checks whether the execution identity is already retained. Exact supported field equality returns success without changing the owner.

Run the replay scenario after the owner builds the laboratory. The first call retains one partial fill. The second call supplies the same report. The program compares workspace revisions and execution counts and checks that the position still contains one filled unit. A success code alone would not prove idempotence.

## Observe the state, not just status

~~~c
UmiStatus first = umi_trading_workspace_record_execution(workspace, &report);
/* Capture an admitted snapshot here. */
UmiStatus retry = umi_trading_workspace_record_execution(workspace, &report);
/* Read again: revision, execution count and position must be unchanged. */
~~~

Idempotence means that repeating this already-accepted operation has no additional effect. It does not mean that every message with a familiar identifier should be accepted. The conflict scenario changes price under the same identifier and expects ALREADY_EXISTS. The original retained report stays authoritative for this local session.

## Replay after later state changes

An earlier exact fill remains a replay after the order is fully filled or cancelled. The workspace checks retained identity before asking whether a new fill is legal in the current order state. Reversing this order would turn harmless recovery traffic into a misleading lifecycle failure.

## Exercise and answer

Why does the low-level umi_order_apply_execution function not provide the same replay guarantee? It owns one order value, not a retained execution catalogue. Calling it twice can apply quantity twice. Use the workspace when your requirement includes retained event identity, and keep the lower-level function for explicitly controlled value calculations.

## Bound the claim

The retained store is finite and local. This lesson does not promise infinite deduplication history, provider reconciliation or crash recovery. A longer-lived system must design those retention boundaries explicitly.

## Use the complete laboratory

[Read the source, owner commands and expected results](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). In an offline checkout, open labs/framework/order-lifecycle/README.md. Build and runtime qualification remains unexecuted for this authored continuation.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/14-replay-without-new-economics.html)
