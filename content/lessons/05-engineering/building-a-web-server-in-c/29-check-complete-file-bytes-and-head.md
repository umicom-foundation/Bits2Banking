<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/29-check-complete-file-bytes-and-head.md

PURPOSE:
Check complete file bytes and HEAD responses

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check complete file bytes and HEAD responses

## Prepare the exercise

Use a matching installed Framework SDK with the web component and preview.h. Run commands separately; stop on errors. Replace the example prefix with the installation you actually built. These exercises open no network port until you explicitly run the native preview command.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
cmake -S labs/native/framework-static-preview -B build/static-preview -G Ninja -DCMAKE_PREFIX_PATH=C:/umicom/installed/applications -DBUILD_TESTING=ON
cmake --build build/static-preview --parallel 2
ctest --test-dir build/static-preview --output-on-failure --no-tests=error
& ".\build\static-preview\btb-static-preview.exe" "C:\umicom\Umicom-Bits2Banking\labs\native\framework-static-preview\site" GET /message.txt
```

Six lab cases are expected. GET /message.txt should report HTTP 200 and fourteen representation bytes. Authored checks are not executed results. Use the laboratory README for the separate CLI and browser steps.

## Count the representation

The sample message contains fourteen bytes, including its LF newline. GET returns those bytes; HEAD describes the same representation without sending its body. The lab reports both representation size and serialized wire size. It prints a bounded hexadecimal prefix so a binary byte or terminal control character cannot be mistaken for ordinary display text.

## Respect the preview capacity

The shared response body holds a bounded complete file. The static service accepts at most 16,383 bytes and returns 413 for a larger file. It does not report a truncated read as a successful asset. HEAD still needs metadata consistent with the actual selected representation; it is not permission to ignore the service’s admission rules.

## Exercise

Compare GET and HEAD for message.txt, then inspect the six-case CMake check. Copy the site to a practice folder and change the text by one byte. Predict the new representation length before running. Restore the fixture after the experiment. Repository attributes preserve LF for the shipped sample so platform checkout conversion does not silently alter the expected size.

## Interpret the standard carefully

Read the linked HTTP semantics definition of HEAD. The absence of a wire body is distinct from an empty representation. This preview’s serializer owns Content-Length and Connection framing, so a handler should not add competing framing headers. Native writes and browser interpretation still require separate execution evidence.

Reference: [RFC 9110: HEAD semantics](https://www.rfc-editor.org/rfc/rfc9110.html#name-head).

## Review and recover

Preserve the exact source, SDK and output. Check package origin for compile/link failures, then distinguish 403, 404 and 413 responses from operation failures. A syntax-only plan, headless request and real browser each need separate evidence.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-static-preview/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-static-preview/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/preview.h)

[Course contents](index.md) · [Previous lesson](28-separate-http-status-from-operation-status.md) · [Next lesson](30-review-loopback-and-browser-admission.md)
