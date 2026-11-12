<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/109-admit-udp-with-an-explicit-checksum-policy.md

PURPOSE:
Admit UDP with an explicit checksum policy

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Admit UDP with an explicit checksum policy

A transport reader should build on an admitted IP packet rather than repeating the IP parser. This lesson follows the Kernel's new UDP entry point and separates three decisions: whether the packet fits its container, whether a checksum was supplied, and whether a consumer requires that checksum.

## Before you begin

Complete the earlier packet-admission and guest-evidence lessons. Have a C23 compiler, CMake and Ninja, and open the Kernel repository. The exercises use fixed byte arrays in ordinary memory. They need no network interface, packet-capture permission or administrator rights.

## Follow one call through the shared reader

Open include/umicom/kernel/network_udp.h and find UmicomEthernetIpv4UdpView. Its ipv4 member contains the metadata copied by the existing reader. The new fields describe ports, UDP extent, checksum presence and the application payload coordinates. They contain no retained input pointer.

~~~c
UmicomEthernetIpv4UdpView view;
UmicomNetworkPacketStatus status = UmicomKernelEthernetIpv4UdpRead(
    capture, capture_bytes, UMICOM_UDP_CHECKSUM_REQUIRE, &view);
if (status == UMICOM_NETWORK_PACKET_OK) {
    /* Keep capture owned before reading the returned payload span. */
}
~~~

This fragment assumes capture points to stable readable RAM and capture_bytes is its accessible size. It is not a function that reads a device. In kernel/network_packet.c, follow the call to UmicomKernelEthernetIpv4Read. That earlier function remains responsible for Ethernet type, fixed IPv4 header, fragmentation refusal and IP checksum admission.

The transport function then checks protocol 17, at least eight UDP bytes and exact agreement between the UDP length and IP payload length. Exact agreement is a product profile choice. UDP options, IP options, IPv6, fragmentation and jumbo packets are outside this implementation.

## Distinguish checksum absence from verification

The API offers REQUIRE and ALLOW_ABSENT. With REQUIRE, a zero checksum field refuses admission. With ALLOW_ABSENT, that representation succeeds with checksumPresent false. A nonzero checksum is verified under either policy. Selecting the permissive policy cannot turn a failed supplied checksum into success.

The IPv4 UDP convention for a zero field and the pseudo-header are specified in [RFC 768](https://www.rfc-editor.org/rfc/rfc768). This course's stricter application choice is explicit in the function argument. A successful checksum is an accidental-corruption check, not authentication or authorization.

## Run the two policy cases

Configure and build tests/network_packet using the preceding lesson's host commands, then select these cases from the configured directory:

~~~powershell
ctest --test-dir build/host-network-packet -R '^kernel[.]network_udp[.]absent_' --output-on-failure --no-tests=error
~~~

Expected result: absent_allowed and absent_required both pass. Passing the second test means the parser refused the input as expected. It does not mean the input packet passed admission. Read the assertion and output-preservation comparison in udp_tests.c to keep those meanings separate.

## Exercise and recovery

A reviewer proposes replacing REQUIRE with ALLOW_ABSENT because a fixture lacks its checksum. First determine the consumer's intended contract. If the fixture should represent a checksummed message, repair the fixture and retain the strict requirement. If absence is intentionally supported, record that choice and ensure the consumer sees checksumPresent false.

Never report an absent checksum as verified. If these tests fail, preserve the failing case name and inspect the field bytes and policy argument before changing assertions. The implemented service still has no socket registry, receive queue, retransmission or live-device integration.

[Course contents](index.md) · [Previous lesson](108-distinguish-input-identity-from-guest-evidence.md) · [Next lesson](110-separate-capture-ip-and-udp-lengths.md)
