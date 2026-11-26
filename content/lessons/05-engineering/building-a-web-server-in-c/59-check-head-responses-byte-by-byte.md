<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-web-server-in-c/59-check-head-responses-byte-by-byte.md

PURPOSE:
Check HEAD responses byte by byte

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Check HEAD responses byte by byte

Receiving a line with a length value tells you what the worker reported. To confirm what the HTTP client actually received, examine the bytes after the blank line following the headers. In a HEAD response that blank line is the end of the response.

## Run the offline C23 lab

Open PowerShell in the Bits2Banking repository. Use a C23-capable compiler already configured for CMake. The lab builds an offline fixture and uses no listener or worker.

```powershell
cmake -S .\labs\framework\fastcgi-head-review -B .\build\fastcgi-head-review -G Ninja
cmake --build .\build\fastcgi-head-review
ctest --test-dir .\build\fastcgi-head-review --no-tests=error --output-on-failure
```

The fixtures compare whole byte sequences. One explicitly reports zero, one reports 42, and another has only the common headers. A fourth supplies a discarded worker document. The final two cases check refusal of an oversized length and an undersized destination with no partial output.

## Make a prediction before changing the example

1. In the test file, find the fixture with an unspecified length. Predict what happens if you make it a known length of zero while keeping the expected response unchanged.
2. Change only the input and run the focused test again. It should fail because a zero length header is now present.
3. Keep your change in a practice copy. Update its expected response to show the zero length, rerun the test, and compare the two outputs.

If CMake cannot detect a C23 compiler, check which C compiler your configured toolchain selects. If only the exact-byte test fails, display the expected and actual strings side by side. Check the CR and LF line endings and stop at the blank line.

The full Framework service checks worker reply framing and handles transport separately. In your own project, use the Framework FastCGI bridge and inspect the HTTP response through the existing native connector fixture. The exercise above isolates the difference between representation length and transmitted bytes.

[Course contents](index.md) · [Previous lesson · Keep HEAD metadata separate from content](58-keep-head-metadata-separate-from-content.md) · [HTML edition](../../../courses/building-a-web-server-in-c/lessons/59-check-head-responses-byte-by-byte.html)
