<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/multikernel-systems/07-check-a-core-owned-memory-range.md

PURPOSE:
Check a core-owned memory range.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material.
-->

# Check a core-owned memory range

<p class="umicom-course-artwork"><span class="umicom-brand-mark"><img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom" width="180"></span> <a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="30"></a></p>

[Course contents](index.md) · [Previous lesson](06-qualify-a-kernel-experiment.md) · [Next lesson](08-qualify-a-bootable-release-in-stages.md)

A firmware memory map tells the kernel where memory exists. A reserved region may already belong to firmware or a device. An ownership record says which part an allocator or execution domain may use. Another core learns these facts from a report or message. A count of available bytes gives it no permission to use an arbitrary address.

A **half-open range** includes its first address and excludes its end. The range `[4096, 8192)` contains 4096 bytes. Byte 8191 fits. Byte 8192 is outside this range. In the exercise, owner 2 is just an example identifier.

## Build and test the C23 lab

1. Open a terminal in the Bits2Banking repository. Check that CMake, Ninja and a C23 compiler are available. Run the three commands below. Use a fresh build folder if this name already belongs to a different configuration.
2. Expect nine passing tests. `last-byte` should admit a one-byte request at 8191. `starts-at-end`, `crosses-end` and `wrong-owner` should refuse their requests. A passing refusal test means the source followed its contract.
3. Open `main.c` and find `contains_request`. Work out the number of bytes left from the requested start before comparing lengths. For a start of 8191 the range has one byte left. Explain why the exercise first checks that adding a start and length cannot wrap.
4. If CMake cannot find the compiler, select your installed C23 toolchain and configure a new build directory. If a test fails, use `ctest --test-dir build/memory-owner --rerun-failed -V` and separate the program output from the test result.

```powershell
cmake -S content/labs/native/multikernel-memory-owner -B build/memory-owner -G Ninja
cmake --build build/memory-owner
ctest --test-dir build/memory-owner --output-on-failure
```

## Practice

Draw a free range next to a reserved one. Label the exclusive end and predict the outcome for a request spanning their boundary. A hart is a RISC-V hardware thread. Describe how a readiness message emitted by a second hart could confirm its identity and current startup attempt. This lab runs as an ordinary hosted C program and uses fictional addresses.

## Apply it to Umicom

Umicom Kernel can use allocator admission observations when it describes startup memory. Umicom Framework can carry workload identity and requested resources to the owner. Umicom OS selects the supported execution and recovery path. This example models one already-recorded authority, without memory mapping or cross-core enforcement.

[C23 lab source](../../../labs/native/multikernel-memory-owner/main.c) · [Barrelfish architecture overview](https://barrelfish-test.systems.ethz.ch/publications/TN-000-Overview.pdf)

