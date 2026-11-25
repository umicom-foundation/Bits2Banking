<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/52-keep-a-saved-representation-after-304.md

PURPOSE:
Keep a saved representation after a 304 response

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Keep a saved representation after a 304 response

Imagine your browser has a saved copy of a Bits2Banking course timetable. A saved copy kept for reuse is called a **cached copy**. Later the browser makes a conditional GET asking for the timetable if its saved version has changed. If the server responds with `304 Not Modified`, the browser uses its matching saved copy. The timetable still appears even though the reply ends after the headers. This is a paper example of HTTP revalidation, which means checking whether a saved copy is still current. [HTTP Semantics on 304](https://www.rfc-editor.org/rfc/rfc9110.html#section-15.4.5) · [HTTP Caching on updating stored responses](https://www.rfc-editor.org/rfc/rfc9111.html#section-4.3.4)

## Match the status to the user’s next action

1. The timetable is unchanged. For `304`, keep displaying the matching saved timetable.
2. A learner saves a setting and receives `204 No Content`. Record the successful save. The reply supplies no body.
3. A learner submits a practice form and receives `205 Reset Content`. The server asks the client to reset the form view for another entry. The reply supplies no body. [HTTP Semantics on 205](https://www.rfc-editor.org/rfc/rfc9110.html#section-15.3.6)

## Compare the two formatter outputs

The Framework test supplies the same response header, `X-Example: retained`, and the same three body bytes for every row. Its counted C array is `{'a', 0U, 'c'}`. The test sets each status explicitly and checks the output in memory. A formatter turns the response into bytes in HTTP message order. `umi_web_response_format` writes the compatibility format. `UmiWebResponseFormatClosed` writes the closed-connection format.

| Status | Generated `Content-Length` in either format | Bytes after the blank line |
| --- | --- | --- |
| `204 No Content` | Omitted | 0 |
| `205 Reset Content` | `0` | 0 |
| `304 Not Modified` | Omitted | 0 |

Both formats include `X-Example: retained`. The closed-connection format also includes `Connection: close`. All three source bytes remain in the response object after formatting. The test checks the emitted message and the stored body separately.

For a 304 reply to a conditional GET, HTTP allows a `Content-Length` field when its value equals the number of content bytes a `200 OK` reply to the same request would send. These Framework formatters omit the field for 304. [HTTP Semantics on Content-Length](https://www.rfc-editor.org/rfc/rfc9110.html#section-8.6)

## Try the timetable trace on paper

Draw a card for the browser’s saved timetable and a second card for the newly received reply. Put three example bytes on the saved card. Write `304 Not Modified`, `X-Example: retained`, and a blank line on the reply card. Add `Connection: close` when you draw the closed-connection version.

Which card supplies the bytes you display? Read the saved card. It still holds all three bytes. Now change the reply card to `205 Reset Content` and add `Content-Length: 0`. The reply still ends at the blank line. The new status asks the client to reset the submitted view.

[Course contents](index.md) · [Previous lesson · Follow a HEAD request through the in-memory router](51-follow-head-through-the-in-memory-router.md) · [Next lesson · Validate an empty response before publishing it](53-validate-an-empty-response-before-publishing.md) · [Finish headers and partial body writes](35-finish-headers-and-partial-body-writes.md) · [Read response status and body length](45-read-response-status-and-body.md) · [Count every response body byte](50-count-every-response-body-byte.md) · [HTML edition](../../../courses/building-a-web-server-in-c/lessons/52-keep-a-saved-representation-after-304.html)
