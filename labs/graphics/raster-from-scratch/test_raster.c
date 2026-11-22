/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/graphics/raster-from-scratch/test_raster.c
 *
 * PURPOSE:
 *   Verify clipped shapes, untouched padding and rejected buffer layouts.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "raster.h"

#include <stdio.h>
#include <string.h>

#define CHECK(condition) do {                                                         \
    if (!(condition)) {                                                              \
        fprintf(stderr, "line %d: %s\n", __LINE__, #condition);                       \
        return 1;                                                                    \
    }                                                                                \
} while (0)

static int pixel_is(const unsigned char *p, unsigned char red, unsigned char green, unsigned char blue)
{
    return p[0] == red && p[1] == green && p[2] == blue;
}

int main(void)
{
    enum { stride = 12 };
    unsigned char bytes[2 * stride];
    memset(bytes, 0xa5, sizeof bytes);
    UmicomRaster view = {0};

    /* Refused layout proposals must not overwrite the existing view. */
    CHECK(umicom_raster_bind(&view, bytes, sizeof bytes, 3, 2, stride) == UMICOM_RASTER_OK);
    CHECK(umicom_raster_bind(&view, bytes, 23, 3, 2, stride) == UMICOM_RASTER_INVALID);
    CHECK(umicom_raster_bind(&view, bytes, sizeof bytes, 0, 2, stride) == UMICOM_RASTER_INVALID);
    CHECK(umicom_raster_bind(&view, bytes, sizeof bytes, 3, 2, SIZE_MAX) == UMICOM_RASTER_INVALID);
    CHECK(view.bytes == bytes && view.width == 3 && view.height == 2 && view.stride == stride);
    CHECK(umicom_raster_fill_rect(&view, 0, 0, 3, 2, 0x123456) == UMICOM_RASTER_OK);
    CHECK(pixel_is(bytes, 0x12, 0x34, 0x56));
    CHECK(pixel_is(bytes + stride + 6, 0x12, 0x34, 0x56));
    CHECK(pixel_is(bytes + 9, 0xa5, 0xa5, 0xa5));
    CHECK(pixel_is(bytes + stride + 9, 0xa5, 0xa5, 0xa5));

    CHECK(umicom_raster_fill_rect(&view, -1, -1, 2, 2, 0xff0000) == UMICOM_RASTER_OK);
    CHECK(pixel_is(bytes, 0xff, 0, 0));
    CHECK(pixel_is(bytes + 3, 0x12, 0x34, 0x56));
    CHECK(pixel_is(bytes + stride, 0x12, 0x34, 0x56));
    CHECK(umicom_raster_fill_rect(&view, INT32_MIN, 1, UINT32_MAX, 1, 0x112233) == UMICOM_RASTER_OK);
    CHECK(pixel_is(bytes + stride + 6, 0x11, 0x22, 0x33));

    /* A line that begins outside must plot only its visible points. */
    CHECK(umicom_raster_line(&view, -3, -3, 2, 2, 0x55bbee) == UMICOM_RASTER_OK);
    CHECK(pixel_is(bytes, 0x55, 0xbb, 0xee));
    CHECK(pixel_is(bytes + stride + 3, 0x55, 0xbb, 0xee));
    CHECK(umicom_raster_line(&view, 2, 1, 2, 1, 0xffffff) == UMICOM_RASTER_OK);
    CHECK(pixel_is(bytes + stride + 6, 0xff, 0xff, 0xff));

    unsigned char before[sizeof bytes];
    memcpy(before, bytes, sizeof before);
    CHECK(umicom_raster_fill_rect(&view, INT32_MAX, INT32_MAX, UINT32_MAX, UINT32_MAX, 0) == UMICOM_RASTER_OK);
    CHECK(umicom_raster_fill_rect(&view, 0, 0, 0, 2, 0) == UMICOM_RASTER_OK);
    CHECK(umicom_raster_fill_rect(&view, 0, 0, 3, 2, UINT32_MAX) == UMICOM_RASTER_INVALID);
    CHECK(umicom_raster_line(&view, INT32_MIN, 0, 0, 0, 0) == UMICOM_RASTER_INVALID);
    CHECK(memcmp(before, bytes, sizeof before) == 0);
    CHECK(umicom_raster_save_ppm(&view, "") == UMICOM_RASTER_INVALID);
    return 0;
}
