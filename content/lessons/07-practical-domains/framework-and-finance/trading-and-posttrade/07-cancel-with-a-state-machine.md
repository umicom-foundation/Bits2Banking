<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/07-cancel-with-a-state-machine.md

PURPOSE:
Cancel an order using its state machine

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Cancel an order using its state machine

This module starts with a local program and synthetic orders. No trading knowledge, broker account or market subscription is required. You will learn how a request becomes a retained order and how a caller checks each result.

## Start here

A terminal is a window for entering commands. A compiler translates C source into a program; CMake prepares its build instructions and Ninja carries them out. Open the [order lifecycle laboratory](../../../../../labs/framework/order-lifecycle/README.md) for complete PowerShell and Bash commands, expected output and installation troubleshooting. Read main.c before running it. Each lesson below names the specific source to inspect and a small exercise. All work stays in local memory; no real orders are placed.

## A state machine describes allowed changes

A state is a named stage such as accepted, partially filled or cancelled. A transition is a move between stages. umi_order_transition_allowed is Framework's shared rule for these moves. sim_cancel consults it before changing the stored record.

1. Draw accepted → cancelled and partially filled → cancelled.
2. Draw filled and rejected as terminal states: cancellation must not rewrite them.
3. Find the check in sim_cancel before the status assignment.
4. Read the regression cases that attempt cancellation from each state.

## Partial fills remain evidence

Cancelling the remaining request does not erase quantities already filled. This local adapter does not create fills, but its cancellation operation preserves an existing filled_quantity field. A broader order service must reconcile real execution events and balances separately.

## Exercise

Make a state/operation table before writing code. Include an invalid numeric enum value; a corrupted state should be refused, not treated as accepted. State the expected status and whether version and quantity may change. A menu label cannot replace these shared domain checks.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/trading/order_state.c).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [Previous: Keep local simulation environments consistent](06-separate-simulation-environments.md) · [Next: Retry cancellation without creating a new change](08-retry-without-new-side-effects.md)
