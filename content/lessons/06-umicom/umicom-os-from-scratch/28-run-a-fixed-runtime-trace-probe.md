<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/28-run-a-fixed-runtime-trace-probe.md

PURPOSE:
Run a fixed runtime trace probe

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Run a fixed runtime trace probe

## Setup recap

Use a trace-enabled Umicom C checkout, a C23 compiler, CMake and Ninja. The commands below build the independent probe on a Windows UCRT64 host. Run each line separately and stop on errors; they do not build or boot the whole OS.

```powershell
Set-Location "C:\umicom\umicomOS"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S boot/cvm-probe -B build/cvm-probe-native -G Ninja -DCMAKE_C_COMPILER=gcc -DUMICOM_C_SOURCE_DIR=C:/umicom/umicom-c -DBUILD_TESTING=ON
cmake --build build/cvm-probe-native --parallel 2
ctest --test-dir build/cvm-probe-native --output-on-failure --no-tests=error
& ".\build\cvm-probe-native\umicom-cvm-probe.exe" --trace-check
```

## Understand the fixed inputs

The trace mode does not read a file or accept arbitrary source. It constructs four reviewed instruction sequences in caller-owned memory and invokes the shared runtime. The successful case produces 42. The other cases check fuel exhaustion before RETURN, division by zero and insufficient trace capacity.

A failed arithmetic row must retain the attempted stack depth and top operand. Insufficient storage must publish zero rows and leave the result unchanged. The probe checks these contracts and prints UMICOM_CVM_TRACE_READY cases=4 only after all four agree. This is an expected marker to verify, not evidence supplied by the lesson.

## Keep ordinary readiness meaningful

Launching without options retains UMICOM_CVM_PROBE_READY value=42. That original marker does not imply that the trace checks ran. Unknown or extra arguments return usage exit 2. The process fixtures check complete stdout, stderr and exit status, so an unrelated success-looking substring cannot hide a failure.

On a Linux host, use the same project with a Linux compiler and launch the executable without .exe. Keep that observation labelled with its own target and toolchain. A host probe result does not establish startup inside a prepared guest image.

## Exercise and recovery

Run the ordinary and trace modes separately after a successful build, then compare their markers. Predict what --trace-check unexpected should do: print usage to stderr, no readiness marker and exit 2.

If trace.h is missing, inspect UMICOM_C_SOURCE_DIR rather than copying a header by itself. The header and library must come from a compatible source tree. If a fixed check fails, retain its case number and reported runtime status before editing the evaluator.

## Read the source

[Open the OS source](https://github.com/umicom-foundation/umicom-os/blob/main/boot/cvm-probe/main.c). Use the matching checkout for qualification.

## Continue learning

[Course contents](index.md) · [Previous: Separate the host, target and image](27-separate-host-target-and-image.md) · [Next: Reuse the Framework preview command](29-reuse-the-framework-preview-command.md)
