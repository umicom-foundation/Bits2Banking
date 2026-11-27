<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-web-servers/13-set-a-message-for-a-missing-page.md

PURPOSE:
Use a familiar page layout to explain a missing route and keep the HTTP status visible.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for the original lesson. Linked references retain their own terms.
-->

# Set a message for a missing page

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg)

A missing page should tell the reader what happened and where to go next. The server can send that message with HTTP 404. Start with the approved logo, icon and stylesheet from your [first website](01-make-a-page-and-stylesheet.md), then reuse those files for the missing-page message.

## 1. Make a page from your existing layout

Open PowerShell 7 in the practice website folder. Type `Get-ChildItem index.html` to confirm that you are in the right place. If you already have `missing.html`, open it and check its content before making changes. Otherwise, make a copy.

```powershell
Copy-Item -LiteralPath index.html -Destination missing.html
```

Open `missing.html` in your editor. Change its title and main heading to `Page not found`. Put a short explanation and a link to the start page under the heading. Keep the existing logo, icon and stylesheet references. The original `index.html` still supplies your home page.

## 2. Check your root with the Umicom Framework example

If you have built the local C example, set `$webExample` to its full path. Keep this terminal in your practice website folder.

```powershell
$siteRoot = (Get-Location).Path
$webExample = 'C:\tools\umicom-web-local-service-example.exe'
& $webExample --port 8080 --root $siteRoot --not-found-page /missing.html --check-routes
```

The command should report that the rooted route and browser admission checks passed in memory. This checks the selected root before listening. Run the last line again with `--check-routes` omitted to start the example on your own computer.

## 3. Check the missing request

Open a second PowerShell window. Use a name you know is absent from the practice folder.

```powershell
$reply = Invoke-WebRequest -SkipHttpErrorCheck 'http://127.0.0.1:8080/not-here.html'
$reply.StatusCode
$reply.Content
```

Look for `404` and the message you wrote. Next, open `http://127.0.0.1:8080/` in your browser. It should still display the original home page. Press Ctrl+C in the first window when you finish.

## 4. Find the equivalent Apache setting

Apache HTTP Server can use `ErrorDocument 404 /missing.html` in a practice site configuration. The path starts at that site's document root. Keep the chosen file in the site you are testing. Use the [Apache configuration check](09-check-an-apache-configuration-copy.md) to validate the practice copy, then compare the two results as separate questions. Which status did the server return, and which page did it show?

If the Umicom example shows its standard text, check the option and the filename in the selected root. If the option is missing from `--help`, check that the example was built from source that provides the error-page option.

[Previous lesson](12-reuse-a-response-with-an-etag.md) · [Next lesson](14-run-a-separate-local-tomcat-instance.md) · [Course index](index.md) · [Apache ErrorDocument reference](https://github.com/apache/httpd/blob/2.4.x/docs/manual/custom-error.xml)
