<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/102-read-a-packet-as-a-bounded-capture.md

PURPOSE:
Read a packet as a bounded capture

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Read a packet as a bounded capture

## Before you begin
Read the byte-span and checked-address lessons. Open include/umicom/kernel/network_packet.h and kernel/network_packet.c in the Kernel repository. You need no network adapter for this exercise.

## Begin with ownership
A driver may eventually receive bytes into a buffer shared with a device. A pointer alone does not say whether the device has finished writing, whether another thread may recycle the buffer, or how many bytes are readable. The current reader deliberately starts after those ownership questions have been answered by its caller.

~~~c
UmicomKernelEthernetIpv4Read(capture, accessible_bytes, &view);
~~~

The caller supplies stable RAM. The reader neither takes ownership nor returns a pointer into the capture. It copies metadata into view and reports the offset and length of the remaining payload. Keep the original capture alive before using that offset.

## Trace the first checks
1. Find the null argument guards.
2. Locate the minimum and maximum capture lengths: 34 and 1514.
3. Follow checked address addition and the overlap refusal.
4. Find ReadNetwork16 and explain why it reads two bytes instead of dereferencing a cast structure.
5. Follow the IP total-length check before any payload observation is published.

The input may be unaligned. The typed output requires its normal C alignment. These are different contracts because wire bytes are decoded individually, while callers use fields of the result structure.

## Padding exercise
The golden fixture holds a 32-byte IP datagram after a 14-byte Ethernet header. Its 12-byte payload starts at offset 34. The padding test extends the capture to 60 bytes. Predict the output before running it: payloadBytes stays 12.

Ethernet padding does not contribute to the IP total-length field; see [RFC 894](https://www.rfc-editor.org/rfc/rfc894.html). This reader also accepts unpadded captures, so it must not be used as proof that a transmitted frame obeys all Ethernet requirements.

## Verify
From the Kernel repository, configure and build tests/network_packet using the commands in docs/NETWORK_PACKET_ADMISSION.md. Then run:

~~~powershell
ctest --test-dir build/host-network-packet -R "kernel.network_packet.(golden|padding|unaligned)$" --output-on-failure --no-tests=error
~~~

Expect three selected groups. If none are selected, check the configured directory and test names rather than counting an empty run as success. If a result differs, inspect the fixed fixture before changing the parser's limits.


[Course contents](index.md) · [Previous lesson](101-qualify-kernel-storage-on-disposable-media.md) · [Next lesson](103-check-headers-without-trusting-payloads.md)
