# Bound a query and preserve its failure

## Why a limit matters

A small result in a demonstration says little about a production query. An unrestricted filter can consume server resources even if the client later discards most results. The supplied guide shows TradeArray queries using a TradeFilter and time; it does not establish a portable pagination interface for every release.

The lab therefore accepts explicit IDs instead of inventing a paged endpoint. It limits requests to 256, rejects zero and duplicates, and clones the input before validation. The complete input is checked before the first remote call.

## Worked example

Input [41, 52, 41] is rejected before any call because the repeated 41 could distort reconciliation totals. Input [41, 52] permits at most two calls. If the second call fails, the method throws and returns no partial success list.

That behaviour does not roll back the first read, and it does not make both reads simultaneous. Record 41 may change before record 52 is fetched. To obtain a consistent as-of report, use a documented release-specific facility and verify its semantics.

## Distinguish three budgets

1. Request count limits the number of operations.
2. Response size limits the amount of data retained locally.
3. A supported transport timeout limits waiting under defined client behaviour.

The adapter covers the first two for small identity results. The host must configure the third. Cancelling a Future is not proof that a server stopped working. Blind retry can amplify an outage.

## Exercise and answer

A service returns 100,000 trades; your loop stops after 100. Did you bound server work? Answer: no. The query may already have loaded and serialized all records. Request a documented bounded query or use a reviewed explicit selection.

## Qualification worksheet

Test empty input, duplicate IDs, 257 IDs, a known identity, a missing-record case and service failure. Verify invalid input causes zero remote calls using a separately instrumented test environment. Do not ship a fake vendor package as evidence. Keep count, permission and timeout failures distinct in the report.

[Course contents](index.md)
