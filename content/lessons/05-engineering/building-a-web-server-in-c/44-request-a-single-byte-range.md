<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/44-request-a-single-byte-range.md

PURPOSE:
Teach how an HTTP response identifies selected byte positions and frames their length.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Request a single byte range

[Course contents](index.md) · [Previous lesson](43-check-native-routes-before-listening.md) · [HTML edition](../../../courses/building-a-web-server-in-c/lessons/44-request-a-single-byte-range.html)

A browser can ask for part of a file by naming byte positions. This is useful when a client has already received the first part of a download. The server tells the client where the new bytes belong and how many bytes it is sending. [HTTP range semantics](https://www.rfc-editor.org/rfc/rfc9110.html#name-range-requests)

## Count positions and lengths

Imagine a file with the eight ASCII bytes `ABCDEFGH` and no final line break. Number the positions from 0 to 7. Bytes 1 through 3 are `BCD` because both ends are included.

~~~c
/* Check that first <= last and last < file_length before subtracting. */
size_t selected_length = last - first + 1U;
~~~

In a partial response, `Content-Range: bytes 1-3/8` tells the reader where to place the bytes in the complete file. `Content-Length: 3` tells the reader how many bytes arrive in this response. Putting 8 in the length field would tell a client to wait for five bytes that never arrive.

## Try the rooted preview

1. Place those eight bytes in `sample.txt` beside an `index.html` in a separate export directory. Run the following commands with your actual folder path. The first checks the export and exits. The second starts the loopback listener.

~~~powershell
$export = 'C:\Sites\MyExport'
umicom-web-local-service-example --port 8080 --root $export --check-routes
umicom-web-local-service-example --port 8080 --root $export
~~~

2. From a second terminal on Windows, request the selected range. On another supported host use `curl` in place of `curl.exe`.

~~~powershell
curl.exe -i -H "Range: bytes=1-3" http://127.0.0.1:8080/sample.txt
~~~

3. Check for status 206, both lengths above, and the exact body `BCD`. If you see 404, confirm the filename and preview root. If the total length differs from eight, check for a line break or an encoding prefix in the file.

## Predict a different response

| Request | Expected result |
| --- | --- |
| GET with `Range: bytes=-2` | 206, `bytes 6-7/8`, body `GH` |
| GET with `Range: bytes=6-` | 206, `bytes 6-7/8`, body `GH` |
| GET with `Range: bytes=8-` | 416, `bytes */8` |
| HEAD with `Range: bytes=1-3` | 200, `Content-Length: 8`, no body |

<!-- The earlier lesson described the whole-file range implementation.
Predict the response for bytes 3 through 99. The preview can stop the selection at the last available byte, which is position 7, and send five bytes. A request with several ranges uses the full response in this preview. The ordinary 1 MiB file limit still applies.
-->
Predict the response for bytes 3 through 99. The preview can stop the selection at the last available byte, which is position 7, and send five bytes. A request with several ranges uses the full response in this preview.

## Read a small range from a larger file

The 1 MiB limit applies to the response bytes. Framework can read a small range in a larger ordinary file and measure its full length through the same open handle. The native C23 fixture uses a 1,048,580-byte file. Its `bytes=-3` request receives 206 with `Content-Range: bytes 1048577-1048579/1048580` and `Content-Length: 3`. A request for all the bytes receives 413. A request starting at byte 1,048,580 receives 416 because the last byte position is one less than the file length.

Follow the [C23 response checks](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/web/test_static_ranges.c) to see how a binary fixture verifies the exact bytes and framing before a listener is involved.

[Next lesson · Read response status and body length](45-read-response-status-and-body.md)
