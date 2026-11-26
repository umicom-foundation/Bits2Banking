<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-sql/14-apply-an-observed-version-edit.md

PURPOSE:
  Explain bounded UTF-8 titles and observed-version edits with the native SQLite lab.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Apply an edit to the version you observed

[Course contents](index.md) · [Previous lesson](13-refresh-a-consistent-outbox-report.md)

Two learners open the same note. Each sees the word `Ready` and revision 1. One saves a new title. When the second learner sends an edit based on revision 1, the note has already changed. A **revision** labels the version read by each learner. An **optimistic edit** lets both learners prepare a draft, then checks the old revision at the moment of writing.

## Build and run the native exercise

Use the [setup from lesson 12](12-read-one-committed-database-view.md). The exercise uses the same C23 target and SQLite library. It opens a fresh in-memory database and writes no files. Run this separate mode from the Bits2Banking checkout after building.

```powershell
ctest --test-dir .\.build\sqlite-outbox-snapshot -V -R '^btb\.education\.sqlite_outbox_observed_edit$'
```

```bash
ctest --test-dir ./.build/sqlite-outbox-snapshot -V -R '^btb\.education\.sqlite_outbox_observed_edit$'
```

## Count the bytes before choosing a limit

The first editor uses the letter `e`, a separate combining acute accent, and a rocket. A [grapheme cluster](https://www.unicode.org/reports/tr29/#Grapheme_Cluster_Boundaries) is a unit a reader tends to see as one character. The accented letter is one cluster here even though the lab stores it as two code points. The rocket is a second cluster.

1. The letter `e` is one UTF-8 byte.
2. The combining accent U+0301 is two UTF-8 bytes. Codes like `U+0301` name Unicode code points.
3. The rocket U+1F680 is four UTF-8 bytes. Together they occupy seven bytes and three code points.

In this UTF-8 database, `length(title)` counts code points for the lab's text. `length(CAST(title AS BLOB))` counts bytes. A BLOB is a byte sequence. Adding the one-byte letter `X` makes the same proposal eight bytes, above this lab's seven-byte cap. SQLite does not count grapheme clusters for either expression. The lab uses fixed valid UTF-8 examples. [SQLite length rules](https://www.sqlite.org/lang_corefunc.html#length)

## Keep the version check inside the write

```sql
UPDATE note
SET title = ?1, revision = revision + 1
WHERE id = 1 AND revision = ?2
  AND length(CAST(?1 AS BLOB)) <= ?3;
```

The question-mark placeholders bind the draft, the revision observed by that editor, and the byte limit. SQL decides whether the same row still matches both predicates. The lab uses `sqlite3_changes()` immediately after completing that statement. One row means the edit was accepted. Zero rows means the predicates selected nothing. The lab changes only one input per failed attempt to identify the cause. [SQLite row-change count](https://www.sqlite.org/c3ref/changes.html)

```text
Both editors observed revision 1.
First edit: 1 row, revision 2, 3 code points, 7 UTF-8 bytes.
Stale short edit: 0 rows changed; revision 2 kept.
Current 8-byte edit: 0 rows changed; revision 2 kept.
```

## Check a refused edit and keep the draft

The second editor sends the valid short word `Draft` with revision 1. The lab checks the accepted title and revision again. It then sends the 8-byte title with revision 2 to test the byte limit on its own. Both rejected attempts leave the accepted text exactly as the first editor saved it.

If two editors disagree, show the latest saved version and keep the rejected draft available for review. The editor can decide whether to resubmit after reading the newer revision. In a separate exercise copy, remove the revision predicate and predict which check fails. Restore the predicate, then explain what a stale editor can safely do next.

The Framework uses an authorized, serialized web handler for a configured string. Its host decides edit permission, and its handler validates the submitted UTF-8 line before publishing. The lab illustrates the write-boundary principle with SQLite, using fixed local data. If the test cannot find SQLite, return to the compiler and library setup in lesson 12. If the displayed code-point or byte counts differ, inspect the C fixture's hex bytes before changing the expected values. [Lab source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/labs/native/sqlite-outbox-snapshot/main.c) · [Framework reactive value admission](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/development/reactive-value-admission.md)

[Course contents](index.md) · [Previous lesson](13-refresh-a-consistent-outbox-report.md)
