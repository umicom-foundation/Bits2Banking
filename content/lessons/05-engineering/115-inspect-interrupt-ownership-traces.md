# 115. Inspect interrupt ownership traces with C23

A successful test tells us whether the program behaved as expected. A **trace** helps us explain *which actions took place and in what order*. The native `umicom-education` command now reads a small binary record format describing fictional interrupt-source ownership.

The trace is a teaching artifact, not a captured Umicom Kernel interrupt log. It cannot tell us whether a real device was acknowledged or a machine register was restored.

## 1. Understand the binary file

The first 16 bytes form a header:

| Offset | Bytes | Meaning |
| --- | ---: | --- |
| 0 | 8 | Magic `UMIIRQ1` followed by a zero byte |
| 8 | 2 | Format version: 1, little-endian |
| 10 | 2 | Flags: must be zero |
| 12 | 4 | Number of records, no more than 4,096 |

Every following record occupies 32 bytes:

| Offset | Bytes | Meaning |
| --- | ---: | --- |
| 0 | 4 | Record number starting at 1 |
| 4 | 1 | Event code (1–9) |
| 5 | 1 | Reserved byte, must be zero |
| 6 | 2 | Source number (1–8) |
| 8 | 4 | Trusted classroom owner identity |
| 12 | 4 | Lease generation number |
| 16 | 8 | Logical tick, never decreasing |
| 24 | 8 | Detail: zero except a fault code (1–255) |

**Little-endian** means the lowest-value byte of an integer comes first in the file, regardless of the processor running the parser. A 32-byte record is fixed size so the parser can reject a truncated final record without guessing where the next event begins.

## 2. Read the nine event types

The inspector recognises CLAIM, ARM, ENTER, ACK, RETURN, CANCEL, FAULT, RECOVER and RELEASE. Source numbers are bounded and each source remembers its last generation. A second CLAIM with the same or an older generation is refused.

The complete state path and its fault/cancellation alternatives are illustrated in [Lesson 112](112-interrupt-ownership-and-critical-sections.md). Notice that the trace is a **decision record**, not an assertion that a CPU performed any of the described actions.

## 3. Run the native inspector

Build Umicom Education with the Framework's standalone teaching CMake project and run its tests. The tests generate a fixture with spaces in its filename:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\tools\umicom-education" `
    -B ".\build\umicom-education" -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON

cmake --build ".\build\umicom-education" --parallel 2
ctest --test-dir ".\build\umicom-education" --output-on-failure

$Education = ".\build\umicom-education\bin\umicom-education.exe"
& $Education interrupt-trace --file `
    ".\build\umicom-education\education-interrupt-trace-test\fixture with spaces\owned interrupt.irq"
```

The inspector should report **20 records, three claims, four arms, three entries, two acknowledgements, two returns, one cancellation, one fault, one recovery and three releases**. The source count reaches two and returns to zero.

## 4. Follow the fault and recovery

Open [`test_interrupt_trace.c`](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/education/test_interrupt_trace.c). The fixture first completes a normal acknowledgement and return, then cancels an armed source. Later, generation 2 of that source enters handling and encounters a recorded fault. A separate RECOVER operation allows the fictional owner to release the lease. Another source finishes normally.

This order allows us to ask specific questions:

1. Why can generation 2 claim source 1 after generation 1 released it?
2. Why must generation 1's old lease no longer work?
3. Why is cancellation refused after ENTER?
4. Why can't a source be released directly from FAULTED?

## 5. Learn how the parser rejects malformed data

The parser checks the complete file size before processing its records. It rejects unknown event codes, out-of-range sources, wrong owner or generation, impossible state changes, time going backwards and nonzero reserved fields.

It keeps a **local** report until the last event has passed. Only then does it copy that report to the caller's output. A corrupted final record therefore cannot partially overwrite a report that previously described a valid file.

The test also runs 20,000 deterministic single-byte mutations. This does not prove the parser free of all defects, but it repeatedly exercises its declared bounds and error paths under compiler and sanitizer checks.

## 6. Try a failure deliberately

Read the test which substitutes CANCEL for ACK after the handler has entered. Trace its state change in your notebook and explain why the parser refuses the record. Then locate the regression test for a reused generation number.

The important result is not simply that an error message appears; it is that **no incomplete state or report is accepted as evidence**.

**Next:** [Lesson 116 — Read Umicom Kernel interrupt ownership source](../06-umicom/116-read-umicom-kernel-interrupt-and-recovery.md).
