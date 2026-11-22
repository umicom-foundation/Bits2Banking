<!--
Umicom Bits2Banking
File: content/lessons/04-web/mysql-c23-ledger/01-store-ledger-values-as-integers.md

PURPOSE:
Use one row per fictional entry and calculate which values a posted total includes.

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

# Store signed cents in a training ledger

[Course contents](index.md) · [Next · Bind a MySQL query parameter from C](02-bind-a-parameter-from-c.md) · [Browser edition](../../../courses/mysql-c23-ledger/lessons/01-store-ledger-values-as-integers.html)

Use one row per fictional entry and calculate which values a posted total includes.

## Read a small table

An account identifier links several rows to the same account. An entry identifier names one row. The amount is a signed count of cents. A table is a named collection of rows, and its schema specifies columns and the constraints that each row follows.

```sql
CREATE TABLE training_entry (
    entry_id BIGINT PRIMARY KEY,
    account_id BIGINT NOT NULL,
    cents BIGINT NOT NULL,
    status VARCHAR(7) NOT NULL,
    CHECK (status IN ('posted', 'pending'))
);
INSERT INTO training_entry VALUES
    (101, 42, 2600, 'posted'),
    (102, 42, -850, 'posted'),
    (103, 42, 500, 'pending');
SELECT cents FROM training_entry WHERE account_id = 42 AND status = 'posted' ORDER BY entry_id;
```

Trace the expected rows, 2600 and −850. Add them to get 1750 cents. If you remove the status predicate, you also receive the pending 500 and the calculation changes. If no rows qualify, keep that fact visible alongside the zero result of a total.

## Check the paper result in FreeBASIC

```basic
Dim total As LongInt = 2600 - 850
Print total
```

The known constants fit in a signed 64-bit LongInt. Expect 1750. Use a checked addition when replacing these two constants with input values. The C exercise supplies an example.

## Optional native practice

From the Bits2Banking checkout, open a Windows UCRT64 toolchain session. In PowerShell with the C23 compiler already on your path, compile the supplied files. Expect exit code 0 and the line shown below when you run the resulting training program. If the compiler is missing, use the paper trace first.

```powershell
Set-Location labs/native/service-practice/mysql-ledger
gcc -std=c23 -Wall -Wextra -Werror main.c -o mysql-ledger-rules.exe
.\mysql-ledger-rules.exe
```

```text
posted cents and overflow checks ready
```

- [Read the complete native lab source](../../../labs/native/service-practice/mysql-ledger/main.c)

## Continue in another course

- [Applied native courses](../../../start/applied-native-courses.md)
- [SQL Statement Reconciliation](../../../courses/sql-statement-reconciliation/index.html)
- [Oracle Database C23 Ledger](../../../courses/oracle-database-c23-ledger/index.html)

[Course contents](index.md) · [Next · Bind a MySQL query parameter from C](02-bind-a-parameter-from-c.md) · [Browser edition](../../../courses/mysql-c23-ledger/lessons/01-store-ledger-values-as-integers.html)
