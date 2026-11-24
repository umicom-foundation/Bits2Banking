<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/13-preserve-output-on-small-buffers.md

PURPOSE:
Explain the lesson: Preserve output when a buffer is too small.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Preserve output when a buffer is too small

<p class="umicom-course-artwork"><span class="umicom-brand-mark"><img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom" width="180"></span> <a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="30"></a></p>

A buffer is a region of memory with a fixed capacity. A formatter must not write beyond that capacity, even when the desired output is much larger.

## Prepare

Open response.c in the HTTP contract lab. Find the four-byte array named tiny. Every byte initially contains 0x55, a recognizable hexadecimal value.

The HTTP response cannot fit in four bytes. The example expects CAPACITY_EXCEEDED, an output length of zero and all four bytes unchanged.

## Why check all three?

An error code alone does not prove the buffer was preserved. A zero length alone does not prove there was no partial write. Comparing the bytes checks the promised failure behavior.

1. Record tiny before the call.
2. Record tiny_length before the call: it is deliberately 99.
3. Inspect the status after the call.
4. Compare the entire array with before.
5. Confirm that the reported length was reset.

This pattern is useful for file names, serialized records and generated messages as well as HTTP.

## Replace text in a saved response

The formatter exercise checks the output buffer that would hold HTTP bytes. Before formatting, the response itself can hold a status, headers and text. A text replacement that exceeds capacity should leave that response available for a corrected attempt.

1. Make a practice copy of the `labs/native/framework-http-contracts` folder. Keep the original serialization example for the earlier exercise.
2. Save this C23 program as `response.c` in your copy. It saves the response bytes, then attempts to replace the text with a string that exceeds the body capacity. After checking the refusal, it takes a pointer to the short suffix of the existing text and uses it for a successful replacement.

~~~c
/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: response.c
 *
 * PURPOSE:
 *   Check that a refused text update preserves the previous response.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/
#include "umicom/web/response.h"

#include <stdio.h>
#include <string.h>

int main(void)
{
    /* Keep the larger exercise buffers in static storage. */
    static UmiWebResponse response;
    static unsigned char saved[sizeof response];
    static char oversized[UMI_WEB_BODY_CAPACITY + 1U];
    if (umi_web_response_set_text(&response, 200, "text/plain", "keep this") != UMI_STATUS_OK)
        return 1;

    /* Save all response bytes so the comparison checks more than its status. */
    memcpy(saved, &response, sizeof saved);
    memset(oversized, 'x', sizeof oversized - 1U);
    oversized[sizeof oversized - 1U] = '\0';
    if (umi_web_response_set_text(&response, 201, "text/plain", oversized) !=
            UMI_STATUS_CAPACITY_EXCEEDED ||
        memcmp(saved, &response, sizeof saved) != 0) {
        (void)fputs("Expected a capacity refusal with the same response.\n", stderr);
        return 1;
    }
    (void)puts("Oversize refused. Prior reply unchanged.");

    /* Skip 'keep ' to borrow the short suffix from the current response. */
    const char *suffix = response.body + 5U;
    if (umi_web_response_set_text(&response, 201, NULL, suffix) != UMI_STATUS_OK ||
        response.body_length != 4U || strcmp(response.body, "this") != 0) {
        (void)fputs("Expected the borrowed suffix to become the new body.\n", stderr);
        return 1;
    }
    (void)printf("Borrowed text saved. Body: %s\n", response.body);
    return 0;
}
~~~

3. In your practice copy, build only the response target with a Framework SDK that preserves the prior reply on a failed replacement. Use the same compiler and architecture as your SDK. Replace the example prefix with your own SDK location.

~~~powershell
cmake -S . -B build/response-replacement -G Ninja -DCMAKE_PREFIX_PATH="C:/path/to/framework-sdk"
cmake --build build/response-replacement --target btb-http-response
& "./build/response-replacement/btb-http-response.exe"
~~~

In Bash, use the same two CMake commands with your SDK path, then run `./build/response-replacement/btb-http-response`.

4. Expect these two lines.

~~~text
Oversize refused. Prior reply unchanged.
Borrowed text saved. Body: this
~~~

A borrowed pointer points into storage a caller already owns. Keep it valid until the function returns. Here the function copies the suffix before replacing the response. Use the new `response.body` to read the result. If a check fails, verify which Framework SDK the build found. If CMake cannot find the package, point `CMAKE_PREFIX_PATH` at the SDK that provides the Framework web component.

## Exercise

Try capacities of one, four and a comfortably large value in separate cases. Predict which should succeed. Never increase the capacity argument beyond the actual array size; that would lie to the function about available memory.

## Recovery

If a case fails only in an optimized build, inspect undefined behavior and lifetime mistakes rather than assuming the optimizer is wrong. The lab's REQUIRE macro remains active regardless of NDEBUG.

Framework owns the formatting rule. The consumer owns the storage and must supply an honest capacity.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-http-contracts/response.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](12-format-get-and-head-responses.md) · [Next lesson](14-register-a-route-and-context.md)

