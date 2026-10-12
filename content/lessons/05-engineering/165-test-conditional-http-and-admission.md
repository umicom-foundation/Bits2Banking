# 165. Verify HTTP cache behaviour and queue invariants

A server that prints “ready” has only proved that it reached a particular line of code. It has not proved that its responses are correctly framed, that a browser can retrieve a file, or that invalid requests are refused safely.

This chapter develops a repeatable validation workflow for the C23 server and admission model.

## 1. Build one version of the application

Use the existing CMake project rather than compiling copied versions of the same source:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\http-loopback-server" `
  -B ".\output\learning-build\http-loopback-server" `
  -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON

cmake --build ".\output\learning-build\http-loopback-server" --parallel 2
```

A successful build produces `btb-http-server.exe`, the test executables and `btb-admission-demo.exe`. The executable and its tests link to the same `btb_http` library. This prevents examples from silently drifting into separate implementations.

## 2. Run the complete regression suite

```powershell
ctest --test-dir ".\output\learning-build\http-loopback-server" `
  --output-on-failure
```

The suite now registers **16 tests**: the 11 established HTTP, route and response tests plus five checks for conditional cache handling and the bounded admission model.

Look for the tests named `cache.validators`, `cache.files`, `admission.queue`, `admission.mutations` and `admission.demo`. Do not report a pass just because the build succeeded: compile and runtime verification are different steps.

## 3. Make a real local request

Start the native server in one PowerShell window:

```powershell
$Root = (Resolve-Path ".\labs\native\http-loopback-server\sample_site").Path
& ".\output\learning-build\http-loopback-server\btb-http-server.exe" `
  --port 8765 --root $Root --routes
```

Use **another** PowerShell window for the client commands. `curl.exe` is used only to inspect HTTP replies; the server itself is implemented in C23.

```powershell
curl.exe -i http://127.0.0.1:8765/index.html
curl.exe -I http://127.0.0.1:8765/index.html
curl.exe -i http://127.0.0.1:8765/api/courses
```

A successful static GET returns 200 and file bytes. HEAD returns headers but no body. The previously implemented C23 JSON route should remain available when `--routes` is selected.

## 4. Test the conditional request

Copy the `ETag` from the first GET response, including its `W/` prefix and quotes:

```powershell
curl.exe -i -H 'If-None-Match: W/"PASTE_THE_ACTUAL_TAG_HERE"' `
  http://127.0.0.1:8765/index.html
```

Replace the placeholder with the exact tag received. A matching request should return `304 Not Modified` and **no content body**. A different tag should return `200 OK` and file contents.

Observe `Cache-Control: private, no-cache`. It tells a cache to revalidate before reusing the stored representation; it does not grant permission to access another file.

## 5. Test refused input deliberately

These requests must not be confused with a cache miss:

```powershell
curl.exe -i -H 'If-None-Match: W/"unfinished' `
  http://127.0.0.1:8765/index.html

curl.exe -i http://127.0.0.1:8765/missing.html
```

The first is a malformed conditional header and should be rejected with a bad-request response. The second is a correctly formed request for a missing file and should return `404 Not Found`.

The test suite also checks duplicate conditional headers, trailing commas, path traversal, oversized requests, unexpected methods, service shutdown behaviour and bounded cancellation.

## 6. Understand the test layers

| Layer | What it proves | What it does not prove |
|---|---|---|
| C23 parser unit test | Known byte buffers are accepted or refused according to the parser contract | A TCP socket can receive a complete request |
| Static-file unit test | An admitted root can open and describe selected sample files | A full browser successfully renders every site asset |
| Live loopback HTTP check | A client can connect and observe actual GET/HEAD/304 replies | The service is safe for the public Internet |
| Admission mutation test | Queue invariants survive 20,000 serial test operations | Multi-threaded, lock-free or production concurrency |
| Clang ASan/UBSan | Detects classes of memory errors during exercised runs | Proves absence of all security vulnerabilities |

Use all appropriate layers. A failed assertion should lead to a small reproducible case, not removal of the test.

## 7. Protect the existing work

After testing, inspect Git changes before committing:

```powershell
git status
git diff --check
git diff --stat
```

The generated `output/learning-build` directory belongs to the build, not the source. The C23 source, Markdown lessons, SVG diagrams and MkDocs navigation belong to the repository.

Next: [166. Relate the lab to Umicom architecture](166-http-service-ownership-in-umicom.md).
