<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/55-keep-the-exact-name-of-a-web-event.md

PURPOSE:
Keep the exact name of a web event

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Keep the exact name of a web event

Imagine a Bits2Banking class where a teacher sends a short update to everyone watching a page. A server can use **Server-Sent Events**, or SSE, to send updates over one HTTP connection. The `event` field names the type of update so the page can decide what to do. The `data` field holds the update itself.

## 1. Count the spaces

Read the example as text. There are **two** spaces between the first colon and the word `update`.

~~~text
event:  update
data: the next lesson is ready

~~~

The colon separates the field name from its value. The receiver removes the first space after the colon if there is one. The second space stays, so the stored name begins with a space. A later `event:` or `event` field has an empty value and restores the default name `message`. A tab is a different character and stays in the stored name. [HTML Standard on interpreting event streams](https://html.spec.whatwg.org/multipage/server-sent-events.html#event-stream-interpretation)

In the table, each `·` stands for one space. Check your prediction before reading the right column.

| Event fields in reading order | Stored name |
| --- | --- |
| `event:·update` | `update` |
| `event:··update` | `·update` |
| `event:·update`, then `event:` | `message` |
| `event:·update`, then `event` | `message` |

## 2. Describe the logic before writing C

~~~text
Set the event name to "message".
For each event field:
    Remove one leading space from its value if present.
    If the remaining value will not fit, refuse the event.
    If the remaining value is empty, use "message".
    Otherwise, use the exact value as the event name.
Store the event after the input has been checked.
~~~

This is **pseudocode**. It explains the decisions in plain language. The C implementation uses a fixed array with one byte reserved to mark the end of the name. An oversized value is refused before the session adds an event. Compare the event count and exact stored bytes when testing. An onscreen label can hide a leading space.

## 3. Read one saved event through Framework

This C23 example submits one string to an in-memory Web Workbench session. The example address labels the session. All event bytes come from the quoted text.

~~~c
#include <string.h>
#include "umicom/web/workbench/stream.h"

static bool check_exact_event_type(void)
{
    UmiWebWorkbenchStreamSession session;
    /* Use an empty session so the first event occupies slot zero. */
    umi_web_workbench_stream_init(&session, "class", "Class updates",
        UMI_WEB_WORKBENCH_STREAM_SSE, "https://example.test/class");
    if (umi_web_workbench_stream_set_phase(&session,
        UMI_WEB_WORKBENCH_RUNNING) != UMI_STATUS_OK)
        return false;

    /* Read the stored event only after checking the import result. */
    const UmiStatus result = umi_web_workbench_stream_ingest_sse(&session,
        "event:  update\r\ndata: the next lesson is ready\r\n\r\n", 1U);
    return result == UMI_STATUS_OK && session.message_count == 1U &&
        strcmp(session.messages[0].event_name, " update") == 0;
}
~~~

The expected result is `true`. Insert `event:\r\n` between the event and data fields as a paper exercise. Predict the new name before comparing it with `"message"`. In C, `\r\n` writes a carriage return followed by a line feed, which is one common line ending. The blank line after the data completes the example event.

## 4. Run the Framework check

Use an existing configured Framework build directory that includes the Web API Workbench tests. Replace the example path with your build directory.

~~~powershell
$Build = 'C:/umicom/Umicom-Applications/framework/build/windows-ucrt64-debug'
cmake --build $Build --target umicom-web-workbench-stream-test
if ($LASTEXITCODE -ne 0) { throw 'Read the build output before continuing.' }
ctest --test-dir $Build -R '^framework\.web_api_workbench\.stream$' --output-on-failure --no-tests=error
if ($LASTEXITCODE -ne 0) { throw 'Read the result for the saved-event fixture.' }
~~~

Expect one named test to report `Passed` on a matching build. If CTest finds no case, check the build directory and its Workbench configuration. If an assertion fails, compare the exact input, its expected stored name and the reported assertion. Repeat one input at a time.

[Course contents](index.md) · [Previous lesson · Add metadata to a counted response](54-add-metadata-to-a-counted-response.md) · [Group console checks by what they submit](../automated-testing-with-umicom/15-group-console-checks-by-what-they-submit.md) · [Next lesson · Keep a FastCGI connector and its backend separate](56-keep-a-fastcgi-connector-and-its-backend-separate.md) · [HTML edition](../../../courses/building-a-web-server-in-c/lessons/55-keep-the-exact-name-of-a-web-event.html)
