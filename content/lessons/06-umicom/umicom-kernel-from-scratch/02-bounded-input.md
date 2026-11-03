# A byte span is not a string

A receive buffer can contain three digits without a terminating NUL. Passing it to an interface that expects a string can read beyond the owned buffer. A span supplies both a pointer and a length; it allows a parser to stop exactly at the declared boundary.

```text
const char received[3] = {'1', '2', '3'};
UmicomU64 value = 0U;
UmicomBoolean accepted =
    UmicomKernelShellUnsignedSpan(received, sizeof received, &value);
```

The Kernel API accepts decimal digits, including leading zeros. It rejects empty input, embedded NUL, non-digits and overflow. The output value changes only after complete success. The old string interface remains available and delegates to the bounded implementation after finding a terminator within the console limit.

## Build the real parser lab

```text
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/native/kernel-bounded-input -B build/kernel-bounded-input -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_KERNEL_SOURCE=C:/umicom/umicom-kernel -DBUILD_TESTING=ON
cmake --build build/kernel-bounded-input --parallel 2
ctest --test-dir build/kernel-bounded-input --output-on-failure --no-tests=error --output-log kernel-input-tests.log
& ".\build\kernel-bounded-input\btb-kernel-input-demo.exe"
```

Expected output begins `Accepted bounded value: 123`. Stop on errors. A missing span symbol means the lesson and Kernel API revisions do not agree; integrate the corresponding Kernel update rather than duplicating the function inside the lesson.

## Need an earlier explanation?

[Review the foundation concepts](../../00-getting-started/04-memory-storage-and-information.md), then use the [connected learning map](../../../courses/learning-paths.html#kernel) for the longer written chapters. For C syntax or compiler commands, use the map's first-programming route before running this lab.

---

[Read this lesson in HTML](../../../courses/umicom-kernel-from-scratch/lessons/02-bounded-input.html) · [Learning sequence](../../../start/learning-sequence.md)
