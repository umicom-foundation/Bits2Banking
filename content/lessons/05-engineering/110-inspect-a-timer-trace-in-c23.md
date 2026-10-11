# 110. Inspect an event and timer trace using native C23

Testing an application is easier when we can describe **what happened**, not just whether the last screen looked correct. A trace is a sequence of records describing observations and decisions in an agreed format.

The Framework-owned `umicom-education` tool can now inspect a small, explicitly versioned classroom timer trace. It uses C23. The file is not a Kernel event log and contains no private application data.

## 1. Read the format before reading the parser

The trace begins with a 16-byte header:

| Byte offset | Width | Meaning |
| --- | ---: | --- |
| 0 | 8 | Exact magic bytes `UMITMR1` followed by a zero byte |
| 8 | 2 | Version 1, little-endian |
| 10 | 2 | Flags: zero |
| 12 | 4 | Number of records, at most 4,096 |

Each record occupies **32 bytes**:

| Offset | Width | Meaning |
| --- | ---: | --- |
| 0 | 4 | One-based record number |
| 4 | 1 | WAIT=1, SIGNAL=2, CANCEL=3, ADVANCE=4 |
| 5 | 1 | Flags: zero |
| 6 | 2 | Reserved: zero |
| 8 | 4 | Wait identity (zero only for ADVANCE) |
| 12 | 4 | Event key (zero only for ADVANCE) |
| 16 | 8 | Logical tick |
| 24 | 8 | WAIT interval; zero for other event types |

All multi-byte fields are encoded in **little-endian** order, independent of the host processor. Record order and exact file length are checked before the model accepts any event.

A WAIT with a zero interval has no finite deadline. A positive interval is limited to 10,000,000 logical ticks, and the parser rejects `currentTick + interval` if that addition would overflow `uint64_t`.

## 2. Reconstruct one reproducible timeline

The included CTest fixture records this sequence:

```text
Tick 10: advance the clock
Tick 10: task 10 waits for event 7, 5-tick deadline
Tick 10: task 20 waits for event 8, no deadline
Tick 12: advance the clock
Tick 12: signal event 8 to task 20
Tick 15: advance the clock; task 10 times out
Tick 15: task 30 waits for event 9, 3-tick deadline
Tick 15: cancel task 30's wait
Tick 16: advance the clock
Tick 16: task 40 waits for event 10, 1-tick deadline
Tick 17: advance the clock; task 40 times out
```

The expected summary is **11 records, four waits, one signal, two timeouts, one cancellation and no pending waits**.

A deliberate `ADVANCE` operation is the only event that changes the logical clock. Other events must use that currently published tick. In this model a newly reached deadline is settled before a later signal can succeed.

## 3. Read the implementation

Open [`src/education/timer_trace.c`](https://github.com/umicom-foundation/umicom-framework/blob/main/src/education/timer_trace.c) and find `Apply()`.

The parser owns a temporary table of at most 32 distinct wait identities. A SIGNAL or CANCEL must match an existing pending identity and event key. Identities cannot be reused in one trace, which prevents an old signal from mistakenly completing a later wait with the same name.

At the end, the parser assigns the complete local report to the caller's output only when **every** record has been accepted. If a malformed final record is found, the caller's previous report remains intact.

## 4. Build and inspect the test trace

After integrating Update 16 into Umicom Framework:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\tools\umicom-education" `
    -B ".\build\umicom-education" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON

cmake --build ".\build\umicom-education" --parallel 2
ctest --test-dir ".\build\umicom-education" --output-on-failure

$Education = ".\build\umicom-education\bin\umicom-education.exe"
& $Education timer-trace --file `
    ".\build\umicom-education\education-timer-trace-test\fixture with spaces\clock events.tmr"
```

The CTest suite creates the fixture; the CLI does **not** create it automatically. The output should start with `Timer trace: 11 records`. Check that the counters correspond to the timeline above.

## 5. Why record validation matters

A corrupted byte count must not make a native parser read beyond its buffer. A duplicated identity must not inherit a completed wait. A retroactive clock value must not pretend that time went backwards. A very large interval must not become a small deadline through overflow.

The new regression test checks truncated records, wrong event keys, late signals, reserved fields, duplicate identities, overflow, capacity limits, paths containing spaces and 20,000 deterministic byte mutations. A mutated input may happen to remain valid; the essential property is that the parser never reads outside its declared bounds and returns a coherent result.

**Practise:** Trace the record numbered 6 and explain why task 10 times out at tick 15. What happens if the SIGNAL for task 20 uses key 9 instead of key 8? What would go wrong if malformed input partially overwrote the existing report?

Continue with [Lesson 111 — Follow Umicom Kernel timers and events](../06-umicom/111-follow-umicom-kernel-timers-and-events.md).
