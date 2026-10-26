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


## Monotonic clocks, event outcomes and timed services

- [Monotonic deadline model](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/monotonic-deadlines) — checked unsigned deadlines, clock ordering, due/cancel precedence and failure-atomic state. [Lesson 107](../lessons/05-engineering/107-monotonic-clocks-and-checked-deadlines.md).
- [Timed Notes service](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/timed-service-waits) — compose the existing round-robin scheduler and logical timer; check early signal, tied timeout, cancellation and overflow. [Lesson 109](../lessons/05-engineering/109-compose-a-timed-service-wait.md).
- [Native timer-trace inspector](../lessons/05-engineering/110-inspect-a-timer-trace-in-c23.md) — inspect synthetic event records with C23 using `umicom-education timer-trace --file`, without controlling Kernel interrupts or processes.

## Interrupt ownership and failure recovery

- [Interrupt-ownership laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/interrupt-ownership) — a small C23 source-lease model with checked owner/generation tokens; no privileged instructions.
- [Service-recovery laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/service-recovery) — reuse the same ownership library, retain an accepted Notes revision and explicitly retry only unfinished work.
- [Framework C23 interrupt trace inspector](../lessons/05-engineering/115-inspect-interrupt-ownership-traces.md) — examine 20 fictional events using `umicom-education interrupt-trace --file`.


## Driver lifetimes and diagnostic retention

- [Driver lifecycle laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/driver-lifecycle) — compose the existing C23 service recovery and interrupt owner libraries; test explicit retries and safe stop.
- [Bounded diagnostic-ring laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/diagnostic-ring) — implement an eight-slot C23 ring with overwrite accounting and copied snapshots.


## Device requests and bounded completions

- [Completion Queue](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/completion-queue) — four-slot C23 FIFO with copied results, full/empty checks and wraparound tests; [Lesson 123](../lessons/05-engineering/123-build-a-bounded-completion-queue.md).
- [I/O Request Lifecycle](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/io-request-lifecycle) — reuse the same queue for admission, cancellation, terminal completion and quiescent release; [Lessons 122–124](../lessons/05-engineering/122-device-io-from-submit-to-completion.md).
- [Native device trace inspector](../lessons/05-engineering/125-inspect-device-io-traces-in-c23.md) — read deterministic teaching records without issuing real I/O.


## Device discovery and VirtIO ownership

- [Read a synthetic Flattened Device Tree in C23](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/device-tree-inspector) — build a bounded FDT reader with big-endian decoding and malformed-input tests. Begin with [Chapter 127](../lessons/05-engineering/127-inspect-device-tree-in-c23.md).
- [Model a device queue and DMA-buffer lifetime](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/virtqueue-lifetime) — learn copied ownership, publication, completion, cancellation and reset acknowledgement. Begin with [Chapter 130](../lessons/05-engineering/130-understand-virtio-split-queues.md).


## Block storage and crash-recovery laboratories

- [Write-back sector store — complete C23 laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/writeback-sector-store) — understand staged writes, simulated durability, interrupted flush, exact image import/export and verified recovery. Read [Lesson 133](../lessons/05-engineering/133-build-a-writeback-sector-store.md).
- [Journalled Notes — complete C23 laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/journalled-notes) — write ahead before applying a Notes snapshot, simulate interruptions and replay the newest accepted revision. Read [Lesson 134](../lessons/05-engineering/134-write-ahead-journalling-and-recovery.md).


## FAT16 learning laboratory

- [Read-only C23 FAT16 image inspector](../../labs/native/fat16-inspector/README.md)


## Virtual filesystem laboratories

- [VFS descriptors and RAM-backed Notes](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/vfs-descriptors) — build a C23 VFS, duplicate descriptors, share offsets and safely unlink a file that remains open.
- [Two VFS providers and safe release](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/vfs-provider-composition) — reuse that VFS with an independent read-only provider and test recovery from a refused final release.

## Process file services and local networking

- [Process-owned file service in C23](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/process-file-services) — reuse the previous VFS library to check process byte ranges, copied pathnames, file descriptors and lifetime cleanup. Start with [Chapter 147](../lessons/05-engineering/147-process-owned-file-services.md).
- [Native loopback HTTP server in C23](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/http-loopback-server) — bind `127.0.0.1`, parse limited HTTP/1.1 GET/HEAD requests and answer fixed routes. Start with [Chapter 149](../lessons/05-engineering/149-tcp-ip-and-native-c23-sockets.md).

## Static website preview using the existing C23 HTTP server

The [native loopback HTTP server](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/http-loopback-server) now accepts an **optional read-only static document root**. Without `--root`, all earlier fixed routes and tests remain unchanged. With it, the same C23 listener uses checked URL paths, no-follow file handles, explicit MIME types, GET/HEAD semantics and 8 KiB streaming buffers.

Start with [Chapter 152](../lessons/05-engineering/152-serve-a-static-website-in-c23.md). The `sample_site/` folder contains a complete small HTML/CSS demonstration. Six CTests include two tests for the new static-file facilities, and the website preview can also serve the generated `site/` directory after MkDocs has completed successfully.

## Update 26 — Routing, HTTP responses and service lifetimes

Extend the [existing C23 HTTP server](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/http-loopback-server) rather than creating a competing socket implementation. Register application handlers for `/api/courses`, `/api/status` and `/workshop`; combine them with the original static-file owner when appropriate. Practise response byte accounting and disconnect reporting.

- [157. Route HTTP requests to C23 handlers](../lessons/05-engineering/157-route-http-requests-to-c23-handlers.md)
- [158. Build response headers and support HEAD](../lessons/05-engineering/158-build-http-response-headers-and-head.md)
- [159. Handle disconnected clients and incomplete replies](../lessons/05-engineering/159-handle-http-disconnects-and-response-completion.md)
- [160. Control C23 service lifetimes](../lessons/05-engineering/160-control-c23-web-service-lifetimes.md)
- [161. Follow the same concerns through Umicom](../lessons/05-engineering/161-follow-c23-routes-into-umicom-services.md)


## HTTP conditional caching and bounded admission (Update 27)

The [existing C23 HTTP web-server laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/http-loopback-server) now illustrates **conditional GET and HEAD** through a weak metadata `ETag`, revalidation with `If-None-Match`, `304 Not Modified` without a response body, and a fixed-capacity *serial admission model*. The latter teaches backpressure, active cancellation and ticket ownership; it does not create worker threads or make the socket server concurrent.

- [162. Browser caching and revalidation](../lessons/05-engineering/162-http-caching-and-revalidation.md)
- [163. Add conditional GET in C23](../lessons/05-engineering/163-build-conditional-get-in-c23.md)
- [164. Bounded request admission and backpressure](../lessons/05-engineering/164-bounded-request-admission-and-backpressure.md)
- [165. Run the new HTTP and admission tests](../lessons/05-engineering/165-test-conditional-http-and-admission.md)

## First C programs, one idea at a time

The [first C programs lab](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/first-c-programs) contains five small demonstrations and a checked count function. Follow [C from the Beginning](../courses/c-from-the-beginning/index.html) for explanations of each step, expected output and recovery from errors. Reading and paper tracing need no compiler.
