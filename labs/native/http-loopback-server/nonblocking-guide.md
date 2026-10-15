# Optional C23 nonblocking HTTP reactor

This guide extends the preserved `README.md` for `http-loopback-server`. The old `tcp_server.c` file and the previously exposed `BtbHttpServeLoopback*` entry points are **unchanged**. All accepted connections still belong to the one C23 process, and the listener binds **only** to `127.0.0.1`.

## Build

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\http-loopback-server" `
    -B ".\output\learning-build\http-loopback-server" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\http-loopback-server" --parallel 2
ctest --test-dir ".\output\learning-build\http-loopback-server" --output-on-failure
```

## Run

```powershell
$Root = (Resolve-Path ".\labs\native\http-loopback-server\sample_site").Path
& ".\output\learning-build\http-loopback-server\btb-http-server.exe" `
    --port 8765 --root $Root --routes --nonblocking
```

`--once` may also be used. It stops accepting after one client has been admitted, then allows that accepted request to finish or expire. The default mode without `--nonblocking` retains the original serial listener.

## What the new backend guarantees locally

| Concern | Policy |
|---|---|
| Admission | At most eight accepted connections; backlog is OS-owned |
| Networking | Nonblocking accepted sockets and one `select()` readiness loop |
| Request memory | Four-kilobyte request header limit per accepted connection |
| Response memory | Eight-kilobyte fixed output staging per accepted connection |
| Static files | Existing checked root and 8 KiB streaming chunks |
| Route precedence | Existing exact registered C23 routes, then fixed/static fallback |
| HTTP semantics | Existing GET/HEAD parser, weak ETag revalidation and 304 body rules |
| Timeout | 3 seconds without real progress or 10 seconds total |
| Shutdown | Signal flag, stop admission, drain/expire clients, 11-second grace |
| Threads | Single-threaded; no parallel request workers |

The existing four-record admission model remains a **separate** teaching demonstration, not an eight-connection work scheduler. This is a loopback-only lab without TLS, authentication, production HTTP keep-alive, bodies, pipelining or public binding. Do not deploy it as an Umicom financial application service.

## Verify

Run `ctest -N` to determine whether optional Python-based integration testing was discovered. The core C23 suite has eighteen registered cases; with a discoverable Python 3 interpreter, the socket-level integration check becomes a nineteenth. Windows UCRT64 compilation and manual Ctrl+C shutdown qualification must be performed on Windows; a Linux test does not prove Windows behaviour.

The integration script starts the compiled C23 server, opens loopback sockets and checks overlapping requests, fixed and registered routes, static GET/HEAD, cache revalidation, a missing file, a real idle timeout and POSIX graceful shutdown. It contains **no** Python HTTP application implementation.

To inspect the source, begin with [Lesson 167](../../../content/lessons/05-engineering/167-why-nonblocking-io-matters.md). Use this guide for the nonblocking exercise and the [laboratory README](README.md) for the other server modes. Check the actual test results on each supported host before reporting success.
