/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/graphics/raster-from-scratch/gtk4_texture.c
 *
 * PURPOSE:
 *   Copy an admitted C raster layout into an owned GTK4 texture.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#include "gtk4_texture.h"

#include <string.h>

GdkTexture *umicom_raster_create_texture(const UmicomRaster *raster)
{
    UmicomRaster checked;
    if (raster == NULL || umicom_raster_bind(&checked, raster->bytes, raster->capacity,
                raster->width, raster->height, raster->stride) != UMICOM_RASTER_OK) {
        return NULL;
    }

    /* Copy only visible samples. The bounded dimensions limit this allocation,
     * and the caller's row padding never becomes part of the GDK snapshot. */
    const size_t row_bytes = (size_t)checked.width * 3U;
    const size_t size = row_bytes * (size_t)checked.height;
    unsigned char *owned = g_malloc(size);
    for (size_t row = 0; row < (size_t)checked.height; ++row) {
        memcpy(owned + row * row_bytes, checked.bytes + row * checked.stride, row_bytes);
    }

    /* The texture retains the immutable snapshot after we release our GBytes. */
    GBytes *snapshot = g_bytes_new_take(owned, size);
    GdkTexture *texture = gdk_memory_texture_new((int)checked.width, (int)checked.height,
                                               GDK_MEMORY_R8G8B8, snapshot, row_bytes);
    g_bytes_unref(snapshot);
    return texture;
}
