<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/45-read-response-status-and-body.md

PURPOSE:
Teach beginners to check HTTP status, Content-Length and sent bytes independently with a native C23 exercise.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read response status and body length

[Course contents](index.md) · [Previous lesson](44-request-a-single-byte-range.md) · [HTML edition](../../../courses/building-a-web-server-in-c/lessons/45-read-response-status-and-body.html)

An HTTP reply begins with a status line. Header fields follow it, then a blank line marks the end of the headers. Any body bytes come after that line. If you count the body bytes and read the length field separately, you can tell an intentionally empty reply from one that stops early.

## Predict the reply

The table uses the same three offered bytes, `abc`, in every row. `GET` asks for the selected response. `HEAD` asks for its metadata without sending its body. Compare the two 200 rows to see how their length field can agree even though one body is empty. [RFC 9110 on HEAD](https://www.rfc-editor.org/rfc/rfc9110.html#section-9.3.2)

| Method and status | `Content-Length` in this exercise | Bytes after the blank line |
| --- | --- | --- |
| GET 200 OK | 3 | 3 |
| HEAD 200 OK | 3 | 0 |
| GET 204 No Content | Field omitted | 0 |
| GET 205 Reset Content | 0 | 0 |
| HEAD 205 Reset Content | 0 | 0 |

A 204 reports success without returning content. A 205 also asks the client to reset the input view, which can be useful after a form is submitted. Both statuses forbid body content. A 204 omits `Content-Length`. The Framework formatter sends an explicit zero for 205. [RFC 9110 on Content-Length](https://www.rfc-editor.org/rfc/rfc9110.html#section-8.6) · [RFC 9110 on Reset Content](https://www.rfc-editor.org/rfc/rfc9110.html#section-15.3.6)

## Check the numbers in C23

The exercise calls the public Framework formatter and inspects the resulting bytes in an array. The blank line is encoded as `\r\n\r\n`. Removing that separator and everything before it from the byte count leaves the body length. The test deliberately offers content for every status so a missing suppression rule is visible.

~~~c
#include "umicom/web/connection.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static bool check_response(int code, bool head, const char *expected_length,
                           size_t expected_bytes)
{
    /* The formatter borrows the response. Offer three bytes in every case. */
    static UmiWebResponse response;
    char wire[256], status_prefix[32];
    size_t written = 0U;
    if (umi_web_response_set_text(&response, code, "text/plain", "abc") != UMI_STATUS_OK ||
        UmiWebResponseFormatClosed(&response, head, wire, sizeof wire - 1U,
                                  &written) != UMI_STATUS_OK) {
        return false;
    }

    /* Leave room for the terminator. The blank line divides headers and body. */
    wire[written] = '\0';
    const char *gap = strstr(wire, "\r\n\r\n");
    if (gap == NULL) return false;
    const size_t body_bytes = written - (size_t)(gap + 4 - wire);
    const char *length = strstr(wire, "Content-Length: ");
    const bool length_matches = expected_length == NULL ? length == NULL
        : length != NULL && strncmp(length, expected_length, strlen(expected_length)) == 0;

    /* Check the status number, the length field and the bytes separately. */
    const int prefix_bytes = snprintf(status_prefix, sizeof status_prefix, "HTTP/1.1 %d ", code);
    const bool passed = prefix_bytes > 0 && (size_t)prefix_bytes < sizeof status_prefix
        && strncmp(wire, status_prefix, (size_t)prefix_bytes) == 0
        && length_matches && body_bytes == expected_bytes
        && (body_bytes == 0U || memcmp(gap + 4, "abc", expected_bytes) == 0);
    printf("%s %d %s\n", head ? "HEAD" : "GET", code, passed ? "PASS" : "FAIL");
    return passed;
}

int main(void)
{
    const char *three = "Content-Length: 3\r\n";
    const char *zero = "Content-Length: 0\r\n";
    /* Run every case so an unexpected result does not hide later checks. */
    const bool get_ok = check_response(200, false, three, 3U);
    const bool head_ok = check_response(200, true, three, 0U);
    const bool no_content = check_response(204, false, NULL, 0U);
    const bool reset_get = check_response(205, false, zero, 0U);
    const bool reset_head = check_response(205, true, zero, 0U);
    return get_ok && head_ok && no_content && reset_get && reset_head
        ? EXIT_SUCCESS : EXIT_FAILURE;
}
~~~

Each of the five lines should end in `PASS`. If a check fails, compare the status number, the length field and the bytes after the blank line with the table. The formatter borrows the response storage for the call and keeps ownership with the caller.

To repeat the checks in a Framework build with the web tests enabled, substitute its directory for `C:\path\to\framework-build`. The registered fixture also tests the original response bytes after serialization.

~~~powershell
ctest --test-dir 'C:\path\to\framework-build' --no-tests=error -R '^framework[.]web[.]closed_response[.](get|head|no-content|reset-content|reset-content-head)$' --output-on-failure
~~~

Use a separate integration test when you need to verify a running listener. The exercise above runs the formatter in memory.

Sammy Hegab · Umicom Foundation · MIT.

[Next lesson · Understand capped request counters](46-understand-capped-request-counters.md)
