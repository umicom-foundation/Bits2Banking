/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/graphics/raster-from-scratch/test_texture.c
 *
 * PURPOSE:
 *   Verify a GTK4 texture owns a snapshot of visible RGB bytes without a window.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "gtk4_texture.h"

#include <stdio.h>
#include <string.h>

int main(void)
{
    /* One visible pixel per row with a spare byte. The test never initializes
     * GTK as an application or opens a display. It only uses a memory texture. */
    unsigned char bytes[] = {0x12, 0x34, 0x56, 0xaa, 0x21, 0x43, 0x65, 0xbb};
    UmicomRaster image;
    if (umicom_raster_create_texture(NULL) != NULL ||
        umicom_raster_bind(&image, bytes, sizeof bytes, 1, 2, 4) != UMICOM_RASTER_OK) {
        fputs("Texture admission accepted an invalid view or rejected a padded view.\n", stderr);
        return 1;
    }

    GdkTexture *texture = umicom_raster_create_texture(&image);
    if (texture == NULL) {
        fputs("Could not snapshot the padded RGB view.\n", stderr);
        return 1;
    }

    /* Replace the source before reading the texture to detect borrowed pixels.
     * GDK downloads to native-endian premultiplied ARGB32 with full opacity. */
    memset(bytes, 0, sizeof bytes);
    uint32_t output[2] = {0};
    const int dimensions_match = gdk_texture_get_width(texture) == 1 && gdk_texture_get_height(texture) == 2;
    if (dimensions_match) {
        gdk_texture_download(texture, (guchar *)output, sizeof output[0]);
    }
    g_object_unref(texture);
    if (!dimensions_match || output[0] != UINT32_C(0xff123456) || output[1] != UINT32_C(0xff214365)) {
        fputs("The texture changed its dimensions or original RGB samples.\n", stderr);
        return 1;
    }
    return 0;
}
