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

<p class="umicom-course-artwork"><span class="umicom-brand-mark"><img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom" width="180"></span> <a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="30"></a></p>

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

## Check a route before registering it

A descriptor is the C record that holds the route's method, path and callback. If you fill in that record yourself, the method and path can be ready while the callback is still missing. The router returns `UMI_STATUS_INVALID_ARGUMENT` and leaves the number of registered routes unchanged.

1. Make a practice copy of the `labs/native/framework-http-contracts` folder. Keep the original lab for the earlier exercise.
2. Save the following C23 program as `routes.c` in your copy. It checks registration in memory. The first attempt has no callback, so it only checks the result and the route count.

~~~c
/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: routes.c
 *
 * PURPOSE:
 *   Check that a router accepts a descriptor only after its callback is assigned.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/web/router.h"

#include <stdio.h>

static UmiStatus Health(const UmiWebRequest *request, UmiWebResponse *response,
    void *context)
{
    /* This handler needs no application state. */
    (void)request;
    (void)context;
    return umi_web_response_set_text(response, 200, "text/plain", "ready");
}

static int CheckAdmission(UmiWebRouter *router)
{
    /* Omitted fields start at zero, so this route has no callback yet. */
    UmiWebRoute route = {.method = UMI_HTTP_METHOD_GET, .pattern = "/health"};
    const size_t before = umi_web_router_count(router);
    const UmiStatus refused = umi_web_router_add(router, &route);
    if (refused != UMI_STATUS_INVALID_ARGUMENT || umi_web_router_count(router) != before) {
        (void)fputs("Expected refusal with the same route count.\n", stderr);
        return 1;
    }
    (void)printf("Incomplete route refused. Routes: %zu\n", before);

    /* Complete the descriptor before asking the router to store its own copy. */
    route.handler = Health;
    if (umi_web_router_add(router, &route) != UMI_STATUS_OK ||
        umi_web_router_count(router) != before + 1U) {
        (void)fputs("Expected one new route after assigning Health.\n", stderr);
        return 1;
    }
    (void)printf("Completed route registered. Routes: %zu\n", umi_web_router_count(router));
    return 0;
}

int main(void)
{
    /* main owns the router throughout the exercise and frees it in one place. */
    UmiWebRouter *router = NULL;
    if (umi_web_router_create(&router) != UMI_STATUS_OK) {
        (void)fputs("Could not create the router.\n", stderr);
        return 1;
    }
    const int result = CheckAdmission(router);
    umi_web_router_destroy(router);
    return result;
}
~~~

3. In your practice copy, build only the existing route target with a Framework SDK that includes the callback check. Use the same compiler and architecture as your SDK. Replace the example prefix with your own SDK location.

~~~powershell
cmake -S . -B build/route-admission -G Ninja -DCMAKE_PREFIX_PATH="C:/path/to/framework-sdk"
cmake --build build/route-admission --target btb-http-routes
& "./build/route-admission/btb-http-routes.exe"
~~~

In Bash, use the same two CMake commands with your SDK path, then run `./build/route-admission/btb-http-routes`.

4. Expect these two lines from an empty router.

~~~text
Incomplete route refused. Routes: 0
Completed route registered. Routes: 1
~~~

The first count shows that the rejected descriptor used no slot. Assigning `Health` completes the record. The second count shows that the router stored one route. If the first check fails, verify which SDK the build found and use a version with the callback admission check. If CMake cannot find the package, point `CMAKE_PREFIX_PATH` at the SDK that provides the Framework web component.

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

