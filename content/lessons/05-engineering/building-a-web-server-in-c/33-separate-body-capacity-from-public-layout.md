<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/33-separate-body-capacity-from-public-layout.md

PURPOSE:
Separate body capacity from public C layout

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->


# Separate body capacity from public C layout

## Start with a file that is too large

Complete the static-preview lab first. Its original command uses the inline response API and accepts a complete file of at most 16,383 bytes. Several approved Umicom SVG files exceed that limit, and the Windows ICO is larger again. A 413 response therefore describes an admission decision; it does not prove that the logo file is damaged. Compare the selected file size with the API contract before changing either artwork or networking code.

The optional --owned lab mode and native preview now use a separate response-body owner with a limit of 1,048,576 bytes. These are authored capabilities requiring a matching installed SDK. The original command and public response structure retain their existing contract.

## Why not enlarge the array?

A public C structure has a layout: each member has an offset and the complete object has a size. A compiled client may reserve that size on its stack or inside another object. Increasing an embedded response array can change the layout expected by existing clients. Rebuilding one library does not rebuild every caller. This is an application binary interface concern, usually abbreviated ABI.

An opaque type hides its layout behind a pointer. The new body owner copies a bounded byte sequence, while the response structure continues to hold status and headers. This keeps the old inline representation available and avoids making every small response reserve a megabyte. It also introduces a responsibility: every successful allocation needs exactly one destruction after the last use.

## Inspect both contracts

```c
/* Include umicom/web/response_body.h. */
UmiWebResponseBody *body = NULL;
const unsigned char payload[] = {0x55, 0x00, 0x4d, 0x49};
UmiStatus status = UmiWebResponseBodyCreate(payload, sizeof payload, &body);
if (status != UMI_STATUS_OK) return status;
size_t length = UmiWebResponseBodyLength(body);
/* length is four; the embedded zero is part of the representation. */
UmiWebResponseBodyDestroy(body);
body = NULL;
```

This fragment belongs inside a function returning UmiStatus. The input is borrowed only for the create call. The returned owner contains a copy, so modifying the input afterwards must not change the copied bytes. Length is explicit; strlen would incorrectly stop at the embedded zero. Destruction ends the lifetime of any pointer obtained from UmiWebResponseBodyBytes.

## Exercise and expected observations

Use the installed lab README to build its eleven checks. Run the same approved SVG request once with the original command and once with --owned. The original mode should produce HTTP 413 when that file exceeds its inline capacity. The owned mode should describe HTTP 200 and exactly the installed file size when it is within the one-MiB bound. Neither invocation opens a listener.

Read response_body.h beside the implementation and identify the output state on allocation failure, invalid input and excessive length. Draw the two lifetimes: caller input during copying, then owned bytes until destruction. A compilation error for an unknown new API usually means the header and installed library are from different revisions; inspect the SDK prefix before changing the example.

[Installed-SDK lab setup](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-static-preview/README.md) · [Body ownership contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/response_body.h) · [Authored regression scenarios](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/web/test_response_body.c) · [HTTP HEAD semantics](https://www.rfc-editor.org/rfc/rfc9110.html#section-9.3.2)

[Course contents](index.md) · [Previous lesson](32-qualify-static-preview-in-layers.md) · [Next lesson](34-own-static-response-bytes-until-consumed.md)
