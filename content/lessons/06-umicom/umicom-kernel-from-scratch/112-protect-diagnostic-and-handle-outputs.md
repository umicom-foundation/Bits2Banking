<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/112-protect-diagnostic-and-handle-outputs.md

PURPOSE:
Protect diagnostic and handle outputs

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Protect diagnostic and handle outputs

A driver can protect every DMA descriptor and still damage its own state through an ordinary C output pointer. In this lesson, trace the actual Umicom block driver and repair that second ownership boundary. You need C pointers, structures and the earlier queue/reset lessons.

## Start with three owners

The domain owns its slot metadata. Each admitted slot owns a queue frame and a bounce frame. The caller owns separate storage for a returned handle or diagnostic record. The device can access the two frames while they are exposed; returning from a timed-out call does not transfer them back to the caller.

Draw those regions before changing code. A pointer is an address, not proof that its region belongs to the caller. Even a read-only disk operation writes a handle to CPU memory, and a probe writes its diagnostic result.

## Follow the existing guard

Open kernel/virtio_block.c in the Kernel repository. UmicomBlockIndependent checks the entire requested output span against the domain and every retained frame in every slot. It rejects a null address or an address range that would wrap. It performs no memory allocation and no device access.

The probe first enters the domain's serial guard, then checks alignment and independence before reading identity registers. Both admission modes now apply this same rule to their handle destinations. Admission also requires an initially zero handle, so a new open cannot silently overwrite an outstanding cleanup obligation.

~~~c
UmicomKernelBlockHandle handle = 0U;
UmicomKernelBlockStatus status =
    UmicomKernelBlockOpen(domain, slot, timeoutTicks, &handle);
if (status != UMICOM_BLOCK_OK && handle != 0U) {
    /* Opening failed, but reset/release still needs this lease. */
    UmicomKernelBlockStatus cleanup = UmicomKernelBlockClose(domain, handle);
    /* Keep handle in caller-owned persistent state if cleanup also fails. */
    (void)cleanup;
}
~~~

This fragment shows the ownership decision; a real caller must retain the handle beyond this scope when cleanup fails. Inspect kernel/block_console.c for the existing retained-close workflow. Do not reset the handle to zero just to make a later Open succeed.

## Diagnose the original omission

Compare the active admission condition with its explained disabled predecessor. The predecessor guarded only writable admission. That distinction concerned disk authority, but the output handle has the same CPU ownership needs in both modes. Probe originally checked only whether outInfo was non-null; its final byte copy could therefore overwrite owner metadata or a live queue.

The repair reuses the common independence function. It does not add another allocator, copy the device adapter or alter the public function signatures. Valid probes still publish observations for empty or unsupported slots. Invalid ownership is refused before MMIO and leaves the destination unchanged after the call returns.

## Exercise the rejection contract

From the Kernel repository, configure the existing native model suite with a GCC-compatible toolchain. A Windows UCRT64 run can use:

~~~powershell
cmake -S tests/virtio_block -B build/host-block -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_BLOCK_SANITIZERS=OFF
cmake --build build/host-block
ctest --test-dir build/host-block -R '^block[.](probe_owner|open_owner|open_nonzero)$' --output-on-failure --no-tests=error
~~~

Stop after a failing command. These tests expect INVALID_ARGUMENT, unchanged owner bytes, unchanged caller storage, no new MMIO operations and no allocation or release. They then perform a valid probe and open/close sequence. A refusal that leaves the domain unusable is still a defect.

Sanitizers are explicitly disabled in this Windows recipe. This is not a sanitizer pass. On a supported ELF host, the project's default address/undefined-behaviour instrumentation can provide additional evidence.

## Review question and boundary

Why is checking only the selected slot insufficient? Another slot can retain exposed pages after a refused reset. The shared guard visits all retained pages before publishing any output.

The guard proves a bounded, disjoint range relative to known owner memory. It cannot establish that an arbitrary address is mapped, writable or alive. Callers still supply valid trusted Kernel storage, and the domain still requires the documented serial execution context. Do not present this API as a user-pointer validator or a malicious-device sandbox.

[Course contents](index.md) · [Previous lesson](111-check-udp-in-the-real-diagnostic-guest.md) · [Next lesson](113-prove-refusal-with-models-and-a-real-guest.md)
