/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/graphics/raster-from-scratch/main.c
 *
 * PURPOSE:
 *   Create a small sample image through the teaching raster library.
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

int main(int argc, char **argv)
{
    if (argc != 2) {
        fputs("Usage: umicom-raster-example NEW_IMAGE.ppm\n", stderr);
        return 2;
    }

    /* The sample makes an image from scratch without depending on a toolkit. */
    enum { width = 80, height = 48 };
    unsigned char bytes[width * height * 3U];
    UmicomRaster raster;
    if (umicom_raster_bind(&raster, bytes, sizeof bytes, width, height, width * 3U) != UMICOM_RASTER_OK ||
        umicom_raster_fill_rect(&raster, 0, 0, width, height, UINT32_C(0x142640)) != UMICOM_RASTER_OK ||
        umicom_raster_fill_rect(&raster, -8, 7, 40, 25, UINT32_C(0x4aa8df)) != UMICOM_RASTER_OK ||
        umicom_raster_fill_rect(&raster, 36, 18, 31, 23, UINT32_C(0xf4bb47)) != UMICOM_RASTER_OK ||
        umicom_raster_line(&raster, 2, 45, 76, 2, UINT32_C(0xffffff)) != UMICOM_RASTER_OK ||
        umicom_raster_save_ppm(&raster, argv[1]) != UMICOM_RASTER_OK) {
        fputs("Could not produce a new PPM image. Check the output name and permissions.\n", stderr);
        return 1;
    }

    puts("Wrote an 80 x 48 RGB image.");
    return 0;
}
