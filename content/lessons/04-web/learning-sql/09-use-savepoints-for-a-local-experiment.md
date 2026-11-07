<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-sql/09-use-savepoints-for-a-local-experiment.md

PURPOSE:
Explain the lesson: Use savepoints for a local experiment.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Use savepoints for a local experiment

A savepoint marks a position inside a transaction. It allows part of the work to be rolled back while earlier work remains available in that transaction.

## Set up

Read the schema and seed in a fresh SQLite session. Open savepoint.sql. Follow the progress value with pencil and paper before running it.

## Follow four states

1. The seed starts at 3.
2. The outer UPDATE changes it to 4.
3. The update after SAVEPOINT experiment changes it to 5.
4. ROLLBACK TO experiment returns it to 4.

RELEASE removes the savepoint. It does not commit the outer transaction in this example. The final ROLLBACK abandons the outer change, leaving the seed value 3.

## Keep names and ownership clear

A name identifies the savepoint being addressed. Use descriptive names for experiments so a reader can tell which part is abandoned. The surrounding code must still own completion of the outer transaction.

A savepoint is not a copy of the entire database that you can store as a portable backup. It belongs to the current database transaction.

## Exercise

Insert a SELECT after each UPDATE and another after the final ROLLBACK. Expected values are 4, 5, 4 and 3.

Next, draw an outer box for BEGIN/ROLLBACK and an inner box for SAVEPOINT/RELEASE. Place every statement in the correct box.

## Recovery

A “no such savepoint” message means the named marker is not currently available. Check spelling and the order of release or rollback operations before retrying; do not silently start a different transaction.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/database/course-progress/savepoint.sql). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](08-change-records-with-rollback.md) · [Next lesson](10-diagnose-a-constraint-failure.md)

