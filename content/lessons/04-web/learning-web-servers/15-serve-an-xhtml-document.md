<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-web-servers/15-serve-an-xhtml-document.md

PURPOSE:
Check the published media type and length of an ordinary XHTML document.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

# Serve an XHTML document

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="220" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="220" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" width="28" alt="Umicom icon"></a>

An XHTML page uses XML syntax to describe a web document. The server sends a media type in its HTTP headers so the browser knows how to read the file. Save a small document and check the headers yourself.

Start with the practice site from [Make a web page and its stylesheet](01-make-a-page-and-stylesheet.md). That folder has an `index.html`, the approved SVG logo and the Umicom icon. Use PowerShell 7 and a built Umicom Framework local service example.

## 1. Save one well-formed page

Save this file as `review.xhtml` next to `index.html`. Choose UTF-8 in your editor.

```xml
<?xml version="1.0" encoding="UTF-8"?>
<html xmlns="http://www.w3.org/1999/xhtml" lang="en">
  <head>
    <title>Statement review</title>
    <link rel="icon" href="umicom.ico" />
  </head>
  <body>
    <img src="umicom-wordmark.svg" width="220" alt="Umicom Foundation" />
    <h1>Statement review</h1>
    <p>Two entries are ready for review.</p>
  </body>
</html>
```

The `xmlns` value identifies the HTML vocabulary. The final `/` on `link` and `img` closes those elements. Each other opening tag has a matching closing tag. The browser can reject XML when a tag is left unclosed.

## 2. Check the root before starting the local example

Replace the executable path with the path to your build. Keep this window in your practice site folder.

```powershell
$siteRoot = (Get-Location).Path
$webExample = 'C:/tools/umicom-web-local-service-example.exe'
& $webExample --port 8093 --root $siteRoot --check-routes
```

Once the rooted route check succeeds, use the same command without `--check-routes` to start the server on your own computer.

```powershell
& $webExample --port 8093 --root $siteRoot
```

## 3. Read the response headers

Open a second PowerShell window and make one HEAD request and one GET request.

```powershell
curl.exe -I http://127.0.0.1:8093/review.xhtml
curl.exe -i http://127.0.0.1:8093/review.xhtml
```

Look for HTTP 200 and `Content-Type: application/xhtml+xml` in both responses. HEAD shows headers without the document body. GET includes the XML you saved. Open the GET address in a browser to see the page. The logo is in the page and the icon is for the browser tab. Press Ctrl+C in the first window when you finish.

If you see 404, check the file's name and the site folder. If you see `application/octet-stream`, check the suffix and verify that your local example was built from the source that supports XHTML.

## 4. Find the equivalent setting in Apache

In a practice Apache configuration using `mod_mime`, this rule associates both recognised filename endings with the same HTTP media type.

```apache
AddType application/xhtml+xml .xhtml .xht
```

Follow [Check an Apache configuration copy](09-check-an-apache-configuration-copy.md) to check the new setting. After starting that practice site, compare its `Content-Type` with the Umicom example. The file chosen and the header returned are two observations you can check independently. [IANA XHTML registration](https://www.iana.org/assignments/media-types/application/xhtml+xml) · [Apache AddType reference](https://github.com/apache/httpd/blob/2.4.x/docs/manual/mod/mod_mime.xml)

[Previous lesson](14-run-a-separate-local-tomcat-instance.md) · [Next lesson](16-send-a-read-only-choice-with-a-form.md) · [Course index](index.md) · [Web development in simple steps](../../../simple-steps/course-guides/web-development-and-servers.md)
