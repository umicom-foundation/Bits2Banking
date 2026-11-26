<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/58-keep-head-metadata-separate-from-content.md

PURPOSE:
Keep HEAD metadata separate from content

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Keep HEAD metadata separate from content

A colleague wants to check whether a published report is available. They can ask for HEAD, which asks for response headers. GET usually returns those headers and the report itself. A report server can use HEAD to avoid preparing or transferring a large document.

Think of a representation as the particular version of a response selected for a request. For example, one route might return a plain-text report. Its Content-Length for HEAD is the number of bytes that would be in the relevant GET response. It can be zero when that representation is empty. If the worker cannot determine the length without producing the report, it can omit the value.

## Learn where each decision belongs

1. The web service admits a request without a body and forwards the actual HEAD method to the FastCGI worker. FastCGI is the protocol the web server uses to communicate with that separate application.
2. The worker reports the headers it knows. A reported length and the bytes the worker might have generated are separate facts.
3. The web gateway reads the bounded worker reply. It prepares the selected headers and discards any worker document bytes for HEAD.

The following C model describes the two possible length states. The boolean records whether a worker supplied a length. The integer can then represent a reported empty document without being confused with an unknown length.

```c
typedef struct HeadMetadata {
    bool length_known;
    size_t length;
} HeadMetadata;

const HeadMetadata empty_report = {.length_known = true, .length = 0U};
const HeadMetadata pending_report = {.length_known = false, .length = 0U};
```

## Practice

Write a three-column table with worker header, bytes sent to the HTTP client, and meaning. Fill it in for a reported length of 42, a reported length of 0, and no reported length. All three send zero document bytes. The first two include a length header and the third omits it.

If your table makes a missing length look like an empty report, revisit the boolean. The next lesson checks these cases on the wire with an offline C23 exercise.

[HTTP HEAD semantics](https://www.rfc-editor.org/rfc/rfc9110.html#section-9.3.2) · [CGI worker behavior](https://www.rfc-editor.org/rfc/rfc3875.html#section-4.3.3)

[Course contents](index.md) · [Previous lesson · Limit compiled bytes before embedding](57-limit-compiled-bytes-before-embedding.md) · [Next lesson · Check HEAD responses byte by byte](59-check-head-responses-byte-by-byte.md) · [HTML edition](../../../courses/building-a-web-server-in-c/lessons/58-keep-head-metadata-separate-from-content.html)
