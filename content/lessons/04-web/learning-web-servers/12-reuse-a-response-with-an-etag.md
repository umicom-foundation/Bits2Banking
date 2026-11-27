<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-web-servers/12-reuse-a-response-with-an-etag.md

PURPOSE:
Read a saved entity tag and decide whether the client can reuse its existing copy.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for the original lesson. Linked references retain their own terms.
-->

# Reuse a response with an ETag

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg)

You requested a reading and kept a copy. Later, the client can ask whether it still has the right version. An ETag is a label for the selected version of the response. This exercise uses three short practice files in PowerShell. You can finish it without running a server.

If HTTP requests and headers are new to you, start with [Read an HTTP request and response](02-read-an-http-exchange.md).

## 1. Save the response and its tag

```powershell
@'
HTTP/1.1 200 OK
Content-Type: text/plain
ETag: "reading-42"

Reading: 42
'@ | Set-Content -LiteralPath response-200.txt
Select-String -LiteralPath response-200.txt -SimpleMatch 'ETag:'
```

You should see `ETag: "reading-42"`. The blank line separates the headers from the body. The body contains `Reading: 42`. Keep this file for the next steps.

## 2. Ask whether the reading has changed

```powershell
@'
GET /reading HTTP/1.1
Host: localhost
If-None-Match: "reading-42"

'@ | Set-Content -LiteralPath request-with-tag.txt
Get-Content -LiteralPath request-with-tag.txt
```

`If-None-Match` sends the saved label with the new GET request. In this practice example the current reading still has the same tag.

## 3. Compare a 304 with the saved 200

```powershell
@'
HTTP/1.1 304 Not Modified
ETag: "reading-42"

'@ | Set-Content -LiteralPath response-304.txt
Get-Content -LiteralPath response-304.txt -TotalCount 1
Select-String -LiteralPath response-200.txt -SimpleMatch 'Reading:'
```

You should see `HTTP/1.1 304 Not Modified` and then the reading from the **saved** 200 response. A 304 has no response body. The client may use the stored response for the same resource. If the server sends a fresh 200 because the selected representation has changed, the client reads the new body and remembers the new tag.

## 4. Apply the check to a real workflow

When you later compare a native C23 route and a deployed Java route, record the first response status and tag, the conditional request, and the second response status. Check the response body separately. A response reporting 304 should have no body even if some headers describe the existing representation. The ETag applies to the selected representation of the requested resource.

If your sample search shows nothing, first confirm the practice file names with `Get-ChildItem response-*.txt`. Then reopen the first file and check the line that starts with `ETag:`. Copy the same label including its quotation marks.

[Previous lesson](11-follow-a-request-in-an-access-log.md) · [Native C23 route](06-compare-a-native-c-web-service.md) · [Course index](index.md) · [HTTP 304 reference](https://www.rfc-editor.org/rfc/rfc9110.html#section-15.4.5)
