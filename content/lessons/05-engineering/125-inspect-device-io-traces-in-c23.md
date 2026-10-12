# 125. Inspect a device I/O trace using native C23

When a driver fails, a list of messages is not enough unless we can establish the order in which its requests changed state. A trace can help us answer which request was submitted, when cancellation was requested, whether a completion was accepted, and when the result was collected.

The Umicom Framework educational command `device-io-trace` reads a **fictional classroom trace**. It does not issue device requests or read privileged Kernel memory.

## A file format that can be checked

The format starts with a 24-byte header and continues with 40-byte records. All multi-byte integers are stored little-endian; the exact layout is documented in the [Framework public header](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/education/device_io_trace.h).

| Offset in record | Size | Meaning |
| --- | ---: | --- |
| 0 | 4 | Record ordinal, starting at one |
| 4 | 1 | Event kind |
| 5 | 1 | Completion outcome, otherwise zero |
| 8 | 4 | Device slot |
| 12 | 4 | Owner identity |
| 16 | 4 | Device generation |
| 20 | 4 | Request identity |
| 24 | 4 | Requested or returned byte count |
| 28 | 8 | Nondecreasing logical tick |
| 36 | 4 | Reserved, must be zero |

The parser checks the declared count against the total file length **before** it reads any record. It checks identities, transitions and completion FIFO order. A reused device slot must carry a newer generation so stale records are refused.

## Run the inspector

After configuring and building the standalone Umicom Education project in `C:\umicom\Umicom-Applications`, run:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
ctest --test-dir ".\build\umicom-education" `
    -R "^framework\.education\.device_io_trace" --output-on-failure
& $Education device-io-trace --file `
    ".\build\umicom-education\education-device-io-test\fixture with spaces\driver requests.dio"
```

The parser test prepares the deterministic file before the CLI test reads it. You should see a summary beginning with `Device I/O trace: 27 records`. It should report five submissions, five completions, five collections and one cancellation request.

## How C23 refuses an invalid record

Read `src/education/device_io_trace.c` in the Framework repository. Find the event switch in `Apply`. A completion is accepted only if its request is still pending and the completion queue has capacity. A cancellation acknowledgement requires an earlier cancellation request. Collecting the result requires the next completed record in FIFO order.

The parser creates a private report and **publishes it only after the whole file passes validation**. This is failure-atomic output. Even a malformed final record must not leave half a summary in a caller-supplied report.

## Explore a failure without editing the production code

The CTest unit test creates mutated copies of the valid trace. It deliberately changes owner generations, completion order, transfer sizes and reserved fields. A 20,000-iteration loop replaces one event with an invalid value and checks that every refused parse preserves the output report.

Run the focused test with `-V` if you want its diagnostic output:

```powershell
ctest --test-dir ".\build\umicom-education" `
    -R "^framework\.education\.device_io_trace$" -V
```

This test corpus is deterministic; it is **not** a claim that every possible malformed file has been explored. The file is not signed or authenticated, so a trace summary alone is not proof of device provenance or persistent storage.
