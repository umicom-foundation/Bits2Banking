/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: labs/languages/native-language-boundary/runtime_types.d
 *
 * PURPOSE:
 *   Contrast compile-time type inspection, runtime class identity and checked class casts.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/


module runtime_types;
import std.stdio : writeln;

class Resource {}
class ImageResource : Resource { uint width = 640; }
class SoundResource : Resource { uint samples = 48000; }
size_t created;
Resource makeResource()
{
    ++created;
    return new ImageResource();
}

void main()
{
    // typeof asks the compiler about the expression without calling it.
    static assert(is(typeof(makeResource()) == Resource));
    assert(created == 0);

    Resource resource = makeResource();
    static assert(is(typeof(resource) == Resource));
    assert(typeid(resource) == typeid(ImageResource));
    assert(created == 1);

    // Class downcasts inspect runtime type. An incompatible cast is null.
    auto image = cast(ImageResource) resource;
    auto sound = cast(SoundResource) resource;
    assert(image !is null);
    assert(sound is null);
    writeln("Image width: ", image.width);

    // Unlike typeof, typeid evaluates its expression, including side effects.
    auto runtimeType = typeid(makeResource());
    assert(runtimeType == typeid(ImageResource));
    assert(created == 2);
    writeln("Resources created: ", created);

    // Numeric conversion needs a value-range check before narrowing.
    long count = 120;
    assert(count >= int.min && count <= int.max);
    int smallCount = cast(int) count;
    assert(smallCount == 120);
    writeln("Type inspection checks passed");
}
