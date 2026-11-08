<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/26-decode-url-paths-once.md

PURPOSE:
Decode a URL path once and retain containment

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Decode a URL path once and retain containment

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

## URLs and filesystem names differ

A browser can encode a space as %20. The static-file service decodes one URL path into one relative filename, then asks rooted storage to enforce its own policy. It refuses separators hidden inside percent escapes. It also refuses traversal and ambiguous portable names instead of simplifying them into an apparently safe destination.

## Read the existing implementation

Locate StaticRelative in src/web/static_files.c. Follow the hexadecimal pair conversion, separator check and index.html selection. Then follow UmiRootedFileValidatePath and UmiRootedFileRead. The lab adds no second decoder or path join. This matters because independently implemented checks can disagree about the filename that finally reaches storage.

## Exercise

Copy the sample site to a separate practice directory and add a file named two words.txt. Request /two%20words.txt, then /%2e%2e/message.txt and /nested%2fnote.txt. Predict success for the ordinary name and refusal for the latter paths. Observe the returned status without attempting to weaken the rooted-file checks.

## Check the reasoning

Why not decode until there are no percent signs? A second decoding pass can give a previously literal filename a new interpretation. The existing decode-once test treats %252e%252e.txt as the literal filename %2e%2e.txt. Review that case alongside encoded traversal; similarity in printed text does not make the storage operations equivalent.

## Review and recover

Preserve the exact source, SDK and output. Check package origin for compile/link failures, then distinguish 403, 404 and 413 responses from operation failures. A syntax-only plan, headless request and real browser each need separate evidence.

[Read the C exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-static-preview/main.c) · [Full setup and native commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-static-preview/README.md) · [Shared contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/preview.h)

[Course contents](index.md) · [Previous lesson](25-select-a-static-document-root.md) · [Next lesson](27-own-the-preview-session.md)
