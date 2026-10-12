# Update 26 — Native HTTP routing and response-completion architecture

## Repository boundary

Only `Umicom-Bits2Banking` is changed. Existing Umicom Framework, Applications, Kernel and OS repositories remain read-only references. The change is an extension of the *existing* `labs/native/http-loopback-server` rather than another TCP stack.

## Reused components

- `http.c` keeps the strict GET/HEAD, HTTP/1.1 and loopback Host parser and the original two-route behaviour.
- `static_files.c` retains rooted, read-only file serving, MIME selection, path checks and the 8 KiB streaming buffer from Update 25.
- `tcp_server.c` keeps the one-threaded socket owner and 10-second per-client elapsed limit. The existing listener and cleanup path serve all modes.
- `main.c` retains the existing `--port`, `--once` and `--root` options. `--routes` is opt-in and may be combined with the static root.

## New components

`route_service.c` and `route_service.h` define a bounded registry with at most eight exact paths. Registration occurs in CONFIGURING state; Start publishes readiness and rejects later registration. A handler receives a borrowed request pointer and one privately owned response buffer with a maximum of 2,048 body bytes. It returns a typed status; it does not own a socket, a filesystem or a user identity. Stop is refused during handler execution. The implementation is single-threaded, non-reentrant and not a concurrent router.

`learning_routes.c` supplies sample `/api/courses` and `/api/status` JSON handlers and a small `/workshop` HTML handler. These are deterministic educational responses; there is no input-driven command execution or database access.

`response_progress.c` and `response_progress.h` count header and body bytes accepted by the native socket send calls. They distinguish HEAD's declared representation length from its zero-byte wire body, refuse body accounting before header completion, and mark incomplete transfers as failed after a disconnect or deadline. **Complete** means bytes accepted by the local networking API, not receipt by the browser or durable application acknowledgement.

`test_routes.c` and `test_progress.c` introduce five focused CTest cases. The original test source and CTests are not altered or removed. The package includes a static `routing-guide.html` page that demonstrates route/file composition without JavaScript.

## Path and response rules

The registered route paths use portable literal ASCII names. They contain no query, dot or percent-encoded segments. Parsed static website paths may include dot filenames; an unmatched path such as `/assets/site.css` returns `BTB_ROUTE_NOT_FOUND` from the API router so the existing filesystem fallback remains authoritative. A route handler can supply only explicitly supported HTTP status codes and one of three fixed media types. Its body is copied to stable storage before the response is encoded. Route-header serialization uses bounded output and copies no bytes to the caller on failure.

The server retains its IPv4 loopback-only bind, one request per connection, request-body refusal, 4 KiB request-header cap, no filesystem listings and no symlink traversal. It is not suitable for public Internet hosting or multi-user production workloads. HTTP is transported without TLS; all endpoints are intended for local demonstrations.

## Source preservation

No files are deleted. Historical books and the original *Islam: Blueprint for Life* navigation are untouched. The existing fixed and static HTTP paths remain usable with their old command forms. The earlier active tail of Update 25's `main.c` is retained inside a disabled review block because the new composition now performs its cleanup with optional route ownership. The prior HTTP parser, static loader and test implementations remain unchanged.

## Learning course

Chapters 157–161 teach routing and callback contracts, HTTP header framing, byte-accurate GET/HEAD responses, partial-send diagnostics, service lifetime management, and how to locate the equivalent concerns in real Umicom Framework web services and Umicom Kernel VFS. Episodes 54–55 present runnable narrated walkthroughs. The diagrams are editable SVG sources and use the existing website's typography and colour scheme.

## Validation

The selected Update 24 and Update 25 HTTP source was reconstructed from the previously delivered ZIPs. The original six tests passed before modification. The extended project has **eleven CTests**; all passed under Linux GCC and under Clang with AddressSanitizer and UndefinedBehaviorSanitizer. Twelve native socket smoke cases covered GET/HEAD, dynamic routes, static fallback, absent routes, unknown paths and preservation of the original health route. A static-file route-miss bug was discovered during live testing, corrected and covered by a new regression assertion. MkDocs YAML parsing confirms that all 242 prior nav targets remain in the exact original order, with seven new distinct targets appended (249 total). Three diagrams render as SVG.

A production release or a Windows UCRT64 qualification is **not** claimed. The full local MkDocs website build and actual Windows native socket behaviour still need acceptance testing on the contributor's checkout.
