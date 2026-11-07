# Owning a request, a route and a transport

```text
lab owns input bytes ----> Framework frame and parser
lab owns service --------> Framework router ----> borrowed handler context
lab owns output storage <---- Framework response formatter
```

An owner decides when an object stops existing. A borrower can use that object only during the agreed interval.

1. Create the service before registering routes.
2. Keep the callback context alive until all requests finish.
3. Allocate large request and response values on the heap when the thread stack is limited.
4. Finish dispatch before destroying the service.
5. Free request/response values only after their final read.

The connection processor borrows its byte transport. It never closes a socket on behalf of the caller. A real host must close the connection on both success and failure because the format used here announces Connection: close.

## Two different outcomes

A handler may update an application record successfully, then sending its reply may fail. The exchange result therefore records **dispatched** separately from **response_complete**.

Do not automatically retry an operation with side effects merely because the response was lost. A production operation needs an explicit duplicate-request policy, such as a reviewed operation identifier and retained result. This lab illustrates the boundary; it does not implement durable request deduplication.

## Exercise

Draw a timeline for exchange.c with fail_write true. Mark the handler call, first write attempt, error return and service destruction. Then explain why the handler counter is one even though zero bytes reached the output array.
