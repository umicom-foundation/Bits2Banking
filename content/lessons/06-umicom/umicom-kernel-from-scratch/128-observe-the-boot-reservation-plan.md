<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/128-observe-the-boot-reservation-plan.md

PURPOSE:
Explain the Kernel's RISC-V boot handoff using the native reservation plan.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Observe the boot reservation plan

[Previous lesson](127-decode-option-values-before-changing-connection-state.md)

![Umicom](../../../assets/branding/umicom-wordmark-on-dark.svg)

## Read the exact image and its reserved pages

A page is a fixed-size block of memory. Before the Kernel can allocate free
pages, boot code reserves the pages that hold the Kernel, its firmware device
tree, or memory owned by firmware.

The RISC-V handoff is a checked description of what boot reserved. The
synthetic Kernel image begins at `0x80200000` and spans `0x9000` bytes. The
boot plan also reserves the RAM before that image. Keeping the exact image and
the page plan in the same report helps a reviewer explain each address.

## Run the host exercise

1. From the Bits2Banking checkout, use C23, CMake and Ninja to build the handoff
   lab. Set the Kernel path to a checkout with `kernel/riscv_boot_handoff.c`.
   Set the Framework path if the default adjacent checkout is unavailable.
2. Run `boot-handoff-reservations review`. Expect one RAM range and three
   reserved spans. The reported firmware span begins at `0x80300000` and has
   `8192` bytes.
3. Run `boot-handoff-reservations unreserved`. The program removes the
   device-tree page from the synthetic plan. Expect
   `Refused uncovered FDT, previous observation retained.` The earlier
   report must stay unchanged.

```powershell
cmake -S labs/native/boot-handoff -B build/boot-handoff -G Ninja -DUMICOM_KERNEL_SOURCE=C:/umicom/umicom-kernel
cmake --build build/boot-handoff
& ./build/boot-handoff/boot-handoff-reservations.exe review
& ./build/boot-handoff/boot-handoff-reservations.exe unreserved
ctest --test-dir build/boot-handoff --output-on-failure --no-tests=error
```

If the executable is missing, check that the configured Kernel source includes
the RISC-V adapter and reconfigure. If a case returns a nonzero exit code, read
its output from CTest before changing the example.

## Predict the page count

Firmware asks to protect `4096` bytes starting at `0x80300123`. The start lies
inside one 4096-byte page and the end lies inside the next. When the Kernel
rounds the boundaries outward, the plan contains two pages. A request beginning
at `0x80300000` for `4096` bytes would occupy one page.

The hosted run uses invented addresses and never reads from them. To observe
a running guest, build the Kernel's RISC-V startup checks and run
`kernel.riscv64.boot_handoff_normal`. Compare the normal, required-service
failure and forced-recovery transcripts.

- [Kernel reservation plan](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/boot_reservations.c)
- [Hosted lab instructions](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/boot-handoff/README.md)
- [Qualify normal boot at separate boundaries](99-qualify-normal-boot-at-separate-boundaries.md)
- [Course contents](index.md)

[Next lesson on the x64 Kernel stack](129-set-up-the-x64-kernel-stack.md)
