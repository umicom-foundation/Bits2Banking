<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/graphics-from-scratch/01-pixels-and-stride.md

PURPOSE:
Teach RGB byte order, row stride and caller-owned buffer admission.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Build a pixel buffer and check its stride

[Course contents](index.md)

Draw three squares on one row and three on the next. The top-left square is `(0, 0)`. Move right to increase `x`, or down to increase `y`. To store one colour in this lab, keep a red byte, a green byte and a blue byte. Each channel holds a value from 0 through 255.

## Work out the address first

1. Three RGB pixels use nine bytes per row.
2. Suppose our **stride**, the distance from one row start to the next, is 12 bytes. Each row has three bytes reserved for padding.
3. Pixel `(1, 1)` starts at byte `1 × 12 + 1 × 3 = 15`. Its green value is at byte 16.
4. A buffer for two rows at that stride must provide 24 bytes, even though only 18 bytes describe visible pixels.

```text
WHEN x and y are inside the image:
    SET offset TO y * stride + x * 3
    STORE red AT offset
    STORE green AT offset + 1
    STORE blue AT offset + 2
```

## Give the library a known buffer

`UmicomRaster` describes storage that your code owns. It contains a pointer, capacity, width, height and stride. The library checks the proposed layout before saving the descriptor. You keep the byte array alive until the last drawing call finishes.

```c
unsigned char pixels[24] = {0};
UmicomRaster image = {0};

int result = umicom_raster_bind(&image, pixels, sizeof pixels, 3, 2, 12);
```

A correct layout returns `UMICOM_RASTER_OK`. Each dimension must be at least 1 and at most 4,096, and stride must cover all the visible bytes in a row. Checking `stride <= capacity / height` avoids computing an overflowing product. The code first checks that height is greater than zero.

**Try it.** Work out the offset for `(2, 1)`. Next, change the passed capacity to 23, which should produce `UMICOM_RASTER_INVALID` and leave the earlier descriptor unchanged. An actual buffer must be at least as large as the capacity you pass.

**Check your answer.** The offset is 18. The final visible channel is stored at byte 20. Byte 21 begins the row's padding.

[Course contents](index.md) · [Next: Clip rectangles and draw an integer line](02-clipped-shapes.md)
