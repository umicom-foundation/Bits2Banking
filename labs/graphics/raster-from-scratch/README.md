<!--
Umicom Bits2Banking
File: labs/graphics/raster-from-scratch/README.md

PURPOSE:
Guide learners through the native raster, assembly, D and GTK4 examples.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

# Native raster laboratory

The [graphics course](../../../content/lessons/03-native-code/graphics-from-scratch/index.md) explains each stage. `raster.h` documents the library contract. `raster.c` implements a bounded RGB surface, clipped shapes and the P6 exporter. Your program owns the pixel buffer. If you use it in an existing GTK4 host, the texture adapter snapshots the visible RGB samples for presentation.

1. From the Bits2Banking checkout, configure and build with CMake and a C23 compiler. Use the following PowerShell sequence on Windows with UCRT64. Run each command separately and stop on an error.

   ```powershell
   $env:Path = "C:/msys64/ucrt64/bin;$env:Path"
   cmake -S labs/graphics/raster-from-scratch -B build/raster -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
   cmake --build build/raster
   ctest --test-dir build/raster --output-on-failure --no-tests=error
   & .\build\raster\umicom-raster-example.exe .\build\raster\practice.ppm
   ```

2. Expect an 80 × 48 image with a dark background, two rectangles and a white line. Choose a new output filename for another run. The exporter protects an existing file. The tests cover clipped and extreme coordinates, buffer padding, PPM bytes and the refusal to overwrite a file.
3. Try a separate build with `-DUMICOM_RASTER_ASSEMBLY=ON` on Windows x64 or Linux x86-64 with a GNU-style assembler. Both raster tests should still pass. Compare the two sample images by SHA-256. This checks output equivalence for the sample scene.
4. To use the library from D on Linux, follow the [C ABI lesson](../../../content/lessons/03-native-code/graphics-from-scratch/05-call-from-d.md). On Linux use the build commands without the two Windows-specific configure flags. The D source is a client of the same C library.
5. If GTK4 headers and `pkg-config` are installed, enable `-DUMICOM_RASTER_GTK4_BRIDGE=ON` in a separate build directory. The bridge builds as a static library. The [GTK4 lesson](../../../content/lessons/03-native-code/graphics-from-scratch/06-present-with-gtk4.md) shows how an existing host can use its texture. The lab creates no window.

If CMake cannot find Windows branding, check the Framework path. If the worked example cannot save its image, check that the directory exists and your filename is new. The lecture and tests can be followed without the optional D compiler or GTK4 toolchain.

[Umicom SVG icon](../../../content/assets/branding/umicom-icon.svg) · [Umicom Windows icon](../../../content/assets/branding/umicom.ico)
