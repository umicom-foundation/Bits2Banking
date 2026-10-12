# Episode 51 — Build a local HTTP server in C23

**Running time:** approximately 18–23 minutes  
**Companion lessons:** [149](../../lessons/05-engineering/149-tcp-ip-and-native-c23-sockets.md) and [150](../../lessons/05-engineering/150-parse-http11-request-bytes-safely.md)  
**Source:** [http-loopback-server laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/http-loopback-server)

## Opening — 0:00–1:40

**On screen:** Browser displaying `http://127.0.0.1:8765/health`, with the raw JSON reply next to the C23 source.

**Narration:**

> When you open a website, the browser does not simply ask your computer to display a file. It connects to another program, sends carefully structured bytes and interprets the response. Today we will write a small version of the receiving program in C23.
>
> We will keep it on the same computer, using the loopback address 127.0.0.1. That gives us a real TCP connection to investigate without putting an unfinished web server on the public internet.

## Part 1 — 1:40–4:20: Address, port and socket

**On screen:** Label 127.0.0.1 and 8765 separately.

**Narration:**

> The IP address identifies the local endpoint, while the port selects a listening service. A TCP connection delivers an ordered stream of bytes. It does not promise that one request arrives in one receive operation.
>
> Our server will create a socket, bind it to the loopback interface and listen. When a browser connects, it will accept the connection and read no more than four kilobytes of request headers.

**Demonstration:** Point to the functions `socket`, `bind`, `listen`, `accept`, `recv`, `send` and `close` in `tcp_server.c`.

## Part 2 — 4:20–8:15: Follow the request bytes

**On screen:** Show the HTTP wire-format diagram with CRLF between lines.

**Narration:**

> An HTTP request starts with a method, path and version. It continues with header lines. The header section ends with a blank line, represented by two consecutive CRLF sequences.
>
> Our parser cannot call `strlen()` on the socket input because those bytes are not automatically terminated as a C string. We carry the received length beside the pointer and check each byte before interpreting any fields.

**Demonstration:** Step through `BtbHttpParse()` in `http.c`. Show how a partial header reports `INCOMPLETE` instead of accepting an unfinished request.

**Question:** What happens if a client sends a duplicate Host header? The parser refuses the request rather than guessing which hostname controls the response.

## Part 3 — 8:15–12:45: Restrict what the server can do

**On screen:** Display a short table with supported routes and results.

**Narration:**

> A small web server becomes easier to understand when its permissions are explicit. Our example accepts GET and HEAD. It understands the routes slash and slash-health. It rejects request bodies, ambiguous length headers, traversal syntax and hostnames outside loopback.
>
> It does not open arbitrary local files. It does not implement uploads. It does not offer authentication or HTTPS. These are deliberate limits, not hidden missing steps that a learner is expected to guess.

**Demonstration:** Search for `Content-Length` and `Transfer-Encoding` in the parser and explain why both request headers are rejected in this learning subset. Then find the response code for 405 and its `Allow` header.

## Part 4 — 12:45–16:45: Build and test

**On screen:** PowerShell, using the actual Bits2Banking repository root.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\http-loopback-server" -B ".\output\learning-build\http-loopback-server" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\http-loopback-server" --parallel 2
ctest --test-dir ".\output\learning-build\http-loopback-server" --output-on-failure
& ".\output\learning-build\http-loopback-server\btb-http-server.exe" --port 8765
```

**Narration:**

> The tests exercise byte framing, safe rejection, response generation and deliberately altered inputs. They should all pass before we trust the example enough to open it in a browser.
>
> Now the server is listening on loopback. We can request slash-health and see the exact response body produced by our C23 program.

**Browser:** Open `http://127.0.0.1:8765/`, then `http://127.0.0.1:8765/health`.

**Second PowerShell window:**

```powershell
Invoke-WebRequest -Uri "http://127.0.0.1:8765/health" | Select-Object StatusCode, Content
```

**Expected:** Status code 200, JSON `status` value `ready`.

## Part 5 — 16:45–20:30: Real framework boundaries

**On screen:** Show the Umicom Framework web-server header alongside the classroom example.

**Narration:**

> The actual Umicom Framework contains reusable HTTP server interfaces and a static-file component. Our small laboratory does not replace them. Its role is to make the core ideas inspectable: native sockets, exact request lengths, bounded parsing, routing and complete responses.
>
> Just as the Notes example should reuse the existing VFS, a real Umicom application should reuse the Framework's web components. This helps avoid competing implementations of security-sensitive functionality.

**Source links:** [Umicom Framework web server](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/server.h) and [local C example](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/web/local_service.c).

## Closing — 20:30–23:00

**Narration:**

> We have now built a local web server in C23, sent an HTTP request to it, examined the complete request boundary and verified the response. The result is deliberately small, but it is a real network service running through the operating system's socket interface.
>
> Next we will learn how to serve selected files safely, choose MIME types, stream responses larger than a small fixed buffer, and test clients that disconnect during transmission.
>
> You can follow the accompanying chapters and source in the Bits2Banking repository, then help another learner reproduce the result. That is how our learning community grows: we understand, we build, we verify, and we share what works.

**Website reference:** [Bits2Banking](https://github.com/umicom-foundation/Bits2Banking), [Umicom Framework](https://github.com/umicom-foundation/umicom-framework).
