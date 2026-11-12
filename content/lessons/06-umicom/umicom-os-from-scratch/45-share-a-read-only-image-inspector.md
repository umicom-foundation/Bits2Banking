<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/45-share-a-read-only-image-inspector.md

PURPOSE:
Share a read-only image inspector

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->



# Share a read-only image inspector

## Prepare the shared service study

Complete lessons 39–44 first, then open the framework-iso-inspection lab README. You need a matching installed Framework SDK and a C23 compiler. Build the client and run its six cases using that guide. Expected results explain what to verify; they are not evidence that your installed SDK has passed.

Setup produces an ISO through a selected Linux GRUB program. Boot Media observes an image before reviewing a transfer. Both need to interpret ISO descriptors, but neither should maintain its own version of the byte-format rules. The independent iso_image library lets both clients use the same parser without making Setup depend on Boot Media, which already depends on Setup.

## A callback supplies a capability

A read callback is a function the parser can call to obtain bytes. It accepts a context pointer, a byte offset, an output buffer and a length. Success means that every requested byte was supplied. Returning success after a short read would let the parser examine bytes that do not belong to the source.

The parser has no filename, device path, process runner or write callback. Its authority is limited to the bytes the caller exposes. The lab uses memory; a file adapter must enforce its own checked-open policy and stable-source lifetime. Sharing a parser does not replace those operating-system responsibilities.

~~~c
UmiIsoImageInfo info = {0};
UmiStatus status = UmiIsoImageInspect(Read, &source, source.size, &info);
/* source and its bytes remain alive until this synchronous call returns. */
~~~

## Check a range without overflowing

Read first asks whether offset exceeds size. Only after that succeeds does it subtract offset from size and compare length with the remainder. Avoid checking offset + length alone: an overflowing addition can produce a small value that appears to fit.

The conversion from the 64-bit offset to size_t occurs after the range check. In this lab, size came from a real allocation represented by size_t, so an accepted offset fits that host type. This reasoning matters when moving an example between 32-bit and 64-bit environments.

~~~c
if (offset > (uint64_t)source->size ||
    (uint64_t)length > (uint64_t)source->size - offset)
    return UMI_STATUS_IO_ERROR;
memcpy(destination, source->data + (size_t)offset, length);
~~~

## Keep accepted observations intact

Framework builds observations in a temporary candidate and copies it to the output only after the entire supported profile succeeds. An error therefore cannot leave iso9660 set while silently losing a failed boot-catalogue check. The lab initializes every flag to zero and prints those unchanged flags for its failing scenarios.

Run the read-failure scenario. It deliberately fails the second callback and should return status 8, process exit 1 and four zero flags. Explain why that result says nothing about real disk reliability. Then inspect the Framework regression case that initializes output with sentinel bytes and requires exact preservation on failure.

## Exercise and recovery

Draw the ownership chain: main owns the allocation, Source borrows it, the parser temporarily borrows Source, and Read fills parser-owned buffers. Mark the point where free is allowed. Change the exercise to fail its first read and predict the number of callbacks before running it.

If the installed component cannot be found, update the SDK through its normal owner-run build and installation workflow. Do not paste the parser into the application. Keep the build log and compiler identity if headers and archives disagree. A small consumer is useful because it exposes an actual shared-library contract rather than hiding a second implementation.

[Installed SDK lab and commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-iso-inspection/README.md) · [Course contents](../../../courses/umicom-os-from-scratch/index.html)

[Written contents](index.md) · [Previous lesson](44-plan-boot-and-distribution-evidence.md) · [Next lesson](46-decode-optical-records-and-byte-order.md)

<!-- Repository laboratory sources live outside the published content root.
Public repository links replace the former local-only routes, retained here for review:
../../../../labs/native/framework-iso-inspection/README.md
Offline source files remain available in their listed repository/learning-pack locations. -->
