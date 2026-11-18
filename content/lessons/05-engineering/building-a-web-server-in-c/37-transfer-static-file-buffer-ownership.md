<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/37-transfer-static-file-buffer-ownership.md

PURPOSE:
Transfer static-file buffer ownership

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Transfer static-file buffer ownership

[Course contents](index.md)
A web response must keep its bytes alive until delivery finishes. Previously the static-file path read a file into one buffer and copied it into a second owned response buffer. Both buffers existed during the copy. Ownership transfer allows the response to keep the first buffer instead. This reduces a specific allocation and copy; it does not establish that the entire application has no leaks.


## 1. Identify the owner

An owner is the code responsible for releasing a resource exactly once. A pointer merely contains an address; copying the pointer does not copy the bytes or create a second legitimate owner. A borrowed pointer can inspect bytes only while the owner keeps them alive. The response body exposes immutable bytes to the sender and retains the release obligation.

~~~text
before transfer:
static-file handler owns -> file buffer

successful transfer:
static-file handler pointer = NULL
response body owns       -> same file buffer

response destroyed:
release callback frees file buffer once
~~~


## 2. Read the transfer contract

~~~c
UmiWebResponseBody *body = NULL;
UmiStatus status = UmiWebResponseBodyTake(
    &bytes, length, release_bytes, context, &body);
if (status != UMI_STATUS_OK) {
    /* bytes is still ours: release it through its original allocator. */
}
/* On success bytes is NULL; body owns the original allocation. */
~~~

The function allocates a small metadata object. It does not allocate and copy the entire payload. The release callback must match the allocator that produced the bytes. Static files use UmiRootedFileFree rather than assuming that every buffer can be released with the application's free. Keep callback context alive until body destruction. Do not modify transferred bytes through an old alias.


## 3. Preserve the copying API

UmiWebResponseBodyCreate remains useful when a caller has borrowed bytes or must keep its own mutable copy. It makes an owned copy. Take is an additional contract, not a reason to change every caller automatically. Decide from lifetime and ownership, not from which function name looks faster.


## 4. Handle failed transfer

An invalid length, invalid pointer contract or metadata allocation failure leaves the input byte pointer unchanged. The output body is null. The original owner must release the buffer. On successful transfer the original pointer becomes null, so the existing cleanup path can safely run without freeing the transferred bytes twice. This convention makes the ownership transition visible in code.


## 5. Verify the static-file path

1. Configure Framework with testing enabled using its documented toolchain.
2. Build the two response-body test targets shown below.
3. Run the matching tests. Their fixtures cover actual SVG/ICO bytes, partial writes, HEAD, cancellation and failure cleanup without opening a listener.

~~~powershell
cmake --build build/windows-ucrt64-debug --target umicom-web-response-body-test umicom-web-response-body-take-test --parallel 2
ctest --test-dir build/windows-ucrt64-debug -R '^framework.web.response_body.' --output-on-failure --no-tests=error
~~~

Use these paths from the Framework repository after configuration. A missing target means the selected build does not contain the new tests or testing is disabled. Do not treat that as a passing result. The transfer test checks pointer identity and allocation size, while the existing response tests check delivery behavior.

Exercise: a 4 MiB file is read once, then copied into another 4 MiB buffer. Ignoring small metadata, the overlap is about 8 MiB. With transfer it is about 4 MiB. This is a local accounting example, not measured process memory: filesystem caches, allocator overhead and other requests still contribute.


[Previous lesson](36-qualify-approved-assets-through-each-layer.md)

[Next lesson](38-release-response-bodies-on-every-exit.md)
