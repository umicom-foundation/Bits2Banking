<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/10-connect-a-trading-command-to-framework.md

PURPOSE:
Connect a trading command to the shared service

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Connect a trading command to the shared service

This module starts with a local program and synthetic orders. No trading knowledge, broker account or market subscription is required. You will learn how a request becomes a retained order and how a caller checks each result.

## Start here

A terminal is a window for entering commands. A compiler translates C source into a program; CMake prepares its build instructions and Ninja carries them out. Open the <!-- The checkout-only laboratory route is retained for review; the active repository route also works in published lessons: [order lifecycle laboratory](../../../../../labs/framework/order-lifecycle/README.md) -->
[order lifecycle laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md) for complete PowerShell and Bash commands, expected output and installation troubleshooting. Read main.c before running it. Each lesson below names the specific source to inspect and a small exercise. All work stays in local memory; no real orders are placed.

## Keep presentation thin

A user interface collects intent and displays results. The Framework service validates and changes domain state. A button handler should not reproduce the order-store or state-transition implementation. Its job is to gather a complete request, call the selected provider, interpret the result and refresh the displayed view.

1. Identify the selected instrument and session before enabling submission.
2. Build a complete candidate request without editing a retained order in place.
3. Call the Framework operation and handle each result visibly.
4. Refresh from the service after success; preserve the draft after refusal so the user can correct it.

## Design a UI test from the contract

Start in local simulation, enter a valid synthetic request, submit once and inspect one retained order. Repeat submission and verify there is still one. Cancel and verify the displayed state, then repeat cancellation. A UI test must observe these results; calling a callback directly does not prove a mouse click, keyboard focus or menu action is correctly wired.

## Next steps

The laboratory does not establish production readiness, market connectivity, risk limits or GUI correctness. Those need separate evidence. Use this service-level contract as one layer of a complete application test rather than treating a successful local example as a completed trading platform.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/trading/broker.h).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [Previous: Test a refusal and the unchanged order book](09-test-failure-without-mutation.md)

[Continue: own a workspace for execution events](11-own-a-workspace-execution-session.md).

## Shared cancellation owner

The current local broker delegates to UmiOrderCancel in Framework. The workspace uses the same transition and separately admits its own revision. Continue with the execution module to see why partial fills and positions remain after cancellation.
