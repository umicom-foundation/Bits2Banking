<!--
Umicom Bits2Banking
File: content/lessons/04-web/mysql-c23-ledger/02-bind-a-parameter-from-c.md

PURPOSE:
Prepare fixed SQL while the account number travels through its own typed value.

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

# Bind a MySQL query parameter from C

[Course contents](index.md) · [Previous · Store signed cents in a training ledger](01-store-ledger-values-as-integers.md) · [Next · Qualify every fetch before publishing a ledger total](03-qualify-fetches-before-publishing.md) · [Browser edition](../../../courses/mysql-c23-ledger/lessons/02-bind-a-parameter-from-c.html)

Prepare fixed SQL while the account number travels through its own typed value.

## Follow the C API steps

A prepared statement fixes the instruction shape. A question mark marks the account value to supply later. The table and column names remain part of the fixed SQL. The fragment assumes conn is an already checked connection to the training database.

```c
const char sql[] = "SELECT cents FROM training_entry "
                   "WHERE account_id = ? AND status = 'posted' "
                   "ORDER BY entry_id";
MYSQL_STMT *stmt = mysql_stmt_init(conn);
long long account_id = 42;
MYSQL_BIND input = {0};
input.buffer_type = MYSQL_TYPE_LONGLONG;
input.buffer = &account_id;
input.is_unsigned = false;
/* Keep account_id alive through execution and close stmt on every path. */
if (stmt != NULL &&
    mysql_stmt_prepare(stmt, sql, sizeof sql - 1) == 0 &&
    mysql_stmt_bind_param(stmt, &input) == 0 &&
    mysql_stmt_execute(stmt) == 0) {
    /* Bind and consume the result here, before closing stmt. */
}
if (stmt != NULL) {
    mysql_stmt_close(stmt);
}
```

Use the MySQL header that declares MYSQL_BIND. In a complete adapter, report the failing stage and statement error before closing its handle. The usual signed BIGINT mapping takes a signed 64-bit long long with is_unsigned clear. Confirm your driver representation and freeze the exact-width C type before passing the decoded row to another module.

Try the thought experiment with account 43 using the same SQL string. The parameter changes. The command text stays fixed. The zero-row response is different from a failed query.

- [MySQL 8.4 C prepared statements](https://dev.mysql.com/doc/c-api/8.4/en/c-api-prepared-statement-interface.html)

## Continue in another course

- [Applied native courses](../../../start/applied-native-courses.md)
- [SQL Statement Reconciliation](../../../courses/sql-statement-reconciliation/index.html)
- [Oracle Database C23 Ledger](../../../courses/oracle-database-c23-ledger/index.html)

[Course contents](index.md) · [Previous · Store signed cents in a training ledger](01-store-ledger-values-as-integers.md) · [Next · Qualify every fetch before publishing a ledger total](03-qualify-fetches-before-publishing.md) · [Browser edition](../../../courses/mysql-c23-ledger/lessons/02-bind-a-parameter-from-c.html)
