# Design scheduled tasks and reports with control totals

## Start with a report contract

A scheduled task automates an operation at a configured time. A report turns selected data into an interpretable result. Neither should hide the selection criteria, time basis or rejected records. The later Calypso refresher discusses these extension families; its examples are starting points, not a replacement for your release's SDK.

Suppose the task exports next-day cash movements. Define business date, timezone, books, legal entities, currencies and included statuses. A trade date is not necessarily a value date, and an unapproved movement is not an available balance.

## Worked control totals

Your approved fixture contains three GBP movements: receipts 10000 and 5000, payment 12000, all in minor units. The expected receipt total is 15000, payment total 12000 and net 3000. Record the row count as three as well as the totals. Equal net values alone can conceal a missing receipt and missing payment.

Keep each currency separate. Do not net 3000 GBP with 3000 USD unless an explicitly defined conversion and rate timestamp are part of the report.

## A controlled task lifecycle

1. Validate configuration before querying.
2. Resolve the supported selection API and authorization scope.
3. Accumulate accepted and rejected records separately.
4. Write output through a reviewed publication boundary.
5. Record counts, currency totals and output identity.
6. Report failure when required rows or publication steps fail.

Do not guess the ScheduledTask process override or Report load signature from an internet snippet. Inspect the licensed abstract class and interface, then document the implementation's transaction and connection ownership.

## Exercise and answer

The output has two rows and net 3000, matching the expected net. Is it complete? Answer: no. Expected count was three. Investigate omitted rows and both gross totals before accepting the output.

## Extension exercise

Prepare a release-specific signature inventory and a fixture with one malformed currency. Decide whether the whole report is refused or the row is explicitly quarantined. Explain that policy in the report itself. Runtime qualification remains pending.

[Course contents](index.md)
