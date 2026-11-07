# Course progress in SQL

Build a small database for three fictional learners. SQL is the language used to ask questions about rows and to change them. SQLite is the existing database engine used in this lab; no database engine is reimplemented here.

## Prepare a disposable workspace

Use a terminal and the SQLite command-line application. Check `sqlite3 --version` (on Windows the executable may be `C:\msys64\ucrt64\bin\sqlite3.exe`). If it is missing, install the SQLite command-line tools from your operating-system package manager or the [official download page](https://www.sqlite.org/download.html).

In PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\database\course-progress"
& "C:\msys64\ucrt64\bin\sqlite3.exe" ":memory:"
```

In Bash, from your own repository checkout:

```bash
cd labs/database/course-progress
sqlite3 :memory:
```

The following lines belong at the SQLite prompt in either terminal:

```text
.bail on
.headers on
.mode column
.read schema.sql
.read seed.sql
.read read.sql
.read joins.sql
.read summary.sql
.read rollback.sql
.read savepoint.sql
.read integrity.sql
.read checks.sql
.quit
```

A database named `:memory:` lasts only for that process. Closing it discards these fictional records. Start a fresh process to repeat the setup; running the schema twice in the same process reports existing tables. Do not point this lab at application databases.

## Compare observations

- Catalogue: Learning C has 10 lessons, Learning RISC-V 8 and Learning HDL 6.
- Four progress rows record a total of 15 completed lessons.
- The left join includes Learner C with no course ID.
- The rollback example displays 4, then 3.
- The savepoint example displays 4, then its outer rollback restores the original value.
- Structural quick-check should print `ok`; foreign-key and application-rule queries should return no diagnostic rows.
- `checks.sql` contains assertions. With `.bail on`, a failed assertion stops before the final observation.

These are expected results, not a report that the lab has been executed.

## Investigate one failure

In a fresh interactive session, read schema and seed again, leave `.bail off`, and read `constraints.sql`. Its invalid insert should report a foreign-key error; the count remains four. The error is the subject of this exercise. Do not treat it as an unexpected failure in the passing checks.

## Connect the ideas to Framework

Read [Framework transaction handles](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/data/transaction.h) and [SQLite health operations](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/data/sqlite.h). They expose ownership and health checks through shared C services. This teaching schema is not the production learning catalogue schema, and these APIs do not claim to execute arbitrary SQL shown in this lab.

The [Learning SQL course](../../../content/courses/learning-sql/index.html) explains the statements in sequence. The [SQLite shell guide](https://www.sqlite.org/cli.html) documents the dot commands used to read files and format output.

