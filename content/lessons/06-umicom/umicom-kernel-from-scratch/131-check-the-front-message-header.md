<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/131-check-the-front-message-header.md

PURPOSE:
Check the front message header

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Check the front message header

A **message header** describes a queued payload. The local Kernel channel keeps the sender identity, a sequence value and a length. A readiness query needs trustworthy metadata before the caller can choose a destination buffer or schedule a receiver.

## Check the front header before publishing a length

The front entry has a payload capacity of 256 bytes in this channel. A length of zero or above that capacity is outside the stored contract. The same header check also requires a nonzero sender and sequence. Query and receive use that admission rule even though their effects and required permissions differ.

| Synthetic front entry | Readiness result |
| --- | --- |
| A known sender, a nonzero sequence and an admitted length | Report the current metadata |
| A length of 257 | Refuse the inconsistent entry |
| A missing sender or a zero sequence | Refuse the inconsistent entry |

The query API validates first and only then writes the result. A higher-level QUERY handler can rely on that status before copying to a caller’s checked buffer. A rejected request leaves the previous bytes intact. A readiness query does not repair or drain the channel.

~~~text
CHECK the endpoint rights and queue shape
IF the queue has a front entry
    CHECK sender, sequence and bounded payload length
    REFUSE inconsistent metadata before writing the result
BUILD and return the readiness information
~~~

## Inspect the hosted regression

Open `tests/message_channels/message_tests.c` in the Umicom Kernel checkout. The fixtures place controlled values in a synthetic queue and initialize their output buffer to a visible marker. Find the checks for payload bounds, sender and sequence. Before reading the expected results, predict what each refusal should leave in the output buffer.

From your existing hosted Kernel build, select the direct and mapped-output cases. Replace `build/hosted` with the directory that contains the configured tests. Expect two passing tests.

~~~powershell
ctest --test-dir build/hosted -R '^kernel\.message_channels\.(query-corrupt-front|syscall-query-corrupt-front)$' --output-on-failure
~~~

The archived implementation could publish readiness when the stored header was inconsistent. The current direct hosted cases check both the normal queue and the protected QUERY result. These cases demonstrate the API’s ordering using ordinary in-memory data. A different test is needed to establish actual boot or cross-processor delivery.

[Course contents](index.md) · [Previous lesson · Observe a message with query rights](130-observe-a-message-with-query-rights.md) · [HTML edition](../../../courses/umicom-kernel-from-scratch/lessons/131-check-the-front-message-header.html)

[Next lesson · Read the scope of a Kernel build identity](132-read-the-scope-of-a-kernel-build-identity.md)
