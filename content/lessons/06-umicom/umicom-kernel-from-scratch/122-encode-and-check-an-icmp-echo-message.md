<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/122-encode-and-check-an-icmp-echo-message.md

PURPOSE:
Encode and check an ICMP echo message in RAM

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Encode and check an ICMP echo message in RAM

[Course contents](index.md)

## What this exercise does

You will trace how a small echo message becomes bytes in a memory buffer. You will inspect a known expected frame, check its checksums, reject an undersized destination and verify that rejected writes leave the caller’s data unchanged. This continues the earlier IPv4 admission and UDP encoding lessons. It uses host tests and an existing Kernel guest fixture; it does not send packets, access a network card or implement the ping command.

A packet is a structured sequence of bytes. An encoder writes that sequence from explicit input fields. A decoder reads a sequence and checks whether it fits a supported structure. Testing both is useful, but an encoder and decoder can share the same mistake. That is why this lesson also compares the encoder against independently calculated expected bytes.


## 1. Place ICMP inside the frame

Ethernet identifies the link-layer destination and source using six-byte addresses. Its type field tells the receiver which next protocol is carried. IPv4 identifies source and destination IP addresses and names the carried protocol. ICMP, the Internet Control Message Protocol, is carried with IPv4 protocol number one. An ICMP echo request has type eight; an echo reply has type zero. Both use code zero in this bounded exercise.

~~~text
Ethernet header       IPv4 header          ICMP echo header       Payload
14 bytes              20 bytes             8 bytes                N bytes
[0 ............ 13]   [14 ............ 33]  [34 ............ 41]   [42 ...]

Total buffer bytes = 14 + 20 + 8 + N = 42 + N
~~~

These offsets describe the supported untagged Ethernet and fixed IPv4-header profile. An IPv4 header with options, a VLAN-tagged Ethernet frame or IPv6 has a different layout. Do not reuse these numbers without checking the profile. This encoder does not append Ethernet padding, preamble or the Ethernet frame-check sequence. A future device driver would have a separate responsibility for the device’s transmission contract.


## 2. Distinguish the two identifiers

The IPv4 identification field belongs to the IP header. The echo identifier and echo sequence number belong to the ICMP message. They are separate fields even when a fixture happens to choose equal values. A real echo client can use an identifier and sequence to help match a response to an outstanding request, but their presence is not proof of authenticity. This writer does no request matching, routing or automatic reply generation.

The specification structure contains explicit source and destination addresses, a nonzero time-to-live value, an IPv4 identification value, an echo identifier, a sequence number and the chosen echo message type. Time to live is a forwarding limit in the IPv4 header; it is not a wall-clock duration. The encoder sets the don’t-fragment flag and limits payload length to 1,472 bytes, giving at most 1,500 IPv4 bytes. That is a deliberate fixed profile rather than a discovery of every link’s actual maximum size.


## 3. Read the native contract before calling it

~~~c
UmicomNetworkPacketStatus UmicomKernelEthernetIpv4IcmpEchoWrite(
    const UmicomEthernetIpv4IcmpEchoSpec *spec,
    const void *payload, UmicomSize payloadBytes,
    void *destination, UmicomSize capacity,
    UmicomSize *written);
~~~

Spec points to the field values. Payload and payloadBytes describe a borrowed byte sequence. Destination and capacity describe the caller’s writable memory, including spare capacity. Written receives the encoded length only on success. The status tells the caller whether encoding succeeded. A null payload pointer is allowed only when its byte count is zero. The structure and written object require their declared alignment.

All complete memory spans must be accessible, stable and pairwise disjoint during the call. A span means an address together with its byte length. Destination’s span includes unused capacity, so placing written in that spare area is still an overlap error. Checked address arithmetic can reject an address-plus-size wrap, but cannot prove that arbitrary addresses are mapped or writable. The caller must still provide actual valid memory. No pointer is retained and no allocation occurs.


## 4. Follow the known request

Open tests/network_packet/icmp_write_tests.c. The MakeSpec function selects example MAC addresses and documentation IPv4 addresses. The golden array is the independent expected byte sequence. The request uses the five ASCII bytes hello, echo identifier 0x1234 and sequence number 0xabcd. The resulting frame contains 47 bytes. The IPv4 total-length field is 33 because it counts its own 20-byte header, the eight-byte ICMP header and the five payload bytes; it excludes Ethernet’s 14 bytes.

~~~text
ICMP words before inserting the checksum:
0800 0000 1234 abcd 6865 6c6c 6f00

Computed ICMP checksum: f62b
Computed IPv4 header checksum for this fixture: 3c71

Echo-reply type changes 0800 to 0000.
With the same remaining ICMP bytes, its checksum becomes fe2b.
~~~

