# Episode 55 — Complete HTTP Responses and Stop C23 Services Safely

**Runtime:** Approximately 13–17 minutes with demonstrations.

**Written lessons:** [159 — Response completion](../../lessons/05-engineering/159-handle-http-disconnects-and-response-completion.md), [160 — Service lifetimes](../../lessons/05-engineering/160-control-c23-web-service-lifetimes.md) and [161 — Umicom service boundaries](../../lessons/05-engineering/161-follow-c23-routes-into-umicom-services.md).

**Demonstration source:** `response_progress.c`, `tcp_server.c`, `route_service.c`, `test_progress.c` and `test_routes.c`.

## Opening — Prepared does not mean delivered (0:00–1:45)

**On screen:** A fictional Notes page with a large illustration. Show the response-byte diagram.

**Narration:**

"When you ask a web server to send a page, the application first prepares its answer. A response might be a few dozen bytes of JSON or an illustration containing many thousands of bytes. Preparing those bytes is not the same as successfully transferring them.

"Consider what happens if the browser disconnects after receiving only part of the illustration. If our server reports that the entire file was sent simply because it opened the file, the diagnostic will be misleading. A correct server must distinguish an accepted request, the bytes prepared for transmission and the bytes actually accepted by the networking stack.

"Today we will add a small C23 response-progress object and examine safe web-service lifetimes. The same care about ownership and acknowledgement is useful in storage systems and financial applications, although the exact network and transaction protocols are different."

## Stage 1 — Follow a short send (1:45–4:00)

**On screen:** Open `tcp_server.c`, locate `BtbSendAll()`, and highlight the return value of `send()`.

**Narration:**

"The `send` function takes a buffer and an amount of data to transmit. It returns a number indicating how many bytes were accepted by the operating system. We cannot assume the entire buffer was accepted in one call. If we asked for one thousand and twenty-four bytes but only three hundred were accepted, the next send must begin at the correct offset, not from the start.

"Our helper continues until the requested buffer has been accepted, unless an error, client disconnect or time limit prevents further progress. The loop checks the remaining length before each operation. It also limits the amount attempted in any one call, which makes the example easier to inspect.

"The new progress object receives the actual count from every successful call. Notice the direction of ownership: the networking code reports accepted bytes to the progress object. The progress object never sends bytes itself."

## Stage 2 — Count headers before body bytes (4:00–6:45)

**On screen:** Open `response_progress.h`, show its struct, then open `test_progress.c`.

**Narration:**

"An HTTP response begins with headers. These tell the browser the status, content type and content length. The blank line at the end of the headers marks the beginning of the body. If the response is a large file, we may send the body in several chunks, but only after the headers have been sent.

"Our response object begins in a HEADERS state. It remembers exactly how many header bytes it expects. Only after those bytes have been counted does it allow body bytes. That means a programming error cannot count body data while the header transmission is still incomplete and claim the whole response succeeded.

"Look at the first test. We tell the progress object to expect eighty header bytes and twenty thousand body bytes. We count thirty header bytes, then try to count a body byte. That operation must be refused. We finish the remaining fifty header bytes and send eight thousand, one hundred and ninety-two body bytes. Is the transfer complete? Not yet. We still need eleven thousand, eight hundred and eight bytes.

"The model checks remaining capacity before increasing its counters. Subtracting the known sent amount from the expected amount avoids an addition that could overflow before we notice the problem. That same checked-arithmetic pattern appeared earlier in our C23 lessons."

## Stage 3 — Disconnect without pretending success (6:45–9:15)

**On screen:** Open the second test, `disconnect`. Highlight `BtbResponseProgressFail()` and the expected final state.

**Narration:**

"The second test begins a response that should have a two-thousand-and-forty-eight-byte body. The header is sent completely, and only one hundred body bytes are counted. We then simulate a lost connection.

"The progress object moves into a FAILED state. The test confirms that the completed flag is false. It also tries to count the remaining bytes after failure. That must be rejected: a failed transfer cannot become successful merely because someone later increments a counter.

