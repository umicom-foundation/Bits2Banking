<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/32-qualify-static-preview-in-layers.md

PURPOSE:
Qualify a static preview in separate layers

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Qualify a static preview in separate layers

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

## Start with the smallest observation

The six installed-SDK lab cases check parsed requests, rooted file responses and serialization. Framework service tests add copied roots, browser admission and invalid arguments. Controlled CLI tests replace only session and signal boundaries, making option admission and cleanup observable without opening a port. Each layer answers a different question.

## Then use the actual executable

Native-entry checks pass a Unicode root through the real command process in dry-run mode. This checks argument capture and presentation while leaving storage and sockets untouched. The next manual step starts the matching CLI, loads the selected asset in a browser and stops it. A successful dry-run cannot substitute for those later observations.

## Exercise

Prepare a small qualification record containing source revisions, SDK prefix, compiler, operating system, root, port, commands and actual results. Add separate rows for unexecuted and skipped checks. Run the installed lab from a working directory outside the source tree to expose accidental current-directory dependencies, using the absolute fixture root in every invocation.

## Choose the next development step

After local static previews, further work can address application input policy, concurrency, reviewed TLS integration and remote deployment. Reuse existing Framework capabilities before introducing new protocol code. Keep the current single-request, bounded-file and local-host restrictions explicit; a larger course or a larger test count does not establish production readiness.

## Review and recover

Preserve the exact source, SDK and output. Check package origin for compile/link failures, then distinguish 403, 404 and 413 responses from operation failures. A syntax-only plan, headless request and real browser each need separate evidence.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-static-preview/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-static-preview/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/preview.h)

[Course contents](index.md) · [Previous lesson](31-run-and-stop-the-native-preview.md)
