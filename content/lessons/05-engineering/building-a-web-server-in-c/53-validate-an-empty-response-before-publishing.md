<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/53-validate-an-empty-response-before-publishing.md

PURPOSE:
Validate an empty response before publishing it

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Validate an empty response before publishing it

A response builder can hold a status, header fields and body bytes in memory before it formats them. Formatting decides which bytes appear in the output. An HTTP 204 response has no body, but the formatter still needs to check the header fields it is about to copy.

In *Preserve output when a buffer is too small*, you checked the return status, buffer and reported length separately. Use the same idea here for a formatting refusal caused by a header field. The earlier small-buffer lab resets its length on refusal. The compatibility formatter in this lesson leaves the caller's existing length in place.

## Trace the checks on paper

1. Draw a response object beside an output buffer. The output buffer is where the formatter writes a complete reply. Mark its first byte `q` and the caller's output count `71`. These recognizable starting values help you spot changes.
2. Set the response to `204 No Content`. Add `X-Example: retained` and store the three body bytes `a`, zero and `c` in the response object. This produces 48 counted header bytes, including the blank line. The compatibility formatter also needs one byte of space for its C string terminator. That terminator is outside the count.
3. For the last two rows, start with a fresh 204 response and add only the indicated header with the value `0`. The header-setting step accepts it. Check which step refuses the finished reply.

| Paper case | Compatibility formatter result | What to check |
| --- | --- | --- |
| Ordinary metadata, 48 bytes of capacity | `UMI_STATUS_CAPACITY_EXCEEDED` | First byte stays `q`. Count stays `71`. |
| Ordinary metadata, 49 bytes of capacity | `UMI_STATUS_OK` | Count becomes `48`. The blank line ends the response. The output contains the ordinary header and zero body bytes. The generated `Content-Length` is omitted. All three stored body bytes are still present in the response object. |
| `CoNtEnT-LeNgTh: 0`, ample capacity | `UMI_STATUS_INVALID_ARGUMENT` | First byte stays `q`. Count stays `71`. |
| `Transfer-Encoding: 0`, ample capacity | `UMI_STATUS_INVALID_ARGUMENT` | First byte stays `q`. Count stays `71`. |

HTTP field names are compared without regard to letter case. The compatibility formatter manages framing, which tells a reader where a response ends. The fields in the last two rows are reserved for that decision when the body is empty.

~~~text
PLAN the response bytes and the required capacity
CHECK every header before copying the reply
IF a check refuses the response
    RETURN its status with the output buffer and count unchanged
COPY the complete reply
SET the count to the number of response bytes
RETURN success
~~~

Explain why adding more capacity fixes the first row and leaves the last two outcomes unchanged. You can compare the same four results in an in-memory test. Keep the status, buffer observation and count as three separate checks.

[Course contents](index.md) · [Previous lesson · Keep a saved representation after a 304 response](52-keep-a-saved-representation-after-304.md) · [Format GET and HEAD responses](12-format-get-and-head-responses.md) · [Preserve output when a buffer is too small](13-preserve-output-on-small-buffers.md) · [HTML edition](../../../courses/building-a-web-server-in-c/lessons/53-validate-an-empty-response-before-publishing.html)

[Next lesson · Add metadata to a counted response](54-add-metadata-to-a-counted-response.md)