Hexadecimal writes a byte as two base-sixteen digits. Network byte order puts the most significant byte first in a multi-byte field. For example, 0x1234 becomes bytes 12 and 34. The checksum is formed from 16-bit words, with carry folded back into the low 16 bits, followed by a one’s-complement operation. The odd last payload byte is paired with zero for the checksum calculation; that calculation padding is not another payload byte in the output.


## 5. Do not borrow UDP’s checksum exception

In IPv4 UDP, a zero checksum field has a special meaning: the checksum is absent. ICMP echo has no such opt-out. A computed ICMP checksum of zero remains zero and the complete message must still validate. The checksum-zero test selects the payload bytes 39 and fe for this fixture, producing the zero field deliberately. A generic “replace every zero checksum with ffff” rule would therefore be wrong for this API.

This is a useful engineering lesson about reuse. IPv4 header serialization can be shared because its field contract is the same in these encoders. Transport-specific checksum rules remain protocol-specific. Reuse should follow a demonstrated common contract, not just similar-looking loops.


## 6. Prove refusal is unchanged output

The capacity test fills the output with a visible sentinel byte, sets written to a recognizable value and tries every capacity below the required frame length. Each call must refuse without changing either output. It then tries exactly the required capacity and checks success. The complete test suite also covers illegal message types, zero TTL, oversized payloads, address wrap, alignment, overlap, corruption, zero-length payloads and all supported payload lengths.

The implementation validates before writing. This makes a failure easier for callers to handle: they can preserve their existing buffer and decide what to do next. It is still necessary to inspect the status before consuming written bytes. An unchanged sentinel is a test technique, not a substitute for the public status contract. Success also leaves spare capacity unchanged, so the caller can detect accidental writes past the encoded frame.


## 7. Run the focused host checks

These commands build a small host-test project from the Kernel source. A host test runs as an ordinary program on the development computer. It does not boot the Kernel. Start in the owner checkout only after integrating the reviewed files; use a mirror path instead when doing your own isolated development. Do not reuse a CMake build directory configured for a different source checkout.

~~~powershell
Set-Location "C:\umicom\umicom-kernel"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S tests/network_packet -B build/host-network-packet -G Ninja -DBUILD_TESTING=ON
cmake --build build/host-network-packet --parallel 2
ctest --test-dir build/host-network-packet -R "^kernel[.]network_icmp_write[.]" --output-on-failure --no-tests=error
ctest --test-dir build/host-network-packet --output-on-failure --no-tests=error
~~~

Run each line separately and stop on a nonzero exit code. The focused expression selects the ICMP writer cases; the final command also checks neighboring packet behavior. Use the actual registered tests and results in your checkout rather than assuming a historical test count. If no tests match, stop and verify the source version and test registration. A green host result does not prove a network card can transmit or a remote host can respond.


## 8. Understand the separate guest check

The Kernel’s packet-admission validation also calls the writer inside the RISC-V guest image. Its ordered markers check request encoding, reply encoding, the valid zero-checksum case and refusal with unchanged output. Follow the existing Kernel build and guest-qualification guide for the configured toolchain. The guest run exercises the compiled Kernel path in an emulator; it still manipulates RAM buffers and performs no live network exchange.

For a future network stack, additional work includes device discovery, DMA ownership, synchronization, address resolution, routing, bounded receive queues, timeouts and request-state tracking. None is supplied by an echo serializer alone. Keep these layers separate so an application cannot mistake successfully constructed bytes for successful delivery.


## Practice and troubleshooting

1. Draw the 47-byte fixture and mark offsets 14, 34 and 42. Explain why IPv4 length is 33 rather than 47.
2. Change the payload in a practice test and calculate its new frame length before running. Do not reuse the old checksum as an expected result.
3. Compare request and reply tests. Identify the changed type and checksum bytes, and explain why the encoder does not swap addresses automatically.
4. Reduce destination capacity by one and verify that both the sentinel buffer and written value remain unchanged.
5. If a checksum test fails, first check byte order, covered byte range, odd-byte padding and whether the checksum field was treated as zero during calculation.
6. If host tests pass but guest checks fail, record the exact image, source and toolchain identity. A stale guest image can test different code from the current host executable.


## Further reading

- [ICMP public contract](../../../../../umicom-kernel/include/umicom/kernel/network_icmp.h)
- [Independent fixtures and refusal tests](../../../../../umicom-kernel/tests/network_packet/icmp_write_tests.c)
- [Kernel packet admission guide](../../../../../umicom-kernel/docs/NETWORK_PACKET_ADMISSION.md)
- [Internet Control Message Protocol specification](https://www.rfc-editor.org/rfc/rfc792)

[Previous: Encode a UDP frame without sending it](121-encode-a-udp-frame-without-sending-it.md)

[Next: Own received bytes before advancing the stream](123-own-received-bytes-before-advancing.md)
