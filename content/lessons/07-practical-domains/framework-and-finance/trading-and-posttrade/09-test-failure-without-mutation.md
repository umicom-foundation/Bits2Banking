<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/09-test-failure-without-mutation.md

PURPOSE:
Test a refusal and the unchanged order book

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Test a refusal and the unchanged order book

This module starts with a local program and synthetic orders. No trading knowledge, broker account or market subscription is required. You will learn how a request becomes a retained order and how a caller checks each result.

## Start here

A terminal is a window for entering commands. A compiler translates C source into a program; CMake prepares its build instructions and Ninja carries them out. Open the <!-- The checkout-only laboratory route is retained for review; the active repository route also works in published lessons: [order lifecycle laboratory](../../../../../labs/framework/order-lifecycle/README.md) -->
[order lifecycle laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md) for complete PowerShell and Bash commands, expected output and installation troubleshooting. Read main.c before running it. Each lesson below names the specific source to inspect and a small exercise. All work stays in local memory; no real orders are placed.

## A failure code is only half the contract

A function can return an error after accidentally changing state. To catch that defect, tests compare the state before and after a refused operation. The regression uses memcpy to retain the bytes of the same initialized storage and memcmp to check that they did not change. This is a same-object mutation check, not a general comparison between independently created C structs.

1. Read the invalid request case.
2. Find the snapshot taken before the callback.
3. Check both the status and the preserved bytes.
4. Repeat the reasoning for invalid mode, terminal status, exhausted revision and corrupt count.

## Write an expectation table

Columns should include starting state, input, expected result, allowed changes and forbidden changes. Include connection state, record count, status, revision and filled quantity. This table exposes missing cases before implementation.

## Exercise

Add an imaginary case for cancellation of an unknown identifier. Predict the error and unchanged book. Locate the actual order-store contract to confirm the prediction. Keep the expected result grounded in that source rather than changing the assertion until it passes.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/trading/test_simulated_broker.c).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [Previous: Retry cancellation without creating a new change](08-retry-without-new-side-effects.md) · [Next: Connect a trading command to the shared service](10-connect-a-trading-command-to-framework.md)

## Shared cancellation owner

The current local broker delegates to UmiOrderCancel in Framework. The workspace uses the same transition and separately admits its own revision. Continue with the execution module to see why partial fills and positions remain after cancellation.
