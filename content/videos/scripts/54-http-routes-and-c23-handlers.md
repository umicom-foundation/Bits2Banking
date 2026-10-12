# Episode 54 — HTTP Routing: From a Browser Address to a C23 Handler

**Runtime:** Approximately 12–16 minutes, including source inspection and live demonstrations.

**Written lessons:** [157 — Route HTTP requests](../../lessons/05-engineering/157-route-http-requests-to-c23-handlers.md) and [158 — HTTP responses and HEAD](../../lessons/05-engineering/158-build-http-response-headers-and-head.md).

**Demonstration source:** `labs/native/http-loopback-server/route_service.c`, `learning_routes.c`, `http.c` and `main.c`.

## Opening — One listener, several responsibilities (0:00–1:30)

**On screen:** A browser window with three addresses: `/`, `/api/courses`, `/assets/site.css`. Display the route-dispatch diagram.

**Narration:**

"When you visit a website, your browser sends a request to a server. The address tells the server what the browser is asking for. A homepage might come from an HTML file. A stylesheet might come from a CSS file. A course list might be prepared by a function at the moment of the request. These are different sources of content, but they can share a single listening port.

"Today we will follow one HTTP request through a small server written in C23. We will add handlers without replacing the existing socket code, and we will keep the earlier static-file mode intact. At the end you will be able to explain where request parsing finishes, where route selection begins and who owns the bytes sent back to the browser."

## Stage 1 — Build the program (1:30–3:15)

**On screen:** PowerShell, then the CMake project tree. Type the commands one at a time.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\http-loopback-server" `
    -B ".\output\learning-build\http-loopback-server" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\http-loopback-server" --parallel 2
```

**Narration:**

"We begin by asking CMake to configure the learning project. The source directory contains our C code. The build directory holds generated build instructions and output files. Ninja follows those instructions and invokes the compiler. You can already see a useful division of responsibilities: CMake describes what belongs to the build; the compiler translates C23 source into machine code; the linker produces the finished executable. None of those tools decides which HTTP route should run. That behaviour belongs to our program.

"If the build reports an error, read the first compiler diagnostic before trying another command. Never hide a build failure just to move to the next demonstration."

## Stage 2 — Read a route in C (3:15–6:00)

**On screen:** Open `learning_routes.c`. Highlight `Courses` and then `BtbLearningRoutesInstall`. Show `route_service.h` alongside.

**Narration:**

"A route is a named place in the server. It connects a path, such as slash-api-slash-courses, to a function that prepares the result. In our example, `Courses` is a C function. It does not open a socket. It does not decide how large a network packet should be. Instead, it prepares a JSON document and supplies a checked status code, media type and byte count.

"Notice the small but important expression `sizeof contents - 1`. The compiler knows how many bytes are in this fixed array. The final zero byte ends a C string, but it is not part of the JSON document we want to return. HTTP needs the exact payload length. Counting the bytes explicitly makes it possible to prepare valid responses and test them without making assumptions about a terminating character.

"Now look at the registration function. It associates `/api/courses` with `Courses`, `/api/status` with `Status`, and `/workshop` with an HTML handler. It uses an eight-entry routing table. This is a deliberate learning limit. If the table becomes full or a path is registered twice, the operation reports a refusal instead of overwriting another handler."

## Stage 3 — Start the server and make requests (6:00–9:00)

**On screen:** Start the server in one terminal and open a second PowerShell window. Run the request. Open `/workshop` in a browser.

```powershell
& ".\output\learning-build\http-loopback-server\btb-http-server.exe" `
    --port 8765 --routes
```

Second terminal:

```powershell
Invoke-RestMethod "http://127.0.0.1:8765/api/courses"
```

**Narration:**

"The server listens on the loopback address, 127.0.0.1. That means the server is reachable from this computer, not from arbitrary machines on the Internet. It is suitable for a local teaching exercise.

"The request reaches the TCP listener. The network layer receives bytes. The HTTP parser checks the request line, the required Host header and the supported method. The routing table then looks for an exact path match. Because `/api/courses` is registered, the `Courses` handler runs and prepares JSON.

"The JSON contains four entries: Computer Architecture, C23, Assembly and Umicom Kernel. You can change the list in the C source and rebuild to see how application data changes while the networking implementation stays the same. This is the benefit of separating a transport from the application operation it carries.

"Now open slash-workshop. This time a different C function prepares HTML. The server still uses the same listener and response code. A second web stack would add complexity without improving our understanding."

## Stage 4 — Add static files without breaking routes (9:00–11:45)

**On screen:** Stop the previous server. Resolve the sample-site root. Start `--root` and `--routes` together. Request `/api/courses` and `/assets/site.css`.

```powershell
$Root = (Resolve-Path ".\labs\native\http-loopback-server\sample_site").Path
& ".\output\learning-build\http-loopback-server\btb-http-server.exe" `
    --port 8765 --root $Root --routes
```

**Narration:**

"The same server can now serve both a registered C handler and files from a chosen website directory. Requesting `/api/courses` selects the route; requesting `/assets/site.css` falls through to the existing static-file owner. We do not weaken the file-path checks simply because a route has been added. A filename containing a dot, such as `site.css`, is valid for the static file server even though it is not a valid route-registration name.

"Ask what would happen if we mistakenly returned a service error whenever a path did not match an API route. Our stylesheet would fail even though the file exists. In a composed server, a route miss means 'not handled here', not 'everything has failed'. Each layer must be clear about when it has authority and when it should let the next layer continue."

## Stage 5 — GET, HEAD and a short review (11:45–14:30)

**On screen:** Issue GET and HEAD to `/api/courses`. Open `test_routes.c` and identify the encoding test.

```powershell
Invoke-WebRequest "http://127.0.0.1:8765/api/courses" -Method Get
Invoke-WebRequest "http://127.0.0.1:8765/api/courses" -Method Head
```

**Narration:**

"GET returns headers and the JSON body. HEAD reports the same representation length but sends no body. This detail matters for clients that want to inspect metadata without downloading the representation itself. Our encoder returns the header boundary separately so the send code can account for the actual bytes it transmits.

"Before finishing, run the route tests. They check successful lookup, duplicate registration, missing paths, malformed names and HEAD formatting. Try to predict whether a request for an unknown path should become an application error or a normal 404 response. Then check what the tests expect.

"You have now seen the whole route path: receiving a request, selecting a C function, preparing owned content and returning an HTTP response. In the next episode, we will examine what happens when a response is too large for one send operation or when the browser disconnects before the transfer completes."

## Practice and reference

Run `ctest --test-dir .\output\learning-build\http-loopback-server --output-on-failure`. In your own words, explain how a registered handler differs from the static-file fallback.

Continue with [Episode 55 — Response completion and lifetimes](55-response-completion-and-service-lifetimes.md), the [Bits2Banking website](https://umicom-foundation.github.io/Bits2Banking/) and the [source repository](https://github.com/umicom-foundation/Bits2Banking).
