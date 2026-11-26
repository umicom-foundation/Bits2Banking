<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-sql/13-refresh-a-consistent-outbox-report.md

PURPOSE:
  Use the C23 snapshot lab to verify refresh and failure boundaries.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Refresh a consistent outbox report

[Course contents](index.md) · [Previous lesson](12-read-one-committed-database-view.md) · [Next lesson](14-apply-an-observed-version-edit.md)

A useful outbox report answers two questions. Which outgoing records belong on the page, and what was the state of each of those records when the page was read? Build on the [previous lesson](12-read-one-committed-database-view.md) and use the same C23 snapshot lab to check the boundary between a page and a refresh.

## Trace the selected-file workflow

Umicom Trader, Umicom Bank, and Umicom TMS use the shared Umicom Framework to review a selected outbox. In a review, the program reads saved delivery information. It does not send anything. The review obtains the ordered identifiers, then reads each selected row. One read-only transaction covers both stages.

```text
OPEN the selected database in read-only mode
BEGIN one read transaction
READ the ordered entry identifiers for one page
READ the saved details of those same entries
END the read transaction and CLOSE the database
IF every step succeeded, DISPLAY the page
```

The lab reads two known IDs to keep the exercise small. A real page may use a **cursor**, which is the last identifier from the previous page. A later page may start another transaction after a writer has committed; a snapshot belongs to one page. To request a later action on a row, a caller still needs the revision it observed.

## Predict what will change

1. Keep the original lab unchanged. In a separate exercise copy, change the writer's `amount + 10` to `amount + 20`.
2. Before you build, write down which lines should still show amounts 100 and 250. Predict the new amounts after ending the snapshot.
3. Change the two refreshed amount checks in `main` to your predictions. Build in a new folder, then run `ctest -V` in that build folder.
4. The first two lines should still show 100 and 250. The refreshed pair should be 120 and 270, with revision 2 on both entries.

## See what happens when a boundary is missing

Use another copy of the original lab. Remove only the first reader `BEGIN` call and keep the assertions. The first `SELECT` ends when its statement is finalized. Predict which assertion fails when the second `SELECT` starts after the writer commit. Rebuild and run the test. Expect the second-entry check to report revision 2 and amount 260, then exit with a failure result. Restore the read transaction before repeating the test.

## Refuse unsafe or incomplete output

An inspection can fail before any page is ready. In the product, keep the previous report visible until a new observation succeeds. In the lab, the success lines are printed only after the sample values are checked, both connections are closed, and the scratch database is removed.

The final write test should return `SQLITE_READONLY` because the reader was opened for inspection. If a run reports a scratch-folder conflict, build in a new folder and leave the existing folder unmodified. If the observed amount differs from your prediction, compare the amended `UPDATE` and expected checks before changing anything else.

Read [the lab's C23 source](../../../labs/native/sqlite-outbox-snapshot/main.c) and [SQLite's isolation explanation](https://www.sqlite.org/isolation.html). Identify where the lab finalizes a statement, ends a snapshot, and closes a connection. Explain how those three lifetimes differ.

[Course contents](index.md) · [Previous lesson](12-read-one-committed-database-view.md) · [Next lesson](14-apply-an-observed-version-edit.md)
