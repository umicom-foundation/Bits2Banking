<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-sql/08-change-records-with-rollback.md

PURPOSE:
Explain the lesson: Change records with rollback.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Change records with rollback

A transaction groups work into a unit that can be committed or abandoned. BEGIN starts the unit. COMMIT accepts it. ROLLBACK abandons it.

## Prepare

Use a new temporary database and read the lab schema and seed. Learner A has completed three lessons in Learning C.

## Observe an uncommitted edit

Read rollback.sql. The UPDATE has two conditions:

```sql
WHERE learner_id = 1 AND course_id = 1
```

Together they identify one progress row. Without the WHERE clause, the statement would change every row in that table.

The SELECT inside the transaction reads 4. After ROLLBACK the following SELECT reads 3. Reading your own temporary change does not prove it has been committed.

## Explain the boundary

This lesson concerns the database connection and its statements. It does not claim that printing a message, sending an email or changing another file is automatically undone by SQL rollback.

Framework's transaction handle API makes begin, commit, rollback and disposal explicit for its data service. Use that shared API in a Framework application instead of spreading connection ownership across buttons.

## Exercise

Repeat the statements interactively, pausing before rollback. Predict the value at each step. Then start a fresh transaction and update a nonexistent learner. A successful UPDATE statement can affect zero rows; success alone does not prove the intended record existed.

## Recovery

If an error leaves you uncertain about an open transaction in this disposable session, issue ROLLBACK and inspect the data. Do not continue issuing dependent changes while guessing the state.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/database/course-progress/rollback.sql). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-summarise-enrolments-with-aggregates.md) · [Next lesson](09-use-savepoints-for-a-local-experiment.md)

