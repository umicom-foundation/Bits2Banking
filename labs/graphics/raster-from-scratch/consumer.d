/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/graphics/raster-from-scratch/consumer.d
 *
 * PURPOSE:
 *   Call the teaching raster library through the D interface to C.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

import std.stdio : stderr, writeln;
import std.string : toStringz;

// Match the C header's field order and widths on the same target and ABI.
// C23 owns the raster logic. D owns this array and the output-name string.
extern(C) struct UmicomRaster
{
    ubyte* bytes;
    size_t capacity;
    uint width;
    uint height;
    size_t stride;
}

extern(C) int umicom_raster_bind(UmicomRaster*, ubyte*, size_t, uint, uint, size_t);
extern(C) int umicom_raster_fill_rect(UmicomRaster*, int, int, uint, uint, uint);
extern(C) int umicom_raster_line(UmicomRaster*, int, int, int, int, uint);
extern(C) int umicom_raster_save_ppm(const(UmicomRaster)*, const(char)*);

int main(string[] args)
{
    if (args.length != 2)
    {
        stderr.writeln("Usage: umicom-raster-d NEW_IMAGE.ppm");
        return 2;
    }

    enum uint width = 32;
    enum uint height = 24;
    ubyte[width * height * 3] bytes;
    UmicomRaster raster;
    if (umicom_raster_bind(&raster, bytes.ptr, bytes.length, width, height, width * 3) != 0 ||
        umicom_raster_fill_rect(&raster, 0, 0, width, height, 0x142640) != 0 ||
        umicom_raster_fill_rect(&raster, -3, 3, 20, 11, 0x4aa8df) != 0 ||
        umicom_raster_line(&raster, 1, 22, 30, 1, 0xffffff) != 0 ||
        umicom_raster_save_ppm(&raster, args[1].toStringz) != 0)
    {
        stderr.writeln("Could not produce a new PPM image.");
        return 1;
    }
    writeln("Wrote a 32 x 24 RGB image through the C ABI.");
    return 0;
}
