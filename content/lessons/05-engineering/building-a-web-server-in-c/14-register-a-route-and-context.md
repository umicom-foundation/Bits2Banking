<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/14-register-a-route-and-context.md

PURPOSE:
Explain the lesson: Register a route and its context.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Register a route and its context

A route connects a request method and path to a C function. A context pointer lets that function use application state without relying on a global variable.

## Prepare

Open routes.c in the HTTP contract lab. Read the Health function first. It increments a caller-owned counter and fills a plain-text response.

## Follow registration

1. Create a UmiWebService.
2. Initialize a route for GET and /health.
3. Pass Health as the callback.
4. Pass the address of calls as its context.
5. Add the route to the service's router.

The route stores a borrowed pointer to calls. The local counter remains alive until main finishes. The service is destroyed before main returns, so the borrower does not outlive that counter.

## Compare two requests

The first request targets /health. Expected: response status 200 and calls equal to one.

The second targets /missing. Expected: response status 404 and calls still equal to one. The service handled a valid request, but it did not invoke the Health callback.

A Framework status of OK can therefore accompany an HTTP response of 404. The C operation completed; the requested route was absent.

## Exercise

Add a separate GET /version handler returning a short version label. Give it its own counter. Verify that requesting /health does not increment the new counter.

If the callback never runs, compare method and exact path before investigating the UI. A route named /health does not automatically cover /health/ or POST /health.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-http-contracts/routes.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](13-preserve-output-on-small-buffers.md) · [Next lesson](15-handle-short-transfers.md)

