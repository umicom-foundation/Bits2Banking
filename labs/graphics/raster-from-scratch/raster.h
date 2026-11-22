/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/graphics/raster-from-scratch/raster.h
 *
 * PURPOSE:
 *   Define bounded RGB canvas, drawing, and image export contracts.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef UMICOM_LESSON_RASTER_H
#define UMICOM_LESSON_RASTER_H

#include <stddef.h>
#include <stdint.h>

enum {
    UMICOM_RASTER_OK = 0,
    UMICOM_RASTER_INVALID = 1,
    UMICOM_RASTER_IO = 2,
    UMICOM_RASTER_MAX_SIDE = 4096,
    UMICOM_RASTER_MAX_COORDINATE = 8192
};

/* The caller owns bytes and keeps the storage alive and disjoint from the
 * descriptor. Stride includes row padding in bytes. The library leaves padding
 * available to the caller. Capacity covers stride * height bytes. */
typedef struct UmicomRaster {
    unsigned char *bytes;
    size_t capacity;
    uint32_t width;
    uint32_t height;
    size_t stride;
} UmicomRaster;

/* Reject zero or excessive dimensions and layouts that do not fit. Rejection
 * leaves the descriptor and the pixel storage unchanged. */
int umicom_raster_bind(UmicomRaster *raster, unsigned char *bytes, size_t capacity,
                       uint32_t width, uint32_t height, size_t stride);

/* Paint the intersection of [x, x + width) × [y, y + height) and the raster.
 * A clipped-out or empty rectangle succeeds. Colours are 0xRRGGBB. An invalid
 * descriptor or colour is rejected before any write. */
int umicom_raster_fill_rect(UmicomRaster *raster, int32_t x, int32_t y,
                            uint32_t width, uint32_t height, uint32_t rgb);

/* Draw both endpoints with integer line stepping and clip each plotted point.
 * Each endpoint coordinate must be between -8192 and 8192 inclusive. The
 * limit also bounds work for lines entirely outside the raster. */
int umicom_raster_line(UmicomRaster *raster, int32_t x0, int32_t y0,
                       int32_t x1, int32_t y1, uint32_t rgb);

/* Write P6 RGB samples to a newly created file. On I/O failure new partial
 * output may remain. Existing files are protected by exclusive creation. */
int umicom_raster_save_ppm(const UmicomRaster *raster, const char *path);

#endif
