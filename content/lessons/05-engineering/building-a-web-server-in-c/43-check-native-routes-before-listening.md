<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/43-check-native-routes-before-listening.md

PURPOSE:
Teach in-memory C request handling and the separate listener check.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material.
-->

# Check native routes before listening

<p class="umicom-course-artwork"><span class="umicom-brand-mark"><img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom" width="180"></span> <a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="30"></a></p>

[Course contents](index.md) · [Previous lesson](42-turn-a-worker-document-into-http.md)

A route connects a request path with a handler. A listener accepts live connections. An in-memory check sends test data directly to the parser and service, before opening a listener.

1. Use a built Umicom Framework local service example that lists **--check-routes** in its help. Use the full Windows executable path if your terminal cannot find the command.
2. Run the following command. Port 8080 identifies the expected local policy in the constructed requests.

~~~text
umicom-web-local-service-example --port 8080 --check-routes
~~~

3. Expect **Local route and browser admission checks passed in memory.** A refusal gives the case name and its expected and observed HTTP status.
4. Open **examples/web/local_service.c**. Find **UmiWebRequestParseStrict** and **UmiWebServiceHandleBody**. Draw separate columns for Framework operation status, HTTP status and response bytes.

The expected home and health responses are HTTP 200. A controlled unrelated Host and a controlled unrelated Origin each require HTTP 403. Test them separately so the reason for a refusal stays clear.

In a branded build, follow the owned SVG and ICO response bodies through comparison and release. Explain how reading the buffers after release would make the test unreliable.

## Predict what each method should do

The method says what the sender wants. A response header describes the reply, while its body holds the returned data. In the C example, find the readiness cases below and cover the last column. Predict the outcome for each case, then compare it with the table and with the source.

| Request | Expected HTTP status | What the in-memory check compares |
| --- | --- | --- |
| `HEAD /api/health` | 200 | The selected representation has the JSON type. The service result still carries its data at this stage. |
| `POST /api/echo` with `message=ready+check` | 200 | The reply has a plain-text type and includes every original byte in order. |
| `POST /favicon.ico` with branding enabled | 405 | The `Allow` header names `GET` and `HEAD`. A successful favicon request uses an icon type. |

Imagine the echo handler sends HTTP 200 and returns only `message=ready`. Explain which check fails. Then explain why a live `HEAD` response should keep its selected representation's headers while sending no body bytes. The in-memory test checks the route choice and representation. The later network test checks the response sent to the client.

Design a separate loopback check that proves listening, receiving, completing a response and shutdown. Add installed package identity and linker results when reporting work through an SDK. [Framework local web service guide](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/local-web-service.html)

[Next lesson on requesting bytes](44-request-a-single-byte-range.md).
