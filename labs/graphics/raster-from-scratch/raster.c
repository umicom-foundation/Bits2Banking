/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/graphics/raster-from-scratch/raster.c
 *
 * PURPOSE:
 *   Draw clipped 2D shapes into caller-owned RGB bytes.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "raster.h"

#include <limits.h>
#include <stdio.h>

static_assert(CHAR_BIT == 8, "P6 RGB storage requires eight-bit bytes");

static int raster_layout_is_valid(const UmicomRaster *raster)
{
    if (raster == NULL || raster->bytes == NULL ||
        raster->width == 0U || raster->width > UMICOM_RASTER_MAX_SIDE ||
        raster->height == 0U || raster->height > UMICOM_RASTER_MAX_SIDE) {
        return 0;
    }

    const size_t row_bytes = (size_t)raster->width * 3U;
    /* Division establishes the capacity bound before any row multiplication. */
    return raster->stride >= row_bytes &&
           raster->stride <= raster->capacity / (size_t)raster->height;
}

int umicom_raster_bind(UmicomRaster *raster, unsigned char *bytes, size_t capacity,
                      uint32_t width, uint32_t height, size_t stride)
{
    const UmicomRaster candidate = {bytes, capacity, width, height, stride};
    if (raster == NULL || !raster_layout_is_valid(&candidate)) {
        return UMICOM_RASTER_INVALID;
    }

    /* Commit only after validating the whole proposed layout. */
    *raster = candidate;
    return UMICOM_RASTER_OK;
}

static void store_pixel(unsigned char *destination, uint32_t rgb)
{
    /* Explicit stores make byte ordering independent of the CPU endianness. */
    destination[0] = (unsigned char)(rgb >> 16U);
    destination[1] = (unsigned char)(rgb >> 8U);
    destination[2] = (unsigned char)rgb;
}

#if defined(UMICOM_RASTER_USE_ASM)
void umicom_raster_fill_span_asm(unsigned char *destination, size_t count, uint32_t rgb);
#endif

static void fill_span(unsigned char *destination, size_t count, uint32_t rgb)
{
#if defined(UMICOM_RASTER_USE_ASM)
    /* Both variants receive a bounded horizontal span from the C layer. */
    umicom_raster_fill_span_asm(destination, count, rgb);
#else
    for (size_t column = 0; column < count; ++column) {
        store_pixel(destination + column * 3U, rgb);
    }
#endif
}

int umicom_raster_fill_rect(UmicomRaster *raster, int32_t x, int32_t y,
                           uint32_t width, uint32_t height, uint32_t rgb)
{
    if (!raster_layout_is_valid(raster) || rgb > UINT32_C(0xffffff)) {
        return UMICOM_RASTER_INVALID;
    }

    /* A right or bottom edge can lie outside the public 32-bit coordinate
     * range. Compute it wide, intersect both axes, then narrow for addressing. */
    const int64_t right = (int64_t)x + (int64_t)width;
    const int64_t bottom = (int64_t)y + (int64_t)height;
    const int64_t left_clip = x < 0 ? 0 : x;
    const int64_t top_clip = y < 0 ? 0 : y;
    const int64_t right_clip = right < raster->width ? right : raster->width;
    const int64_t bottom_clip = bottom < raster->height ? bottom : raster->height;
    if (right_clip <= left_clip || bottom_clip <= top_clip) {
        return UMICOM_RASTER_OK;
    }

    const size_t columns = (size_t)(right_clip - left_clip);
    for (size_t row = (size_t)top_clip; row < (size_t)bottom_clip; ++row) {
        fill_span(raster->bytes + row * raster->stride + (size_t)left_clip * 3U, columns, rgb);
    }
    return UMICOM_RASTER_OK;
}

static int coordinate_is_bounded(int32_t value)
{
    return value >= -UMICOM_RASTER_MAX_COORDINATE && value <= UMICOM_RASTER_MAX_COORDINATE;
}

int umicom_raster_line(UmicomRaster *raster, int32_t x0, int32_t y0,
                      int32_t x1, int32_t y1, uint32_t rgb)
{
    if (!raster_layout_is_valid(raster) || rgb > UINT32_C(0xffffff) ||
        !coordinate_is_bounded(x0) || !coordinate_is_bounded(y0) ||
        !coordinate_is_bounded(x1) || !coordinate_is_bounded(y1)) {
        return UMICOM_RASTER_INVALID;
    }

    const int32_t step_x = x0 < x1 ? 1 : -1;
    const int32_t step_y = y0 < y1 ? 1 : -1;
    const int32_t dx = x0 < x1 ? x1 - x0 : x0 - x1;
    const int32_t dy = y0 < y1 ? y0 - y1 : y1 - y0;
    int32_t error = dx + dy;

    /* The integer error tracks when a step on each axis gets the visited point
     * closer to the requested line. Off-screen points never form an address. */
    for (;;) {
        if (x0 >= 0 && y0 >= 0 && (uint32_t)x0 < raster->width && (uint32_t)y0 < raster->height) {
            store_pixel(raster->bytes + (size_t)y0 * raster->stride + (size_t)x0 * 3U, rgb);
        }
        if (x0 == x1 && y0 == y1) {
            return UMICOM_RASTER_OK;
        }

        const int32_t doubled = 2 * error;
        if (doubled >= dy) {
            error += dy;
            x0 += step_x;
        }
        if (doubled <= dx) {
            error += dx;
            y0 += step_y;
        }
    }
}

int umicom_raster_save_ppm(const UmicomRaster *raster, const char *path)
{
    if (!raster_layout_is_valid(raster) || path == NULL || *path == '\0') {
        return UMICOM_RASTER_INVALID;
    }

    FILE *output = fopen(path, "wbx");
    if (output == NULL) {
        return UMICOM_RASTER_IO;
    }

    /* Binary mode preserves RGB bytes. Each row exports only its visible
     * pixels, so caller-owned alignment padding never reaches the file. */
    int written = fprintf(output, "P6\n%u %u\n255\n",
                          (unsigned)raster->width, (unsigned)raster->height) >= 0;
    const size_t row_bytes = (size_t)raster->width * 3U;
    for (size_t row = 0; written && row < (size_t)raster->height; ++row) {
        written = fwrite(raster->bytes + row * raster->stride, 1, row_bytes, output) == row_bytes;
    }

    /* Closing still checks errors from buffered writes. Always release it. */
    const int closed = fclose(output);
    return written && closed == 0 ? UMICOM_RASTER_OK : UMICOM_RASTER_IO;
}
