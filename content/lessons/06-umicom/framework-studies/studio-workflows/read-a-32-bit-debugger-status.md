![Umicom](../../../../assets/branding/umicom-wordmark.svg)

[Umicom icon](../../../../assets/branding/umicom.ico)

# Read a 32-bit debugger status

The same 32 bits can appear three different ways in build evidence. A Windows debugger startup log can show hexadecimal, a signed decimal number, or an unsigned decimal number. The bits underneath the spelling stay the same.

In the lab, the hexadecimal word 0xc0000135 appears as 3221225781 unsigned and -1073741515 signed. Windows names this status STATUS_DLL_NOT_FOUND. It indicates that the loader could not locate a required component. The number does not name the specific DLL. Compare the saved startup output and the executable’s dependencies before changing the toolchain.

## Reproduce the number in C23

1. Open PowerShell in the Bits2Banking repository and configure `labs/framework/studio-build-evidence` as shown in the lab README.
2. Build the `umicom-lab-status32` target. Run the named `bits.studio.status32` tests.
3. Read `status32.c`. When the unsigned value is higher than the largest signed 32-bit integer, it subtracts 2^32 in a wider signed variable. Explain why the calculation gives a negative result.
4. Compare the zero and overflow cases. Zero is a valid status word. A decimal value above 4294967295 exceeds the width and produces the exact refusal.

The three equivalent examples print the same line. A bad number yields exit 3 and no numeric report. An output failure yields exit 1. The lab performs arithmetic on text you supply and does not start a debugger.

If your result has a different width, confirm that you are comparing a 32-bit status and remove any extra characters before entering it. If a real debugger probe recorded this status, use its saved transcript to find the selected executable and its runtime requirements.

[Windows NTSTATUS values](https://learn.microsoft.com/en-us/openspecs/windows_protocols/ms-erref/596a1078-e883-4972-9bbc-49e60bebca55)

[Previous lesson](compare-a-recorded-artifact-identity.md) · [HTML edition](../../../../courses/framework-and-finance/studio-workflows/lessons/read-a-32-bit-debugger-status.html)

[Next lesson · Read incomplete CTest console results](read-incomplete-ctest-console-results.md)
