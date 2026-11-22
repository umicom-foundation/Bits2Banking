/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/graphics/raster-from-scratch/gtk4_texture.h
 *
 * PURPOSE:
 *   Expose an owned GTK4 texture snapshot without a GUI application.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

#ifndef UMICOM_LESSON_GTK4_TEXTURE_H
#define UMICOM_LESSON_GTK4_TEXTURE_H

#include "raster.h"

#include <gtk/gtk.h>

/* Snapshot an admitted RGB buffer. The caller releases the returned reference.
 * An invalid layout gives NULL. GTK uses its normal allocation failure policy. */
GdkTexture *umicom_raster_create_texture(const UmicomRaster *raster);

#endif
