<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/27-own-the-preview-session.md

PURPOSE:
Own the preview session and its borrowed contexts

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Own the preview session and its borrowed contexts

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

## Separate construction from listening

UmiWebPreviewCreate allocates the owner, copies the root and configures a service. UmiWebPreviewStart separately opens the listener. This separation lets a headless client inspect behavior without a port and lets a graphical caller prepare state before scheduling worker activity. The CLI dry-run goes further: it validates syntax without constructing a session.

## Follow the references

The router borrows a pointer to the embedded static-file descriptor. The request gate borrows a pointer to the embedded port configuration. The server borrows the service. Those references remain valid because their storage belongs to the same preview object. Destroy releases the server first, then the service, then the object holding the contexts.

## Exercise

Draw an ownership arrow for every allocation and a different arrow for each borrowed pointer. Read the copied-root test, which changes the caller’s path buffer after creation. Explain why a later request still reads the original directory. Then identify which public operations require a single owner thread and which cancellation operation may come from elsewhere.

## Avoid an invalid extension

Do not keep a service pointer after destroying its preview or move the embedded descriptor into a temporary stack scope. A new asynchronous frontend must keep the preview alive until its worker returns. A stop request is not proof that a file handler has finished; destruction must follow actual completion.

## Review and recover

Preserve the exact source, SDK and output. Check package origin for compile/link failures, then distinguish 403, 404 and 413 responses from operation failures. A syntax-only plan, headless request and real browser each need separate evidence.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-static-preview/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-static-preview/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/preview.h)

[Course contents](index.md) · [Previous lesson](26-decode-url-paths-once.md) · [Next lesson](28-separate-http-status-from-operation-status.md)
