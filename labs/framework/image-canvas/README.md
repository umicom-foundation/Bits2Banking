# Put an image on an explicit canvas

![Umicom](../../../content/assets/branding/umicom-wordmark.svg)

This C23 program calls Framework canvas, histogram and tensor services. It places two white pixels on a 4 × 3 black canvas, checks the ten border pixels, and proves that black becomes -1 in signed-unit tensor conversion. It also checks that insufficient output capacity leaves the previous canvas unchanged. No model, decoder, remote provider or image-file writer is involved.

## Build and inspect

From the Bits2Banking repository, run each command separately and stop on errors:

```powershell
cmake -S labs/framework/image-canvas -B build/image-canvas -G Ninja -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/image-canvas --parallel 2
ctest --test-dir build/image-canvas --output-on-failure
& .\build\image-canvas\umicom-image-canvas.exe
```

The matching Framework checkout supplies the implementation. The laboratory does not clone it or copy its algorithms into application code. Windows branding is applied through the existing Framework helper and approved ICO asset. This source composition is a teaching workflow; it does not validate an installed SDK package.

Expected output:

```text
Canvas: 12 pixels, red bin 0=10, red bin 255=2
Black border becomes -1 in the signed-unit tensor, not a loss mask.
A short output span was refused; the previous canvas is unchanged.
```

Read [the complete lesson](../../../content/courses/generative-ai-foundations/lessons/26-place-an-image-on-a-canvas-without-confusing-padding-and-masks.html) before changing dimensions, normalization or annotations. A loss mask is separate data with its own model contract.
