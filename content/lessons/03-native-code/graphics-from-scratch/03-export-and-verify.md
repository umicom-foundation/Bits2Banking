<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/graphics-from-scratch/03-export-and-verify.md

PURPOSE:
Build, run and independently verify a binary PPM export.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Export and verify a picture

[Previous: Clip rectangles and draw an integer line](02-clipped-shapes.md) · [Course contents](index.md)

A PPM image stores a short description followed by pixels. The binary `P6` form gives us a repeatable way to inspect the output without opening a window. The sample writes the format identifier, the width and height, a maximum channel value of 255, and then RGB bytes row by row. Each row starts at its stride offset and only its visible bytes are saved. [Netpbm PPM format](https://netpbm.sourceforge.net/doc/ppm.html)

## Build the practice project

Open PowerShell in the Bits2Banking checkout. Use a compiler that supports C23. For Windows UCRT64, set its bin directory on the local shell PATH and give CMake the matching Framework checkout for the approved application icon.

```powershell
$env:Path = "C:/msys64/ucrt64/bin;$env:Path"
cmake -S labs/graphics/raster-from-scratch -B build/raster -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/raster
ctest --test-dir build/raster --output-on-failure --no-tests=error
& .\build\raster\umicom-raster-example.exe .\build\raster\practice.ppm
```

On Linux with C23 GCC or Clang, run the same CMake steps without either Windows-specific `-D` option. Run `./build/raster/umicom-raster-example ./build/raster/practice.ppm`.

## Predict the result

1. Expect two successful tests. One checks memory and geometric boundaries. The other checks the example's actual image bytes and its response to an existing output path.
2. The example prints `Wrote an 80 x 48 RGB image.` The picture contains a darker background, two rectangles and a white line.
3. Calculate the byte count. The visible pixels take `80 × 48 × 3 = 11520` bytes. The header takes 13, giving 11,533 bytes.
4. Run the example again with the same filename. It should refuse the existing output and leave its bytes unchanged. To create a second image, choose a fresh filename in the build folder.

If an image viewer cannot decode PPM, use a viewer that supports `P6` or inspect the first bytes with `Format-Hex` on Windows. A second output attempt normally fails by design. If the first attempt fails, check that the output directory exists, that you can write there and that the selected name is new.

**Practice.** Change the example's background colour in `main.c`, rebuild and save a new image. Update the expected background in `check_ppm.cmake` if you want this to be the new example contract. The old test should otherwise catch your intentional change.

[Previous: Clipped shapes](02-clipped-shapes.md) · [Course contents](index.md) · [Next: Fill a span with x86-64 Assembly](04-assembly-span.md)
