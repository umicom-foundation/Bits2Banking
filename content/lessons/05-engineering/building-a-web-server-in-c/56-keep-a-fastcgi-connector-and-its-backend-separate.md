<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/56-keep-a-fastcgi-connector-and-its-backend-separate.md

PURPOSE:
Keep a FastCGI connector and its backend separate

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Keep a FastCGI connector and its backend separate

A FastCGI connector is a small record that says how to open and close a connection to the program that serves a request. In Umicom Framework, a managed connector checks whether one worker job is ready before passing a request to the backend. The backend is the connector that does the actual opening and closing. We can model that handoff with paper labels and two counters.

## 1. Give each record its own place

1. Draw three boxes labelled Mock backend, Gate and Route connector. Inside Gate draw a Saved backend slot. The mock backend has an Open function, a Close function and two counters.
2. Draw an arrow from the Route connector to Gate, then from Gate’s Saved backend to the mock Open and Close functions. Framework’s `UmiWebManagedFastCgiBind` creates this arrangement for one current job. It copies the backend connector record into the gate and publishes the route connector in separate output storage.
3. Next, point to the Saved backend slot as the proposed route output. Publishing there would overwrite the connector that handles opens and closes. Then try passing the same gate’s existing Route connector as its backend. That would send the gate’s work back to itself. With an otherwise valid job, the binding refuses either proposal with `UMI_STATUS_INVALID_ARGUMENT` and leaves both existing records in place.

~~~text
if proposed output is the gate's saved backend slot
    refuse the binding and keep both existing records
if proposed backend is the connector for this same gate
    refuse the binding and keep both existing records
save the real backend in the gate
publish the route connector in separate storage
~~~

## 2. Count the lifetime of one loan

A successful open hands the caller a connection to use temporarily. This temporary ownership is called a lease. Start the mock counters at zero and label the first job `A`. Cover the counter column first and explain which record does the work at each step.

| Action | Mock opens / closes | What to observe |
| --- | --- | --- |
| Try to open while job `A` is running and readiness is still unconfirmed. | 0 / 0 | The gate reports `UMI_STATUS_BUSY`. |
| Mark `A` ready and let the mock open succeed. | 1 / 0 | Keep the returned lease beside the original gate. |
| Request a stop and try a second open before the child finishes. | 1 / 0 | Readiness has been withdrawn. The mock sees no new open. |
| Return the first lease through the original gate. | 1 / 1 | The gate calls the backend that issued that lease. |
| Collect `A`, then replace it with a different job `B`. Try the connector still bound to `A`. | 1 / 1 | The old job identifier is stale. The gate reports `UMI_STATUS_NOT_FOUND`. |

Keep the gate, worker and backend storage available while the connector is registered. Remove the route registration and finish its leases before reusing the gate or releasing the worker. A new job needs its own binding and readiness check.

## 3. Check your explanation

Reset the counters. Suppose the mock open returns `UMI_STATUS_TIMEOUT` after readiness is confirmed. Predict the counters and what the caller owns. The backend was called once, so the counters are `1 / 0`. The open failed, so the caller’s output stays as it was and there is no new lease to close. This paper exercise follows the Framework source and its authored managed-worker fixtures.

[Course contents](index.md) · [Previous lesson · Keep the exact name of a web event](55-keep-the-exact-name-of-a-web-event.md) · [Start and stop a local service safely](03-own-the-server-lifetime.md) · [Encode a FastCGI request with bounded bytes](40-encode-a-fastcgi-request-with-bounded-bytes.md) · [Read a FastCGI reply before forwarding](41-read-a-fastcgi-reply-before-forwarding.md) · [Next lesson · Limit compiled bytes before embedding](57-limit-compiled-bytes-before-embedding.md) · [HTML edition](../../../courses/building-a-web-server-in-c/lessons/56-keep-a-fastcgi-connector-and-its-backend-separate.html)
