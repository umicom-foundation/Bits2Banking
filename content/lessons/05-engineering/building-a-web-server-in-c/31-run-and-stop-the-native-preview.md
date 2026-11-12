<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/31-run-and-stop-the-native-preview.md

PURPOSE:
Run and stop the native preview command

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Run and stop the native preview command

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

## Inspect before starting

Run umicom preview with an absolute root, an explicit port and --dry-run. It checks the whole option vector, rejects duplicates and reports a plan. It does not verify that the port is free or the directory can be read. Remove --dry-run only when you intend to start the local server and keep its terminal open.

## Observe a real request

Open the printed address followed by /message.txt in a browser. The fixture root intentionally has no homepage. Compare the loaded text with the headless lab, then request a missing file. Record the chosen port, exact root and CLI build identity. A cache or a different server on another port can otherwise make the observation misleading.

## Stop through the owner

Press Ctrl+C in the server terminal. The signal handler only sets a small stop flag; ordinary control flow destroys the session after the current bounded exchange returns. The CLI distinguishes an ordinary timeout or disconnected client from a listener failure with no request progress, avoiding an endless loop of the same fatal failure.

## Recover without guessing

If startup fails, first inspect the reported status and whether another process owns the port. Choose a different explicit port when appropriate and update the URL too. Socket timeouts do not preempt a synchronous filesystem operation, so a stalled storage read can delay shutdown. Preserve that distinction when investigating an apparently slow stop.

## Review and recover

Preserve the exact source, SDK and output. Check package origin for compile/link failures, then distinguish 403, 404 and 413 responses from operation failures. A syntax-only plan, headless request and real browser each need separate evidence.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-static-preview/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-static-preview/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/preview.h)

[Course contents](index.md) · [Previous lesson](30-review-loopback-and-browser-admission.md) · [Next lesson](32-qualify-static-preview-in-layers.md)
