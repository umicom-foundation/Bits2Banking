<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/54-add-metadata-to-a-counted-response.md

PURPOSE:
Add metadata to a counted response

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Add metadata to a counted response

Imagine a WebServer practice route that returns the three characters `abc`. Its handler wants to attach a short label for a reader. The label is **metadata**, which describes the reply. **Framing** gives the recipient the rules for finding the end of the reply. The Framework formatter counts the body bytes and supplies `Content-Length: 3` for this ordinary 200 response.

## 1. Add an ordinary field with the public helpers

The saved C23 fixture prepares a 200 reply as plain text. It adds `X-Range-Label` through the public header helper. That name uses letters and hyphens. The value contains an internal tab. The tab is one character even when an editor displays it as a wide gap.

~~~c
#include "umicom/web/response.h"

static UmiStatus prepare_labelled_reply(UmiWebResponse *response)
{
    /* Prepare the body and its media type before appending the extra field. */
    UmiStatus status = umi_web_response_set_text(response, 200, "text/plain", "abc");
    if (status != UMI_STATUS_OK)
        return status;

    /* Add an application label. The formatter manages the body length. */
    return umi_web_response_set_header(response, "X-Range-Label", "one\ttwo");
}
~~~

After both calls succeed, pass the response to a formatter and check its result. Both `umi_web_response_format` and `UmiWebResponseFormatClosed` preserve the internal tab in `X-Range-Label: one\ttwo`. A field name follows a different rule. It must have at least one character, and an embedded space makes it invalid.

## 2. Predict what changes in the destination

Draw a response object and a separate output buffer. Give the buffer 256 bytes, fill every byte with `z` and set its result count to `79`. For each row, start with a fresh 200 reply containing `abc`. Attach just the listed extra field. Restore the original buffer and count before each trial.

| Extra field | Why the formatters refuse |
| --- | --- |
| Empty name with the value `example` | A field needs a name. |
| `Invalid Name: example` | A space breaks the name. |
| `cOnTeNt-LeNgTh: 3` | Framework supplies the framing length. The mixed letter case still names the same reserved field. |

In the fixture, the header helper stores each of those pairs. Both formatters then return `UMI_STATUS_INVALID_ARGUMENT`. For each failure, compare all 256 destination bytes with the original. They stay `z`. The compatibility formatter leaves the count at `79`. The closed formatter resets the count to `0`. Read the status before treating an output count as the length of a new reply.

Use the same paper trace for a fictional Bits2Banking export label. Sketch a valid metadata field name, then identify where to check the formatter's result. Keep the data bytes, metadata and framing count in separate boxes. The stored Framework fixture checks these operations in memory.

[Course contents](index.md) · [Previous lesson · Validate an empty response before publishing it](53-validate-an-empty-response-before-publishing.md) · [Format GET and HEAD responses](12-format-get-and-head-responses.md) · [Check export and download headers](48-check-export-and-download-headers.md) · [Count every response body byte](50-count-every-response-body-byte.md) · [Next lesson · Keep the exact name of a web event](55-keep-the-exact-name-of-a-web-event.md) · [HTML edition](../../../courses/building-a-web-server-in-c/lessons/54-add-metadata-to-a-counted-response.html)
