<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/49-read-status-codes-before-deciding.md

PURPOSE:
Read status codes before deciding what to do

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read status codes before deciding what to do

Imagine a practice site that prepares a book export. Your request contains a fictional title and a page count. The site sends back an HTTP status code. That number tells you what happened to the request so far and which information to read next.

## Separate the number from the words

A status code is a three-digit number in an HTTP response. In the line below, `202` is the code and `Accepted` is its human-readable reason phrase.

~~~text
HTTP/1.1 202 Accepted
~~~

Use the numeric code when choosing a program action. The words help a person read an HTTP/1.1 transcript. A reason phrase can be absent or different in another service. This example means that the request was accepted for processing. Keep its result pending until you have separate evidence of completion.

## Choose the next step for each code

Use fictional files and identifiers throughout the exercise. A worker is the part of a service that carries out a task, such as preparing an export. A gateway passes requests to another service and returns the response.

| Code and phrase | What it tells you | What to record or check |
| --- | --- | --- |
| `202 Accepted` | The service accepted the work for processing. | Record a pending result. Use the service’s documented job status information if it supplies any. |
| `412 Precondition Failed` | A request condition failed. For example, the version named in an `If-Match` header did not match the current version. | Read the current version and compare it with your intended change before submitting again. |
| `422 Unprocessable Content` | The service understood the content and its syntax. It could not carry out the requested instructions. | Read the validation details. A fictional export that asks for zero pages may need a valid page count. |
| `429 Too Many Requests` | The service applied a limit to the rate of requests. | Look for a `Retry-After` header. Follow the wait it specifies when present, then check whether the operation may be repeated. |
| `502 Bad Gateway` | The gateway received an invalid response from a service it called. | Record the gateway error and use the documented work status before repeating a request that can start another job. |
| `504 Gateway Timeout` | The gateway waited for another service and did not receive a reply in time. | Record the timeout. Check the work’s status before acting on an assumption about completion. |

An `If-Match` header expresses a condition about the current representation. A representation is the form in which the service sends a resource. For a paper exercise, suppose the draft you read has version A and the server now holds version B. Under the matching condition, a rejected update can report `412`.

A `Retry-After` value of `5` asks the client to wait at least five seconds. Draw a small timeline and count five seconds after the response. Use a second exercise card to show what a client might do when the service provides its own retry instructions.

## Read the same labels in a small C23 program

Save this as `status-practice.c` in a fresh practice folder. It asks Framework for each label. It uses an array, which is an ordered list of values, and a `for` loop to read them one at a time.

~~~c
#include "umicom/web/types.h"
#include <stdio.h>

int main(void)
{
    const int codes[] = {
        UMI_HTTP_STATUS_ACCEPTED,
        UMI_HTTP_STATUS_PRECONDITION_FAILED,
        UMI_HTTP_STATUS_UNPROCESSABLE_CONTENT,
        UMI_HTTP_STATUS_TOO_MANY_REQUESTS,
        UMI_HTTP_STATUS_BAD_GATEWAY,
        UMI_HTTP_STATUS_GATEWAY_TIMEOUT
    };

    /* The exercise calls the shared lookup with fictional status values. */
    for (size_t index = 0U; index < sizeof codes / sizeof codes[0]; ++index) {
        printf("%d %s\n", codes[index], umi_http_status_reason(codes[index]));
    }
    return 0;
}
~~~

If you have GCC with C23 support and the current Framework source, run these commands in PowerShell. The exercise makes a local function call that reads the registered labels. You can also predict the output from the table.

~~~powershell
$Framework = Read-Host 'Enter the full path to the Framework checkout'
gcc -std=c23 -Wall -Wextra -Werror -I "$Framework/include" status-practice.c "$Framework/src/web/types.c" -o status-practice.exe
if ($LASTEXITCODE -ne 0) { throw 'Compile failed. Check the source and Framework paths.' }
.\status-practice.exe
~~~

~~~text
202 Accepted
412 Precondition Failed
422 Unprocessable Content
429 Too Many Requests
502 Bad Gateway
504 Gateway Timeout
~~~

The label summarizes the code. Confirming a real job outcome requires evidence from the service that handles that job. The lookup provides the same descriptive words that you can compare with the registry.

## Follow a fictional request by hand

Draw a request card with the title `Practice book` and job label `demo-42`. Read one response card at a time. Trace the decision before writing any code.

~~~text
READ the numeric response code
IF the code is 202, RECORD the job as pending
IF the code is 412, READ the current version and check the condition
IF the code is 422, READ the validation details and review the input
IF the code is 429, CHECK Retry-After and record the wait
IF the code is 502 or 504, RECORD the gateway outcome
    and check work status before repeating the operation
~~~

Start with `202`. Later, suppose a separate status request receives `504`. Your paper record shows that the original job was accepted and that you have yet to confirm its final state. A Bits2Banking export or a synthetic Umicom TMS task can use this same evidence pattern.

[HTTP status code registry](https://www.iana.org/assignments/http-status-codes/http-status-codes.xhtml) · [HTTP status semantics](https://www.rfc-editor.org/rfc/rfc9110.html#section-15) · [HTTP/1.1 status lines](https://www.rfc-editor.org/rfc/rfc9112.html#section-4) · [Rate limit response](https://www.rfc-editor.org/rfc/rfc6585.html#section-4)

[Course contents](index.md) · [Previous lesson · Check export and download headers](48-check-export-and-download-headers.md) · [Related lesson · Read a FastCGI reply before forwarding](41-read-a-fastcgi-reply-before-forwarding.md) · [Related lesson · Understand capped request counters](46-understand-capped-request-counters.md) · [HTML edition](../../../courses/building-a-web-server-in-c/lessons/49-read-status-codes-before-deciding.html)
