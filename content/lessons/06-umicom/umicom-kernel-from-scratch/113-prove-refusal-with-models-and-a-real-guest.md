<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/113-prove-refusal-with-models-and-a-real-guest.md

PURPOSE:
Prove refusal with models and a real guest

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Prove refusal with models and a real guest

A successful error return is only part of a driver regression. This lesson combines controlled host faults with a named virtual device, using the caller-output checks introduced in the previous lesson. The objective is to distinguish what each environment actually proves.

## Establish the observation before the call

Read OutputOwnership in tests/virtio_block/virtio_block_tests.c. The fixture saves every byte of the domain, the model RAM and independent caller storage. It also saves MMIO read/write counters and physical allocation/release counters. Only then does it make the deliberately invalid call.

The owner snapshot includes the serial busy flag. The guard may change that flag during a call, but it must restore it before returning. The RAM comparison catches accidental writes even when the API eventually reports an error. Counter comparisons catch premature register access that a byte snapshot cannot detect.

## Separate active and retained DMA

Run the active and retained-page cases:

~~~powershell
ctest --test-dir build/host-block -R '^block[.](probe|open)_(queue|data|retained_queue|retained_data)$' --output-on-failure --no-tests=error
~~~

The retained cases first open the real driver against the register model, then make reset acknowledgement stop arriving. Close must report RESET_PENDING and retain both pages. Probe and Open must refuse outputs in those pages too. Finally, the fixture allows reset to complete and verifies that a later Close releases the memory.

This model can inject a nonresponsive reset deterministically. It does not execute RISC-V fences, emulate a bus or demonstrate real hardware timing. There is no asynchronous cancellation API in this driver; the tested lifecycle is synchronous timeout followed by explicit reset/retry.

## Check a named virtual device

The root Kernel CMake project registers kernel.riscv64.read_only_block when QEMU is available. It uses virtio-blk-device, modern MMIO and the repository's synthetic raw fixture with readonly=on. Run it from an already configured Kernel checkout:

~~~powershell
cmake --preset riscv64-clang-debug
cmake --build --preset riscv64-clang-debug
ctest --preset riscv64-clang-debug -R '^kernel[.]riscv64[.](block_without_device|read_only_block)$' --output-on-failure --no-tests=error
~~~

The CTest build fixture checks the current image before execution. Do not substitute a physical disk or remove readonly=on. The existing fixture is deterministic test input, not a filesystem image.

In kernel/virtio_block_validation.c, the guest refuses an occupied handle and a diagnostic destination inside the owner. After admission it refuses destinations in the actual queue and bounce pages. Successful normal reads then demonstrate that the queue still works after those refusals. Look for the following marker followed by successful sector checks and the final acceptance marker:

~~~text
block.output-ownership=refused-before-io
block.first-sector=verified
block.multi-sector-and-ring-reuse=verified
UMICOM_KERNEL_READ_ONLY_BLOCK_READY
~~~

The marker identifies the checked code path. Host MMIO counters provide the direct no-I/O observation; the guest checks refusal and continued operation. A marker copied from an older transcript does not identify the current source, and a no-device acceptance marker does not prove any sector read.

## Build a defensible evidence record

Record the toolchain, source content identity, exact configure/build/test commands, exit codes and test transcript. Keep the pre-repair failing cases as well as the repaired results. Re-run the writable suite because both admission paths share the changed guard:

~~~powershell
cmake -S tests/virtio_block_write -B build/host-block-write -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_BLOCK_WRITE_SANITIZERS=OFF
cmake --build build/host-block-write
ctest --test-dir build/host-block-write --output-on-failure --no-tests=error
~~~

If a build fails, resolve that failure before interpreting test output. If no tests are found, check the configured source directory and QEMU discovery; do not remove --no-tests=error to obtain a green command.

## Extend the experiment

Explain why a passing QEMU read cannot prove that every physical device stops DMA correctly, and why a host snapshot cannot prove I/O fence ordering. Then add a new meaningful fault to the existing model, with an unchanged-output assertion and successful cleanup. Do not replace the real driver with a second implementation inside the test. A network driver, noncoherent cache management and multi-hart synchronization require their own contracts and evidence.

[Course contents](index.md) · [Previous lesson](112-protect-diagnostic-and-handle-outputs.md) · [Next lesson](114-qualify-private-vm-locals-in-user-mode.md)
