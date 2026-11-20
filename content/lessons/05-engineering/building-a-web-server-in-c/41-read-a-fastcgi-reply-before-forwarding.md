<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/41-read-a-fastcgi-reply-before-forwarding.md

PURPOSE:
Read one bounded worker reply and distinguish stream endings from completion.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Read a FastCGI reply before forwarding

[Course contents](index.md) · [Previous lesson](40-encode-a-fastcgi-request-with-bounded-bytes.md) · [Next lesson](42-turn-a-worker-document-into-http.md)

Network and local-process reads may return part of a header or several records at once. Keep a bounded receive buffer and pass the available byte count to `UmiWebFastCgiReadReply`. On an incomplete record the service returns `UMI_STATUS_UNAVAILABLE`, keeping the previous reply state and result. After a complete record, consume exactly its `consumed` count. Its body still points into your receive buffer, so copy any needed bytes before moving or reusing the buffer.

## Keep each result in its own place

1. Initialize the reply with its exact request ID and an output budget. The combined budget covers both worker streams.
2. Preserve `STDOUT` for the later CGI response parser. Keep `STDERR` in a controlled diagnostic path. After an empty record closes one stream, later data for that stream is refused.
3. Require an `END_REQUEST` record before declaring the worker response complete. Check the protocol status and application exit status individually. The end record closes any remaining streams.
4. Pass admitted output to a separately checked CGI-to-HTTP response adapter. Apply its own header and body limits before writing a response. Leave an incomplete worker result out of the HTTP response.

## Try the reply checks

Use the configured build directory from the previous lesson. Run these cases before trying a real worker.

```powershell
$wireBuild = Join-Path $PWD 'build/fastcgi-wire'
ctest --test-dir $wireBuild --no-tests=error -R '^framework[.]web[.]fastcgi[.](response|truncated-frame|wrong-request|shared-budget|end-status)$'
```

Expect five passing tests. The response fixture carries three output bytes and one diagnostic byte. Under a three-byte budget, the first record fits and the diagnostic is refused. A transport that ends after the output record has left the response incomplete. If a worker appears to return output before completion, record its request ID, stream lengths and the end status separately. The local examples use synthetic records, so verify worker launch, CGI header translation and HTTP delivery in their own integration checks.
