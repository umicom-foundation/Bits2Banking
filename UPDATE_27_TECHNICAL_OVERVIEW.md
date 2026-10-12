# Update 27 — Conditional HTTP requests and bounded admission in C23

## Scope

This update extends only `Umicom-Bits2Banking`, building on the existing `labs/native/http-loopback-server` library from Updates 24–26. It does not introduce new Framework APIs, Kernel services, OS components, additional socket listeners, replacement parsers or Python application code.

## Conditional HTTP caching

`http.h` and `http.c` extend the parsed request with a bounded, optional `If-None-Match` field for the static-files grammar. The original fixed-route grammar is preserved. `cache_validator.c` implements bounded ASCII entity-tag parsing, weak comparison, wildcard admission and 200/304 header construction. Invalid syntax is distinct from a valid cache miss.

`static_files.c` observes the size and modification timestamp of the already opened, authorised file handle. The response tag is therefore weak, formatted as `W/"<16-hex-size>-<16-hex-timestamp>"`. No content digest is claimed. The server returns `Cache-Control: private, no-cache`, requiring revalidation before reuse; the older fixed-route and error responses retain their established no-store policy. `tcp_server.c` returns 304 only after an admitted file has been opened and matched, without a response body. HEAD also remains bodyless.

Metadata validators are not suitable for exact-byte attestation, tamper evidence or reliable change detection under arbitrary timestamp-preserving edits. This educational server is still limited to a loopback listener, one handled client at a time, a 64 MiB file size ceiling, no TLS, no Range responses, no uploads and no global response cache.

## Admission and backpressure

`admission_queue.c` adds a **serial simulation** with four fixed slots and a configurable number of active tickets. A new request cannot silently overflow the queue. Tickets increase monotonically and are not reused. FIFO selection chooses the earliest queued record; active operations may finish in a different order. An active cancellation records intent and waits for explicit completion before release. A queued cancellation removes its record immediately.

The admission simulation is not integrated into the socket accept loop, not thread-safe and not a claim that the web server now processes concurrent clients. It teaches policy and ownership before a later, separately tested worker implementation.

## Verification

The eleven previous tests remain registered. Five new CTests exercise cache grammar, file metadata tags, bounded admission, 20,000 deterministic admission transitions and the standalone demonstration. Additional live HTTP smoke checks validate GET with 200, a matching validator with 304, HEAD with no body, unchanged routing and invalid header rejection.

The lessons 162–166, videos 56–57 and three editable SVG diagrams connect those mechanisms to actual Umicom Framework web-service contracts and Umicom Kernel I/O and file-service boundaries. The other repositories are references only.

## Next milestone

Update 28 will examine nonblocking socket I/O, backpressure at the network boundary, per-client resource budgets and graceful shutdown. Real concurrency must be designed around proper shared-state synchronization; the current `BtbRouteService` and `BtbStaticRoot` do not claim unrestricted concurrent access.
