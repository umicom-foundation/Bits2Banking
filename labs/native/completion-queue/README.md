# Completion queues in C23

An I/O driver may finish a request before its caller is ready to read the result. A **completion queue** retains the result until the caller explicitly collects it. This exercise stores **copied values**, not pointers to another function's stack.

## Build on Windows (PowerShell)

From `C:\umicom\Umicom-Bits2Banking`:

```powershell
cmake -S .\labs\native\completion-queue -B .\output\learning-build\completion-queue -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build .\output\learning-build\completion-queue --parallel 2
ctest --test-dir .\output\learning-build\completion-queue --output-on-failure
```

Both tests should pass. The demonstration prints `Collected completion for request 42: 128 bytes.`

## Follow the source

Open `queue.h` before `queue.c`. The public header declares the stored record, the queue capacity and operation status. `Push` checks capacity **before changing any field**. `Pop` copies the result to the caller only when an item is present. The ring wraps its index after reaching the fourth slot.

Try reducing `BTB_COMPLETION_CAPACITY` from four to three. Predict which assertion in `test_queue.c` will need changing, then restore the original value before committing.

The queue is single-threaded. Real multi-threaded queues need synchronisation and a documented memory-ordering policy; adding `volatile` alone is not sufficient.
