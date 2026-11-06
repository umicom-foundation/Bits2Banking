# Recognise complete requests and honest results

A network read can stop in the middle of a message. A response can fail after a handler has already run. Study the existing Framework contracts before treating either event as success or retrying work.

## 1. One read is not necessarily one request

A connection transports bytes. A callback may return fewer bytes than the complete request. The parser must distinguish “more bytes are needed” from “these bytes cannot form a supported request.” This distinction is part of [`connection.h`](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/connection.h).

```text
UmiStatus status = UmiWebRequestFrameRead(
    bytes, length, maximum_bytes, &frame);
```

This is a source-reading excerpt, with caller-owned byte storage and a result variable. `UMI_STATUS_BUSY` means the frame is incomplete. The service must not dispatch a handler yet. Other failures identify unsupported or invalid input. For this framing function, output is cleared on failure or incomplete input; the later strict parser has a different unchanged-on-failure contract. Read each API's own rule.

## 2. Bound both memory and work

The current request and response types have 16,384-byte body arrays. That capacity is not permission to accept every request of that body length: the strict request contract also enforces its framing and body limits. The native server limits the entire received request to at most 16 KiB. The portable exchange API has its own 64 KiB wire-request bound and still respects the smaller body type.

A limit is a reason to refuse an oversized message, not to cut off bytes and pretend the remaining prefix is the whole message. The Kernel's bounded input lessons use the same ownership principle with a different protocol.

## 3. Use the deliberately supported HTTP subset

The strict path accepts one HTTP/1.1 origin-form request with one Host header and at most one decimal Content-Length. It refuses transfer encoding, protocol upgrades, Expect, duplicate lengths and extra pipelined bytes. Each connection receives one response and then closes. Those are limits of this Framework path, not claims that HTTP itself forbids every refused feature.

The response formatter supplies authoritative length and close headers. It omits a HEAD body while retaining the representation length. This example does not provide persistent connections, HTTP/2, TLS or a general public web-hosting service.

## 4. Separate execution from delivery

`UmiWebExchangeResult` records `dispatched` and `response_complete`. They answer different questions:

| Observation | What you may conclude |
| --- | --- |
| Not dispatched | The service routing phase was not entered for this exchange. |
| Dispatched | Routing ran; it may have produced a route-miss response or called a handler. |
| Response complete | The server completed its response write. This does not prove a user read it. |
| Dispatched, response incomplete | A handler may already have changed state even though the client did not receive the full response. |

Do not automatically retry a state-changing operation just because sending the response failed. A future application needs an explicit duplicate-request design and appropriate authorization. The local echo demonstration has no persistent operation to retry.

## 5. Understand static preview before choosing a folder

The example supports `--root` followed by an absolute export directory. In that mode, exported files replace the demo routes. Choose a folder containing only intended website assets. There are no directory listings or uploads, and files must be smaller than 16 KiB in this bounded example. A larger asset is refused rather than streamed.

The rooted reader rejects links at and below the selected root but trusts its ancestors. This is not a privileged filesystem sandbox. Static preview and a private developer-source directory are different purposes; select the export deliberately.

## 6. Read the actual regression boundaries

1. Open `cmake/UmicomWebConnection.cmake`.
2. Follow its request-frame, closed-response, exchange, native-exchange, static-preview and request-gate test includes.
3. For each area, identify the actual test source and the contract it exercises.
4. Keep pure byte-transport tests separate from native socket execution.

The optional build in lesson 3 creates only the demonstration target and its dependencies. It does not establish that these regression executables exist or have passed. Follow the project's full qualification guide when testing a Framework change.

## Exercises with explanations

A connection disappears after a handler updates a record. Should the server call the handler again automatically?

<details>

<summary>Answer</summary>

No. The first update may already exist. Inspect the exchange result and apply the application's explicit request-identity and recovery rules. A missing response is not proof of no effect.

</details>

A request has a complete-looking first line but no terminating blank line after its headers. Should routing start?

<details>

<summary>Answer</summary>

No. The framing stage has not established a complete request. Wait within the configured limits or refuse the incomplete exchange; do not treat a damaged prefix as a whole message.

</details>

Continue with [Umicom Framework Development](../../../courses/umicom-development/index.html) and [Learning HTML](../../../courses/learning-html/index.html) to connect native services with understandable user interfaces.

---

[Read this lesson in HTML](../../../courses/building-a-web-server-in-c/lessons/04-framing-errors-and-exercises.html) · [Learning sequence](../../../start/learning-sequence.md)


## Next lesson

Continue with [Requests are bytes, not packets](05-requests-are-bytes-not-packets.md).
