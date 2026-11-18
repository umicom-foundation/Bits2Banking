<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/121-encode-a-udp-frame-without-sending-it.md

PURPOSE:
Encode a UDP frame without sending it

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Encode a UDP frame without sending it

[Course contents](index.md)
Earlier lessons read packet captures: they inspected bytes that already existed. A network stack also needs the opposite operation, serialization, which turns named values and payload bytes into an exact byte sequence. This lesson studies a small Kernel encoder that works entirely in ordinary memory. You will build its host tests, inspect a fixed expected frame and understand what a device driver still has to do before anything could travel over a network.


## 1. Separate a message from its envelopes

The payload is the application message. In the example it contains the five ASCII bytes for hello. UDP, the User Datagram Protocol, adds source and destination port numbers, a length and a checksum. IPv4 adds network addresses and other delivery fields. Ethernet adds local-link addresses and a type number. These headers are envelopes around the same payload. An address or port field is only a value in this exercise; constructing it does not give your program ownership of that address or open a socket.

~~~text
Byte offsets in the untagged frame
0              14                 34        42           47
| Ethernet 14  | IPv4 header 20    | UDP 8   | hello 5     |

IPv4 length = 20 + 8 + 5 = 33 bytes
UDP length  = 8 + 5      = 13 bytes
RAM result  = 14 + 33    = 47 bytes
~~~

Offsets count from zero. Byte 14 is therefore the fifteenth byte in ordinary counting. The interval [34,42) contains byte positions 34 through 41; the closing parenthesis means that 42 is not included. Keeping offsets and lengths distinct prevents reading the next field by accident. This profile uses fixed headers, so it does not interpret IPv4 options or fragmented datagrams.


## 2. Initialize a specification

~~~c
UmicomEthernetIpv4UdpSpec spec;
UmicomBootMemoryClear(&spec, sizeof spec);
/* Assign both MAC arrays and both IPv4 address arrays first. */
spec.sourcePort = 12345U;
spec.destinationPort = 53U;
spec.identification = 0x1234U;
spec.timeToLive = 64U;

UmicomU8 frame[1514];
UmicomSize written = 0U;
UmicomNetworkPacketStatus status = UmicomKernelEthernetIpv4UdpWrite(
    &spec, "hello", 5U, frame, sizeof frame, &written);
~~~

This is a fragment: use the complete udp_write_tests.c fixture for initialized addresses. A MAC address contains six bytes and an IPv4 address contains four. The example uses documentation IP addresses and never sends them. The encoder borrows the specification and payload only during the call. It writes copied bytes into your separate frame array. Changing the source objects later does not retroactively change the encoded frame.

Time to live, abbreviated TTL, is a limit used by IP forwarding. This API refuses zero because it is not a useful outgoing value. It sets the do-not-fragment flag and permits at most 1472 payload bytes: 1500 minus the 20-byte IP header and 8-byte UDP header. This chosen profile is not proof that every real interface supports that size. Routing and path-MTU behavior belong to later work.


## 3. Why not copy a C struct directly?

A compiler can insert padding between struct fields, and processors can store multi-byte numbers in different byte orders. Network byte order puts the most significant byte first. The encoder therefore writes each 16-bit field explicitly. The number 13 becomes bytes 00 and 0d. It never casts the destination into a packed network-header pointer. That also allows the ordinary byte destination and payload to be unaligned.

Typed objects have a separate requirement. The specification and output counter need the alignment required by their C types. The entire destination capacity, specification, counter and nonempty payload must be pairwise disjoint. Even a payload placed in supposedly unused capacity at the end of the destination is refused. These restrictions make ownership clear and avoid surprising mutations while the function is reading its inputs.


## 4. Understand the checksum boundary

A checksum is a small error-detection value calculated from data. It is not a cryptographic signature and does not authenticate a sender. The IPv4 checksum covers only the IP header. The UDP checksum also includes a pseudo-header: source and destination IP addresses, protocol and UDP length. That pseudo-header participates in the calculation but is not an additional section inserted into the transmitted UDP message.

