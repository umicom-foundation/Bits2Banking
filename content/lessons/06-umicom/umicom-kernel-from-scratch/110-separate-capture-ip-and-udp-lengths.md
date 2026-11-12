<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/110-separate-capture-ip-and-udp-lengths.md

PURPOSE:
Separate capture, IP and UDP lengths

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Separate capture, IP and UDP lengths

One buffer can carry several nested lengths. Confusing them can expose padding as application data or accept a truncated packet. The Kernel's UDP reader uses the existing IP extent, then returns a smaller application-payload span.

## Before you begin

Read the preceding UDP policy lesson and keep the isolated host test build available. Open tests/network_packet/udp_tests.c and the public network_udp.h header. You need no browser, server, physical drive or network device for this exercise.

## Account for the fixed golden capture

The fixed vector contains 47 bytes. The Ethernet header occupies 14, the fixed IP header 20 and the UDP header eight. The remaining five bytes spell hello. The IP total length is 33, while the UDP length is 13. The view returns payloadOffset 42 and payloadBytes 5.

Write these relationships in your notes:

~~~text
14 + 33 = 47 accessible capture bytes
20 + 13 = 33 IP bytes
8 + 5 = 13 UDP bytes
14 + 20 + 8 = 42 application-payload offset
~~~

Do not derive application payload size from capture_bytes minus 42. The padding fixture extends the capture to 100 accessible bytes. Its application payload must still have five bytes. The checksum covers only the admitted datagram extent.

## Read every boundary before reading its bytes

Follow the production function in kernel/network_packet.c. It validates accessible length and address arithmetic first. The IPv4 reader proves that the IP extent fits the capture. The UDP reader checks that the IP payload can hold the eight-byte transport header before reading its length field. Only after that admission can it scan the checksum span.

The implementation refuses UDP lengths below eight as HEADER errors and lengths differing from the IP payload as LENGTH errors. These statuses describe this API's admission policy. An excess IP payload is not silently treated as transport options.

## Investigate three different refusals

~~~powershell
ctest --test-dir build/host-network-packet -R '^kernel[.]network_udp[.](truncation|short_header|short_length|long_length)$' --output-on-failure --no-tests=error
~~~

Expected result: four groups pass. The truncation group tries every shorter accessible prefix of the golden vector. The short_header case changes the admitted IP extent to seven transport bytes. The short_length and long_length cases change the declared UDP length while keeping the accessible capture intact.

These cases distinguish missing memory from inconsistent metadata. Adding spare bytes after the IP datagram must not repair a declared length mismatch. Inspect the independent original values before editing any fixture.

## Preserve ownership on failure and success

The Refused helper fills an output view with a sentinel and compares all its bytes after refusal. This catches accidental partial publication. The implementation stages successful metadata before copying it to the output. It does not allocate or retain the input.

After success, copied ports and addresses remain valid if the capture contents change. The payload coordinates do not make the original memory immutable or owned by the reader. A future driver must prevent buffer reuse while its consumer reads that span.

## Exercise and recovery

Sketch a receive queue handing a capture to a parser and then returning it to the device. Mark the last point at which an application could safely read payload bytes. If it needs them later, an ownership transfer or explicit copy is required; preserving an offset alone is insufficient.

If a length test fails, print the accessible, IP and UDP lengths in the test diagnostic. Fix the specific boundary check and rerun the related groups. Do not increase the maximum capture size or remove exact-length admission merely to make a malformed fixture pass.

[Course contents](index.md) · [Previous lesson](109-admit-udp-with-an-explicit-checksum-policy.md) · [Next lesson](111-check-udp-in-the-real-diagnostic-guest.md)
