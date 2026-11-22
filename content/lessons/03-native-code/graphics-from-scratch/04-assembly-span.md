<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/graphics-from-scratch/04-assembly-span.md

PURPOSE:
Teach a portable C call boundary and the x86-64 leaf span routine.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Fill a span with x86-64 Assembly

[Previous: Export and verify a picture](03-export-and-verify.md) · [Course contents](index.md)

A span is a consecutive run of pixels on a single row. The C clipping code proves which span is inside the image before it passes the destination address, count and RGB value to the optional Assembly function. The Assembly routine performs the writes while the C code owns the image bounds.

## Follow three arguments into registers

An application binary interface, or ABI, specifies how compiled code passes data across functions. The two x86-64 builds use different argument registers.

| Argument | Windows x64 | System V AMD64 |
| --- | --- | --- |
| Address of first pixel | `RCX` | `RDI` |
| Number of pixels | `RDX` | `RSI` |
| 32-bit RGB value | `R8D` | `EDX` |

`span_x86_64.S` copies these inputs to shared working registers before the loop. It makes no other calls and changes only caller-saved registers. The same code after the entry block works on both builds. [Microsoft Windows x64 ABI](https://learn.microsoft.com/en-us/cpp/build/x64-calling-convention) · [System V AMD64 ABI](https://gitlab.com/x86-psABIs/x86-64-ABI)

1. Suppose the colour is `0x123456` and the count is 2.
2. The three stores produce bytes `12 34 56` in that order.
3. Advance the pointer by three bytes and subtract one from the count.
4. Repeat once, then return at zero. Six bytes have changed. Passing zero at entry returns before a store.

## Compare the two implementations

Create a second build directory with the same configure flags as the previous lesson and add `-DUMICOM_RASTER_ASSEMBLY=ON`. For example, replace `-B build/raster` with `-B build/raster-asm`. The option requires an x86-64 Linux or Windows toolchain with GNU-style Assembly. Run the build and CTest in that second directory. Create a second PPM and compare the files with PowerShell `Get-FileHash` or Linux `sha256sum`. Matching hashes establish that the two produced images are byte-identical for the example.

**Practice.** On paper, follow the addresses for destination 100 and count 2. The first pixel uses 100–102 and the second uses 103–105. A store at 106 would exceed the requested span.

If CMake rejects the target architecture or assembler, use the plain C build while reading the example. A correct Assembly version can still be slower than optimised C. To test speed later, benchmark both builds on the same machine, input and optimisation settings.

[Previous: Export a picture](03-export-and-verify.md) · [Course contents](index.md) · [Next: Call the C library from D](05-call-from-d.md)
