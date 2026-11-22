<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/graphics-from-scratch/index.md

PURPOSE:
Introduce the native graphics course and ordered lessons.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Build a 2D graphics library from scratch

A digital picture is a grid of small colour squares called pixels. This course starts with that grid and builds a small library that fills rectangles, draws lines and saves a picture. You can follow the explanations with pencil and paper. The practice work uses a C23 compiler and CMake.

1. [Build a pixel buffer and check its stride](01-pixels-and-stride.md)
2. [Clip rectangles and draw an integer line](02-clipped-shapes.md)
3. [Export and verify a picture](03-export-and-verify.md)
4. [Fill a span with x86-64 Assembly](04-assembly-span.md)
5. [Call the C library from D](05-call-from-d.md)
6. [Present a pixel buffer with GTK4](06-present-with-gtk4.md)

The course lab lives at `labs/graphics/raster-from-scratch/` in the Bits2Banking checkout. It includes a complete **C23** software rasterizer, an optional **x86-64 Assembly** fill routine, a **D** consumer and an optional **GTK4** texture adapter. A software rasterizer turns geometric shapes into ordinary memory bytes. You can use the core without a graphics driver or window system.

The example renders solid RGB pixels. Alpha blending, text shaping, GPU rendering and window management remain separate topics. The GTK4 adapter gives an existing host application a texture. The same C shapes and tests drive both the plain C and Assembly builds.

[Start with pixels and stride](01-pixels-and-stride.md) · [All lessons](../../index.md)
