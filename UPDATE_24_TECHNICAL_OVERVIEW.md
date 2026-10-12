# Major Update 24 — Process-owned file services and networking

This update connects two practical topics: how a running process reaches a file through checked copies, and how a native C23 application receives a local HTTP request over TCP.

## Process-owned file service

The previous virtual filesystem course established a single owner of mounts, open descriptions, descriptor tokens and provider operations. The new `process-file-services` library consumes those exact source files via CMake's `add_subdirectory`; it does not duplicate the VFS.

The new adapter owns a stable fictional process identity, 512 bytes of training memory and a bounded array of accepted descriptors. OPEN accepts length-delimited pathname bytes; READ and WRITE copy up to 64 bytes through local staging storage. The result is published only on success, and a failed close leaves a tracked handle available for retry. A terminated process owner refuses further use.

The memory range is deliberately represented by one fixed array, not by a true virtual-memory mapping. No real system call is executed. The educational project illustrates trust-boundary mechanics while the authoritative Umicom Kernel source is maintained separately.

## Networking and HTTP

The `http-loopback-server` exercise uses POSIX sockets or Windows Winsock2 to listen at IPv4 loopback only. The C23 parser receives counted bytes and supports a limited HTTP/1.1 GET/HEAD grammar. Its fixed routes are `/` and `/health`, with 404 for other safe pathnames and 405 for unsupported methods.

Limits and refusals are explicit: one Host header naming localhost/127.0.0.1, a 4 KiB header limit, a short socket timeout, no request bodies, no percent-decoding, no connection pipelining and one response per connection. `HEAD` includes GET's representation length without transmitting the body. This is an educational local service, **not** a production HTTP server.

## Source references

- [Umicom Kernel VFS contract](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/vfs.h)
- [Umicom Kernel process file services](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/PROCESS_FILE_SERVICES.md)
- [Umicom Kernel user-memory checks](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_memory.c)
- [Umicom Framework web server](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/server.h)
- [Umicom Framework local service example](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/web/local_service.c)

All links refer to the existing projects. This package has **no changes** for Framework, Applications, Kernel or OS.

## Acceptance

The new VFS composition lab registers three CTest cases. The HTTP lab registers four CTest cases and includes 8,192 deterministic altered input samples. Each can be configured and tested as a standalone CMake project. The website content preserves the prior navigation entries and adds chapters 147–151 plus episodes 50–51.

For a meaningful networking acceptance run, compile and start the C23 server on an unused loopback port, send GET and HEAD requests, verify exact HTTP status and body, and stop it. CTest parser tests are necessary but do not replace this loopback runtime check.

## Next course milestone

**Update 25 — Serving local files securely in C23.** Build on the existing parser and listener with a narrowly scoped read-only static-file resolver, MIME selection, bounded file streaming, range/size policies, symlink and path-traversal defences, client-disconnect handling, and visible error responses. Keep it a learning lab rather than introducing a second production Framework web server.
