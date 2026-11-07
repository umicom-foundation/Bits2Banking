<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/06-separate-simulation-environments.md

PURPOSE:
Keep local simulation environments consistent

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Keep local simulation environments consistent

This module starts with a local program and synthetic orders. No trading knowledge, broker account or market subscription is required. You will learn how a request becomes a retained order and how a caller checks each result.

## Start here

A terminal is a window for entering commands. A compiler translates C source into a program; CMake prepares its build instructions and Ninja carries them out. Open the [order lifecycle laboratory](../../../../../labs/framework/order-lifecycle/README.md) for complete PowerShell and Bash commands, expected output and installation troubleshooting. Read main.c before running it. Each lesson below names the specific source to inspect and a small exercise. All work stays in local memory; no real orders are placed.

## A mode belongs to the whole session

An environment distinguishes simulation, paper and live identities. This particular provider implements local simulation only: both its simulation and paper modes stay in memory. It rejects live mode and never authenticates with a broker. A real broker adapter is a different implementation of the common contract.

1. Connect this lab in simulation mode.
2. Submit a request with the same mode.
3. Change only the request mode and predict refusal.
4. Inspect sim_connect: a session containing orders cannot switch to a different mode. Destroy the local session before choosing another mode.

## Keep meaning visible

A GUI should display the provider and mode together. Showing Paper without identifying the local simulator can mislead a person into thinking a broker account is connected. The environment enum also does not grant permissions: those checks belong to the relevant broker and application policies.

## Exercise

Create a small table of connection mode, request mode and expected result. Include invalid enum input. For each rejected operation, explain why the earlier order history must remain unchanged. Reconnecting the same valid mode should preserve the existing book.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/trading/simulated_broker.c).

## Continue learning

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [Previous: Own a broker session and borrow its results](05-own-a-broker-session.md) · [Next: Cancel an order using its state machine](07-cancel-with-a-state-machine.md)
