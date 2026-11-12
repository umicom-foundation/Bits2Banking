<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/03-read-a-local-order-request.md

PURPOSE:
Read the fields of a local order request

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Read the fields of a local order request

This module starts with a local program and synthetic orders. No trading knowledge, broker account or market subscription is required. You will learn how a request becomes a retained order and how a caller checks each result.

## Start here

A terminal is a window for entering commands. A compiler translates C source into a program; CMake prepares its build instructions and Ninja carries them out. Open the <!-- The checkout-only laboratory route is retained for review; the active repository route also works in published lessons: [order lifecycle laboratory](../../../../../labs/framework/order-lifecycle/README.md) -->
[order lifecycle laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md) for complete PowerShell and Bash commands, expected output and installation troubleshooting. Read main.c before running it. Each lesson below names the specific source to inspect and a small exercise. All work stays in local memory; no real orders are placed.

## A request is a named set of values

A C struct groups values that belong together. UmiOrderRequest contains an identifier, an account identifier, an instrument, a side, a type, a duration, quantity, price and environment. An identifier is a stable label used to find the same record later. The account name in this lab is a fictional label, not a login.

1. Find the initializer that sets request to zero. It establishes a known starting state.
2. Read the literal copies. sizeof a string literal includes its final zero byte, which marks the end of a C string.
3. Locate quantity 2.0 and limit_price 10.0. A limit order requests a price constraint; this example does not implement matching.
4. Locate UMI_TRADING_SIMULATION. The enum is a declared choice, not a password or a connection address.

## Exercise

Write a table with each field, its value and its purpose. Change the fictional symbol to another short literal and check that instrument_id remains a distinct stable identifier. Explain why the program must not infer instrument identity solely from a display symbol.

## Check your understanding

Does an accepted request prove that two units were bought? No: acceptance and execution are different events. The local adapter retains the request but generates no fill.

## Read the source

[Open the example source](../../../../../labs/framework/order-lifecycle/main.c).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [Next: Validate a request before retaining it](04-validate-before-retaining-orders.md)

## Shared cancellation owner

The current local broker delegates to UmiOrderCancel in Framework. The workspace uses the same transition and separately admits its own revision. Continue with the execution module to see why partial fills and positions remain after cancellation.
