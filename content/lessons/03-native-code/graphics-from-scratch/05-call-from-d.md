<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/graphics-from-scratch/05-call-from-d.md

PURPOSE:
Explain D-to-C ownership and demonstrate an extern(C) client.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Call the C library from D

[Previous: Fill a span with x86-64 Assembly](04-assembly-span.md) · [Course contents](index.md)

Two languages can use one graphics library when they agree on function names, argument types and how a record is laid out in memory. The D sample owns a byte array and calls the C functions through `extern(C)`. The drawing code stays in the same C23 library. [D language specification for C interoperability](https://dlang.org/spec/interfaceToC.html)

## Compare the boundary types

| What crosses the boundary | C | D on the same target |
| --- | --- | --- |
| Address of first image byte | `unsigned char *` | `ubyte*` |
| Length in bytes | `size_t` | `size_t` |
| Dimension | `uint32_t` | `uint` |
| Signed position | `int32_t` | `int` |
| File path used by a C function | `const char *` | `const(char)*` from a zero-terminated string |

The order of the `UmicomRaster` fields matches the C header. The complete sample is `labs/graphics/raster-from-scratch/consumer.d`. The `toStringz` function gives the C exporter an address it can read until a zero byte. The exporter uses that string during the call. The D function keeps its fixed-size array alive through every drawing and export call.

## Build the caller

On Linux, first build the plain C project as shown in the export lesson. With LDC installed and targeting the same architecture as the C build, run these commands from the repository root.

```bash
ldc2 labs/graphics/raster-from-scratch/consumer.d build/raster/libumicom_raster.a -of=build/raster/umicom-raster-d
./build/raster/umicom-raster-d ./build/raster/from-d.ppm
```

The executable should print `Wrote a 32 x 24 RGB image through the C ABI.` The output is intentionally a different scene from the C example. Read its header to verify the width and height. Choose a new output name if the file already exists.

**Diagnose.** If the linker cannot find `umicom_raster_bind`, check that the C library archive is present, that both compilers target the same object format and architecture and that the D declaration uses `extern(C)`. If the call links but draws in the wrong place, compare the layout of every field before changing the raster algorithm.

**Practice.** Change the D caller's blue rectangle to start at `x = -5`. The left five requested columns fall outside the image. The same C clipping tests explain how the visible part is drawn.

[Previous: Assembly spans](04-assembly-span.md) · [Course contents](index.md) · [Next: Present a pixel buffer with GTK4](06-present-with-gtk4.md)
