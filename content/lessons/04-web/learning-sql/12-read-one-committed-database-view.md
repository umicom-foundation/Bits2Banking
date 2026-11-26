<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-sql/12-read-one-committed-database-view.md

PURPOSE:
  Build a native C23 lab and trace a stable committed SQLite view.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read one committed database view

[Course contents](index.md) · [Previous lesson](11-check-application-rules-and-structural-health.md) · [Next lesson](13-refresh-a-consistent-outbox-report.md)

A database report often asks more than one question. Imagine looking at two cards on a desk. If someone replaces both cards after you read the first, the two numbers in your notes can come from different editions. A **read snapshot** gives all the questions in one report the same committed edition.

## Before you start

You can read the expected output and trace the steps with pencil and paper. To run the lab, use a checkout of Bits2Banking, CMake 3.24 or newer, Ninja, a C23 compiler, and the SQLite development headers and library. Use a local drive. The program creates its own database of made-up entries and asks for no login or existing database.

## Build and run the lab

Open a terminal from your Bits2Banking checkout. On Windows, use the UCRT64 terminal or use PowerShell with the UCRT64 compiler and SQLite development files already available at `C:\msys64\ucrt64`. Run each command separately and stop if it reports an error.

### PowerShell

```powershell
$env:PATH = 'C:\msys64\ucrt64\bin;' + $env:PATH
cmake -S .\content\labs\native\sqlite-outbox-snapshot -B .\.build\sqlite-outbox-snapshot -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/msys64/ucrt64
cmake --build .\.build\sqlite-outbox-snapshot
ctest --test-dir .\.build\sqlite-outbox-snapshot -V
```

### Bash

```bash
cmake -S ./content/labs/native/sqlite-outbox-snapshot -B ./.build/sqlite-outbox-snapshot -G Ninja
cmake --build ./.build/sqlite-outbox-snapshot
ctest --test-dir ./.build/sqlite-outbox-snapshot -V
```

## Read the result

```text
Before writer commit: entry 1 revision 1 amount 100
Same snapshot after writer commit: entry 2 revision 1 amount 250
New snapshot: entry 1 revision 2 amount 110, entry 2 revision 2 amount 260
Reader write refused. Scratch database removed.
```

The **revision** is the number this lab gives each edition of its practice data. An **outbox** is a record of work an application intends to send. The lab's two sample outbox entries contain integer amounts in pretend minor units. They represent neither payment nor delivery.

1. The reader opens the same file as the writer, but with `SQLITE_OPEN_READONLY`.
2. The reader runs `BEGIN` and reads entry 1. With SQLite's default deferred transaction, the first read establishes the view.
3. The writer updates both entries and commits. The local write-ahead log, or **WAL**, lets that commit happen while the earlier reader remains open.
4. The reader asks for entry 2. It still sees revision 1. Ending the reader transaction and starting a new one makes revision 2 visible.

## Recover from setup problems

If CMake cannot find SQLite, confirm your compiler and SQLite development library come from the same environment. A SQLite command-line program alone may come without headers. If the program cannot enable WAL, move the build to a local filesystem. If it refuses to create `outbox-snapshot-scratch`, choose a fresh build folder. The program refuses to touch a directory already present.

Read [the lab's C23 source](../../../labs/native/sqlite-outbox-snapshot/main.c) after running it. Find `ReadEntry` and identify the call that closes each SELECT statement while leaving the wider read transaction active.

[SQLite explains deferred transactions and committed read views](https://www.sqlite.org/lang_transaction.html#read_transactions_versus_write_transactions).

[Course contents](index.md) · [Previous lesson](11-check-application-rules-and-structural-health.md) · [Next lesson](13-refresh-a-consistent-outbox-report.md)
