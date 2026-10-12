# Keep useful diagnostics in bounded memory — C23 laboratory

When a service produces more diagnostic records than a fixed memory budget can
hold, it must either reject new records or replace old ones. This exercise uses
a small, eight-entry **circular buffer**. The oldest diagnostic is replaced
when the ring is full, and the number of overwritten rows is recorded.

## Build on Windows (PowerShell)

From `C:\umicom\Umicom-Bits2Banking`:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\diagnostic-ring -B .\output\learning-build\diagnostic-ring -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build .\output\learning-build\diagnostic-ring --parallel 2
ctest --test-dir .\output\learning-build\diagnostic-ring --output-on-failure
```

Run the demonstration. Its expected output is:

```text
Retained rows: 8. Overwritten rows: 2. First sequence: 3.
```

The tests also reject backwards logical time, invalid source IDs, invalid
codes, copied live ring objects and exhausted sequence numbers. A snapshot
contains **copies** of record values, not pointers into the live ring.

This buffer is not a durable or forensic evidence store: power loss loses all
entries, overwritten rows cannot be recovered and no signature identifies the
producer. See the companion Framework `evidence-trace` inspector for a
separate example of a SHA-256-linked read-only teaching file. Neither example
should be presented as a secure audit trail.
