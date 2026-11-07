<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-html/10-relative-resources-and-http.md

PURPOSE:
Explain the lesson: Resolve relative resources over HTTP.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Resolve relative resources over HTTP

## Prepare the server
Build the browser activity example using its README. From the Bits2Banking checkout, an already-installed PHP interpreter can serve this folder:
~~~powershell
php -S 127.0.0.1:8088 -t labs/web/framework-activity
~~~
Open `http://127.0.0.1:8088/`. The same command works in Bash. Stop the server with Ctrl+C. This is a local learning server, not a public deployment recipe.

A **relative URL** is resolved against the current document or module's location. The page loads `./page.js`; that module imports `./activity.js`.

## Follow a request
1. Inspect the page's script element.
2. Find `type="module"`.
3. Open the browser Network panel.
4. Reload and locate the JavaScript and WebAssembly requests.
5. Check their status and response type.

A server can return an HTML error page under a filename ending in `.js`. The spelling alone does not make the content executable JavaScript.

## Exercise
Draw a folder containing `index.html`, `page.js`, generated `activity.js` and its generated WebAssembly companion. Label which files are authored and which are build outputs.

Expected conclusion: copying only the HTML cannot carry the entire interactive application. Keep generated outputs together when running the lab, and do not mistake them for source changes to commit.

## Diagnose
Opening a file directly with a `file:` URL may encounter module-loading restrictions. Use the documented HTTP route before changing the source. If one request fails, verify its exact resolved URL and server root. A correct relative path depends on where the server exposes the folder.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/web/framework-activity/index.html). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](09-status-messages-and-page-language.md)

