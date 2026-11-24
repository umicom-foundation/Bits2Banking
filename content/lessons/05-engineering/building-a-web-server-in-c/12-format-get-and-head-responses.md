<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/12-format-get-and-head-responses.md

PURPOSE:
Explain the lesson: Format GET and HEAD responses.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Format GET and HEAD responses

A response consists of headers and sometimes a body. GET normally asks for the representation. HEAD asks for its metadata without transferring the body.

## Prepare

Build the HTTP contract lab using its README and open response.c. The response body is the five-byte text ready.

The program asks the same Framework formatter to produce a normal response and a HEAD response. The boolean argument selects whether body bytes are omitted.

## Inspect the expectations

1. Both responses declare Content-Length: 5.
2. Both announce Connection: close.
3. The GET output ends with ready.
4. The HEAD output contains five fewer bytes.
5. The test checks the declared size independently of the transmitted size.

A length in a header describes a protocol value. It is not automatically the number of bytes transmitted in every response mode.

## Understand the spare byte

The output arrays begin filled with zero. The formatter receives capacity minus one. This leaves a zero after its bounded output so this particular lab can safely use strstr to inspect headers.

The formatter's length remains the authoritative count. In a socket adapter, write exactly that count; do not send the spare zero.

## Exercise

Change ready to waiting in a personal copy. Predict the new declared length and the difference between GET and HEAD. Update every expectation that depends on the body length.

If the HEAD test fails, examine the length and body rules before altering the route. A request method, response content and transmission format have related but separate responsibilities.

## Retry a refused response header

The response stores a bounded list of fields in memory before it formats the HTTP message. Each field has a name and a value. An application can pull a value from its settings, check the status returned by the response service, and supply a corrected value when the first attempt is refused.

Save this exercise as `retry-response-field.c`. The string named `too_long` contains one more byte than a header value can store when you include the terminating zero. The tool can refuse that value while keeping the current header count and the field that the application already set.

~~~c
#include "umicom/web/response.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    UmiWebResponse reply;
    umi_web_response_init(&reply);

    if (umi_web_response_set_header(&reply, "X-Preview", "current") != UMI_STATUS_OK)
        return 1;

    /* Use the public capacity so the example follows the current field size. */
    char too_long[UMI_WEB_HEADER_VALUE_CAPACITY + 1U];
    memset(too_long, 'x', sizeof too_long - 1U);
    too_long[sizeof too_long - 1U] = '\0';

    if (umi_web_response_set_header(&reply, "X-Preview", too_long) != UMI_STATUS_CAPACITY_EXCEEDED ||
        umi_web_response_set_header(&reply, "X-Preview", NULL) != UMI_STATUS_INVALID_ARGUMENT ||
        reply.header_count != 1U || strcmp(reply.headers[0].value, "current") != 0)
        return 1;
    puts("Both refused values left one existing field.");

    /* A successful retry takes the next slot. This response API appends
     * repeated names and keeps them in the order the caller supplied. */
    if (umi_web_response_set_header(&reply, "X-Preview", "next") != UMI_STATUS_OK ||
        reply.header_count != 2U || strcmp(reply.headers[0].value, "current") != 0 ||
        strcmp(reply.headers[1].value, "next") != 0)
        return 1;
    puts("The valid retry used the next slot.");
    return ferror(stdout) || fflush(stdout) ? 1 : 0;
}
~~~

On paper, trace the field count after each call. It should be 1 after the first append, stay at 1 after the long and missing values, and reach 2 after the corrected append. This is the same distinction as preparing a candidate copy and publishing it only after the input passes its check. The application can still show the previous state if it has to ask for a corrected setting.

In a configured Framework build, run `ctest --test-dir <build-directory> --output-on-failure -R "^framework[.]web_response$"` after building its `umicom-web-response-tests` target. Open `tests/test_web_response.c` in Framework and find the field append checks. They cover the preserved count, the corrected append, and a case where all field slots are full.

If a test reports that CTest found zero tests, check that the Framework build has its native tests enabled. If the test executable is missing, build the named target in the same build directory. Keep the exercise in memory while you work through the count and recovery steps.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-http-contracts/response.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](11-reject-ambiguous-framing.md) · [Next lesson](13-preserve-output-on-small-buffers.md)

