# Episode 56 — Why the Browser Can Reuse a Page

**Duration:** Approximately 13–17 minutes. **Source:** [Lesson 162](../../lessons/05-engineering/162-http-caching-and-revalidation.md) and [Lesson 163](../../lessons/05-engineering/163-build-conditional-get-in-c23.md). **Laboratory:** [Native C23 HTTP server](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/http-loopback-server).

## 00:00–01:45 — Opening: where the extra bytes go

**On screen:** Two browser windows open the same Bits2Banking course page. An overlay highlights the HTML document, CSS stylesheet and illustrations.

**Narration:**

“When you open an educational website, your browser does not receive one mysterious object called a web page. It makes requests for HTML, stylesheets, diagrams and other resources. Every response has a set of headers and, usually, a body containing file bytes.

“Now imagine opening the same page again. Most of the files have not changed. Transferring all those bytes again would be unnecessary work. The HTTP protocol gives the browser a way to ask whether the content it already has is still useful. That is what we will implement today, using a small web server written in C23.”

## 01:45–04:10 — First GET and the entity tag

**On screen:** Run CMake configure and build in `C:\umicom\Umicom-Bits2Banking`. Start the server with `--root` pointing to its `sample_site`. In a second terminal, run `curl.exe -i` on `/index.html`.

**Narration:**

“We start with an ordinary GET request. The server selects a file under the explicitly configured document root, opens it through a checked native file handle and sends its bytes. Look at the response headers. `Content-Type` describes the representation. `Content-Length` describes the body size. `ETag` supplies a validator.

“Our learning server uses a weak entity tag, with the prefix `W/`. It is derived from the opened file's length and modification timestamp. That is enough to show how revalidation works, but it is not a cryptographic checksum. Two content changes can occasionally produce the same metadata. This is why we must be precise about the guarantees our code actually provides.”

**Demonstration command:**

```powershell
curl.exe -i http://127.0.0.1:8765/index.html
```

**On screen:** Highlight the actual `ETag` from this response. Do not use a made-up value as though it came from the running server.

## 04:10–06:40 — Conditional GET and 304

**On screen:** Make the same request with `If-None-Match`, pasting the tag observed above. Show the arrow in the diagram that returns to the browser without a body.

**Narration:**

“The browser can now say: I still have the page identified by this tag. Please send the content only if your current version is different.

“Our server first parses the full HTTP request. It checks the Host field and the optional entity-tag list. Only after the request is accepted does it open the corresponding file beneath the safe document root. If the tag matches, it returns `304 Not Modified`.

“Look carefully: there is no new HTML body. The browser can reuse its saved representation. If we provide a different tag, the server responds with `200 OK` and the current file. A matching validator never bypasses filesystem access checks.”

**Demonstration command:**

```powershell
curl.exe -i -H 'If-None-Match: PASTE_THE_ETAG_HERE' `
    http://127.0.0.1:8765/index.html
```

**Narration:**

“`Cache-Control: private, no-cache` sounds contradictory until we define the words. Here `no-cache` requires revalidation before reuse; it does not forbid a browser from storing the bytes. `private` rules out reuse by a shared intermediary cache.”

## 06:40–09:30 — Read the C23 code

**On screen:** Show `http.h`, `http.c`, `cache_validator.c`, `static_files.c` and `tcp_server.c` in that order.

**Narration:**

“In C23, every byte count and lifetime is explicit. The request structure has room for one bounded conditional header. The parser rejects duplicate headers and malformed lists rather than storing arbitrary input. A comparison function has three results: invalid, no match and match.

“The file service still owns the path-validation logic. The cache helper never receives an unchecked filesystem path. The socket adapter keeps the existing response-completion accounting. That is one of the most useful lessons in a growing application: we do not replace working components each time we add a feature. We extend them through clear responsibilities.”

**On screen:** Explain the difference between the `200` and `304` header encoders. Highlight that `304` has no body.

## 09:30–12:20 — What happens when input is wrong?

**On screen:** Send a malformed `If-None-Match` value, then a valid request for `/missing.html`. Run the two cache-specific CTests.

**Narration:**

“A malformed validator is not the same as a valid validator that does not match. The first is invalid input. The second is an ordinary request for a new representation. Our tests make this difference visible.

“Try a missing quote, a duplicate header and a trailing comma. The parser refuses these before it publishes a request. Now request a file that does not exist. This time the request is valid and the result is `404 Not Found`. A robust implementation keeps those failure categories separate.”

```powershell
ctest --test-dir ".\output\learning-build\http-loopback-server" `
    -R '^bits2banking\.http\.cache\.' --output-on-failure
```

## 12:20–15:30 — Review and exercise

**Narration:**

“Before we finish, remember the boundary of our experiment. This server is for local education. It does not implement Range requests, a shared cache service, public-network security or full HTTP negotiation. It uses a weak metadata tag, not a byte-exact digest.

“Your exercise is to predict four results: an ordinary GET, a HEAD request, a matching conditional GET and a conditional GET with a different tag. Run each one, inspect the headers and compare the outcome with your prediction. Then read the corresponding test case. You now understand not only the response code, but the chain of checks that made it safe to send.”

**Final card:** Bits2Banking → Chapters 162 and 163 → C23 source laboratory → Umicom Foundation GitHub. **Closing:** “We Value Each Other and Together Everyone Achieves More. Service to Many Leads to Greatness.”
