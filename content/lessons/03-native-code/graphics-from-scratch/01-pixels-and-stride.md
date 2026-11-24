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

## Copy visible rows between two arrays

Two buffers can hold the same picture with different spacing between rows. In this exercise, each grayscale pixel uses one byte for its brightness. That gives us three visible bytes in each row of a picture that is three pixels wide and two pixels high. You may see the term **row pitch** for the stride measured in bytes.

| Row | Source bytes, pitch 5 | Destination before the copy, pitch 4 |
| --- | --- | --- |
| 0 | `1 2 3` followed by padding `90 91` | `0 0 0` followed by padding `99` |
| 1 | `4 5 6` followed by padding `92 93` | `0 0 0` followed by padding `99` |

1. Write each row's starting byte index on paper. Row 0 starts at index 0 in both arrays. Row 1 starts at index 5 in the source and index 4 in the destination.
2. Move three bytes from each source row start to its matching destination row start. The two destination padding bytes were set to `99` so any accidental change is easy to spot.
3. Predict the printed rows. What would happen to the first `99` if you copied the first six source bytes as one block?

```text
FOR each row from 0 up to height, excluding height
    SET source_start TO row * source_pitch
    SET destination_start TO row * destination_pitch
    COPY width bytes from source_start to destination_start
END FOR
```

Save the following as `row-pitch.c` in a practice folder. Both arrays belong to the program, and all the dimensions are fixed.

```c
#include <stddef.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    enum { width = 3, height = 2, source_pitch = 5, destination_pitch = 4 };
    const unsigned char source[height * source_pitch] = {
        1, 2, 3, 90, 91,
        4, 5, 6, 92, 93
    };
    unsigned char destination[height * destination_pitch] = {
        0, 0, 0, 99,
        0, 0, 0, 99
    };

    /* Each array has its own row starts. Copy only the visible bytes. */
    for (size_t row = 0; row < height; ++row) {
        const size_t source_start = row * source_pitch;
        const size_t destination_start = row * destination_pitch;
        memcpy(destination + destination_start, source + source_start, width);
    }

    /* Print the copied row and its original padding side by side. */
    for (size_t row = 0; row < height; ++row) {
        const size_t start = row * destination_pitch;
        printf("%u %u %u | pad %u\n",
            (unsigned)destination[start],
            (unsigned)destination[start + 1],
            (unsigned)destination[start + 2],
            (unsigned)destination[start + 3]);
    }
    return 0;
}
```

With a C23 GCC on your PowerShell PATH, run these commands from the practice folder. Stop if compilation reports an error.

```powershell
gcc -std=c23 -Wall -Wextra -Wpedantic row-pitch.c -o row-pitch.exe
.\row-pitch.exe
```

Expect these two lines.

```text
1 2 3 | pad 99
4 5 6 | pad 99
```

**Check your prediction.** A single six-byte copy would put the source's `90` into the first destination padding slot. If the second printed row is wrong, check that you multiplied the row number by each array's own pitch. For an RGB image, change the copy count to `width * 3` and choose pitches large enough for that number of visible bytes.

The display choice in a virtual machine plan describes whether it would show a window and which software would present it. An image array still needs its own width, height and row pitch. This exercise models the array in memory. [Virtual machines, hosts and guests](../../08-system-administration/61-understand-virtual-machines-hosts-and-guests.md)

[Course contents](index.md) · [Next: Clip rectangles and draw an integer line](02-clipped-shapes.md)
