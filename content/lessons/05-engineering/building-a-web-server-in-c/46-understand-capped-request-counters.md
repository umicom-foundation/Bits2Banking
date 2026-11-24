<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/46-understand-capped-request-counters.md

PURPOSE:
Understand capped request counters

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Understand capped request counters

Each request gives a web service something to count. Umicom Framework keeps a request total, two byte totals, and separate totals for selected HTTP response groups. These values can help you explain what a service has handled since counting began.

| Counter | What it adds for each recorded request |
| --- | --- |
| `requests` | One request |
| `bytes_in` and `bytes_out` | The input and output sizes supplied by the caller |
| `responses_2xx` | One response for a status in the 200s, such as 200 |
| `responses_4xx` | One response for a status in the 400s, such as 404 |
| `responses_5xx` | One response for a server error status, such as 503 |

A redirect such as 302 adds to the request and byte totals. The three listed response groups stay unchanged. In the Framework web service, the byte inputs come from the request and response body lengths. Other traffic, such as headers, needs its own measurement.

## What happens at the largest value?

The Framework stores each total in a `uint64_t`. It holds whole numbers from zero through `UINT64_MAX`, or 18,446,744,073,709,551,615. A regular unsigned addition can wrap to a small number after the limit. On a dashboard, that could look like an old, busy service suddenly handled almost nothing.

A **saturating counter** keeps the highest representable value once the running total reaches it. The service first works out how much room remains. It adds the amount when there is enough room. A larger amount sets the counter to its maximum. Each counter has its own available room.

~~~text
ROOM = MAXIMUM minus CURRENT
IF AMOUNT exceeds ROOM
    STORE MAXIMUM
ELSE
    STORE CURRENT plus AMOUNT
~~~

When a total shows `UINT64_MAX`, the service has counted at least that much since initialization. The number alone cannot tell you how much additional activity occurred after the cap. Other totals can keep increasing.

## Try the boundary with C23

1. Make a practice folder and save the code below as `metrics-lesson.c`. It uses the current Framework metrics implementation. The large starting values are practice data so you can reach the boundary on the first call and try to pass it on later calls.
2. Read the checks after each recorded response. Pay particular attention to the byte counts and supported response groups. The example uses an ordinary structure in memory.
3. Use `umi_web_metrics_init` on the practice record again. That clears all six counters. The final call records the first request of a new counting period.

~~~c
#include "umicom/web/metrics.h"

#include <assert.h>
#include <stdint.h>
#include <stdio.h>

int main(void)
{
    UmiWebMetrics totals;
    umi_web_metrics_init(&totals);

    /* Start near the limit so one small input reaches both boundaries. */
    totals.requests = UINT64_MAX - UINT64_C(1);
    totals.bytes_in = UINT64_MAX - UINT64_C(2);

    umi_web_metrics_record(&totals, 2U, 200, 4U);
    assert(totals.requests == UINT64_MAX);
    assert(totals.bytes_in == UINT64_MAX);
    assert(totals.bytes_out == 4U);
    assert(totals.responses_2xx == 1U);

    /* A capped total stays put while another response group grows. */
    umi_web_metrics_record(&totals, 8U, 404, 5U);
    umi_web_metrics_record(&totals, 1U, 302, 1U);
    assert(totals.requests == UINT64_MAX);
    assert(totals.bytes_in == UINT64_MAX);
    assert(totals.bytes_out == 10U);
    assert(totals.responses_2xx == 1U);
    assert(totals.responses_4xx == 1U);
    assert(totals.responses_5xx == 0U);

    /* Begin a new counting period and check all six starting values. */
    umi_web_metrics_init(&totals);
    assert(totals.requests == 0U && totals.bytes_in == 0U && totals.bytes_out == 0U);
    assert(totals.responses_2xx == 0U && totals.responses_4xx == 0U && totals.responses_5xx == 0U);

    umi_web_metrics_record(&totals, 3U, 503, 1U);
    assert(totals.requests == 1U && totals.bytes_in == 3U && totals.bytes_out == 1U);
    assert(totals.responses_5xx == 1U);

    puts("Boundary and reset checks passed.");
    return 0;
}
~~~

Use PowerShell in the practice folder with a recent GCC on your command path. Set `$framework` to the folder containing the current Framework `include` and `src` folders. In this command, `-I` gives the compiler the header folder. The second C file supplies the metrics functions. Run the program after the build succeeds.

~~~powershell
$framework = 'C:/path/to/umicom-framework'
gcc -std=c23 -Wall -Wextra -Werror -I "$framework/include" ./metrics-lesson.c "$framework/src/web/metrics.c" -o ./metrics-lesson.exe
if ($LASTEXITCODE -eq 0) { ./metrics-lesson.exe }
~~~

Expect the line `Boundary and reset checks passed.` If the compiler cannot find `umicom/web/metrics.h`, check the Framework folder. If a counter reaches zero before the call that clears the record, compare the Framework source with the implementation that caps additions, and confirm you ran the new executable after a successful build.

For a real service, keep the start of the counting period alongside the totals. Keep different periods separate when comparing activity. A zero just after initialization is the start of a new observation.

[Course contents](index.md) · [Previous lesson · Read response status and body length](45-read-response-status-and-body.md) · [HTML edition](../../../courses/building-a-web-server-in-c/lessons/46-understand-capped-request-counters.html)

[Next lesson · Read media types from filename extensions](47-read-media-types-from-filename-extensions.md)