The calculation adds 16-bit network-order words and folds carries back into the low 16 bits, then complements the result. An odd final payload byte is treated as the high half of a final word whose low half is zero for calculation only. The five-byte hello example is deliberately odd-length. If the calculated UDP checksum is zero, the encoder stores ffff. An actual zero field in IPv4 UDP means that a checksum was omitted; those meanings must not be confused.


## 5. Build the tests on your development computer

1. Open the Kernel repository in PowerShell. This host exercise needs CMake, Ninja and a C23-capable compiler; it does not require administrator access or a network adapter.
2. Run each command below separately. Stop on an error and inspect the first compiler or test diagnostic.
3. Read tests/network_packet/udp_write_tests.c. Compare golden with the writer result. The expected bytes are a fixed independent vector, not generated by the function under test.
4. Run the complete packet suite after the focused writer cases. The existing admission cases remain useful because writing and reading share a production source owner.
5. For a real Kernel build, also run the diagnostic guest and no-libc link targets through the Kernel guide. Hosted success alone cannot establish a freestanding link or a physical network driver.

~~~powershell
Set-Location "C:\umicom\umicom-kernel"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S tests/network_packet -B build/host-network-packet -G Ninja -DBUILD_TESTING=ON
cmake --build build/host-network-packet --parallel 2
ctest --test-dir build/host-network-packet -R "^kernel[.]network_udp_write[.]" --output-on-failure --no-tests=error
ctest --test-dir build/host-network-packet --output-on-failure --no-tests=error
~~~

The writer suite has thirteen named groups, including every payload length from zero through 1472 inside one group. It checks exact bytes, encoded zero checksums, rejected capacities, address wraparound, overlapping storage, alignment and lifetime. A passing read-after-write test is useful but insufficient by itself: the writer and reader could agree on the same mistake. That is why the fixed expected vector and field assertions are also present.


## 6. Follow the unchanged-output rule

Before publishing anything, the writer checks arguments, lengths, integer address ranges, alignment, overlaps and TTL. It computes a small header in local storage and includes the payload in the checksum. Only then does it copy the completed header and payload and assign written. A refused request leaves both the destination and counter unchanged. The function allocates no heap memory and performs no I/O.

Checked address arithmetic prevents integer wraparound; it cannot tell whether a pointer refers to mapped memory or whether another CPU is modifying that memory. The caller must provide stable accessible RAM. A DMA buffer has additional ownership and synchronization rules that this API does not implement. Do not turn a successful integer check into permission to dereference an arbitrary physical address.


## 7. Do not send the entire destination capacity

For hello, written is 47 even though the destination has room for 1514 bytes. The rest retains its previous contents. Passing the entire array to a future driver could disclose unrelated memory. The result excludes preamble, Ethernet padding and frame-check sequence, or FCS. A real device adapter must supply the correct padding and FCS according to its hardware contract; required padding must be initialized, not copied from spare memory.

The encoder does not perform ARP resolution, route selection, socket binding, retransmission, congestion control or firewall checks. UDP itself does not promise delivery or order. This feature is a useful building block for a later stack because its behavior can be tested independently, but a complete network service requires those surrounding ownership and policy decisions.


## 8. Explain the result before extending it

1. Calculate the result size for an empty payload and for 1472 bytes. Expected sizes are 42 and 1514.
2. Explain why byte order is independent of how a C compiler lays out a struct.
3. Explain why a valid checksum does not prove that a sender is trustworthy.
4. Describe what must remain unchanged when the destination is one byte too small.
5. List the additional work required before the encoded memory could become a real packet on an Ethernet link.


## Further reading

- [UDP protocol and checksum, RFC 768](https://www.rfc-editor.org/rfc/rfc768)
- [Internet Protocol, RFC 791](https://www.rfc-editor.org/rfc/rfc791)

[Previous: Qualify shared VM slices in a guest](120-qualify-shared-vm-slices-in-a-guest.md)

[Next: Encode and check an ICMP echo message in RAM](122-encode-and-check-an-icmp-echo-message.md)
