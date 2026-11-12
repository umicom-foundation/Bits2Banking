<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/103-check-headers-without-trusting-payloads.md

PURPOSE:
Check headers without trusting payloads

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Check headers without trusting payloads

## Before you begin
Complete the bounded-capture lesson and build its host checks. Keep the fixed golden bytes visible beside the parser. The fixture is synthetic; its protocol field does not make its payload a complete UDP message.

## What a checksum proves
The fixed IPv4 header checksum uses 16-bit words in network byte order. Carries are folded back into the low 16 bits. The reader includes the checksum field and expects the folded sum 0xffff. The format is described in [RFC 791](https://www.rfc-editor.org/rfc/rfc791.html).

~~~c
UmicomU32 sum = 0U;
for (UmicomSize i = 0U; i < 20U; i += 2U)
    sum += ReadNetwork16(ip + i);
while (sum >> 16U)
    sum = (sum & 0xffffU) + (sum >> 16U);
~~~

This is the real bounded loop from the implementation. There are only ten words; the intermediate sum fits UmicomU32. A future variable-length header profile would need its own bounds review.

## Use independent expectations
1. Read golden's fixed checksum bytes 0x3c, 0x62.
2. Notice that the test helper Checksum is used only after a header mutation.
3. Compare the helper's fold-after-each-add strategy with the reader's final fold.
4. Read the header-corruption test and predict CHECKSUM.
5. Read payload_policy and explain why changing payload bytes still passes header admission.

The reader does not verify UDP, TCP, sender identity or application content. A matching checksum is not authentication.

## Preserve the old observation on refusal
Refused fills the result with a sentinel, saves its full byte representation, calls the parser and compares the result afterward. A parser that wrote a source address before discovering a bad checksum would fail this contract.

Staging has a cost: a temporary result occupies stack space. Here the result has a fixed small size and no allocation. The benefit is a clear publication point after every required check.

## Verify and recover
~~~powershell
ctest --test-dir build/host-network-packet -R "kernel.network_packet.(checksum|payload_policy|truncation)$" --output-on-failure --no-tests=error
~~~

Expect three groups. In a scratch fixture, flip one header bit and keep the original checksum. Expect refusal with unchanged output. Restore the fixture before rerunning the canonical suite. Do not recalculate a broken test's checksum unless the case is intentionally about a different, valid header.


[Course contents](index.md) · [Previous lesson](102-read-a-packet-as-a-bounded-capture.md) · [Next lesson](104-separate-parser-evidence-from-network-readiness.md)