"There is a subtle limitation here. When `send` reports success, it tells us that the local networking stack accepted the bytes. It does not tell us that the browser displayed the page. This is why higher-level applications use acknowledgements when they need an end-to-end confirmation. A response counter is valuable diagnostic evidence, but it is not proof of a business transaction."

## Stage 4 — The unusual HEAD response (9:15–10:45)

**On screen:** Show a GET response next to a HEAD response with identical Content-Length headers.

**Narration:**

"HEAD is a useful counterexample. Suppose GET would return sixty-nine bytes of JSON. A HEAD response may announce sixty-nine bytes in Content-Length, but it must not send the JSON body. Our progress object therefore expects the full header bytes and zero wire-body bytes. Once the headers are accepted, HEAD is complete.

"If we had confused the declared length with the number of bytes we planned to send, we would either wait forever for a body that should not exist or report every HEAD response as incomplete. Keeping those two measurements separate avoids that mistake."

## Stage 5 — A handler must not destroy its owner (10:45–13:30)

**On screen:** Switch to the service-lifetime diagram. Open `route_service.c` and `test_routes.c`.

**Narration:**

"Now consider another type of ownership. A routing table borrows pointers to handler functions and, optionally, handler context. While a request is running, the server must keep the related application objects alive. Freeing a context too early would leave the handler with a pointer to memory that no longer belongs to it.

"Our small routing owner has three important stages: configuring routes, serving requests, and stopped. During configuration, we can add registered paths. After starting, route registration stops. During a handler callback, a busy marker prevents a second dispatch or shutdown from interfering with the active operation.

"The test deliberately tries to stop the service from inside a handler. It expects BUSY. After the handler finishes and returns a complete response, the ordinary owner can stop the service. This is a controlled single-threaded model: it teaches lifetime ownership, not a general concurrency or thread-safety guarantee.

"A handler also prepares its response in temporary storage first. The result is copied to the caller only after every field is validated. If the callback fails, the caller's previous output remains unchanged. This prevents a failed request from producing a believable but partially filled response."

## Stage 6 — Reuse the correct Umicom services (13:30–16:15)

**On screen:** Open the source links in [Chapter 161](../../lessons/05-engineering/161-follow-c23-routes-into-umicom-services.md). Compare the Bits2Banking file tree with the Umicom Framework web interfaces and the Kernel VFS source.

**Narration:**

"The reason we build small educational components is to understand how systems work, not to start another competing production web platform. Umicom Framework already provides web-server, routing and static-file services. Umicom Kernel owns privileged memory, device and filesystem mechanisms. Our Notes application should use shared Framework services when it grows beyond the classroom.

"Follow a request from the listener to HTTP parsing, routing and content generation. Then trace a file request through the static-file owner and, conceptually, through the operating system's file interfaces. Each layer validates what belongs to it. Each layer also reports the limits of what it knows.

"Finally, run all eleven HTTP learning tests. They exercise the original parsing and static-file functions, the new routing rules, response-completion accounting and service lifetimes. If one test fails, investigate the first failure before changing the implementation."

## Closing — Three facts to remember (16:15–17:00)

**On screen:** Show three statements: "prepared", "sent", "acknowledged".

**Narration:**

"Remember three distinct facts. Content can be prepared without being sent. Bytes can be accepted by the local socket API without proving that the remote application acted on them. And a service can be stopped safely only after the work and pointers it owns are no longer in use.

"These principles will serve us again when we study reusable network services, authentication, durable messages and real application lifecycle management."

## Further practice

Build and run the laboratory described in [Chapter 160](../../lessons/05-engineering/160-control-c23-web-service-lifetimes.md). Inspect the [Bits2Banking repository](https://github.com/umicom-foundation/Bits2Banking), the [Umicom Framework web interfaces](https://github.com/umicom-foundation/umicom-framework/tree/main/include/umicom/web) and the [Umicom Kernel VFS implementation](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/vfs.c).
