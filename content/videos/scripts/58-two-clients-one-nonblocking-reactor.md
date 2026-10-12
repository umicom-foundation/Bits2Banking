# Episode 58 — Two Clients, One Nonblocking C23 Reactor

**Estimated duration:** 16–19 minutes.  
**Companion lessons:** [Chapter 167](../../lessons/05-engineering/167-why-nonblocking-io-matters.md) and [Chapter 168](../../lessons/05-engineering/168-build-a-c23-select-reactor.md).  
**Demonstration:** `labs/native/http-loopback-server`, Windows PowerShell, two client terminals and the SVG architecture diagram.

## 00:00–02:20 — Why a slow client matters

**On screen:** Two browser clients request the same local teaching server. Client A sends half a header and pauses. Client B sends a complete `/health` request.

**Narration:**

"When a browser connects to a server, it may not send its complete request in one operation. It could be waiting for network packets or for a slow client device. A straightforward server accepts one connection and calls `recv` until it receives the complete request. That is useful for learning the TCP interface, but it can leave every other client waiting behind the slowest one.

"Today we will change the scheduling of socket work without creating a new worker thread. The goal is not to build an Internet-scale web server. It is to understand the difference between a blocking operation, a nonblocking operation and the operating system's notification that a socket is ready for work."

## 02:20–05:00 — Follow the original C23 code

**On screen:** `tcp_server.c`, `BtbHandleClient`, `recv`, then the original listener loop.

**Narration:**

"The existing server remains intact. It receives a bounded header, asks the HTTP parser to check those bytes, creates one response and closes the connection. Its lifetime is clear and its limitations are easy to see. Our next mode should preserve that parser, the file-safety checks, route ownership and GET/HEAD response rules.

"We will introduce an optional `--nonblocking` option. Without that option, the earlier lessons and the old server still behave exactly as before. Keeping the original makes it possible to compare two techniques rather than silently rewriting the course."

## 05:00–08:00 — The readiness loop

**On screen:** `nonblocking-two-clients.svg`, then `FD_ZERO`, `FD_SET`, `select()` and `BtbNbSetNonblocking`.

**Narration:**

"A socket marked nonblocking does not wait for input if none exists. It reports that no bytes can be read just now. We could repeatedly ask every socket whether it is ready, but that wastes CPU time. `select` asks the operating system to wait for activity across several descriptors.

"For every active request we store one small connection record. We ask for readable readiness while collecting HTTP headers and writable readiness while sending the response. We only ask for listener readiness when a free slot exists. This is the basis of our backpressure rule.

"The operating system may say a descriptor is ready, but the code must still handle a would-block result. Readiness is information, not a guarantee that an unlimited operation can be completed."

## 08:00–10:40 — Read and write complete bytes

**On screen:** `BtbNbRead`, `BtbNbPrepare`, `BtbNbTrackSend`, `BtbNbWrite`.

**Narration:**

"When `recv` reports 128 bytes, we process 128 bytes. We never assume the buffer contains a complete C string. The established HTTP parser checks the length-delimited input and tells us if more bytes are needed. A 4 KiB header boundary still applies, no matter how fragmented the request becomes.

"When sending, we ask the socket to accept at most 2,048 bytes in one turn. If it accepts only 400 bytes, those are the only bytes we account for. The remaining suffix stays in the connection's buffer until another writable notification arrives. The same progress owner used by our earlier chapter distinguishes response headers from body bytes and recognises incomplete responses."

## 10:40–13:40 — Practical demonstration

**On screen:** PowerShell command and the resulting listening address.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$Root = (Resolve-Path ".\labs\native\http-loopback-server\sample_site").Path
& ".\output\learning-build\http-loopback-server\btb-http-server.exe" `
    --port 8765 --root $Root --routes --nonblocking
```

In another PowerShell window:

```powershell
curl.exe -i http://127.0.0.1:8765/health
curl.exe -i http://127.0.0.1:8765/api/courses
curl.exe -I http://127.0.0.1:8765/index.html
```

**Narration:**

"These requests take three distinct routes through the same listener. `/health` is the fixed diagnostic response. `/api/courses` uses a registered C23 route. A static HTML file uses the read-only root and streamed response. HEAD sends no body. None of these cases requires a second network stack, a Python web application or an extra listening port.

"Next, our socket-level test creates a deliberately incomplete header on one connection while another makes a complete request. We verify that the second request can finish promptly. A successful demonstration proves that this particular overlap works; we still need negative tests and platform-specific builds."

## 13:40–16:30 — What is genuinely concurrent?

**On screen:** Eight-slot resource budget and the difference between a connection and worker thread.

**Narration:**

"Eight accepted connections can be live at once, but there is only one C23 event-loop thread. The programme is concurrent in the sense that several socket conversations can make progress independently. It is not parallel CPU execution. The registered route service remains single-owner and no handler runs on a background thread.

"The earlier four-entry queue is a separate educational model. It explains logical admission and cancellation. We must not claim that it has automatically become a real thread pool. When we eventually add workers, we will first specify safe ownership transfers, capacity and shutdown acknowledgements."

**Closing exercise:** Trace Client A and Client B across READ and WRITE states. Which client's response can be sent while the other is incomplete? Which resource is released when each closes?  
**Final card:** Chapters 167–168 → source and tests → future structured concurrency; "Pay knowledge forward: learn, contribute and help the next learner."
