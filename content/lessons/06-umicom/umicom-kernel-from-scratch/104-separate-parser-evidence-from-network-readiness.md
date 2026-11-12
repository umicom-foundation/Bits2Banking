<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/104-separate-parser-evidence-from-network-readiness.md

PURPOSE:
Separate parser evidence from network readiness

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Separate parser evidence from network readiness

## Before you begin
Complete the capture and checksum lessons. Review the distinction between host tests and guest tests in the earlier qualification chapters. Use the documented cross-toolchain only for the link-contract step.

## Three separate claims
A host test proves behavior for its supplied bytes on the host compiler/runtime. A freestanding link check proves that compiled code can link without a hosted C library. A network guest test would exercise a driver and actual queue ownership. The current packet foundation provides the first two contracts; it does not implement the third.

## Why a successful ordinary link can be misleading
Linkers can discard unused functions. If the parser is not called by a guest, discarding it could also hide an unresolved runtime-library reference. The existing boot-memory contracts keep all sections and link the actual parser at O0 and O2 without libc.

1. Open cmake/BootMemoryContracts.cmake.
2. Find kernel/network_packet.c in its source list.
3. Locate the two optimization settings.
4. Find the no-undefined and nostdlib options.
5. Explain why these contract images are not offered as bootable kernels.

~~~powershell
cmake --build build/riscv64-clang-debug --target umicom-boot-memory-contracts
~~~

Use the cross-build directory you actually configured. Expect both link images to complete. An undefined memcpy or memset is a real freestanding dependency problem; do not fix it by adding a host operating-system library.

## Plan the next device boundary
Write a small ownership table with the states device-owned, completed, admitted and released. For each transition, name who may read or write the buffer. Add one bounded queue-full outcome and one shutdown case where completion arrives late. This is a design exercise, not an implemented driver state machine.

The parser refuses options, fragments and unsupported frame types. Reassembly would need storage limits, expiry and collision handling. A receive queue needs resource accounting before exposing a packet to a service. Each new capability must preserve the existing refusal behavior until its replacement contract is explicit.

## Verification and recovery
Run all 19 host groups after changing the reader. Run the O0/O2 link targets after changing byte-copy or result-publication logic. Keep these results separate from QEMU boot evidence and physical hardware evidence.

If a test fails only after optimization, compare generated dependencies and object symbols, then reduce the failing case. Do not label a host-only pass as a working network stack. No socket, live NIC, ARP exchange or packet transmission is implemented by these lessons.


[Course contents](index.md) · [Previous lesson](103-check-headers-without-trusting-payloads.md) · [Next lesson](105-move-a-packet-check-from-host-to-guest.md)
