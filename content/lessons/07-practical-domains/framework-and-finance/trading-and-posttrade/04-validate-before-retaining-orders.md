<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/04-validate-before-retaining-orders.md

PURPOSE:
Validate a request before retaining it

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Validate a request before retaining it

This module starts with a local program and synthetic orders. No trading knowledge, broker account or market subscription is required. You will learn how a request becomes a retained order and how a caller checks each result.

## Start here

A terminal is a window for entering commands. A compiler translates C source into a program; CMake prepares its build instructions and Ninja carries them out. Open the <!-- The checkout-only laboratory route is retained for review; the active repository route also works in published lessons: [order lifecycle laboratory](../../../../../labs/framework/order-lifecycle/README.md) -->
[order lifecycle laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md) for complete PowerShell and Bash commands, expected output and installation troubleshooting. Read main.c before running it. Each lesson below names the specific source to inspect and a small exercise. All work stays in local memory; no real orders are placed.

## Validation establishes a boundary

Validation checks whether values satisfy a contract before another component relies on them. umi_order_request_validate checks identifiers, instrument fields, enum choices and finite positive quantity. It checks prices when the selected order type needs them. A valid record is still not a credit, risk or trading-permission approval.

1. Find the validation call in sim_submit. It occurs before the local order is added.
2. Follow a failure return: no accepted order is created on that path.
3. Change quantity to zero in the lab and predict which REQUIRE fails.
4. Restore the valid quantity before the next experiment.

## Why finite matters

Floating-point arithmetic can represent infinity and a special not-a-number value. Comparing only quantity <= 0 can miss a not-a-number input. The canonical validator uses isfinite as well as a positive-value check. Applications should call this shared validator instead of writing a weaker second version.

## Exercise

List four invalid requests: an empty identifier, zero quantity, unsupported type and missing required price. For each, describe the state that must remain unchanged. A test should inspect both the returned status and the book count.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/trading/order_request.c).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [Previous: Read the fields of a local order request](03-read-a-local-order-request.md) · [Next: Own a broker session and borrow its results](05-own-a-broker-session.md)

## Shared cancellation owner

The current local broker delegates to UmiOrderCancel in Framework. The workspace uses the same transition and separately admits its own revision. Continue with the execution module to see why partial fills and positions remain after cancellation.
