# 162. Why a browser does not need to download the same file twice

A learner opens the Bits2Banking website in a browser. The browser requests `index.html`, then a stylesheet and several diagrams. On a second visit, many of those files may be unchanged. Repeatedly transferring identical bytes takes time and network capacity.

**HTTP caching** allows a client to retain a representation and ask whether it is still suitable. This chapter explains that exchange before introducing the C23 implementation.

## 1. Start with an ordinary request

Suppose a local web server has an `index.html` containing the course homepage. A browser sends:

```http
GET /index.html HTTP/1.1
Host: 127.0.0.1:8765
```

The server reads the file and responds with a status code, headers and content:

```http
HTTP/1.1 200 OK
Content-Type: text/html; charset=utf-8
Content-Length: 639
ETag: W/"000000000000027f-0123456789abcdef"
Cache-Control: private, no-cache
```

The actual file length and `ETag` depend on your files. The header `Content-Length` counts the **body bytes**; it does not include the response headers.

An **entity tag**, written `ETag`, identifies a version of a representation. The client can retain it alongside the downloaded content. An `ETag` is a validator, not a filename, an access token or a cryptographic signature.

![A browser asks whether a retained file is current](../../assets/diagrams/conditional-http-requests.svg)

## 2. Ask if the file changed

The browser can make another request and include the validator it received:

```http
GET /index.html HTTP/1.1
Host: 127.0.0.1:8765
If-None-Match: W/"000000000000027f-0123456789abcdef"
```

If the selected representation still matches, the server can return:

```http
HTTP/1.1 304 Not Modified
ETag: W/"000000000000027f-0123456789abcdef"
Cache-Control: private, no-cache
```

The status **304 Not Modified has no response body**. The browser uses its retained content. The server has still handled a request, but it has not resent the whole HTML file.

If the validator does not match, the server returns **200 OK** and the current file body. This is revalidation, not an unconditional promise that everything in a browser cache stays fresh.

## 3. Why this laboratory uses a weak validator

Our existing C23 static-file laboratory already opens files using platform-specific handles. Update 27 captures two properties of that opened file: its byte length and its modification timestamp. It combines those properties into a tag resembling:

```text
W/"000000000000027f-0123456789abcdef"
```

The prefix `W/` means **weak validator**. The server does not claim that a metadata match proves the file bytes are identical. Two edits with the same length and modification timestamp might produce the same tag, particularly on a filesystem with coarse timestamp precision. Weak tags are useful for illustrating revalidation, but they are not cryptographic content digests or reliable audit evidence.

The server includes `Cache-Control: private, no-cache`. This does **not** mean “never retain this file”; it means that a cache must revalidate it before reuse. `private` keeps a shared intermediary cache from using it as a public reusable response. This is a deliberately conservative policy for a local educational server.

For genuinely byte-exact validators, a future implementation could compute a strong content digest from a stable snapshot and establish that it matches the actual bytes served. That would require careful treatment of content changes during streaming, not simply a different `printf` format.

## 4. GET, HEAD and 304 are different

| Request or response | What is transferred? | What can the client learn? |
|---|---|---|
| GET, 200 OK | Headers and file body | Current content and its validator |
| HEAD, 200 OK | Headers only | File length and validator without downloading the body |
| GET with matching `If-None-Match`, 304 | Headers only | Retained representation can be reused |
| GET with a different tag, 200 | Headers and current file body | The retained representation needs replacement |

`HEAD` is a **request method**. `304` is a **response status**. They are not substitutes. Even for HEAD, a successful `200` response announces the byte length that a corresponding GET would transfer.

## 5. Run the demonstration

From PowerShell, configure and build the existing laboratory:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\http-loopback-server" `
  -B ".\output\learning-build\http-loopback-server" `
  -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\http-loopback-server" --parallel 2
ctest --test-dir ".\output\learning-build\http-loopback-server" --output-on-failure
```

Start the server using the absolute sample-site path:

```powershell
$Root = (Resolve-Path ".\labs\native\http-loopback-server\sample_site").Path
& ".\output\learning-build\http-loopback-server\btb-http-server.exe" `
  --port 8765 --root $Root
```

In a **second** PowerShell window, inspect the response headers using `curl.exe`:

```powershell
curl.exe -i "http://127.0.0.1:8765/index.html"
```

Read the `ETag` printed by the server. Substitute that exact value for `TAG_FROM_RESPONSE` in this request:

```powershell
curl.exe -i -H 'If-None-Match: TAG_FROM_RESPONSE' `
  "http://127.0.0.1:8765/index.html"
```

A matching validator produces `304 Not Modified`. An unmatched validator produces `200 OK` and file contents. Stop the server with **Ctrl+C**.

## 6. Questions and an experiment

1. Why does a `304` response have no body?
2. What is the difference between a weak validator and a cryptographic digest?
3. Why does `Cache-Control: no-cache` still permit storing a response?
4. What does HEAD tell the client that GET would also reveal?

**Your experiment:** Send `If-None-Match: "some-other-version"` and observe the response. Then change the length of the sample HTML file, restart the server and compare the new tag. Do not modify the real repository's generated website for this exercise; use the laboratory sample or a separate copy.

Next: [163. Implement conditional GET in C23](163-build-conditional-get-in-c23.md).
