<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/30-review-loopback-and-browser-admission.md

PURPOSE:
Review loopback binding and browser admission

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Review loopback binding and browser admission

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

## Two independent boundaries

The preview listener binds only IPv4 127.0.0.1. The service also checks Host, Origin and available browser fetch metadata before reading a file. Binding controls the listening address; request admission controls which presented browser origin is accepted. Keeping both decisions in Framework lets headless exercises and native exchanges share the same policy.

## Follow a refusal

Read UmiWebLoopbackRequestGate. A valid Host names localhost or 127.0.0.1 with the selected port. An Origin, when present, must match that HTTP origin; duplicate headers and unrelated origins are refused. The composed service runs this gate before the static fallback. No CORS grant is added to make unrelated sites pass.

## Exercise

Inspect the foreign-host, foreign-origin, same-origin and duplicate-host cases in test_preview.c. Each exercises the real composed service without sockets. Change only one request field in a separate practice copy and predict whether the response should become 403. Do not infer browser behavior solely from a manually constructed parsed request.

## Keep the claim narrow

These headers are not user credentials. Another local process can construct allowed values, so the preview provides no account authorization or sandbox. Select only an intended export directory. A public server would require a separate reviewed transport, authentication, authorization and operational design; removing the loopback check does not supply those capabilities.

## Review and recover

Preserve the exact source, SDK and output. Check package origin for compile/link failures, then distinguish 403, 404 and 413 responses from operation failures. A syntax-only plan, headless request and real browser each need separate evidence.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-static-preview/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-static-preview/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/preview.h)

[Course contents](index.md) · [Previous lesson](29-check-complete-file-bytes-and-head.md) · [Next lesson](31-run-and-stop-the-native-preview.md)
