<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/40-encode-a-fastcgi-request-with-bounded-bytes.md

PURPOSE:
Build a small FastCGI responder request using the Framework wire encoder.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Encode a FastCGI request with bounded bytes

[Course contents](index.md) · [Previous lesson](39-measure-memory-without-confusing-ownership.md) · [Next lesson](41-read-a-fastcgi-reply-before-forwarding.md)

A web server can give approved application work to another process. FastCGI defines the byte records that travel between the server and that process. A record is a short header followed by a stated number of content bytes and optional padding. Worker startup, endpoint selection and transport deadlines belong to the server configuration. [Apache mod_proxy_fcgi](https://httpd.apache.org/docs/2.4/mod/mod_proxy_fcgi.html)

## Follow one request

1. Reserve a nonzero request ID and emit `BEGIN_REQUEST` with the responder role. The Framework example uses ID `0x1234`. Its header begins `01 01 12 34 00 08 00 00`. The bytes store the version, record type, request ID, content length, padding length and a reserved byte. Read multi-byte numbers high byte first.
2. Use `UmiWebFastCgiParameter` to encode each approved CGI name and value. A count below 128 takes one byte. A longer count takes four bytes with the high bit set. Use `UmiWebFastCgiInput` to wrap completed pairs in a `PARAMS` record. The fixture encodes a single pair at a time to make its lengths easy to check.
3. Emit an empty `PARAMS` record. Then send request-body bytes in `STDIN` records and end that stream with an empty `STDIN` record. A binary body can contain a zero byte. Always use its byte count.
4. Keep route-to-worker configuration under the server owner's control. Only forward variables the route explicitly accepts. Keep an executable or script path from the reviewed route configuration.

## Try the wire checks

Open a terminal at the Framework source root. Use the same build directory for configure, build and test.

```powershell
$wireBuild = Join-Path $PWD 'build/fastcgi-wire'
cmake -S tests/web/fastcgi -B $wireBuild -G Ninja
cmake --build $wireBuild
ctest --test-dir $wireBuild --no-tests=error -R '^framework[.]web[.]fastcgi[.](begin|padded-input|long-parameter|short-output)$'
```

Expect four passing tests. If CMake cannot identify a C23 compiler, open the configured toolchain shell and repeat the commands. If a short-buffer test fails, check the header, content and padding lengths before changing the requested capacity.

In the padded input fixture the header consumes eight bytes, its content consumes three and the record ends with five zero padding bytes. Add these numbers before looking at the test. The expected record is 16 bytes. This lab exercises the production codec with local fixtures. A separately configured integration test should qualify a real FastCGI process for the chosen application runtime.
