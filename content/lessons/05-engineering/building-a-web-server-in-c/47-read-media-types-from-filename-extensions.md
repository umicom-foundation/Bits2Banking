<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/47-read-media-types-from-filename-extensions.md

PURPOSE:
Read media types from filename extensions

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read media types from filename extensions

A browser reads two pieces of information when a server returns a
file. It receives the file bytes and a `Content-Type` header. The
header gives a name for the format. For example, `image/avif`
identifies an AVIF image.

## Predict the media type before sending a response

Read the final filename suffix by starting at the last dot.
`cover.AVIF` and `cover.avif` both name an AVIF file.
`cover.avif.backup` ends in `.backup`. The preview's ordinary
fallback for an unknown suffix is `application/octet-stream`,
which describes general binary data.

Save this example as `show-media-types.c`. It calls the same
Framework classifier as the local static preview.

~~~c
#include "umicom/web/mime.h"
#include <stdio.h>

int main(void)
{
    const char *const paths[] = {
        "assets/cover.AVIF",
        "assets/background.WebP",
        "assets/headline.WOFF2",
        "assets/intro.MP4",
        "assets/cover.avif.backup"
    };

    /* The classifier returns a media type based on each supplied path. */
    for (size_t index = 0U; index < sizeof paths / sizeof paths[0]; ++index)
        puts(umi_web_mime_from_path(paths[index]));
    return 0;
}
~~~

1. Open PowerShell beside the practice file. Use a current GCC on your
   path and point it at the Framework source checkout.
2. Build the exercise and run it. Compare its lines with the expected
   types below.
3. Change the suffix of the fourth input to `.woff`. Expect
   `font/woff` in that position. The program only receives path strings,
   so this change is an exercise in classification. To serve real
   content, supply bytes encoded in the format named by their suffix.

~~~powershell
$Framework = Read-Host 'Enter the full path to the Umicom Framework checkout'
gcc -std=c23 -I "$Framework/include" show-media-types.c "$Framework/src/web/mime.c" -o show-media-types.exe
if ($LASTEXITCODE -eq 0) { & .\show-media-types.exe }
~~~

~~~text
image/avif
image/webp
font/woff2
video/mp4
application/octet-stream
~~~

## Check an exported asset in the browser

When you use the local preview from the preceding course, open the
browser's network panel and select an asset request. Find
`Content-Type` among the response headers. If the format is unexpected,
compare the path in the request to the final suffix of the file in the
selected document root.

This is the same decision used when Umicom WebServer sends static
preview files for an Umicom site. Use the existing Umicom logo and icon
as supplied. SVG and ICO retain their own media types. [IANA media type registry](https://www.iana.org/assignments/media-types/)

[Course contents](index.md) · [Previous lesson · Understand capped request counters](46-understand-capped-request-counters.md) · [HTML edition](../../../courses/building-a-web-server-in-c/lessons/47-read-media-types-from-filename-extensions.html)

[Next lesson · Check export and download headers](48-check-export-and-download-headers.md)
