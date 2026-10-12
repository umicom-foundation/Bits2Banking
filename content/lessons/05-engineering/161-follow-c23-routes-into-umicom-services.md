# 161. Follow HTTP routes into Umicom Framework and Kernel

The Bits2Banking web-server laboratory is deliberately small, but the design questions are the same ones encountered in a professional application: Who owns a connection? Who chooses an operation? Who is allowed to read a file? Who reports an incomplete transfer? What happens when a service stops?

The educational implementation keeps each concern in a separate C23 source file. Understanding these boundaries helps you read the larger Umicom projects without mistaking a classroom model for a production component.

## 1. Follow a request through Bits2Banking

Run the teaching server with `--routes --root` as shown in [Chapter 157](157-route-http-requests-to-c23-handlers.md). Then follow the code in this order:

1. **`main.c`** — validates `--port`, opens an optional static root, configures routes and owns cleanup.
2. **`tcp_server.c`** — binds the loopback socket, accepts a client, enforces deadlines, receives and sends bytes.
3. **`http.c`** — parses request headers and checks the Host header and supported method.
4. **`route_service.c`** — selects an exact handler and validates its response.
5. **`learning_routes.c`** — supplies actual course and status content.
6. **`static_files.c`** — serves files if no registered route matches and a root is present.
7. **`response_progress.c`** — accounts for bytes accepted by the socket and records incomplete sends.

This order is useful when diagnosing a problem. A bad Host header fails before route selection. A missing file is reported by the static-file owner, not by an API handler. A disconnect occurs at the transport boundary; it does not change the handler's content.

## 2. Compare with Umicom Framework

The Framework already owns reusable web-server and routing services. Its public interfaces include:

- [`include/umicom/web/server.h`](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/server.h) — web-server lifecycle and connection handling.
- [`include/umicom/web/static_files.h`](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/static_files.h) — rooted static-file handling and the filesystem-access boundary.
- [`examples/web/local_service.c`](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/web/local_service.c) — application composition of routes and the local C web service.

Read each contract before its implementation. Notice that the existing Framework static-file example has its own explicit file-size and transport limits; do not assume they are identical to the Bits2Banking exercise's limits.

The application provides content, while Framework owns shared capabilities. That is why adding an educational route to the Bits2Banking laboratory does **not** justify adding another production HTTP stack to Studio, Trader or Bank.

## 3. Compare with Umicom Kernel

A web server eventually asks the operating system to read bytes, use memory and communicate over a network. Those operations cross privilege and ownership boundaries.

For the filesystem part, read:

- [`kernel/vfs.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/vfs.c) — how paths, descriptors and provider callbacks are managed.
- [`kernel/ramfs.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/ramfs.c) — RAM-backed nodes and file byte ownership.
- [`kernel/user_files.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_files.c) — task-owned file-service boundaries.

For the system-level design, see the [Umicom Kernel repository](https://github.com/umicom-foundation/umicom-kernel) and the [Umicom OS repository](https://github.com/umicom-foundation/umicom-os). The native kernel research track is distinct from the current Linux-libre distribution track. Neither is modified by this lesson.

## 4. Practise a source-code review

Open the learning source files in Umicom Studio or your editor. For a request to `/api/courses`, find the line that first knows the request path, the line that selects the handler, the point where the response bytes are copied, and the code that checks whether sending finished.

Then repeat with `/assets/site.css`. Explain why that request belongs to the rooted-file owner rather than the API handler.

Record one concrete improvement you would make, the test that would prove it, and the layer that should own it. A useful improvement might be a new bounded content type or a clearer error message. Changing a production Framework interface is **not** required to complete this exercise.

### Questions

1. Why should a Notes application not write its own second socket library when Framework already offers reusable web services?
2. Which layer should decide whether a pathname is permitted under a document root?
3. Why does safe user-buffer access belong to a privileged OS boundary, rather than trusting an HTTP handler to cast any address to a pointer?

Continue with [Episode 54](../../videos/scripts/54-http-routes-and-c23-handlers.md) for a narrated demonstration and [Episode 55](../../videos/scripts/55-response-completion-and-service-lifetimes.md) for failure and lifecycle testing.
