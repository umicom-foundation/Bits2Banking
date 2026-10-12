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

The server accepts only GET/HEAD with one Host header naming `localhost` or `127.0.0.1`. Header bytes are limited to 4 KiB and request bodies, HTTP pipelining, query parameters and URL decoding are deliberately unsupported. Connections use a bounded receive/send timeout and are closed after one response. It supports IPv4 only, processes clients serially and deliberately provides **no live reloading, file serving, dynamic routes or HTTPS**.

For production web services, use a mature supported HTTP stack or the vetted Umicom Framework web services; this educational implementation is not a substitute.
