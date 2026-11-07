<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/04-borrowed-streams-and-failure-boundaries.md

PURPOSE:
Explain the lesson: Define a failure boundary for a borrowed stream.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Define a failure boundary for a borrowed stream

## Start with ownership

Ownership answers who must release a resource. Borrowing lets another function use it temporarily. In this lab, `main` opens and closes a file stream. `BtbChecksumStream` borrows it and never closes it. This makes success and failure paths easier to reason about.

## Setup recap

Use the [checksum lab guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-checksum/README.md). It names the C23 tools, Framework SDK and separate configure, build and test commands for PowerShell and Bash. Review pointers as addresses of objects; a null pointer identifies no object.

## Three different state promises

The local digest context is private to one call. The caller's output is changed only after success. The borrowed stream can advance even when a later step fails. These are three different promises.

~~~text
resource          owner       after failure
stream            caller      may be advanced; caller still closes
digest context    adapter     local object expires on return
output buffer     caller      unchanged
~~~

The output pointer must identify enough writable memory and must not overlap the stream object. Checking for null does not prove every other pointer is valid. The caller remains responsible for the documented memory contract.

## Lab: inspect every exit

1. Find the invalid-argument return.
2. Find the read-error return.
3. Find the finalisation-error return.
4. Confirm none closes the borrowed stream.
5. Find the caller's close after the adapter returns.
6. Run the checks from the guide, including invalid arguments.

Now imagine a reader that closes the stream on failure. The caller would close it again. That is a lifetime defect. Conversely, a caller that returns immediately without closing its successfully opened stream can leak the resource.

## Error-handling exercise

Suppose reading fails and closing also fails. Which result should be reported? In this example, the earlier read failure is retained. If reading succeeds but closing fails, the result becomes an I/O error. The command prints no success digest in either case.

## Recovery and limitations

Retry by reopening the chosen file, not by assuming the failed stream is at its original position. A file changed by another program during reading can produce a digest of observed bytes without representing a stable file revision. Production file workflows need a separate snapshot or change-detection policy.

## Application connection

The same ownership discipline applies to Framework documents, sockets and task handles. Read each API's lifetime contract before wrapping it in a GUI callback. A reusable service should keep its failure promises consistent across every interface.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-checksum/checksum.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](05-untrusted-sizes-and-representations.md)


[Previous lesson](03-numbers-files-and-checks.md)
