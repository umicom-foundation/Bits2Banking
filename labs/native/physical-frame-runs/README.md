<!--
Umicom Bits2Banking
File: labs/native/physical-frame-runs/README.md

PURPOSE:
Teach aligned runs with the production Kernel allocator and explicit hosted qualification.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Physical frame runs in the Umicom Kernel

![Umicom](../../../content/assets/branding/umicom-logo.svg)

This C23 laboratory calls the real Kernel allocator. Four scenarios explain alignment, fragmentation, complete release and compatibility with single-page ownership. The physical addresses are synthetic integers; no address is dereferenced and no device is opened.

## Prepare source and tools

Use the Kernel checkout containing AllocateFrames and FreeFrames in its physical_memory header and implementation. Also provide Framework's canonical application-branding helper. GCC or Clang must support C23; CMake 3.24 or newer and Ninja are required. On Windows, the commands below use MSYS2 UCRT64.

Run each command separately and stop on an error.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/native/physical-frame-runs -B build/physical-frame-runs -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_KERNEL_SOURCE=C:/umicom/umicom-kernel -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework -DBUILD_TESTING=ON
cmake --build build/physical-frame-runs --parallel 2
ctest --test-dir build/physical-frame-runs --output-on-failure --no-tests=error
.\build\physical-frame-runs\physical-frame-runs.exe alignment
.\build\physical-frame-runs\physical-frame-runs.exe fragmentation
.\build\physical-frame-runs\physical-frame-runs.exe release
.\build\physical-frame-runs\physical-frame-runs.exe coexist
~~~

~~~bash
cd ~/umicom/Umicom-Bits2Banking
cmake -S labs/native/physical-frame-runs -B build/physical-frame-runs -G Ninja -DCMAKE_C_COMPILER=gcc -DUMICOM_KERNEL_SOURCE="$PWD/../umicom-kernel" -DUMICOM_FRAMEWORK_SOURCE="$PWD/../Umicom-Applications/framework" -DBUILD_TESTING=ON
cmake --build build/physical-frame-runs --parallel 2
ctest --test-dir build/physical-frame-runs --output-on-failure --no-tests=error
./build/physical-frame-runs/physical-frame-runs alignment
./build/physical-frame-runs/physical-frame-runs fragmentation
./build/physical-frame-runs/physical-frame-runs release
./build/physical-frame-runs/physical-frame-runs coexist
~~~

## Predict the results

| Scenario | Observation to verify |
|---|---|
| alignment | Three pages start at 0x4000 despite RAM beginning at 0x1000. Release restores sixteen free pages. |
| fragmentation | Eight isolated free pages cannot satisfy two consecutive pages. Releasing one lab-owned reservation permits a run at 0x1000. Final free count is nine with seven reservations. |
| release | A four-page release with a hole is refused. Three allocated pages remain until the example releases their actual extents. |
| coexist | A single page and a three-page run share the same bitmaps; releasing both restores the baseline. |

These are acceptance expectations, not reported passes. Retain the output, exit codes and exact source revision when running them.

## Read and extend

Read [main.c](main.c), then [course lessons 90–93](../../../content/courses/umicom-kernel-from-scratch/lessons/90-align-a-physical-frame-run.html). Change one request at a time and predict the resulting addresses and counts. Do not add a second allocator to the lesson; improve shared Kernel code and its isolated tests when the contract needs new behavior.

The Kernel's tests/physical_memory project contains the broader refusal and boundary suite. Its docs/PHYSICAL_FRAME_RUNS.md describes host qualification and the separate no-runtime link target.

## Branding and troubleshooting

The hosted executable uses Framework's application-branding helper for canonical SVG and Windows ICO resources. Inspect the built Windows icon and staged assets during qualification. A terminal controls its own font, so the program does not force a font or claim that resource embedding changes console typography. The course reader uses its existing Umicom style and appearance settings.

A missing API declaration usually means UMICOM_KERNEL_SOURCE points to an older checkout. A missing brand helper means UMICOM_FRAMEWORK_SOURCE is incorrect. Correct the path and reconfigure; do not bypass the checks. If compilation fails, stop before running stale executables.

This is serialized ownership bookkeeping. It does not qualify physical RAM access, page tables, DMA, cache coherence, SMP, a loader or a bootable ISO.
