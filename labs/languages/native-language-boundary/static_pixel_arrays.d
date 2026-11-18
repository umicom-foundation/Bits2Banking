/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/static_pixel_arrays.d
 *
 * PURPOSE:
 *   Trace nested static-array copies and reference iteration before crossing native image boundaries.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module static_pixel_arrays;
import std.stdio : writeln;

alias Pixel = ubyte[3];
alias Row = Pixel[2];
alias Image = Row[2];
static assert(Image.sizeof == 12);

Image originalImage() @safe pure nothrow @nogc
{
    Image image;
    image[0][0] = [255, 0, 0];
    image[0][1] = [0, 255, 0];
    image[1][0] = [0, 0, 255];
    image[1][1] = [255, 255, 255];
    return image;
}

uint channelTotal(Image image) @safe pure nothrow @nogc
{
    // A deliberate 12-byte value parameter keeps this tiny read-only example
    // independent. Large images need a reviewed borrowing/storage strategy.
    uint total;
    foreach (row; image)
        foreach (pixel; row)
            foreach (channel; pixel)
                total += channel;
    return total;
}

void editRowCopies(ref Image image) @safe pure nothrow @nogc
{
    // row is a static-array value copy. ref pixel refers to that local copy,
    // not to a pixel in image. Editing it does not edit the original image.
    foreach (row; image)
        foreach (ref pixel; row)
            pixel[0] = 0;
}

void removeRed(ref Image image) @safe pure nothrow @nogc
{
    // Both levels now refer into caller storage. The caller grants this edit
    // for the call; no reference is stored for later use.
    foreach (ref row; image)
        foreach (ref pixel; row)
            pixel[0] = 0;
}

unittest
{
    Image image = originalImage();
    Image saved = image;
    editRowCopies(image);
    assert(image == saved);
    removeRed(image);
    assert(channelTotal(image) == 1020);
    assert(channelTotal(saved) == 1530);
    assert(image[0][0][0] == 0 && saved[0][0][0] == 255);
}

int main()
{
    Image image = originalImage();
    if (channelTotal(image) != 1530) return 1;
    editRowCopies(image);
    if (channelTotal(image) != 1530) return 2;
    writeln("Editing row copies: original total = ", channelTotal(image));
    Image saved = image;
    removeRed(image);
    if (channelTotal(image) != 1020 || channelTotal(saved) != 1530) return 3;
    writeln("Editing referenced rows: image total = ", channelTotal(image));
    writeln("Independent static-array copy: saved total = ", channelTotal(saved));
    return 0;
}
