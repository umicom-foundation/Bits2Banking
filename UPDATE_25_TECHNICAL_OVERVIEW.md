# Update 25 — Static file serving and native HTTP response completion

## Scope

This delivery modifies only `Umicom-Bits2Banking`. It extends the previously
delivered `labs/native/http-loopback-server` rather than adding a new web
stack or modifying Umicom Framework. The authoritative Framework and Kernel
source repositories remain unchanged and appear only as references in lessons.

Five Markdown chapters (152–156), two spoken-video scripts (episodes 52–53)
and three editable SVG diagrams introduce document roots, file/path selection,
media types, GET/HEAD semantics, bounded streaming and service boundaries.

## Existing capabilities retained

Without `--root`, the original native server continues serving its fixed `/`
HTML page and `/health` JSON response. The original HTTP parser's conservative
request-target grammar remains the default via `BtbHttpParse()`. Its full
previous source body is retained for review in a disabled section while the
shared parser accepts a separate `BtbHttpParseForFiles()` mode. The first four
CTest cases and all older lesson links remain present.

With `--root ABSOLUTE_DIRECTORY`, the original listener receives a checked
static document root. The same native HTTP parser and socket send helper are
reused; file opening and byte streaming are separate, narrowly owned services.
No source has been deleted from the baseline update, and all earlier MkDocs
navigation entries remain in their original order.

## Boundary contracts

- **Network:** binds IPv4 `127.0.0.1`, one client at a time, GET/HEAD only,
  one response then close. Headers at most 4096 bytes, no pipelining or uploads.
- **Path:** portable ASCII URL paths, up to 1023 bytes, decoded at most once.
  Dot segments, hidden metadata, encoded separators, Windows device names and
  invalid names are rejected. Queries are not used in file lookup.
- **Storage:** root must be an explicit absolute directory. POSIX uses
  `openat()` and `O_NOFOLLOW`. Windows uses `CreateFileW()` with reparse-point
  and final-handle path checks. Only ordinary files may be served.
- **Memory:** a fixed 8192-byte stream buffer; an admitted file may contain up
  to 64 MiB. The transport retries short sends and checks byte counts; partial
  completion is reported as an incomplete response.
- **Lifetime:** the root directory is opened before serving and closed after
  the listener exits. Each file stays open only while its response is served.
  A three-second socket I/O timeout and ten-second total client deadline apply.
- **Output:** Content-Type is selected from an explicit suffix table; unknown
  types remain `application/octet-stream`. Successful HEAD responses advertise
  the file's full Content-Length without sending a body. Error responses use
  distinct 403, 404, 413 and 500 codes, with MIME and `nosniff` headers.

## Known limits

This is a classroom server and not a public Internet server. It does not have
TLS, HTTP/2, range requests, compression, cache negotiation, multi-client
concurrency, authenticated access, directory listing, POST, PHP execution,
Unicode URL support or complete handling of concurrently mutated website
folders. In particular, Windows path confinement uses resolved-handle checks;
protecting a directory actively modified by an untrusted local actor would
require additional Windows directory-handle-relative opens and race tests.

The optional example HTML and CSS are unavoidable website data, not another
application implementation language. Native server and test logic use C23.

## Validation boundary

GCC C23, Clang C23 with AddressSanitizer/UndefinedBehaviorSanitizer and Release
builds each passed all six CTests in the isolated Linux environment. Live
loopback GET/HEAD, 404/403, `/health`, a 151,241-byte streamed file and a
mismatched Host-port refusal were checked there. MkDocs YAML parsed, seven
new navigation targets were found, all 235 earlier entries remained, and new
local lesson/video links resolved. SVG diagrams were validated.

**Still required:** UCRT64 Windows build/tests, live Windows path/reparse-point
validation, strict MkDocs build with the complete source checkout, and any
future production hosting review. Isolated checks do not claim these passed.

## Next milestone

Update 26 can address routing tables, HTTP status/problem responses,
deterministic network integration testing and the controlled lifecycle of a
C23 request handler. Keep the existing networking/file code authoritative
within Bits2Banking rather than inventing a competing implementation.
