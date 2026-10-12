# Build a small loopback HTTP web server in C23

This laboratory creates a real IPv4 TCP listening socket at **127.0.0.1 only**. It handles one connection at a time, checks a small HTTP/1.1 request subset and answers with two fixed pages. It is designed for local learning, **not** public hosting. It does not access your files, accept uploads, offer TLS or perform authentication.

## 1. Configure, build and test

In Windows PowerShell:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\http-loopback-server" -B ".\output\learning-build\http-loopback-server" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\http-loopback-server" --parallel 2
ctest --test-dir ".\output\learning-build\http-loopback-server" --output-on-failure
```

The parser checks raw byte boundaries, Host headers, unsupported methods, ambiguous bodies, traversal syntax and response generation. Its malformed-input test mutates 8,192 request samples. These tests alone do not establish security against all network attacks.

## 2. Start the server

```powershell
& ".\output\learning-build\http-loopback-server\btb-http-server.exe" --port 8765
```

Open `http://127.0.0.1:8765/`, then `http://127.0.0.1:8765/health` in a browser. The first page contains **Bits2Banking C23 web lab**. The second responds with a small JSON status.

Stop with **Ctrl+C**. If port 8765 is used by the earlier `umicom-education` web preview, stop that programme first or select another port, such as 8766.

To inspect the response without a browser, in another PowerShell window:

```powershell
Invoke-WebRequest -Uri "http://127.0.0.1:8765/health" | Select-Object StatusCode, Content
```

## 3. Trace the bytes

1. In `main.c`, see how the port is validated before any socket is created.
2. In `tcp_server.c`, locate `bind`, `listen`, `select`, `accept`, `recv` and `send`.
3. In `http.c`, find the `\r\n\r\n` sequence separating headers from the body.
4. Examine `BtbHttpParse()`: the function receives **bytes plus a length**, not an assumed NUL-terminated string.
5. Examine `BtbHttpRespond()`: the HEAD response announces the same content length without including a body.
6. Edit the **fixed** HTML text in a separate working copy and rebuild. Keep the loopback binding and byte checks in place.

## 4. Limits

This section describes the original fixed-route server. Later optional extensions are introduced below; they do not change its default behaviour.

The server accepts only GET/HEAD with one Host header naming `localhost` or `127.0.0.1`. Header bytes are limited to 4 KiB and request bodies, HTTP pipelining, query parameters and URL decoding are deliberately unsupported. Connections use a bounded receive/send timeout and are closed after one response. It supports IPv4 only, processes clients serially and deliberately provides **no live reloading, file serving, dynamic routes or HTTPS**.

For production web services, use a mature supported HTTP stack or the vetted Umicom Framework web services; this educational implementation is not a substitute.

## 5. Serve a static website (Update 25)

The original two fixed routes remain the default. To serve files instead,
provide the **absolute** path of a directory containing `index.html`. An
included sample website is in `sample_site/`. No site generation is required.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$Root = (Resolve-Path ".\labs\native\http-loopback-server\sample_site").Path
& ".\output\learning-build\http-loopback-server\btb-http-server.exe" `
    --port 8765 --root $Root
```

Open `http://127.0.0.1:8765/`, then `http://127.0.0.1:8765/assets/site.css`.
The established `/health` route also remains available.

To preview a generated MkDocs website, first build it with the existing MkDocs
installation, then select that **generated** folder rather than the repository
root. This example does not invoke Python or modify the generated website.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
if ($LASTEXITCODE -ne 0) { throw "MkDocs build failed." }
$Root = (Resolve-Path ".\site").Path
& ".\output\learning-build\http-loopback-server\btb-http-server.exe" `
    --port 8765 --root $Root
```

The static mode deliberately limits URLs to portable ASCII path characters,
one percent-decode pass, and 1023 bytes of path storage. The current lesson does
not serve Unicode filenames, URLs containing spaces or their escaped forms,
directory listings, symbolic links, `.git` files, uploads, dynamic PHP or CGI.
Encoded dot characters may be used within legitimate filenames; dot segments
such as `..`, including `%2e%2e`, are refused. The browser may use query
parameters; they are ignored when selecting a file.

Regular files are streamed in 8 KiB blocks, with a 64 MiB per-file cap and a
10-second overall client deadline. HTTP HEAD sends headers with the same
`Content-Length` as GET and no body. Short sends are retried; a disconnected
client ends that response and closes the file handle. These limits suit a local
exercise, not public hosting or adversarial multi-user workloads.

The generated website must contain its own HTML, styles and scripts. Its files
remain under the selected folder, and the native server never runs those files
as programs. Strict local Content Security Policy may also block remote fonts
or services used by a third-party theme.

## 6. Verify static-file safety

```powershell
ctest --test-dir ".\output\learning-build\http-loopback-server" `
    --output-on-failure
```

Two additional CTests cover static-target parsing and rooted-file access.
Inspect `test_static.c` for a 151,241-byte streamed file, percent-encoded path
refusals, MIME responses and, where available, symlink rejection. Windows tests
should be run on your UCRT64 machine before relying on its platform-specific
reparse-point and resolved-handle checks.

Continue with [Chapter 152](../../../content/lessons/05-engineering/152-serve-a-static-website-in-c23.md)
from the Bits2Banking website.

## 7. Register C23 routes and track response completion (Update 26)

The fixed routes and static-file modes above are unchanged by default.
Update 26 adds an **optional** `--routes` mode that composes three C23 request
handlers with the same existing listener. In this mode, GET and HEAD requests
to `/api/courses`, `/api/status` and `/workshop` use registered functions.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\output\learning-build\http-loopback-server\btb-http-server.exe" `
    --port 8765 --routes
```

To serve both API responses and files, select the bundled sample root:

```powershell
$Root = (Resolve-Path ".\labs\native\http-loopback-server\sample_site").Path
& ".\output\learning-build\http-loopback-server\btb-http-server.exe" `
    --port 8765 --root $Root --routes
```

Open `/routing-guide.html` to compare a static HTML page with the JSON returned
by `/api/courses`. Exact registered paths win; unmatched URLs go to the original
static-file owner when a root is configured. With `--routes` omitted, no API
routes have been added and existing fixed/static behaviour remains in force.

The routing service in `route_service.c` has one stable caller-owned lifetime,
up to eight exact routes, borrowed handler contexts, and failure-atomic output.
Registration ends when the service starts. Handlers do not own sockets; a
handler that tries to stop the service while it is being called receives BUSY.

The response-progress owner in `response_progress.c` tracks **wire bytes**
accepted by `send()`. Header bytes must finish before body bytes are counted.
HEAD declares the GET body length but sends no wire-body bytes. If the peer
closes early, the response is incomplete; even a successful local `send()` is
not an application-level acknowledgement from the peer.

```powershell
ctest --test-dir ".\output\learning-build\http-loopback-server" `
    --output-on-failure
```

There are now eleven CTests: the original six plus routing, service lifetime,
route rejection mutations, response completion and disconnect semantics.
These are local teaching interfaces, **not** an authenticated API, an Internet
hosting service or a concurrent request router. Public production services
should continue using established, reviewed Framework capabilities.

Continue with [Chapter 157](../../../content/lessons/05-engineering/157-route-http-requests-to-c23-handlers.md).
