<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/111-check-udp-in-the-real-diagnostic-guest.md

PURPOSE:
Check UDP in the real diagnostic guest

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Check UDP in the real diagnostic guest

A hosted unit test and a freestanding guest answer different questions. The host suite explores many malformed inputs. The diagnostic guest demonstrates that the actual Kernel image can execute the production UDP reader without relying on a host C runtime.

## Before you begin

Complete the packet and UDP host lessons. Follow the Kernel build guide to configure its RISC-V Clang toolchain and QEMU. Use the configured build directory from that guide. The commands below use build/riscv64-clang-debug as an example; do not invent a second unrelated cache if yours has another path.

## Locate production and fixture code

kernel/network_packet.c owns both IPv4 and UDP admission. kernel/network_packet_validation.c supplies synthetic byte arrays and assertions. Read udpCapture: it is separate from the earlier IPv4-only capture, whose arbitrary payload deliberately does not represent a valid UDP datagram.

UdpValidateExecution adds four groups. udp-golden checks the copied fields and five-byte application payload. udp-refusals changes the odd final payload byte, declares a mismatched length and supplies a truncated capture. udp-padding extends accessible storage while retaining the same admitted payload. udp-checksum-policy checks both required and explicitly absent checksum cases.

These are tests of RAM parsing. No virtual NIC, DMA completion, network interrupt or packet transmission is involved.

## Build the current image and collect the transcript

~~~powershell
cmake --build build/riscv64-clang-debug --target umicom-kernel-evidence --parallel 2
ctest --test-dir build/riscv64-clang-debug -R '^kernel[.](qualification[.]identity|riscv64[.]packet_admission)$' --output-on-failure --no-tests=error
~~~

Stop after a failed command. CTest may add the required current-image setup fixture. Keep its result separate from the single guest test and from the groups printed inside that guest.

Expected transcript: the seven original IPv4 groups, the four UDP groups in order, packet-admission.cases=11, the packet ready marker and the final Kernel end marker. The wrapper also requires successful emulator exit and rejects explicit failure text. A log containing only a ready marker cannot qualify the run.

## Check the linkage boundary separately

~~~powershell
cmake --build build/riscv64-clang-debug --target umicom-boot-memory-contracts
~~~

This target links admission code at O0 and O2 without libc and without discarding unused sections. It can reveal a compiler-inserted memory helper that a hosted build would quietly supply. The resulting contract images check linkage; they are not substitutes for the guest execution above.

## Explain an odd-byte checksum failure

The golden payload has an odd number of bytes. The checksum reader includes its final byte without reading a nonexistent partner byte. The guest changes that final byte and requires checksum refusal with unchanged output. This catches an implementation that accidentally ignores the last payload byte while still accepting even-length examples.

The host suite remains broader: it also checks independent pseudo-header changes, absent-checksum policy, the all-ones checksum encoding, maximum extent, overlap, unaligned input and every truncated prefix. Do not describe four guest groups as covering every hosted boundary.

## Exercise and recovery

Suppose an older transcript contains packet-admission.cases=7 and an end marker. Explain why it is insufficient for the extended reader. Preserve it as historical evidence, regenerate the build after changing test definitions, build the current image and collect a new transcript.

If a guest fails, preserve its serial output and source/image identities before retrying. A passing host suite does not authorize ignoring a guest failure. Passing both still leaves physical hardware, device queues, DMA ownership, socket policy and live networking unqualified.

[Course contents](index.md) · [Previous lesson](110-separate-capture-ip-and-udp-lengths.md) · [Next lesson](112-protect-diagnostic-and-handle-outputs.md)
