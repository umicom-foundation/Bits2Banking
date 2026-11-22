<!--
Umicom Bits2Banking
File: content/lessons/04-web/sql-statement-reconciliation/01-summarise-posted-movements.md

PURPOSE:
Teach Summarise posted movements through original worked exercises.

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

# Summarise posted movements

[Course contents](index.md) · [Next: Distinguish mismatches and missing totals](02-distinguish-mismatches-and-missing-totals.md)

## What you will learn

Show a posted movement per account, including a training account that has no entries.

## Set up a practice database

Start sqlite3 :memory: in a terminal. This database lasts for that SQLite process. Leave it open for the next lesson. A primary key identifies one row. A foreign key relates an entry to its account. Paste these statements and press Enter after every completed statement.

```sql
PRAGMA foreign_keys = ON;
CREATE TABLE account (
    name TEXT PRIMARY KEY NOT NULL
);
CREATE TABLE entry (
    reference INTEGER PRIMARY KEY,
    account TEXT NOT NULL REFERENCES account(name),
    cents INTEGER NOT NULL,
    state TEXT NOT NULL CHECK (state IN ('posted', 'pending'))
);
INSERT INTO account VALUES ('reserve'), ('operating'), ('clearing');
INSERT INTO entry VALUES
    (101, 'reserve', 2600, 'posted'),
    (102, 'reserve', -850, 'posted'),
    (103, 'reserve', 500, 'pending'),
    (104, 'operating', 1200, 'posted'),
    (105, 'operating', -300, 'posted'),
    (106, 'operating', -150, 'pending');
```

## Query matched and unmatched accounts

A left join keeps each account. Its ON condition selects only that account’s posted entries. SUM adds matched amounts; an account with no matching amounts produces NULL, which COALESCE replaces with zero.

```sql
CREATE VIEW posted_movement AS
SELECT a.name AS account, COALESCE(SUM(e.cents), 0) AS posted_cents
FROM account AS a
LEFT JOIN entry AS e
    ON e.account = a.name AND e.state = 'posted'
GROUP BY a.name;

SELECT account, posted_cents
FROM posted_movement
ORDER BY account;
```

```text
clearing|0
operating|900
reserve|1750
```

## Practice and check your answer

Change a copy of the SELECT inside the view by moving the state test to a WHERE clause below the join. Predict which row disappears.

**Worked answer**

Clearing disappears because the unmatched right-side state is NULL and WHERE keeps only true conditions. Put the state requirement inside ON for a report that includes every account.

## If the result differs

If SQLite reports that a table already exists, you are reusing the same practice database. Start a fresh sqlite3 :memory: process and paste the steps in order. If the query prints columns in a different style, compare the account and amount values rather than the separators.

[Read this lesson as HTML](../../../courses/sql-statement-reconciliation/lessons/01-summarise-posted-movements.html)

## Continue learning

- [Learning SQL](../../../courses/learning-sql/index.html)
- [Learning Umicom Framework and Financial Systems](../../../courses/framework-and-finance/index.html)

## Further reading

- [Tech Sustainify course catalogue](https://techsustainify.com/)
- [W3Schools SQL tutorial](https://www.w3schools.com/sql/default.asp)


[Course contents](index.md) · [Next: Distinguish mismatches and missing totals](02-distinguish-mismatches-and-missing-totals.md)
