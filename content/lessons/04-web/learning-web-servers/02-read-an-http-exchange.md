<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-web-servers/02-read-an-http-exchange.md

PURPOSE:
Identify HTTP request and response fields and compare GET, HEAD and missing resources.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Read an HTTP request and response

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="220" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="220" }

An address beginning with `http:` asks a server for something. Opening the website file from the previous lesson worked directly from disk. After Apache is running, use the same page to see what changes when the browser asks a server.

## Read a request

Look at `http://127.0.0.1:8180/index.html`. The address `127.0.0.1` points back to your own computer. The server listens on port `8180`. The path `/index.html` identifies what to request.

Here is a small HTTP/1.1 request. `GET` asks for the selected content. The `Host` line identifies the intended server, and the empty line ends the headers.

```http
GET /index.html HTTP/1.1
Host: 127.0.0.1:8180

```

The first line of a response gives the HTTP version and status. Headers follow it. The body, when present, comes after a blank line.

```http
HTTP/1.1 200 OK
Content-Type: text/html

<!doctype html>
...
```

The response is abbreviated. A real server can send additional headers. `Content-Type` tells the browser that these bytes represent HTML. The page asks for the stylesheet, wordmark and icon with their own requests.

## Check three paths

First [start the local Apache exercise](03-serve-files-with-apache-http-server.md). Then run these commands in another PowerShell window.

```powershell
curl.exe -i http://127.0.0.1:8180/index.html
curl.exe -I http://127.0.0.1:8180/site.css
curl.exe -i http://127.0.0.1:8180/missing.html
```

| Command | What to look for |
| --- | --- |
| `-i` on `/index.html` | Status `200`, an HTML content type and the page body |
| `-I` on `/site.css` | Status `200` and content type `text/css`, followed by the end of the response |
| `-i` on `/missing.html` | Status `404`, typically with an HTML page describing the missing resource |

The lower-case `-i` includes response headers with a GET. Upper-case `-I` sends HEAD and displays the headers. A `404` response means a server answered. A connection error means you have no HTTP response to read, so first check the listener and the port.

For the browser view, open the developer tools, choose **Network** and reload the page. Select one line for `index.html` and one for `site.css`. Identify the path, status and type on both lines. Cached files might be marked differently. Use the curl checks for a fresh observation.

[HTTP methods and semantics](https://www.rfc-editor.org/rfc/rfc9110.html) · [HTTP/1.1 message syntax](https://www.rfc-editor.org/rfc/rfc9112.html)

[Previous, make a page](01-make-a-page-and-stylesheet.md) · [Course](index.md) · [Next, serve files with Apache](03-serve-files-with-apache-http-server.md)
