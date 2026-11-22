<!--
Umicom Bits2Banking
File: content/lessons/04-web/mysql-c23-ledger/03-qualify-fetches-before-publishing.md

PURPOSE:
Distinguish a row, end of results, conversion failure and an overflowing total.

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

# Qualify every fetch before publishing a ledger total

[Course contents](index.md) · [Previous · Bind a MySQL query parameter from C](02-bind-a-parameter-from-c.md) · [Browser edition](../../../courses/mysql-c23-ledger/lessons/03-qualify-fetches-before-publishing.html)

Distinguish a row, end of results, conversion failure and an overflowing total.

## Draw the acquisition order

- Prepare the statement, bind the account number and execute.
- Bind the result buffer and associated NULL/error indicators with mysql_stmt_bind_result.
- Read with mysql_stmt_fetch. Handle each successful row, normal end of data, truncated data and other errors according to the C API result values.
- Keep any partial sum private until all expected fetches complete; release the statement on every path.

The lab first produces 1750, then refuses the batch INT64_MAX plus 1 without replacing that complete amount. It also checks an empty batch. Model the same rule for a failed second fetch after you have already read 2600. The last successful total remains visible and the operation reports a failure.

## Apply this to Umicom Bank

Keep database row admission and exact cent validation in a reusable Framework service. Give Umicom Bank separate delivery results for a usable total and failures. An application adapter can show an unavailable result alongside the last successful total.

- [Read the complete native lab source](../../../labs/native/service-practice/mysql-ledger/main.c)
- [MySQL prepared statement fetch](https://dev.mysql.com/doc/c-api/8.4/en/mysql-stmt-fetch.html)
- [Oracle Database C23 Ledger](../../../courses/oracle-database-c23-ledger/index.html)

## Continue in another course

- [Applied native courses](../../../start/applied-native-courses.md)
- [SQL Statement Reconciliation](../../../courses/sql-statement-reconciliation/index.html)
- [Oracle Database C23 Ledger](../../../courses/oracle-database-c23-ledger/index.html)

[Course contents](index.md) · [Previous · Bind a MySQL query parameter from C](02-bind-a-parameter-from-c.md) · [Browser edition](../../../courses/mysql-c23-ledger/lessons/03-qualify-fetches-before-publishing.html)
