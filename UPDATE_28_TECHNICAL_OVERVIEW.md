# Bits2Banking — Major Update 28: Technical Overview

**Scope:** `Umicom-Bits2Banking` only.  
**Observed upstream reference:** `umicom-foundation/Bits2Banking`, `main` at `6a30bcfea3240f64e8605770955d5f710f2c6036` (Update 27).  
**Ownership:** Sammy Hegab, Umicom Foundation.  
**Implementation:** C23, small native API and operating-system socket adapters; MkDocs/Markdown/SVG and optional Python test automation retain their established roles.

## 1. Architecture and source placement

The native learning server contains two selectable backends. The pre-existing `tcp_server.c` remains the default, with its original public entry points, parser, route owner, cache validation and static-file semantics unchanged. `nonblocking_server.c` is an optional single-threaded reactor selected with `--nonblocking`. It maintains eight real descriptor slots, not eight worker threads. Existing common code remains the only implementation of request parsing, safe file selection, route dispatch, weak ETag comparison and response-progress accounting.

`nonblocking_policy.c` contains a no-socket state-and-clock contract. It is included in the existing `btb_http` static library because it can be verified with synthetic timestamps and reused by later connection/event-loop lessons. Each connection has stable storage, a socket descriptor, one optional file owner, 4 KiB input, 8 KiB output, response progress, a three-second idle budget and a ten-second total budget.

The reactor uses readiness-based `recv`/`send`. Both the listener and accepted sockets are nonblocking. Temporary would-block is not a disconnection. Short sends retain their unsent suffix. Static files continue streaming without allocating their full 64 MiB file-size allowance. Routes run sequentially under the already-owned route service; no borrowed route context is accessed after its lifetime ends.

## 2. Acceptance and known limits

This is not a production web stack. The listener is always IPv4 loopback-only and supports one closed GET or HEAD response per connection, no request bodies, no keep-alive, no TLS, no public binding, no authentication, no HTTP/2 and no embedded scripting. On POSIX, `select()` requires descriptors smaller than `FD_SETSIZE`; on Windows `FD_SETSIZE` also constrains the set. A full slot array temporarily stops listener readiness instead of allocating more sockets, but the OS may still queue pending connections.

Graceful shutdown begins after SIGINT/SIGTERM or the optional accepted-client limit. The listener is closed; accepted clients can complete or expire during an eleven-second maximum drain. Signals only set a `sig_atomic_t` flag; the reactor owns all descriptor and file closure. The outer time budget is longer than the ten-second connection maximum. Windows console signal delivery is a manual host gate.

## 3. Educational delivery

The continued numbered curriculum adds five chapters (167–171), two narrated video scripts (Episodes 58–59) and three editable SVG diagrams. Every chapter links to the actual C23 code and uses an Umicom-relevant practical task rather than unrelated toy output. The lesson group covers motivation, nonblocking reactor implementation, deterministic deadlines and shutdown, verification and Framework/Kernel ownership comparisons.

## 4. Regression policy

No feature, comment or archived `#if 0` implementation has been deleted from `main.c`. `tcp_server.c`, HTTP parser/response, route service, static-files, cache-validator and admission-model sources are not part of the patch. The existing 16 CTests remain registered. Two new C23 tests cover pure policy and 30,000 deterministic state transitions. One optional Python standard-library integration test exercises actual C23 loopback sockets and POSIX signals; no Python HTTP server is added. The expected registered count is **18 without** optional Python or **19 with** it.

The merge-time PowerShell script updates only the existing publishing navigation and appends the new roadmap/README notes. It refuses a missing or duplicated known Update 27 anchor, preserves existing navigation and can be rerun idempotently. Every code file delivered as a replacement is complete, not a partial diff. The publishing file `mkdocs.yml` is intentionally updated through a checked append-only script to avoid overwriting its 256 existing navigation entries.

## 5. Release qualification

A complete result requires: GCC C23 compilation; all CTests; socket-level GET/HEAD/304/404/route and overlapping-request checks when optional Python is available; Windows UCRT64 compile and interactive Ctrl+C; valid SVG; a strict MkDocs website build; and a human review of `git diff`. Linux policy tests alone are not evidence of Windows integration or site publication.

**Next Update 29:** Bounded asynchronous work handoff, deterministic worker ownership and completion contracts. This should extend the single-owner theory before introducing real threads. Production and reusable service code remains owned by Umicom Framework, outside this educational repository.
