# 155. Test a local web server without exposing your files

A successful `200 OK` response is a useful start, but it does not prove that a server is safe. We must also check failures: unknown files, invalid URLs, unsupported methods, abandoned connections and content larger than the supported limit.

## 1. Start with a known directory

The `--root` argument is deliberately separate from the current working directory. You can start the server from a different folder and still know exactly which files it is allowed to read.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$Root = (Resolve-Path ".\labs\native\http-loopback-server\sample_site").Path
& ".\output\learning-build\http-loopback-server\btb-http-server.exe" `
    --port 8765 --root $Root
```

Keep this PowerShell window open. Open a second one for requests. **Do not select your repository root, home directory, or the drive root as the static folder.** Select the dedicated generated site or the supplied sample.

## 2. Check the expected responses

If `curl.exe` is installed, use the following commands from the second window:

```powershell
curl.exe -i "http://127.0.0.1:8765/"
curl.exe -I "http://127.0.0.1:8765/assets/site.css"
curl.exe -i "http://127.0.0.1:8765/health"
curl.exe -i "http://127.0.0.1:8765/does-not-exist.css"
curl.exe --path-as-is -i "http://127.0.0.1:8765/%2e%2e/private.txt"
```

The five response codes should be **200, 200, 200, 404 and 403**. The second request uses HEAD, so it should have no response body.

A `404 Not Found` means the selected file does not exist. A `403 Forbidden` means the path was refused before any file was admitted. We keep these cases separate so users and tests can understand the result.

## 3. Why we bind only to loopback

`127.0.0.1` is the IPv4 loopback address. A server listening there accepts connections directed to that address on the same machine. It does not provide an externally accessible endpoint on your local network.

The browser's `Host` header is also validated. This matters because a website opened from another origin may try to access local services. A strict host check is one protection, but it is **not an authentication system**. This educational server has no user accounts or access tokens and is not designed to be exposed to other machines.

The server sends `X-Content-Type-Options: nosniff` and a small Content Security Policy. These headers reduce some browser behaviours but do not compensate for unsafe server-side file access.

## 4. Test invalid and incomplete work

The parser refuses request bodies and pipelined requests. It accepts only a bounded HTTP/1.1 GET/HEAD request with one allowed Host value. The original `BtbHttpParse()` function keeps its conservative fixed-route target rules; the static mode explicitly adds filename punctuation and the query/path distinction.

Inside `test_static.c`, add a case for `/assets/%2e%2e/secret`. It should be refused whether the traversal is literal or percent encoded. The test also verifies that a file opened under the selected root cannot be used after its owner is closed.

When reviewing a network failure, identify which part rejected the input: parsing (`http.c`), path admission (`static_files.c`), or transfer (`tcp_server.c`). Do not bypass a boundary merely to make a request succeed.

## 5. Practical limits

This implementation is suitable for local instruction and a small preview. It does not provide TLS, HTTP/2, IPv6, Unicode URLs, upload handling, directory listings, access logs with sensitive-data controls, rate limiting, connection pools or comprehensive resource-exhaustion defences.

For actual public services, use a supported HTTP server and follow its security and deployment guidance. The current Umicom Framework has its own web-server facilities. We study those as an architectural reference in the next chapter; we do not add a competing production server to Framework.

## Your exercise

Stop the server using Ctrl+C. Start it again with `--once` and issue a single request from the second PowerShell window. It should answer that client and exit. Start it normally again, then attempt a request to a missing file and verify that the next valid request still succeeds.

Continue with [Chapter 156 — Follow the request through Umicom Framework and Kernel](156-follow-static-files-through-umicom.md).
