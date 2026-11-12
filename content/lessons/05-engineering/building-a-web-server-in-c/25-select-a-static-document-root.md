<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/25-select-a-static-document-root.md

PURPOSE:
Select a root for static files

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Select a root for static files

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

## A root is a content decision

A static server maps a URL to a file below a chosen directory. That directory defines what ordinary files are available, so use a dedicated export folder. The sample site contains message.txt and a nested note. It contains no index.html; a request for the slash path therefore produces 404 rather than an automatic listing.

## Follow the owning service

Read UmiWebPreviewCreate and umi_web_static_files_init in Framework. Creation checks an absolute portable path and copies it into the preview owner. It does not open a listener or prove that a file exists. Later reads use rooted-file operations. Changing the caller’s original string cannot change the root captured by an existing session.

## Exercise

Run the lab for GET /message.txt and GET /nested/note.txt. Draw the selected root and the two relative paths. Then pass a relative root such as site and predict the admission error. Keep the current directory unchanged: the point is to demonstrate that an explicit root, rather than hidden working-directory state, chooses the content.

## Explain the limit

Does a valid root mean all files can be served? No. A file can be absent, too large, denied or unreadable. Root syntax admission and actual storage access are separate observations. Record which operation failed before changing path policy or copying files into a different directory.

## Review and recover

Preserve the exact source, SDK and output. Check package origin for compile/link failures, then distinguish 403, 404 and 413 responses from operation failures. A syntax-only plan, headless request and real browser each need separate evidence.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-static-preview/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-static-preview/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/preview.h)

[Course contents](index.md) · [Previous lesson](24-qualify-a-local-c-web-workflow.md) · [Next lesson](26-decode-url-paths-once.md)
