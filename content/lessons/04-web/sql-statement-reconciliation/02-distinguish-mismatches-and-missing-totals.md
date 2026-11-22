<!--
Umicom Bits2Banking
File: content/lessons/04-web/sql-statement-reconciliation/02-distinguish-mismatches-and-missing-totals.md

PURPOSE:
Teach Distinguish mismatches and missing totals through original worked exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom">
</picture>

# Distinguish mismatches and missing totals

[Course contents](index.md) · [Previous: Summarise posted movements](01-summarise-posted-movements.md)

## What you will learn

Classify matching, mismatching and missing statement totals with their original values visible.

## Use a separate comparison input

Reconciliation is a comparison between independently supplied and calculated records. Use the open database from the previous lesson. These invented statement totals include a one-cent difference and omit the clearing account. A missing observation is not interpreted as zero.

```sql
CREATE TABLE statement (
    account TEXT PRIMARY KEY NOT NULL REFERENCES account(name),
    reported_cents INTEGER NOT NULL
);
INSERT INTO statement VALUES ('operating', 900), ('reserve', 1751);

SELECT p.account, p.posted_cents, s.reported_cents,
       s.reported_cents - p.posted_cents AS delta_cents,
       CASE
           WHEN s.account IS NULL THEN 'missing'
           WHEN s.reported_cents = p.posted_cents THEN 'match'
           ELSE 'mismatch'
       END AS review
FROM posted_movement AS p
LEFT JOIN statement AS s ON s.account = p.account
ORDER BY p.account;
```

```text
clearing|0|||missing
operating|900|900|0|match
reserve|1750|1751|1|mismatch
```

The difference is reported minus calculated. Increase the reported number by one and the difference increases by one; write down the convention before using the output.

## Practice and check your answer

Add a statement row for clearing with a reported amount of zero. Rerun the SELECT without changing any ledger entry.

```sql
INSERT INTO statement VALUES ('clearing', 0);
```

**Worked answer**

Clearing now reports match, with zero calculated, zero reported and zero difference. An actual zero statement is a stronger observation than a blank statement.

## If a row is missing

If no table or view named posted_movement exists, open one SQLite session and repeat the previous lesson in that session. If a statement row already exists, inspect it. Make further changes only in the in-memory training database.

[Read this lesson as HTML](../../../courses/sql-statement-reconciliation/lessons/02-distinguish-mismatches-and-missing-totals.html)

## Continue learning

- [Learning SQL](../../../courses/learning-sql/index.html)
- [Learning Umicom Framework and Financial Systems](../../../courses/framework-and-finance/index.html)

## Further reading

- [Tech Sustainify course catalogue](https://techsustainify.com/)
- [W3Schools SQL tutorial](https://www.w3schools.com/sql/default.asp)


[Course contents](index.md) · [Previous: Summarise posted movements](01-summarise-posted-movements.md)
