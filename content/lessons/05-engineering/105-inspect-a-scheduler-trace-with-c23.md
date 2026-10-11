# 105. Read a scheduling trace using native C23

Logs and traces make invisible system events easier to investigate. A trace is a sequence of records describing what a programme observed or attempted. A trace is not automatically a trustworthy account of what happened inside a kernel.

This lesson uses a versioned educational trace and a new Framework-owned inspector to show how Ready, Running and Waiting states change.

## 1. Find the native inspection command

After building Umicom Education, you can run:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"

& $Education schedule-trace --file `
    ".\build\umicom-education\education-schedule-trace-test\fixture with spaces\round robin.sch"
```

The file above is produced by the automated scheduler-trace test. Run `ctest` first so it exists. This is a synthetic classroom trace, **not** a recording of Umicom Kernel activity.

## 2. Understand the fixed-length binary format

The file begins with a 16-byte header and contains 24 bytes per event record.

```text
Header (16 bytes)
  offset  0 : seven ASCII bytes `UMISCH1` followed by one zero byte
  offset  8 : version, little-endian 16-bit integer (1)
  offset 10 : flags, little-endian 16-bit integer (0)
  offset 12 : record count, little-endian 32-bit integer

Each record (24 bytes)
  offset  0 : ordinal number, LE32
  offset  4 : event kind, U8
  offset  5 : flags, U8 (0)
  offset  6 : reserved, LE16 (0)
  offset  8 : task identity, LE32
  offset 12 : wait key, LE32, or zero
  offset 16 : logical tick, LE64
```

**Little-endian** means the least-significant byte of a multibyte integer is stored first. A logical tick is just a nondecreasing counter value used for ordering. It is not a measured processor cycle or elapsed real time.

The header's record count must exactly match the file length. The inspector refuses extra bytes, incomplete records, unexpected format versions and traces containing more than 4,096 records.

## 3. Interpret the event types

| Event | Preconditions | Effect |
|---|---|---|
| ADMIT | New nonzero task ID | Add task to back of Ready queue |
| DISPATCH | Task is oldest Ready; processor is idle | Make task Running |
| YIELD | Matching task is Running | Put task at back of Ready queue |
| WAIT | Matching task Running; nonzero key | Make task Waiting |
| WAKE | Task Waiting; same key | Put task into Ready queue |
| EXIT | Matching task Running | Stop task |
| CANCEL | Task Waiting; same key | Stop task and discard wait registration |

The inspector rejects a DISPATCH that skips an older Ready task, or a WAKE that does not match the saved wait key. It also rejects task IDs reused within the same trace.

## 4. Inspect the C23 parser

Open [`schedule_trace.c`](https://github.com/umicom-foundation/umicom-framework/blob/main/src/education/schedule_trace.c) and the [public format definition](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/education/schedule_trace.h).

Three functions perform different jobs:

1. `Read32` reads a four-byte integer without casting untrusted input to an unaligned machine pointer.
2. `Apply` validates one proposed state transition against its current task and queue state.
3. `UmiEducationScheduleTraceInspect` checks the complete format before storing a report in the caller's output.

The parser uses no heap allocation. Its task table and ready queue have fixed capacities. The file wrapper does allocate one bounded input buffer and frees it after inspection.

## 5. Build, test and run

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\tools\umicom-education" `
    -B ".\build\umicom-education" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\build\umicom-education" --parallel 2
ctest --test-dir ".\build\umicom-education" `
    -R "framework\.education\.schedule_trace" --output-on-failure
```

The two new tests create and inspect a trace in a directory containing spaces. The report begins:

```text
Scheduler trace: 11 records
Admitted: 2 | Dispatched: 4 | Yielded: 1
Waits: 1 | Wakes: 1 | Exits: 2 | Cancelled: 0
Peak ready: 2 | Peak waiting: 1
```

The parser test also changes more than 20,000 individual byte positions across deterministic trials. A random change can still produce a valid record; the purpose is to ensure that malformed input never causes unsafe memory access or a partially published report.

## 6. Practise

In `test_schedule_trace.c`, find the case that changes a wake key from 7 to 8. Predict the result, then run the test. Next, find the deliberately incorrect FIFO dispatch and explain why the inspector rejects it. Finally, explain why a successful parsing report cannot prove that the real kernel correctly handled an interrupt or a syscall.

Continue with [Lesson 106 — Follow the actual Kernel scheduler](../06-umicom/106-follow-umicom-kernel-scheduler-and-ipc.md).
