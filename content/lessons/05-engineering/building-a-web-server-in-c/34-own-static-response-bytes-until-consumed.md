<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/34-own-static-response-bytes-until-consumed.md

PURPOSE:
Own static response bytes until they are consumed

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->


# Own static response bytes until they are consumed

## Separate metadata from storage

The body-aware static handler still uses the rooted-file service to admit the URL path and read the complete file. Root selection, one-time URL decoding and refusal of escaped paths remain shared Framework policy. Larger storage does not authorize arbitrary file access. The handler copies an admitted file into an immutable owner and releases the rooted read buffer.

A successful body-aware call may return an owner for an admitted file, or no owner for an inline error response. Always inspect both the operation status and HTTP status. An intentional 404 can be a successful operation. Do not assume every successful operation returns external bytes.

## Use one cleanup point

```c
/* preview and request are valid objects created by the caller. */
UmiWebResponseBody *body = NULL;
UmiStatus status = UmiWebPreviewHandleBody(preview, request, response, &body);
if (status == UMI_STATUS_OK) {
    const void *bytes = body != NULL ? UmiWebResponseBodyBytes(body)
                                      : response->body;
    size_t length = body != NULL ? UmiWebResponseBodyLength(body)
                                : response->body_length;
    /* Consume or copy exactly length bytes before the cleanup below. */
    (void)bytes;
    (void)length;
}
UmiWebResponseBodyDestroy(body);
body = NULL;
```

Read this fragment alongside InspectMain in the installed-SDK lab, which creates and destroys the surrounding objects. It illustrates a borrowed view; it does not send a response. Destroy accepts NULL, making a single cleanup path practical. If another component needs the bytes later, either transfer ownership through an explicit contract or make its own copy before this cleanup. A pointer alone does not extend lifetime.

## Keep callbacks unambiguous

UmiWebServiceSetBodyFallback registers a borrowed handler context. Keep that context alive until the service stops using it. The service runs its request gate and middleware before selecting the fallback; exact registered routes keep their existing inline dispatch. Clearing the body fallback restores the ordinary router path.

A body handler transfers a returned owner to the service. It must not also populate response->body_length with an inline body. Those two representations would be ambiguous, so the service rejects the conflict and destroys the owner. It also destroys an owner returned together with a failed operation. The connection owns an accepted body until writing finishes or fails.

## Exercise the failure boundary

Read the body-failure, body-conflict, gate and exact-route scenarios in Framework test_response_body.c. For each, predict whether the body callback runs, which component destroys an allocation, and whether a 500 replacement can be formatted. Then compare your predictions with owner-executed results. Authored assertions are expectations, not evidence that the runtime followed them.

For a debugging exercise, annotate a copy of the source with acquisition and release points. Do not add a second destroy after transferring ownership. If a browser shows a damaged icon, first compare stored and delivered bytes; a lifetime error, truncation and an incorrect media type require different corrections. Avoid treating a different visual appearance as proof of any one cause.

[Installed-SDK lab setup](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-static-preview/README.md) · [Body ownership contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/response_body.h) · [Authored regression scenarios](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/web/test_response_body.c) · [HTTP HEAD semantics](https://www.rfc-editor.org/rfc/rfc9110.html#section-9.3.2)

[Course contents](index.md) · [Previous lesson](33-separate-body-capacity-from-public-layout.md) · [Next lesson](35-finish-headers-and-partial-body-writes.md)
