<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/38-release-response-bodies-on-every-exit.md

PURPOSE:
Release response bodies on every exit

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Release response bodies on every exit

[Course contents](index.md)
Network output does not happen in one guaranteed step. A connection may accept only part of a buffer, fail after sending headers, or be cancelled. The response owner must keep the body alive while it is needed and destroy it on every completed or failed path. Ownership transfer makes this obligation more explicit; it does not remove it.


## 1. Separate headers from body

Headers describe the response: its status, media type and length. The body contains the payload, such as an SVG logo. Sending a correct Content-Length header does not prove that the payload reached the peer. A successful write may consume fewer bytes than requested, so the sender advances by the actual count and retries only the unsent portion.

~~~text
payload length = 10
write 1 accepts 4 -> remaining 6
write 2 accepts 3 -> remaining 3
write 3 accepts 3 -> remaining 0
then release the body
~~~


## 2. Trace the failure paths

1. Inspect the connection's body-owner variable before writing. It must be the only cleanup owner.
2. Follow a normal complete response to its destruction call.
3. Follow a failed write after headers. The same owner must still be released.
4. Follow cancellation during body delivery. The operation must stop and release its body.
5. Follow handler failure after creating a body. A failed status does not mean no resource was allocated.

The existing test_response_body.c deliberately constructs these cases with read and write callbacks. A callback is a function pointer supplied to another component. Here the callbacks simulate transport behavior so the test does not depend on a real browser or network.


## 3. Understand HEAD and empty content

A HEAD request asks for response metadata without a message body. It does not grant permission to leak a file buffer that was read while preparing metadata. Likewise an empty file is a valid zero-byte payload. If a transferred empty buffer has a release callback, destruction still honors that callback once. The callback must tolerate the exact pointer contract documented by the producer.


## 4. Test ownership separately from content

Correct bytes and correct lifetime are different properties. A test can compare the SVG payload byte for byte yet miss a leaked allocation. A lifetime test can count one release but miss a truncated response. Keep both kinds of evidence. The transfer regression counts releases, injects allocation failure and checks that unsuccessful admission retains caller ownership.


## 5. Diagnose a crash without guessing

A double free means two cleanup paths released the same allocation. A use-after-free means code accessed it after release. A leak means a live allocation lost its cleanup path. A large peak may instead be legitimate simultaneous buffers. Record which property failed before making a repair. Moving code from Python to C does not automatically establish any of these properties.

Exercise: the sender fails after writing half a response. Should it retain the body forever so the browser can retry? No. A new request is a new operation; the failed connection releases its own resources. If resumable transfers are required, design an explicit storage and retry contract instead of retaining an unreachable response object.


[Previous lesson](37-transfer-static-file-buffer-ownership.md)

[Next lesson](39-measure-memory-without-confusing-ownership.md)
