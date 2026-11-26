<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/127-decode-option-values-before-changing-connection-state.md

PURPOSE:
Decode option values before changing connection state

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Decode option values before changing connection state

[Next lesson](128-observe-the-boot-reservation-plan.md)

[Course contents](index.md)

## An option can fit without having the right meaning

The previous lesson walked a TCP option area and reported each item’s kind, length and offset. That answered where the bytes were. A two-byte item with kind 2 fits structurally, but it is too short to contain the two-byte Maximum Segment Size field expected for that kind. This lesson adds a separate known-value reader. Keeping the two jobs separate lets a packet viewer show unfamiliar options while a narrower consumer refuses ambiguous known fields.

1. Review the structural option lesson and its 40-byte bound. An option area is a slice of a TCP header; it is not an entire Ethernet frame.
2. Open include/umicom/kernel/tcp_options.h and find UmicomTcpOptionValues. Each member is an owned scalar value, not a pointer into the packet.
3. Open tests/network_packet/tcp_option_values_tests.c. The fixture consists of invented bytes already in memory. The exercise opens no network socket and requires no remote machine.


## Read the four recognized shapes

Kind is the identifying byte. Length includes the kind byte and the length byte. The reader first verifies the complete area using UmicomKernelTcpOptionsRead, then checks the exact payload length of each recognized kind. Other kinds remain opaque and increase unknownCount. NOP does not increase that count. SACK block kind 5 is still opaque here; the two-byte SACK-permitted kind 4 is a different option.


| Kind | Required total bytes | Copied fields |
| --- | --- | --- |
| 2: Maximum Segment Size | 4 | 16-bit MSS and presence flag |
| 3: Window Scale | 3 | Raw shift, bounded shift and presence flag |
| 4: SACK-permitted | 2 | Presence flag only |
| 8: Timestamp | 10 | 32-bit timestamp value, echo and presence flag |


## Turn network bytes into a host value

Network byte order places the most significant byte first. The two bytes 05 B4 represent 5 × 256 + 180 = 1460. A bytewise reader combines them deliberately. Casting a byte pointer to a 16-bit integer pointer would instead depend on the processor’s byte order and alignment. The Kernel helper reads individual bytes and returns the value, which is safe for an unaligned input span when the span itself is accessible.

~~~text
MSS option bytes: 02 04 05 B4
                 kind length value

value = (0x05 << 8) | 0xB4
      = 0x05B4
      = 1460
~~~


## Presence is different from a zero value

A missing MSS option and a present option containing zero both leave the mss member numerically zero. hasMss distinguishes them. This reader preserves zero because its job is to report the wire value; it does not invent a default send size. Likewise, a present timestamp containing zero is different from no timestamp. A display or connection policy must inspect the corresponding presence flag before using a field. The all-absent result has every field zeroed.


## Keep a raw offer and its bounded interpretation

For window scale, the wire byte is retained as windowScaleRaw. The helper also returns min(raw,14) in windowScaleBounded. For the fixture’s raw value 15, the bounded value is 14. Retaining both lets an application report the unusual offer without shifting by an uncontrolled amount. No window is actually scaled here. Whether the offer applies depends on TCP flags and negotiation outside this reader.

~~~text
wire bytes:       03 03 0F
raw shift:        15
bounded shift:    14
connection state: unchanged
~~~


## Observe values without claiming negotiation

The timestamp fields are copied integers, not a wall-clock date. Their interpretation needs connection context. Observing SACK-permitted similarly does not mean both peers have enabled it. This function receives neither SYN/ACK flags nor a connection record. It cannot establish handshake state, timestamp validity, retransmission policy, checksum correctness or peer identity. Existing fixed-header TCP packet readers retain their no-options profile; this standalone helper does not silently enable options in those readers.


## Why this value reader refuses repeated known kinds

The structural reader deliberately preserves duplicate option coordinates. The value reader has one slot for each recognized value, so this implementation refuses a second occurrence of any recognized kind with HEADER. It does not silently choose the first or last value. This is an explicit local extraction policy, not a claim that all unknown or repeated TCP options are forbidden by the protocol. Repeated unknown kinds remain counted and opaque. A future connection layer can define a different reviewed policy without changing the structural contract.


## A late error must not publish early fields

Suppose a valid MSS is followed by a malformed timestamp. Publishing MSS immediately would leave a partially updated output object when the call fails. The implementation instead clears a local candidate, fills it only after structural admission, and copies it to the caller after every known option passes. Any refusal leaves every output byte unchanged. The caller keeps the input stable for the duration of the call and provides aligned output disjoint from the entire input span.

~~~text
admit input and output extents
walk the complete option structure
clear a local candidate
for each recognized item:
    check exact length and duplicate policy
    copy scalar values into the candidate
publish the complete candidate
~~~


## Build and run the hosted contracts

Hosted means the checks run as ordinary programs on your development operating system. This is quicker than booting a whole machine and useful for byte-array contracts. It does not test a network device. The test executable receives a case name. CTest supplies that name for each registered check.

~~~powershell
Set-Location "C:\umicom\umicom-kernel"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S tests/network_packet -B build/learning-packet-options -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe
cmake --build build/learning-packet-options
ctest --test-dir build/learning-packet-options -R "^kernel.tcp_option_values[.]" --output-on-failure
~~~


## Understand the checks rather than trusting a green total

The golden case expects MSS 1460, raw scale 15, bounded scale 14, SACK permission present, timestamp 0x11223344 and echo 0x8899AABB. Other cases examine every 16-bit MSS value, every one-byte scale, individual timestamp bits, all orders of the four known items, unknown kinds, incorrect lengths, duplicates and late failures. Ownership checks alter the input after the call and verify that the copied result remains intact.

1. Run the golden case and read its assertions beside the byte fixture. A successful test exits zero without needing printed payloads.
2. Run known-lengths and observe that the structural reader accepts the fixture before the value reader refuses it. This establishes the intended layer distinction.
3. Run late-refusal and verify the entire sentinel output is unchanged, rather than checking one field only.
4. Run the existing full packet suite after changing shared decoding helpers. Other IPv4, IPv6 and encoding functions use the same byte-order helpers.
5. Use the repository’s current RISC-V diagnostic workflow separately for freestanding validation. A hosted pass alone does not establish guest linkage or execution.


## Practice with a small byte record

Write expected values on paper before changing the test fixture. Use a new local experiment rather than weakening the original assertions.

1. Replace MSS bytes 05 B4 with 01 00. Predict 256. Then reverse them to 00 01 and predict 1.
2. Change the window scale byte to 00. Predict hasWindowScale true and both shift values zero.
3. Remove an option by replacing the whole remaining area with zero padding after EOL. Predict an absent flag, not a default value.
4. Append a second MSS item and predict HEADER with unchanged output.
5. Replace a recognized kind with 253 while retaining a structurally valid length. Predict one opaque item instead of a decoded field.
6. Explain why none of these results proves a live TCP connection is usable.


## Read the protocol alongside the implementation


- [TCP option definitions — RFC 9293 section 3.2](https://www.rfc-editor.org/rfc/rfc9293.html#section-3.2)
- [Window scale and timestamps — RFC 7323](https://datatracker.ietf.org/doc/html/rfc7323)
- [SACK-permitted and SACK blocks — RFC 2018](https://www.rfc-editor.org/rfc/rfc2018.html)


[Previous: Walk TCP options without trusting lengths](126-walk-tcp-options-without-trusting-lengths.md)
