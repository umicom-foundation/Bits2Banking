# Connect routes to ordinary C functions

Separate application meaning from socket handling. A route identifies a request; a handler is the C function that prepares the answer.

## 1. Understand a route

A **route** pairs an HTTP method and path with a function. The same path may have different meanings for different methods. The local example registers GET and HEAD explicitly for its home and health paths, and POST for its echo path.

The route table is ordinary C data. Its `handler` member is a function pointer: it lets the router call the selected function later. This is the same idea introduced in [the C callback lesson](../../learning-c/13-function-pointers-and-test-doubles.md).

## 2. Read the handler signature

```text
static UmiStatus Health(
    const UmiWebRequest *request,
    UmiWebResponse *response,
    void *context)
```

`static` keeps this function's name within its translation unit. `UmiStatus` is the Framework operation result. `const` says this callback must not change the request through that pointer. `response` points to output storage. `context` lets an application supply state whose lifetime it owns; this simple handler does not need it.

The HTTP response status and the C operation result are different. A successfully prepared HTTP 404 is still a complete response saying no matching resource was found. A C error can instead mean that response preparation failed. Do not collapse those two layers into one “success” flag.

## 3. Register only a successfully initialized route

```text
UmiWebRoute route;
status = umi_web_route_init(&route, method, path, handler, NULL);
if (status == UMI_STATUS_OK)
    status = umi_web_router_add(umi_web_service_router(service), &route);
```

This excerpt follows the real example. The names `method`, `path` and `handler` stand for one selected table entry. Check each returned status before using the result of the preceding step. Initialization refusal should not be followed by registration of uninitialized data.

## 4. Let Framework own message framing

A **content type** describes what the response bytes represent, such as HTML, JSON or plain text. A **content length** describes the number of bytes in the body. The closed-response transport owns authoritative framing headers. A handler must not insert conflicting lengths or connection headers.

For bounded text, use `umi_web_response_set_text`. For the real Echo path, read how `body_length` is copied together with the bytes. Do not use a string terminator to guess the length of arbitrary request data; the parser's contract permits zero bytes inside a body.

## 5. Add behavior at the correct layer

When extending a real application, keep reusable validation and business operations in Framework services. A handler should translate the request, call the owning service and translate its result. Socket loops do not belong in each application's handler.

The local example's `--root` mode selects a static-file fallback instead of registering the demo routes. It does not combine those modes by accident. The underlying router can support a separately designed exact-route-plus-fallback composition, but the example's command-line behavior stays explicit.

## Exercise

A new handler calls a Framework operation that fails, then returns an empty HTTP 200 page. What useful information has been lost?

<details>

<summary>Explanation</summary>

The caller can no longer distinguish an operation that succeeded from one that did not. Map the actual result to a suitable response and preserve the C failure where required by the service contract. An empty success page is not error handling.

</details>

---

[Read this lesson in HTML](../../../courses/building-a-web-server-in-c/lessons/02-routes-and-handlers.html) · [Learning sequence](../../../start/learning-sequence.md)

[Previous: Follow a browser request into C](01-follow-a-request.md)

[Next: Start and stop a local service safely](03-own-the-server-lifetime.md)
