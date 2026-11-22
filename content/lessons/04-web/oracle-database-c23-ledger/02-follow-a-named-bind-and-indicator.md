<!--
Umicom Bits2Banking
File: content/lessons/04-web/oracle-database-c23-ledger/02-follow-a-named-bind-and-indicator.md

PURPOSE:
Use a bound entry identifier for input and an indicator to recognise Oracle NULL after a fetch.

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

# Follow a named OCI bind and a result indicator

[Course contents](index.md) · [Previous · Read an exact numeric projection in Oracle](01-read-an-oracle-number.md) · [Next · Keep optional values distinct in a financial report](03-keep-optional-values-in-a-report.md) · [Browser edition](../../../courses/oracle-database-c23-ledger/lessons/02-follow-a-named-bind-and-indicator.html)

Use a bound entry identifier for input and an indicator to recognise Oracle NULL after a fetch.

## Name each boundary step

```sql
SELECT cents FROM training_adjustment WHERE entry_id = :entry_id;
```

OCI prepares the SQL. A named bind, such as OCIBindByName or its size-aware variant, associates :entry_id with prepared C storage. Defining the output with OCIDefineByPos associates the first result column with a value buffer, type and indicator. Each buffer must live through the call that uses it. The chapter below gives the exact prototypes and external types for the chosen SDK.

```text
prepare -> bind input -> define output -> execute/fetch
successful row, indicator -1 -> present = false
successful row, indicator 0 -> present = true, use checked cents
normal end of data -> present no new row
conversion or fetch error -> refuse this result
```

For this lesson, inspect and reject unsupported indicators or conversion outcomes. Treat OCI_SUCCESS_WITH_INFO as a signal to examine diagnostics before accepting a value. For example, working with a numeric buffer that cannot represent the selected range must not silently turn either row into zero.

The compiled lab accepts successful checked projections only. It has no OCI dependency. In a complete adapter, verify return codes, conversions, buffer lengths and indicators before calling the native decision.

## Optional native practice

From the Bits2Banking checkout, open a Windows UCRT64 toolchain session. In PowerShell with the C23 compiler already on your path, compile the supplied files. Expect exit code 0 and the line shown below when you run the resulting training program. If the compiler is missing, use the paper trace first.

```powershell
Set-Location labs/native/service-practice/oracle-ledger
gcc -std=c23 -Wall -Wextra -Werror main.c -o oracle-ledger-rules.exe
.\oracle-ledger-rules.exe
```

```text
null, zero and refusal checks ready
```

- [Oracle Call Interface bindings and definitions](https://docs.oracle.com/en/database/oracle/oracle-database/26/lnoci/binding-and-defining-in-oci.html)
- [Read the complete native lab source](../../../labs/native/service-practice/oracle-ledger/main.c)

## Continue in another course

- [Applied native courses](../../../start/applied-native-courses.md)
- [MySQL Ledger Practice in C23](../../../courses/mysql-c23-ledger/index.html)
- [Bookkeeping from Your First Entry](../../../courses/bookkeeping-from-first-entry/index.html)

[Course contents](index.md) · [Previous · Read an exact numeric projection in Oracle](01-read-an-oracle-number.md) · [Next · Keep optional values distinct in a financial report](03-keep-optional-values-in-a-report.md) · [Browser edition](../../../courses/oracle-database-c23-ledger/lessons/02-follow-a-named-bind-and-indicator.html)
