# Reconcile counts, gross totals and status

## What reconciliation means

Reconciliation compares two independently produced views of the same business activity. It should explain differences, not merely force totals to match. A trade list, payment instruction list and bank statement represent different lifecycle stages.

Start with a documented matching key, currency, amount, value date and status. Reused external identifiers, amendments and partial settlement need explicit handling. A numeric trade ID alone may be insufficient for a payment-level match.

## Worked fixture

The expected GBP movements are receipt A 10000, receipt B 5000 and payment C 12000. Expected count is three, gross receipts 15000, gross payments 12000 and net 3000.

An export containing receipt A 10000 and payment D 7000 also nets to 3000. It is wrong despite the equal net: B is missing, C is missing and D is unexpected. Gross totals and identifiers expose the discrepancy.

1. Compare selection dates and currencies.
2. Compare counts and unique keys.
3. Compare gross receipts and payments.
4. Compare net only after those checks.
5. Classify unmatched records by reason and ownership.

## Status is part of the data

A submitted payment has not necessarily settled. A rejected instruction must not become settled merely because its amount appears in a forecast. Keep expected, instructed, confirmed and statement-observed facts distinguishable in your own integration model; map them to actual product statuses only after checking documentation.

## Exercise and answer

A duplicate receipt B is present but another receipt of equal value is absent. Could totals detect the problem? Answer: totals alone may not. A unique-key comparison and missing/unexpected sets are also required.

## Practical task

Create a small approved fixture using fictional identifiers. Record expected keys and totals in a text file, then implement comparison through a suitable existing Framework service rather than changing the treasury amount calculator into an unrelated reconciliation engine. Test missing, duplicate, wrong-currency and wrong-date cases. Report unmatched records explicitly; do not label a report complete when input selection failed.

This exercise is based on the supplied Treasury training material. It does not claim production reconciliation or Calypso status mapping has been executed.

[Course contents](index.md)
