# Practical source-code exercises

Each project below contains the editable source files used by the programming chapters. Open the files in an editor, run the example and then make one small change to confirm that you understand what it does.

| Project | Files | Related lessons |
| --- | --- | --- |
| C notes programme | [`notes.c`](c-notes/notes.c) | [C](../lessons/03-native-code/09-c.md) |
| C++ notes journal | [`notes.cpp`](cpp-notes/notes.cpp) | [C++](../lessons/03-native-code/10-cpp.md) |
| Python notes with tests | [`notes.py`](python-notes/notes.py), [`test_notes.py`](python-notes/test_notes.py) | [Python](../lessons/02-programming/07-python.md) |
| Java journal example | [`LedgerDemo.java`](java-ledger/LedgerDemo.java) | [Java](../lessons/03-native-code/11-java.md) |
| Web task board | [`board.html`](task-board/board.html), [`board.css`](task-board/board.css), [`board.js`](task-board/board.js) | [HTML](../lessons/04-web/12-html.md), [CSS](../lessons/04-web/13-css.md), [JavaScript](../lessons/04-web/14-javascript.md) |
| PHP tasks | [`index.php`](php-tasks/index.php) | [PHP](../lessons/04-web/15-php.md) |
| SQLite tasks | [`tasks_db.py`](sqlite-tasks/tasks_db.py) | [Databases](../lessons/05-engineering/19-databases.md) |
| CMake task count | [`main.c`](task-count/main.c), [`CMakeLists.txt`](task-count/CMakeLists.txt) | [Build and test](../lessons/05-engineering/18-build-and-tests.md) |

The repository contains source files rather than compiled programs. Build outputs and personal data files should remain outside version control.

## Native C23 laboratories

The [safer C notes laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/safe-notes) introduces a bounded Notes model, separate header and implementation, CMake targets and CTest. Its source files are in the repository's `labs/native/safe-notes` directory.

The [HTTP header-scanner laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/http-header-scanner) compares a C23 implementation with x86-64 or RISC-V Assembly using the same test cases.

## Processor and binary-data exercises

- [Assembly functions laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/assembly-functions) compares Windows x64, System V x86-64 and RISC-V64 argument registers. [Lesson 53](../lessons/03-native-code/53-call-assembly-from-c.md).
- [Binary payment records laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/binary-payment-records) demonstrates explicit widths, big-endian representation and rejection without partial writes. [Lesson 55](../lessons/03-native-code/55-write-a-safe-binary-record-in-c.md).

## Safer C23 and memory management

- [Owned Notes laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/owned-notes): C23 opaque handles, deep copies, dynamic allocations and failure-atomic edits. [Lesson 58](../lessons/03-native-code/58-memory-ownership-in-c23.md).
- [Checked fictional accounts laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/checked-money): exact minor currency units, checked integer arithmetic, revision validation and two-record rollback-on-failure behaviour. [Lesson 59](../lessons/03-native-code/59-checked-arithmetic-and-money.md).
## Testing failures, not only successful runs

- [Allocator failure injection](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/fault-injection) — C23 deep-copy ownership and an allocator which can fail at a chosen call. [Lesson 64](../lessons/03-native-code/64-test-allocation-failures.md).
- [Bounded HTTP request-line parsing](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/http-byte-parser) — parse exact byte spans, reject incomplete requests, and run deterministic malformed-input tests. [Lesson 65](../lessons/03-native-code/65-parse-bounded-http-bytes.md).

## Pointers, arenas and defensive parsing

- [Arena Allocator laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/arena-allocator) — construct a temporary Notes report with checked alignment and checkpoints. [Lesson 68](../lessons/03-native-code/68-arenas-and-checkpoints.md).
- [Bounded ledger-line laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/bounded-ledger-line) — decode exact bytes, detect integer overflow and fuzz malformed fictional records. [Lesson 69](../lessons/03-native-code/69-bounded-byte-slices.md).

## Object files and reusable libraries

- [Course catalogue static-library laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/course-catalogue-library) — build a C23 static library, link it into an application and test, inspect its symbols, and diagnose an intentionally missing library. [Lessons 72–73](../lessons/05-engineering/72-source-to-machine-code.md).
- [Native ELF/PE/COFF inspection](../lessons/05-engineering/74-read-elf-pe-coff-with-c23.md) — run the Framework-owned `umicom-education binary --file` command against an executable, object file or Umicom Kernel image.
