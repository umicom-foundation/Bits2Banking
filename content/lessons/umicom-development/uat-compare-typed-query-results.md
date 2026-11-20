<!--
Umicom Bits2Banking
File: content/lessons/umicom-development/uat-compare-typed-query-results.md

PURPOSE:
Use a disposable SQLite fixture to verify an exact typed database result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare typed database results

![Umicom](../../assets/branding/umicom-wordmark.svg)

[![Umicom icon](../../assets/branding/umicom-icon.svg)](../../assets/branding/umicom.ico)

A database assertion checks what was stored or returned after an action. The text shown by a grid can hide storage details. An empty string, a database NULL and a binary value with zero bytes are three different results. In this exercise, one local SQLite fixture makes those distinctions observable.

## Build the disposable example

Use CMake, Ninja, a C23 compiler and matching SQLite development files. The commands below use the UCRT64 toolchain and assume the Framework checkout is at the shown Windows path. Change that path to your checkout. The fixture opens its own in-memory table, so it does not need a database filename or login.

```powershell
$framework = "C:/umicom/Umicom-Applications/framework"
$build = Join-Path $framework "build/uat-workshop"
$env:PATH = "C:/msys64/ucrt64/bin;$env:PATH"
cmake -S "$framework/tests/uat" -B $build -G Ninja -DUMICOM_UAT_SQLITE_EXAMPLE=ON -DSQLite3_INCLUDE_DIR=C:/msys64/ucrt64/include -DSQLite3_LIBRARY=C:/msys64/ucrt64/lib/libsqlite3.dll.a
cmake --build $build --target umicom-uat-database-example umicom-uat-database-rows-tests
ctest --test-dir $build -R '^framework[.]uat[.](database|database_rows)[.]' --output-on-failure --no-tests=error
```

Expect 24 CTest cases. Eighteen exercise the shared comparator and six run the SQLite example. If CMake cannot find SQLite, point it at the headers and library from the toolchain you installed. Stop on a configure or build error before running an executable left over from an earlier build.

## Read both outcomes

Run one command that should pass and one that should report a mismatch. Save the second program's exit code before running another native command.

```powershell
& "$build/umicom-uat-database-example.exe" --verify-types
$report = & "$build/umicom-uat-database-example.exe" --reject-typed-change | ConvertFrom-Json
$fixtureExit = $LASTEXITCODE
$report.findings | Select-Object id, state, output
$fixtureExit
```

The passing run reads a full row containing an integer, text, binary data, empty text, NULL and a real number. The second query returns the saved text followed by an embedded zero byte and an extra character. A C string comparison stops at zero. A byte-counted database comparison can see the additional character.

| Finding | Expected outcome in the mismatch run |
|---------|--------------------------------------|
| `create` | The private table was created |
| `edit` | The fixture applied its changes |
| `verify` | The read failed at row 1, column 2 |
| `drop` | Cleanup passed |
| Program exit | `1` |

The report gives the position and keeps the field values out of the evidence. A CTest case for this deliberate mismatch passes when it observes both the expected failure and successful cleanup.

## Reuse the Framework comparator

Give `UmiUatCompareDatabaseRows` an independent expected grid and the actual result, each arranged in row order. Know the column count even when the query returns zero rows. Use an explicit column list and `ORDER BY` when positions matter. Read each database value's storage kind before asking the driver to convert it for display. Keep text and binary lengths, and compare borrowed values while their driver still owns them.

An `OK` status means the two complete snapshots were admitted. Read the result's `match` field to decide whether they agree. Cell coordinates in the C result start at zero, while the sample displays them starting at one. If a result is incomplete or exceeds the documented bounds, fix the adapter or narrow the fixture before interpreting it.

Try the `null-empty` and `embedded-nul` cases separately. Predict which fails because of the storage kind and which fails because of the bytes. [Open the comparator contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/testing/uat_database_rows.h) · [Read the SQLite example](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/uat/database_workflow.c)
