<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/28-separate-http-status-from-operation-status.md

PURPOSE:
Separate an HTTP refusal from an operation failure

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Separate an HTTP refusal from an operation failure

## Prepare the exercise

Use a matching installed Framework SDK with the web component and preview.h. Run commands separately; stop on errors. Replace the example prefix with the installation you actually built. These exercises open no network port until you explicitly run the native preview command.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
cmake -S labs/native/framework-static-preview -B build/static-preview -G Ninja -DCMAKE_PREFIX_PATH=C:/umicom/installed/applications -DBUILD_TESTING=ON
cmake --build build/static-preview --parallel 2
ctest --test-dir build/static-preview --output-on-failure --no-tests=error
& ".\build\static-preview\btb-static-preview.exe" "C:\umicom\Umicom-Bits2Banking\labs\native\framework-static-preview\site" GET /message.txt
```

<!-- Earlier inline-only lab guidance is retained for review; the active explanation includes owned assets and explicit evidence boundaries.
Six lab cases are expected. GET /message.txt should report HTTP 200 and fourteen representation bytes. Authored checks are not executed results. Use the laboratory README for the separate CLI and browser steps.
-->
Eleven lab cases are authored. GET /message.txt should describe HTTP 200 and fourteen representation bytes. The optional --owned mode also checks approved SVG and ICO assets from the installed SDK; the original inline command remains available. Reported wire sizes are inspection results, not bytes delivered to a peer. Use the laboratory README for qualification and the separate CLI and browser steps.

## Two results answer different questions

The C status reports whether Framework could perform the requested operation. The HTTP status describes the response sent to the client. A missing asset can therefore produce UMI_STATUS_OK with HTTP 404: the server successfully constructed a deliberate refusal. The lab returns zero for that completed inspection while printing the HTTP status clearly.

## Trace the paths

Follow missing file, traversal and POST requests. Static-file handling produces 404, 403 and 405 respectively. Unsupported request framing or storage failures can instead produce a nonzero C status. In native exchanges, a response may be partly sent before transport failure. Neither a handler call nor an HTTP status alone proves complete delivery.

## Exercise

<!-- Earlier inline-only lab guidance is retained for review; the active explanation includes owned assets and explicit evidence boundaries.
Run all six lab cases and build a table with C process exit, printed HTTP status and body-sent field. Add a malformed request method in a practice invocation and compare its operational failure. Explain why changing the program to return failure for every 4xx response would change the meaning of the existing refusal tests.
-->
Run the eleven authored lab cases and build a table with C process exit, printed HTTP status, selected inline or owned mode and planned body output. The historical body-sent label describes serialization; the added transport line confirms that this inspection client sends nothing to a peer. Add a malformed request method in a practice invocation and compare its operational failure. Explain why returning failure for every 4xx response would change the meaning of the refusal tests.

## Write a precise report

State that a particular request produced the expected refusal when that is what was checked. Do not call a deliberate 403 a broken server, and do not call every zero exit a successful user operation. In a product, map both layers to useful messages while preserving enough evidence to diagnose the original failure.

## Review and recover

Preserve the exact source, SDK and output. Check package origin for compile/link failures, then distinguish 403, 404 and 413 responses from operation failures. A syntax-only plan, headless request and real browser each need separate evidence.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-static-preview/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-static-preview/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/preview.h)

[Course contents](index.md) · [Previous lesson](27-own-the-preview-session.md) · [Next lesson](29-check-complete-file-bytes-and-head.md)
