# Building a Web Server in C

Start with the first module and follow its lessons in order. Later project modules build on the earlier ideas. Each exercise identifies the source files, setup, expected result and recovery steps; keep your practice work in a separate folder.

## Requests, routes and server lifetime

Trace one request through a handler and identify who owns the service.

1. [Follow a browser request into C](01-follow-a-request.md)
1. [Connect routes to ordinary C functions](02-routes-and-handlers.md)
1. [Start and stop a local service safely](03-own-the-server-lifetime.md)
1. [Recognise complete requests and honest results](04-framing-errors-and-exercises.md)

## Framing and configuration

Bound incomplete input and validate a port before launching a Framework service.

1. [Requests are bytes, not packets](05-requests-are-bytes-not-packets.md)
1. [Buffer capacity and partial input](06-buffer-capacity-and-partial-input.md)
1. [Run and explain a Framework service](07-run-and-explain-a-framework-service.md)
1. [Reject an invalid port before starting a server](08-reject-an-invalid-port-before-launch.md)

## Project: a request and response contract

Parse into owned storage, reject ambiguous framing and distinguish dispatch from actual delivery.

1. [Observe a complete HTTP message](09-observe-a-complete-http-message.md)
1. [Parse into owned storage](10-parse-into-owned-storage.md)
1. [Reject ambiguous request framing](11-reject-ambiguous-framing.md)
1. [Format GET and HEAD responses](12-format-get-and-head-responses.md)
1. [Preserve output when a buffer is too small](13-preserve-output-on-small-buffers.md)
1. [Register a route and its context](14-register-a-route-and-context.md)
1. [Handle short reads and writes](15-handle-short-transfers.md)
1. [Distinguish dispatch from delivery](16-distinguish-dispatch-from-delivery.md)

## Project: own and admit fragmented input

Trace copied bytes, shared header policy, terminal refusals, explicit reset and transport ownership.

1. [Own an incomplete request across reads](17-own-an-incomplete-request.md)
1. [Scan new header bytes and reuse strict rules](18-scan-only-new-header-bytes.md)
1. [Keep binary body length explicit](19-keep-binary-body-length-explicit.md)
1. [Bound input and keep terminal errors visible](20-bound-input-and-terminal-errors.md)
1. [Reset parser state without claiming keep-alive](21-reset-state-without-keeping-a-connection.md)
1. [Test message decisions across fragment boundaries](22-test-every-fragment-boundary.md)
1. [Connect parser state to the transport owner](23-connect-stream-state-to-transport-ownership.md)
1. [Qualify the parser, exchange and local host separately](24-qualify-a-local-c-web-workflow.md)

<!-- The module guide above owns the reading order. Earlier explanations and reference links remain available for readers following existing material. -->

<details markdown="1">
<summary>Additional explanations and reference links</summary>

# Building a Web Server from Scratch in C

Continue the existing web-server course with byte framing, bounded input and a real Framework service walkthrough. Build reusable server behaviour in Framework and keep application handlers small.

## Before you begin

- [Learning C](../../../courses/learning-c/index.html)
- [Umicom Framework Development](../../../courses/umicom-development/index.html)

The first prerequisite supplies the subject background. Additional language courses prepare you for the code examples; read their first-program, values, functions and data lessons before attempting the labs.

## Lessons available now

1. [Follow a browser request into C](01-follow-a-request.md)
2. [Connect routes to ordinary C functions](02-routes-and-handlers.md)
3. [Start and stop a local service safely](03-own-the-server-lifetime.md)
4. [Recognise complete requests and honest results](04-framing-errors-and-exercises.md)
5. [Requests are bytes, not packets](05-requests-are-bytes-not-packets.md)
6. [Buffer capacity and partial input](06-buffer-capacity-and-partial-input.md)
7. [Run and explain a Framework service](07-run-and-explain-a-framework-service.md)

## How to study

Read one lesson, predict the example result, then attempt the exercise before opening its explained answer. Save optional practice programs in a folder you choose. Expected outputs describe what to check; they are not a record that a command has run on your computer.

## Planned continuation

<!-- The new module replaces the earlier incremental-parser continuation plan. The previous wording is retained for engineering review.
Next modules: a bounded incremental parser; partial writes; connection timeouts; routing and methods; static-file containment; concurrency; graceful shutdown; TLS through a reviewed library; authentication boundaries; request limits and fault-injection coverage.
-->
The incremental input module above is now available. Further work covers static-file delivery, application input policy, concurrency, host shutdown and reviewed deployment. Runtime outcomes still need target-environment execution.

These opening lessons do not claim a complete pricing engine, Bitcoin node, blockchain network, Linux distribution or production web server. Each course develops the relevant part in order.

[Finance and systems learning routes](../../../courses/finance-and-systems.html)

[Browser contents](../../../courses/building-a-web-server-in-c/index.html)

## Continue with a practical source study

Before a server opens a socket, it needs a valid port number. The Framework example parses a chosen port without trusting the input text. We will trace its arithmetic and publish-on-success behaviour.

- [Reject an invalid port before starting a server](08-reject-an-invalid-port-before-launch.md)

- [Observe a complete HTTP message](09-observe-a-complete-http-message.md)

- [Parse into owned storage](10-parse-into-owned-storage.md)

- [Reject ambiguous request framing](11-reject-ambiguous-framing.md)

- [Format GET and HEAD responses](12-format-get-and-head-responses.md)

- [Preserve output when a buffer is too small](13-preserve-output-on-small-buffers.md)

- [Register a route and its context](14-register-a-route-and-context.md)

- [Handle short reads and writes](15-handle-short-transfers.md)

- [Distinguish dispatch from delivery](16-distinguish-dispatch-from-delivery.md)

</details>

## Project: preview selected static files

Own one root and routing context; distinguish path admission, HTTP responses, listening and browser observations.

- [Select a root for static files](25-select-a-static-document-root.md)
- [Decode a URL path once and retain containment](26-decode-url-paths-once.md)
- [Own the preview session and its borrowed contexts](27-own-the-preview-session.md)
- [Separate an HTTP refusal from an operation failure](28-separate-http-status-from-operation-status.md)
- [Check complete file bytes and HEAD responses](29-check-complete-file-bytes-and-head.md)
- [Review loopback binding and browser admission](30-review-loopback-and-browser-admission.md)
- [Run and stop the native preview command](31-run-and-stop-the-native-preview.md)
- [Qualify a static preview in separate layers](32-qualify-static-preview-in-layers.md)
