<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/graphics-from-scratch/02-clipped-shapes.md

PURPOSE:
Explain half-open rectangle clipping and integer raster line stepping.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Clip rectangles and draw an integer line

[Previous: Build a pixel buffer and check its stride](01-pixels-and-stride.md) · [Course contents](index.md)

When you place a postcard partly outside a picture frame, the frame still shows the part that overlaps. Raster clipping does the same with numbers. The clipping step finds visible coordinates before the drawing code touches memory.

## Fill a visible rectangle

A two-pixel-wide rectangle at column 1 covers columns 1 and 2. Its right edge is 3. The library uses a range from the left edge up to, and excluding, the right edge. This convention gives a width of `right - left`.

```text
SET left TO MAX(x, 0)
SET right TO MIN(x + width, image_width)
SET top TO MAX(y, 0)
SET bottom TO MIN(y + height, image_height)
IF right > left AND bottom > top THEN
    FOR each row from top up to bottom excluding bottom
        FILL right - left consecutive pixels starting at left
    END FOR
END IF
```

In C, the library converts `x` and `width` separately to `int64_t` before adding. It widens `y` and `height` the same way. The narrowed values used as buffer offsets come from the clipped range. A rectangle with no visible area succeeds and changes no pixels.

1. Draw a three-column, two-row grid.
2. Mark the requested rectangle `x = -1`, `y = -1`, width 2, height 2.
3. Shade only the overlap with the grid. The result is one pixel at `(0, 0)`.
4. Change the rectangle start to `(3, 0)`. The result contains zero pixels because the grid ends just before 3.

## Choose the next point on a line

A horizontal line advances one column at a time. A vertical line advances one row at a time. For a sloped line, keep an integer error term. It records whether the next step should move horizontally, vertically or on both axes. This gives a discrete staircase of pixels between the endpoints. The code visits each endpoint and checks each point against the image before computing its address.

**Try it.** Trace the short diagonal from `(-1, -1)` to `(2, 2)` on the three-column, two-row grid. You should see `(0, 0)` and `(1, 1)`. The two endpoints are outside. The code still protects the two legal writes between them.

The lab accepts line endpoints between −8,192 and 8,192, inclusive. This bounds the number of steps even for an off-screen line. Within that range the doubled error and coordinate differences fit in signed 32-bit integers. Colours use six hexadecimal digits, with two digits for each channel, such as `0x55bbee`.

**Diagnose.** If a bright stripe appears in the next row, check stride, the three-channel pixel size and whether you treated the exclusive right edge as another visible pixel.

[Previous: Pixels and stride](01-pixels-and-stride.md) · [Course contents](index.md) · [Next: Export and verify a picture](03-export-and-verify.md)
