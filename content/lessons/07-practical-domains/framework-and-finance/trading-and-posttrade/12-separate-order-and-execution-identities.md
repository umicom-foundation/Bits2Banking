<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/framework-and-finance/trading-and-posttrade/12-separate-order-and-execution-identities.md

PURPOSE:
Give orders and executions different identities

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../../assets/branding/umicom-logo.svg)

# Give orders and executions different identities

## Two records answer two questions

An order identifier answers which request this fill belongs to. An execution identifier answers which event is being reported. Two partial fills can belong to one order while remaining different events. Reusing the order identifier as every execution identifier would make the second fill look like a replay or a conflict.

The example reads the selected order identifier from an admitted workspace snapshot and copies it into the report. It then assigns LESSON-FILL-1 as a separate synthetic execution identity. The report owns its character arrays; it does not keep a borrowed pointer into the workspace.

## Construct the report

~~~c
UmiExecutionReport report = {0};
strcpy(report.execution_id.value, "LESSON-FILL-1");
/* Copy the checked selected order ID into report.client_order_id. */
report.fill_quantity = 1.0;
report.fill_price = 10.0;
report.event_time_ms = 1001;
~~~

These fixed strings fit their fields. A real input adapter must validate variable lengths, termination, provider identity and event semantics before using them. A timestamp is evidence about the event; it is not a replacement for a stable execution identifier. This example supplies a synthetic nonnegative time and makes no claim about exchange clock synchronization.

## Compare the records

| Value | First fill | Second fill |
| --- | --- | --- |
| Order ID | Same retained request | Same retained request |
| Execution ID | LESSON-FILL-1 | LESSON-FILL-2 |
| Quantity | Part of requested amount | Another part of requested amount |
| Replay meaning | Same supported report fields | Not the same event as the first ID |

## Exercise and answer

Change only the price while keeping LESSON-FILL-1. Should the workspace silently replace the first report? No. The conflict scenario expects ALREADY_EXISTS and no new revision, execution or position quantity. Retain both incoming observations for investigation instead of manufacturing an ID that bypasses the conflict.

## Read the shared contract

Inspect execution_report.c and execution_store.c in Framework. The validator admits fields before the store compares identifiers. The workspace adds semantic replay handling; adding directly to the store has a different contract and must not be substituted casually.

## Use the complete laboratory

[Read the source, owner commands and expected results](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/order-lifecycle/README.md). In an offline checkout, open labs/framework/order-lifecycle/README.md. Build and runtime qualification remains unexecuted for this authored continuation.

[Course contents](../../../../courses/framework-and-finance/trading-and-posttrade/index.html) · [HTML edition](../../../../courses/framework-and-finance/trading-and-posttrade/lessons/12-separate-order-and-execution-identities.html)
