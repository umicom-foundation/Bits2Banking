<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/116-admit-icmp-echo-without-trusting-the-sender.md

PURPOSE:
Teach admit ICMP echo without trusting the sender.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; referenced sources retain their terms.
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Admit ICMP echo without trusting the sender

## Goal

Extend your packet-reading knowledge from UDP to ICMP echo. You will trace the existing C implementation, calculate exactly which bytes its checksum covers, and explain why successful admission does not prove that a reply is expected or its sender is trustworthy. This is a RAM-only exercise; no network interface or administrator permission is needed.

## Start at the existing boundary

Open include/umicom/kernel/network_icmp.h and kernel/network_packet.c in Umicom Kernel. UmicomKernelEthernetIpv4IcmpEchoRead first checks the output alignment and its separation from the complete accessible capture. It then calls the shared IPv4 reader. That earlier reader owns Ethernet type, IPv4 length, fragmentation and header-checksum checks; the echo layer does not duplicate them.

After IPv4 admission, the echo reader requires protocol 1, an eight-byte-or-longer message, type 8 for a request or type 0 for a reply, and code zero. Other ICMP messages have different layouts. An error message can quote part of an earlier datagram, so treating every message as echo would misinterpret its fields.

~~~c
#include "umicom/kernel/network_icmp.h"

/* capture points to stable readable RAM owned by this caller. */
UmicomEthernetIpv4IcmpEchoView echo;
UmicomNetworkPacketStatus status = UmicomKernelEthernetIpv4IcmpEchoRead(
    capture, capture_bytes, &echo);
if (status == UMICOM_NETWORK_PACKET_OK) {
    /* Inspect copied identifiers, then consume payload coordinates only
     * while the original capture remains owned and unchanged. */
}
~~~

## Calculate the message boundary

The independent golden request in tests/network_packet/icmp_tests.c has 47 capture bytes. Its Ethernet header takes 14 bytes and its fixed IPv4 header takes 20. The remaining 13 bytes are the echo message: eight header bytes and five bytes spelling hello. Its application payload therefore starts at offset 42. Appending Ethernet padding does not extend the IP datagram or the message checksum.

The checksum in RFC 792 starts at the ICMP type byte. Unlike the UDP checksum, it has no pseudo-header containing IP addresses. The golden request uses checksum f62b; changing the type to reply requires fe2b. Read those literal bytes before trusting a helper that computes test fixtures. The helper folds each word during accumulation, while production folds after bounded accumulation, so the test does not merely call the implementation it is checking.

For odd lengths, the last data byte contributes as the high byte of a conceptual word whose low byte is zero. No extra capture byte is read or changed. A zero checksum field does not disable checking. The zero_checksum case first refuses an invalid zero field, then accepts a different message whose complete sum is valid with a zero field. This differs from IPv4 UDP checksum absence.

## Run the host contracts

From the Kernel repository, use a fresh host build directory. These Windows commands assume UCRT64 GCC, CMake and Ninja are installed. Run each command separately and stop if it fails; on Linux omit the Windows compiler path and select your C23 compiler.

~~~powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S tests/network_packet -B build/host-network-packet -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DBUILD_TESTING=ON
cmake --build build/host-network-packet --parallel 2
ctest --test-dir build/host-network-packet -R "^kernel[.]network_icmp[.]" --output-on-failure --no-tests=error
~~~

Expect 24 echo test groups, with no failed or skipped groups. Omitting the -R selection also runs the existing 19 IPv4 and 27 UDP groups, for 70 total. A compilation failure means the tests have not run. Preserve the failing command and its diagnostics before changing a test expectation.

## Compare checksums with trust

1. Read address_scope. It changes both IP addresses and repairs only the IP checksum. Predict why the unchanged echo checksum still passes.
2. Read corruption. Each selected message-bit change must refuse while preserving every output byte. Compare this with the preceding address change.
3. Read overlap. A result placed in Ethernet padding is still refused: excluded checksum bytes remain owned capture storage.
4. Read lifetime. Clearing the capture after return does not change copied metadata, but destroys its payload. Offsets do not own memory.

Identifier and sequence values are observations. A future ping client needs its own bounded outstanding-request table, expiry policy and matching rules. Even a matching tuple is not cryptographic authentication. This reader implements none of those client obligations.

## Relate host and guest evidence

The diagnostic image calls the same production reader on synthetic bytes. After building umicom-kernel-evidence in your configured RISC-V build, select kernel.riscv64.packet_admission together with kernel.qualification.identity. The current-image fixture may add another test. Expect four ICMP groups after the earlier eleven groups and packet-admission.cases=15. The wrapper uses -nic none; it does not send ping packets.

If a guest marker is missing, first establish whether the current-image fixture succeeded and which ELF was selected. A no-libc link at O0/O2 checks library dependencies; it cannot replace guest execution. Conversely, a successful guest does not validate a NIC, DMA synchronization, a queue or physical hardware.

The next TCP lesson retains these fifteen groups and adds four, bringing the current combined guest count to nineteen. The fifteen-group count above describes the ICMP checkpoint.

## Exercise and recovery

In a separate scratch fixture, change one payload byte without repairing the message checksum. Predict the status and unchanged output, then run the focused case. Next change an IP address and repair its header checksum. Explain the different outcomes in terms of byte coverage. If the golden case fails, compare the literal bytes, admitted lengths and byte order before widening the parser or recomputing every expected value.

## Reference

Read the echo layout in [RFC 792](https://www.rfc-editor.org/rfc/rfc792.html). The Umicom API deliberately adds a bounded capture and ownership contract; it is not a complete implementation of every ICMP message.

[Course contents](index.md) · [Previous lesson](115-execute-forward-vm-paths-in-user-mode.md) · [Next lesson](117-inspect-tcp-without-claiming-a-connection.md)
