<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/08-retry-without-new-side-effects.md

PURPOSE:
Retry cancellation without creating a new change

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Retry cancellation without creating a new change

This module starts with a local program and synthetic orders. No trading knowledge, broker account or market subscription is required. You will learn how a request becomes a retained order and how a caller checks each result.

## Start here

A terminal is a window for entering commands. A compiler translates C source into a program; CMake prepares its build instructions and Ninja carries them out. Open the <!-- The checkout-only laboratory route is retained for review; the active repository route also works in published lessons: [order lifecycle laboratory](../../../../../labs/framework/order-lifecycle/README.md) -->
[order lifecycle laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md) for complete PowerShell and Bash commands, expected output and installation troubleshooting. Read main.c before running it. Each lesson below names the specific source to inspect and a small exercise. All work stays in local memory; no real orders are placed.

## Idempotence makes a retry predictable

An operation is idempotent when repeating it has the same resulting state as performing it once. Cancelling an already cancelled local order returns success without increasing its revision. A revision is an integer recording a state change; it is not a timestamp.

1. Run the unmodified lab after building it.
2. Locate the first cancellation: revision becomes two.
3. Locate the second cancellation: revision remains two.
4. Compare duplicate submission. A duplicate identifier returns ALREADY_EXISTS rather than adding another record. These are deliberately different response contracts.

## Bound the revision

An unsigned revision has a largest representable value. Incrementing past it wraps to zero. The shared adapter refuses a new cancellation when the revision is already UINT64_MAX. An already cancelled order at that value can still acknowledge a retry without incrementing.

## Exercise

Explain two separate cases: accepted at the largest revision, and cancelled at the largest revision. Predict both results. Do not implement a workaround that resets revision to zero; that would make an old observation appear current.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/trading/test_simulated_broker.c).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [Previous: Cancel an order using its state machine](07-cancel-with-a-state-machine.md) · [Next: Test a refusal and the unchanged order book](09-test-failure-without-mutation.md)

## Shared cancellation owner

The current local broker delegates to UmiOrderCancel in Framework. The workspace uses the same transition and separately admits its own revision. Continue with the execution module to see why partial fills and positions remain after cancellation.
