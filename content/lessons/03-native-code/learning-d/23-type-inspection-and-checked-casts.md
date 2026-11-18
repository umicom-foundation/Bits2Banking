<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/23-type-inspection-and-checked-casts.md

PURPOSE:
Inspect types and check conversions without guessing

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Inspect types and check conversions without guessing

[Course contents](index.md)
A type describes what a value means and which operations are valid for it. An integer, a string and an image object are different kinds of values. The compiler checks types while translating source code. A running program can also carry information about an object’s actual class. These are two different times at which a question about a type can be answered. In this lesson you will predict both answers, run one small D program, and explain why a conversion needs a check.


## Prepare one small experiment

Complete the installation and first-program lesson before this one. You need a working D compiler and a terminal. A compiler is a program that translates source text into an executable. This example uses ordinary D classes, the D runtime and the standard output library. It is not a BetterC example. No Umicom application, model download or network connection is involved.

1. Open PowerShell and change to the Bits2Banking repository using Set-Location. A repository is the folder containing the project and its recorded history.
2. Run dmd --version. If PowerShell says that dmd is not recognized, return to the installation lesson and fix compiler discovery before continuing. Do not type the compiler command into a D source file.
3. Open labs/languages/native-language-boundary/runtime_types.d in your editor. Read the file below before executing it. Keep a copy of the original if you want to experiment.
4. Build from the lab folder with the commands below. Run each command separately and stop if it reports an error. Keep assertions enabled: do not add -release for this exercise.

~~~powershell
Set-Location labs/languages/native-language-boundary
dmd --version
dmd runtime_types.d -of=runtime-types.exe
.\runtime-types.exe
~~~

On a supported Unix system, compile with dmd runtime_types.d -of=runtime-types and run ./runtime-types. If you use LDC or GDC instead, follow that compiler’s output-name and runtime instructions; command-line options are not automatically interchangeable. Record the compiler version and target with your result. These D commands require your own D compiler; the native C test in this lab does not execute this file.


## Read the declarations first

Resource is a base class: a general kind of object. ImageResource and SoundResource derive from it, meaning that each can be used where a Resource reference is expected. A reference identifies an object owned by the D runtime; it is not an inline copy of all its fields. The image has a width field and the sound has a samples field. Their simple numbers are teaching data, not real decoded media. The variable created counts calls to makeResource. The function increments that counter with ++ and returns a newly allocated image through the general Resource type.

~~~d
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

~~~


## Ask the compiler with typeof and is

Read typeof(makeResource()) as “the type of this expression.” The expression would return Resource, so that is the answer known to the compiler. typeof does not call makeResource here. The counter remains zero. The is expression asks a type-related question; is(typeof(resource) == Resource) is true because resource was declared with that type. static assert checks this claim during compilation. A false claim stops the build before there is a program to run. This is a useful tool for checking a generated declaration or a template assumption.

Do not confuse the type-test expression is(...) with the identity operator used later as image !is null. The latter asks whether a reference is not the absent-reference value null. In D, spelling and grammatical position matter: similar-looking tokens can serve different roles. The punctuation parentheses encloses the expression being inspected, while semicolons finish declarations and statements.


## Ask the running object with typeid

Resource resource = makeResource() declares a general reference but creates an ImageResource object. typeof(resource) still answers Resource. typeid(resource), however, obtains the runtime type information for that class object and compares equal to typeid(ImageResource). Runtime means while the executable is running. This is a limited form of reflection: the program can inspect a type represented by metadata. It is distinct from the compile-time field catalogues in the earlier reflection lesson.

The call typeid(makeResource()) evaluates its expression. That evaluation creates another object and increments created again. The expected final counter is two. This difference matters when the inspected expression reads a file, allocates memory or changes application state. Do not put an expensive operation inside typeid merely to discover the type you already know at compile time. Use typeof for the static question. This lesson deliberately uses nonnull class objects; handle absent references explicitly before accessing their members.


## Treat each cast as a specific contract

A cast asks for an explicit conversion. It is not a universal validation operation. cast(ImageResource) resource performs a class downcast here. It succeeds because the object really is an ImageResource. cast(SoundResource) resource produces null because the object is not a SoundResource. Check for null before using a derived field. An assertion is useful in this controlled exercise; a real application must also handle the mismatch through its normal error or alternative-path logic when assertions are disabled.

The numeric cast is a different operation. long can represent more integer values than int. The program first checks that count is between int.min and int.max, then uses cast(int) count. An explicit narrowing cast should never be used as proof that a value fits. For a reusable library, return a documented error when a range check fails. Avoid casts that remove const or immutable, reinterpret arbitrary bytes as pointers, or pretend that one runtime’s object is another runtime’s handle.


## Predict, run and change one thing

1. Before running, write down the expected static type of resource, actual class of its object, result of each class cast and final created counter.
2. Run the program. Expect Image width: 640, Resources created: 2, and Type inspection checks passed on separate lines. No assertion failure should occur.
3. Change makeResource to return new SoundResource(). Predict which assertion fails first and why. Compile and run again; a failure is the intended observation for this changed input. Restore the image return afterward.
4. Change count to 2147483648L, which is above the largest signed 32-bit integer. The range assertion should fail before the narrowing cast. Restore 120 afterward.
5. Replace only typeof(makeResource()) with typeof(resource) in a location after resource is declared. Explain why declaration order affects whether a name can be resolved, even though typeof does not execute the expression.


## Use the idea at a Framework boundary

A D application can use runtime classes for its own presentation objects and compile-time reflection to generate adapters. Shared Umicom Framework services still expose explicit C declarations, status values and ownership rules. A D class reference, TypeInfo instance or delegate is not a portable C ABI message. Use plain documented fields or opaque Framework handles at that boundary. For a catalogue, expose a stable application-defined identifier rather than serializing compiler-specific type names and expecting another compiler to understand them.

Reflection can reduce repetitive declarations, but it cannot prove that a buffer is long enough, that an object remains alive during a callback or that a model fits in memory. Those are separate contracts. Finish this exercise by explaining which facts were checked at compile time, which were checked at runtime, and which remain the responsibility of the caller. If a cast fails, inspect the object’s creation path rather than forcing a pointer conversion until the compiler is quiet.


## Choose the right question

| Question | Use | Important limit |
| --- | --- | --- |
| What type does this expression have in source? | typeof and is(...) | Does not tell you a derived object’s runtime class |
| What class does this nonnull object actually have? | typeid(object) | The expression is evaluated |
| Can this class object be used as a derived type? | cast(Derived) and a null check | Does not validate unrelated memory |
| Can this integer fit in a smaller integer? | Range check, then cast | The cast itself is not the range check |

## Further reading

- [D typeid expressions](https://dlang.org/spec/expression.html#typeid_expressions)
- [D typeof](https://dlang.org/spec/declaration.html#typeof)
- [D cast expressions](https://dlang.org/spec/expression.html#cast_expressions)

[Previous: Use scope guards to make cleanup paths visible](22-scope-guards-and-native-cleanup.md)

[Next: Use a C callback without capturing a D delegate](24-use-an-explicit-c-callback-context.md)
