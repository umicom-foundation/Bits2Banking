<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/05-own-a-broker-session.md

PURPOSE:
Own a broker session and borrow its results

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Own a broker session and borrow its results

This module starts with a local program and synthetic orders. No trading knowledge, broker account or market subscription is required. You will learn how a request becomes a retained order and how a caller checks each result.

## Start here

A terminal is a window for entering commands. A compiler translates C source into a program; CMake prepares its build instructions and Ninja carries them out. Open the [order lifecycle laboratory](../../../../../labs/framework/order-lifecycle/README.md) for complete PowerShell and Bash commands, expected output and installation troubleshooting. Read main.c before running it. Each lesson below names the specific source to inspect and a small exercise. All work stays in local memory; no real orders are placed.

## Storage and operations have different roles

UmiSimulatedBrokerStorage holds the local state. UmiBroker is a table of function pointers and an instance pointer. A function pointer identifies an operation that can be called; the instance pointer says which session that operation should use. This separates a common interface from a particular provider.

1. Locate storage and broker in main. Both live until main returns.
2. Follow umi_simulated_broker_create: it initializes storage and fills the operation table.
3. Read broker.connect(broker.instance, ...). The explicit instance carries ownership context.
4. Find the UmiOrder pointer returned by umi_order_store_find. It points inside storage; it is borrowed and must not be freed.

## Avoid a dangling pointer

A pointer becomes dangling when its referenced object no longer exists. Resetting this book also invalidates the logical record previously identified by a borrowed pointer, even though the surrounding storage still exists. Clear or stop using borrowed pointers before reset and never retain a pointer to storage after its owning function returns.

## Exercise

Draw three boxes: main owns storage; broker refers to storage; stored refers to an order inside storage. Mark when each relationship ends. Explain why copying the pointer does not extend the underlying lifetime.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/trading/simulated_broker.h).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [Previous: Validate a request before retaining it](04-validate-before-retaining-orders.md) · [Next: Keep local simulation environments consistent](06-separate-simulation-environments.md)
