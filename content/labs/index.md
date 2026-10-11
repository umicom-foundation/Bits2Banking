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

## Native archives, linker maps and target architectures

- [Static library and linker map](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/static-library-map) — compile a fictional C23 ledger library, test exact pence arithmetic, read the archive with `umicom-education archive`, follow a linker map and install privately. [Lessons 77–79](../lessons/05-engineering/77-understand-static-archives.md).
- [Cross-target object compilation](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/cross-target-object) — compare host objects with RISC-V64 ELF objects and inspect one privileged Assembly instruction without running it. [Lesson 80](../lessons/05-engineering/80-cross-compile-c23-riscv64.md).

## Linker symbols and C23/Assembly ABI

- [C23 and Assembly linker-relocations laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/linker-relocations) — build one public C23 API and an ABI-specific Assembly leaf function; test overflow contracts and inspect native object symbols. [Lessons 82–86](../lessons/05-engineering/82-inspect-elf-symbols-in-c23.md).


## Kernel memory foundations (C23, without privileged execution)

- [Physical frame pool](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/physical-frame-pool): protect boot-reserved frames, allocate the lowest free frame and refuse invalid releases. [Chapter 88](../lessons/05-engineering/88-physical-pages-and-frame-ownership.md).
- [Sv39 virtual-address translation](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/sv39-address-translation): walk three 512-entry tables, preserve the 12-bit offset and enforce R/W/X permissions. [Chapter 89](../lessons/05-engineering/89-sv39-virtual-address-translation.md).
- [ELF PT_LOAD inspection](../lessons/05-engineering/87-read-elf-program-headers-and-load-plan.md): use Framework's read-only C23 `umicom-education load-plan` command and portable synthetic RISC-V64 fixture.


## Process address spaces, faults and state transitions

- [Page-fault model](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/page-fault-model): mapped and unmapped pages, R/W/X access rights, canonical Sv39 addresses and failure-atomic outputs. [Lessons 92–93](../lessons/05-engineering/92-understand-a-process-address-space.md).
- [Process lifecycle](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/process-lifecycle): admit, dispatch, yield, wait, wake and exit with explicit revision checks. [Lesson 95](../lessons/05-engineering/95-model-a-process-lifecycle-in-c23.md).
- [ELF W^X audit](../lessons/05-engineering/94-review-executable-memory-protection.md): inspect safe and suspicious segment layouts using Framework's `umicom-education memory-audit --file`.

## Kernel services and copied IPC messages

- [Copied-message channel](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/bounded-channel) — a bounded C23 FIFO with recipient checks, complete copied payloads and deterministic capacity failures. [Lesson 98](../lessons/05-engineering/98-build-a-copied-message-channel.md).
- [Checked service-request dispatcher](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/syscall-dispatch) — read a training clock, validate publishing rights and refuse stale versions before changing state. [Lesson 100](../lessons/05-engineering/100-design-checked-service-requests.md).
- [Framework IPC trace inspector](../lessons/05-engineering/99-inspect-an-ipc-trace-with-c23.md) — examine synthetic SEND/RECEIVE records using `umicom-education ipc-trace --file`, without real IPC.

## Scheduling, blocking IPC and service lifetimes

- [Round-robin scheduler](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/round-robin-scheduler) — a FIFO ready ring with waiting, waking, task generations and two automated tests. [Lesson 102](../lessons/05-engineering/102-understand-round-robin-scheduling.md).
- [Blocking IPC service](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/blocking-ipc-lifetimes) — compose the existing message queue and scheduler, then check delivery and cancellation separately. [Lesson 103](../lessons/05-engineering/103-wait-and-wake-without-spinning.md).
- [Native scheduling trace inspector](../lessons/05-engineering/105-inspect-a-scheduler-trace-with-c23.md) — observe a synthetic little-endian trace without running privileged tasks or claiming Kernel audit evidence.

