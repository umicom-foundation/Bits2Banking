# 170. Test a nonblocking web server rather than trusting a demo

**Practical objective:** Produce build and runtime evidence for the preserved blocking server and the optional C23 reactor.  
**Files:** `test_nonblocking.c`, `test_nonblocking_integration.py`, `CMakeLists.txt`.  
**Prerequisite:** [Chapter 169](169-monotonic-timeouts-and-graceful-shutdown.md).

## 1. Reproduce the build on Windows

Open an ordinary **PowerShell** window. The native HTTP learning laboratory is a small CMake project within the Bits2Banking repository. Configure it independently of Umicom Framework, Studio IDE, Kernel and OS.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --version
gcc --version
ninja --version

cmake -S ".\labs\native\http-loopback-server" `
    -B ".\output\learning-build\http-loopback-server" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON

cmake --build ".\output\learning-build\http-loopback-server" --parallel 2
ctest --test-dir ".\output\learning-build\http-loopback-server" `
    --output-on-failure
```

The previous version registered **16** CTests. Update 28 adds two deterministic C23 policy tests and, when a Python 3 interpreter is discoverable by CMake, one socket-level integration test: **18 or 19** registered cases. An absent optional Python interpreter is not represented as a successful integration test. All original sixteen tests must remain registered and passing before checking in the change.

## 2. Inspect both server modes

The old command deliberately stays available:

```powershell
& ".\output\learning-build\http-loopback-server\btb-http-server.exe" `
    --port 8765
```

Stop it with Ctrl+C. Then enable the new backend and static root:

```powershell
$Root = (Resolve-Path ".\labs\native\http-loopback-server\sample_site").Path
& ".\output\learning-build\http-loopback-server\btb-http-server.exe" `
    --port 8765 --root $Root --routes --nonblocking
```

In a second terminal, request the fixed health endpoint, dynamic educational courses and an ordinary website file:

```powershell
curl.exe -i http://127.0.0.1:8765/health
curl.exe -i http://127.0.0.1:8765/api/courses
curl.exe -i http://127.0.0.1:8765/index.html
curl.exe -I http://127.0.0.1:8765/index.html
```

Record the HTTP status line, `Content-Length`, optional weak `ETag` and whether any body bytes are present. `HEAD` must not send a body; a matching conditional GET must return `304 Not Modified` without a body. Read the exact contents of the HTTP parser test before using a request outside the deliberately supported HTTP subset.

## 3. Prove that a slow reader is isolated

A functional test sends only the beginning of a valid HTTP/1.1 header from one socket. It then sends a complete request from another socket. A nonblocking reactor must not let that first socket prevent the second from reaching a normal response. This specifically distinguishes our new backend from the earlier serial `recv()` loop.

The optional `test_nonblocking_integration.py` implements this test using only Python's standard `socket` and `subprocess` modules. The actual listening service, parser, file access and routing still run in **C23**, not in Python. The test also checks static GET, HEAD, cache revalidation, registered route selection, a missing file and a real idle deadline.

To run only these tests:

```powershell
ctest --test-dir ".\output\learning-build\http-loopback-server" `
    -R "nonblocking" --output-on-failure
```

An integration pass means the observed test cases succeeded on that host. It does not prove the absence of memory-corruption vulnerabilities, all request interleavings or production readiness.

## 4. Test refusal and cleanup paths

Use the following review table while reading `nonblocking_server.c`:

| Condition | Required behaviour | Owner to inspect |
|---|---|---|
| Nine clients wish to connect | At most eight user-space slots exist; listener admission pauses | Event loop |
| Header never ends | Idle or total deadline releases the socket | Connection lifetime |
| Incoming header exceeds capacity | A bounded refusal or failed request; no buffer overflow | HTTP parser and input array |
| `send()` accepts a partial chunk | Retain unsent suffix and update only accepted-byte counts | Output offset and progress |
| Browser disconnects | Do not report completed delivery | Response progress and slot release |
| Static file missing | Return 404; do not dereference an absent file owner | Static-file boundary |
| Matching weak `If-None-Match` | Return 304 with zero response body | Cache validator |
| Ctrl+C with active clients | Stop new admission, finish or expire admitted clients, release all owners | Signal and reactor loop |

**Security distinction:** This laboratory accepts only local IPv4 loopback connections and has no authentication or TLS. Do not expose it on a public interface or reuse the server as a payment, trading or banking endpoint. The appropriate production implementation belongs in reviewed Umicom Framework web services.

## 5. Qualification boundaries and troubleshooting

If `cmake` is not found, ensure the MSYS2 UCRT64 bin folder is on `$env:Path`. If port 8765 is already in use, stop the earlier preview or choose another permitted high port. If `ctest` says an executable cannot be found, verify that configuration and build completed before testing. If the Python socket test is absent, run `python --version`, reconfigure with a discoverable Python 3 interpreter, and inspect `ctest -N` to confirm the test registered.

A test failure after `--nonblocking` is selected is not evidence that the old blocking server has changed. Repeat the same URL in both modes and capture the status, stderr, timing and selected option. Separate HTTP parser refusal from connection timeout: malformed complete input should yield an HTTP refusal, while a permanently incomplete idle header is closed after its budget expires.

On Windows, verify the UCRT64 executable, the console Ctrl+C behaviour and the complete MkDocs site build on the actual workstation. Linux GCC/Clang tests do not substitute for those checks. Do not claim the new feature is cross-platform qualified until its platform-specific tests have run.

## 6. Capture useful evidence

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
ctest --test-dir ".\output\learning-build\http-loopback-server" -N
ctest --test-dir ".\output\learning-build\http-loopback-server" `
    --output-on-failure | Tee-Object ".\output\learning-build\update28-ctest.txt"
```

Do not commit transient output or unreviewed test logs. Record the exact CMake compiler, operating-system version, number of discovered CTests and any failure in a release note. Continue with [Chapter 171](171-connect-reactors-to-umicom-service-ownership.md) to compare this educational code with the real Framework and Kernel boundaries.
