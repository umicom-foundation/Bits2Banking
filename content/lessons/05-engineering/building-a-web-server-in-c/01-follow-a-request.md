# Follow a browser request into C

A browser and a C program can cooperate without the browser knowing how C works. Their agreement is a message format. Follow the actual Umicom local example from its address to the response.

## 1. Identify the client and server

A **client** asks for something; a **server** waits for requests and sends responses. These are roles, not necessarily different computers. In this exercise both run on your computer. The browser is the client. The executable built from `examples/web/local_service.c` is the server.

Its address is `http://127.0.0.1:8080/`. `http` names the message protocol. `127.0.0.1` is an IPv4 loopback address: it refers back to this computer. `8080` is a port, the numbered endpoint selected by the server. The final `/` is the requested path.

 <svg viewbox="0 0 700 110" role="img" aria-label="The browser sends a request; Framework selects a route; a C handler fills a response." style="width:100%;max-width:700px"><title>The browser sends a request; Framework selects a route; a C handler fills a response.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">Browser request</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Framework router</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">C response handler</text></svg>

The browser sends a request; Framework selects a route; a C handler fills a response.

## 2. Read a small request

```text
GET /api/health HTTP/1.1
Host: 127.0.0.1:8080
```

This displayed example shows the start line, a header and the blank line ending the headers. The wire format uses carriage-return and line-feed bytes for line endings. `GET` is the method, `/api/health` is the target and `HTTP/1.1` is the protocol version. The header supplies the selected host and port. The [HTTP/1.1 specification](https://www.rfc-editor.org/rfc/rfc9112.html) describes the message syntax; Umicom's local service deliberately supports a smaller bounded subset.

A browser may send more headers. A request is not a function call, executable code or a pathname that the server should blindly open. It is untrusted input that must be interpreted under the service's rules.

## 3. Follow the real health route

1. Open [`examples/web/local_service.c`](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/web/local_service.c).
2. Find the route table entry for `UMI_HTTP_METHOD_GET` and `"/api/health"`.
3. Follow its `Health` function pointer.
4. Read the call to `umi_web_response_set_text`. It selects status 200, the JSON content type and the response text.

```text
{"service":"umicom-local-example","status":"ready"}
```

**JSON** is a text format for named values. Here the two names are `service` and `status`. This fixed example reports that its handler was reached; it does not check every subsystem, database or dependency.

## 4. Read the form's behavior honestly

The home page's form sends a `POST` request to `/api/echo`. Typing `hello` produces form-encoded text such as `message=hello`. The Echo callback copies the validated request body into a plain-text response and sets its exact byte length.

The example does not decode the form, save a record, authenticate a user or execute commands. A displayed string is not evidence that a banking transaction or other application operation happened.

## 5. Predict before running

What changes if the browser uses port 8081 while the server is listening on 8080?

<details>

<summary>Explanation</summary>

The client contacts a different endpoint. A refusal or another service's response is not a route error inside the server listening on 8080. First compare the exact address printed by the intended executable.

</details>

No installation is needed to read this lesson. [Learning HTML](../../../courses/learning-html/index.html) explains the form; [Learning C](../../../courses/learning-c/index.html) explains functions, structures and pointers.

---

[Read this lesson in HTML](../../../courses/building-a-web-server-in-c/lessons/01-follow-a-request.html) · [Learning sequence](../../../start/learning-sequence.md)

[Next: Connect routes to ordinary C functions](02-routes-and-handlers.md)
