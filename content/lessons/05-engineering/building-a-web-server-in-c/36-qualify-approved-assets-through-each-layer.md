<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/36-qualify-approved-assets-through-each-layer.md

PURPOSE:
Qualify approved assets through each delivery layer

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->


![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Qualify approved assets through each delivery layer

## Use the artwork that ships with the SDK

The installed-SDK lab obtains Framework assets from UMICOM_FRAMEWORK_RESOURCE_ROOT. It does not generate a substitute icon or shrink an approved SVG to fit an older buffer. The owned-svg and owned-ico cases compare the selected file size, first bytes and media type; legacy-svg retains the expected inline-capacity refusal. Full native transport tests compare complete response bytes.

Use the README configuration commands with the installed SDK you intend to qualify. A missing resource folder is an installation failure to investigate, not a reason to silently skip the asset cases. Record the Framework revision, SDK prefix and asset checksum with the result. The website has its own approved wordmark variants; equal branding does not require overwriting those variants with unrelated files.

## Inspect without opening a port

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\build\static-preview\btb-static-preview.exe" "C:\umicom\installed\applications\share\umicom\framework\resources\brand" GET /umicom.ico --owned
& ".\build\static-preview\btb-static-preview.exe" "C:\umicom\installed\applications\share\umicom\framework\resources\brand" HEAD /umicom.ico --owned
```

Run each command separately after the documented lab build and stop on an error. Substitute your actual installed prefix if it differs. Both inspections should report the same admitted representation length. HEAD should plan no body bytes. The historical body-sent label describes the selected serialization path; the added transport line explicitly says no bytes were sent to a peer. This tool does not prove a browser received the image.

## Check static media types in memory

A media type tells a reader how to interpret the response bytes. In HTTP, it appears in the `Content-Type` header. For example, `text/css` identifies a style sheet and `image/svg+xml` identifies an SVG drawing.

Framework checks the final filename extension and matches the ASCII letters A to Z with a to z. CSS, MjS and ICO can therefore use the same registered types as their lowercase forms. An unknown final extension or a filename without one gets the generic `application/octet-stream` value. A period in a parent directory does not give its child file an extension.

The C23 program below classifies six path strings. It reports the first mismatch and exits with a failure status. The program runs in memory and opens no assets. The native preview uses this same classification when it prepares headers for a rooted file.

~~~c
#include "umicom/web/mime.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    const struct
    {
        const char *path, *expected;
    } examples[] = {
        {"assets/STYLE.CSS", "text/css; charset=utf-8"},
        {"assets/worker.MjS", "text/javascript; charset=utf-8"},
        {"assets/logo.sVg", "image/svg+xml"},
        {"assets/UMICOM.ICO", "image/vnd.microsoft.icon"},
        {"assets/logo.ICO.bIn", "application/octet-stream"},
        {"assets.css/worker", "application/octet-stream"}
    };

    /* Ask the Framework to classify each path string in memory. */
    for (size_t i = 0U; i < sizeof(examples) / sizeof(examples[0]); ++i)
    {
        const char *type = umi_web_mime_from_path(examples[i].path);
        if (strcmp(type, examples[i].expected) != 0)
        {
            fprintf(stderr, "%s: expected %s, got %s\n",
                    examples[i].path, examples[i].expected, type);
            return EXIT_FAILURE;
        }
        printf("%s -> %s\n", examples[i].path, type);
    }
    return EXIT_SUCCESS;
}
~~~

1. Using a Framework source checkout and a C23-capable GCC, save the program as `check-mime.c` in a new exercise folder. Open PowerShell in that folder.
2. Set the Framework path for your checkout and compile. Stop if the command reports an error.

   ~~~powershell
   $framework = 'C:\umicom\Umicom-Applications\framework'
   gcc -std=c23 -Wall -Wextra -Wpedantic -I "$framework\include" .\check-mime.c "$framework\src\web\mime.c" -o .\check-mime.exe
   ~~~

3. Run the program and compare all six lines with the expected output.

   ~~~powershell
   .\check-mime.exe
   ~~~

~~~
assets/STYLE.CSS -> text/css; charset=utf-8
assets/worker.MjS -> text/javascript; charset=utf-8
assets/logo.sVg -> image/svg+xml
assets/UMICOM.ICO -> image/vnd.microsoft.icon
assets/logo.ICO.bIn -> application/octet-stream
assets.css/worker -> application/octet-stream
~~~

If the test prints a different type for a known suffix, check that your header and MIME source come from the same current Framework checkout. For a surprising fallback, read the final extension of the filename and separate the directory name from the filename.

To check the same behavior through the registered native tests, set the path below to your configured Framework build. The four cases cover direct classification and rooted CSS, JavaScript module and ICO response headers.

~~~powershell
ctest --test-dir 'C:\path\to\framework-build' --no-tests=error -R '^framework[.]web[.]static_preview[.]mime-' --output-on-failure
~~~

[Framework MIME API](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/mime.h) · [Native preview checks](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/web/test_static_preview.c) · [Read response status and body length](45-read-response-status-and-body.md)

## Then observe the real transport

Follow the native preview guide to start umicom preview with an explicit root and port. In another terminal, retrieve the ICO to a new temporary file and compare its SHA-256 with the installed source file. Request headers separately for HEAD and check the content length and media type. Finally inspect the actual page in a browser, including its logo proportions and local font fallback. Stop the listener when finished.

Keep source-contract review, headless inspection, transport retrieval and browser appearance as separate rows in your evidence. A checksum match establishes byte identity for that retrieval. It does not establish correct font selection, layout at another display scale, authentication, TLS or production deployment. The preview remains a bounded, read-only local development service.

## Recover from a mismatch

For HTTP 413, compare file size with the selected API limit. For 404, confirm the URL is relative to the chosen root rather than the current shell directory. For 403, inspect path and browser admission without bypassing the gate. For an unknown API at link time, check that headers and libraries come from the same installed SDK.

If size agrees but the checksum differs, preserve both files and the response headers. A size-only assertion cannot detect substitution or changed bytes. If bytes agree but artwork looks wrong, inspect the browser media type, the approved light or dark variant, scaling and computed font. Report an unexecuted or skipped step honestly; neither should be folded into a pass count.

[Installed-SDK lab setup](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-static-preview/README.md) · [Body ownership contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/response_body.h) · [Authored regression scenarios](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/web/test_response_body.c) · [HTTP HEAD semantics](https://www.rfc-editor.org/rfc/rfc9110.html#section-9.3.2)

[Course contents](index.md) · [Previous lesson](35-finish-headers-and-partial-body-writes.md)

[Next lesson](37-transfer-static-file-buffer-ownership.md)
