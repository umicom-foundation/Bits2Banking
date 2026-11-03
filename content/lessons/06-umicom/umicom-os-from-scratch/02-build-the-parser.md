# Build one real OS component

A small component lets you inspect failures without rebuilding every application. This laboratory compiles the actual OS configuration parser, with a thin demonstration around it. It does not link PID1, mount filesystems or execute configured services.

## Before starting

You need the Bits2Banking and Umicom OS source checkouts, CMake, Ninja and a C23-capable compiler. On Windows the following example uses the UCRT64 compiler. Stop after a failed command and read that command's output.

```text
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/native/os-boot-plan -B build/os-boot-plan -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_OS_SOURCE=C:/umicom/umicomOS -DBUILD_TESTING=ON
cmake --build build/os-boot-plan --parallel 2
ctest --test-dir build/os-boot-plan --output-on-failure --no-tests=error --output-log os-plan-tests.log
& ".\build\os-boot-plan\btb-os-plan.exe"
```

## Expected demonstration output

```text
Host: lesson
1. storage
2. display
Inspection only: no service was executed.
```

The sample lists display first in its input. The parser orders storage before display because display depends on it. Four registered tests cover order, rollback, a cycle and recovery controls. These are expected outcomes for your run, not a claim that your environment has already passed.

## If it fails

A configuration error about `UMICOM_OS_SOURCE` means the source path is missing or points at the wrong folder. A missing executable usually means compilation failed or a multi-configuration generator used a configuration subdirectory. Keep configure, build and test output together; do not interpret an absent executable as a runtime regression.

## Need an earlier explanation?

[Review the foundation concepts](../../00-getting-started/07-applications-os-and-kernel.md), then use the [connected learning map](../../../courses/learning-paths.html#os) for the longer written chapters. For C syntax or compiler commands, use the map's first-programming route before running this lab.

---

[Read this lesson in HTML](../../../courses/umicom-os-from-scratch/lessons/02-build-the-parser.html) · [Learning sequence](../../../start/learning-sequence.md)
