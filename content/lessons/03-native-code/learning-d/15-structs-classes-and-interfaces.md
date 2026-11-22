<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/15-structs-classes-and-interfaces.md

PURPOSE:
Choose a struct, class or interface

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Choose a struct, class or interface

[Course contents](index.md)

## Before you begin

Draw two copies of a record and two names that point to the same record. Predict what each name will see after one field changes.
A struct groups fields and operations into a value type. A class is a reference type that supports inheritance and normally depends on the D runtime. An interface describes operations that implementing classes must supply. These choices affect copying, lifetime and interoperability; they are not interchangeable spelling styles.

~~~d
import std.stdio : writeln;
struct PreviewSize
{
    uint width;
    uint height;
    bool valid() const { return width > 0 && height > 0; }
}
void main()
{
    PreviewSize original = PreviewSize(640, 360);
    auto copy = original;
    copy.width = 320;
    writeln(original.width);
    writeln(copy.width);
    writeln(copy.valid());
}
~~~

1. Compile as records.d. Expect 640, 320 and true.
2. Explain why changing copy.width did not change original.width: the scalar fields were copied.
3. Add a dynamic array field in a separate experiment and draw its pointer and length. Copying the struct would copy that descriptor, not necessarily duplicate the elements.
4. Write the invariant that dimensions must be nonzero and add a test for width zero. An invariant is a condition that should hold for a valid object.

public, private, protected and package control visibility. this refers to the current instance and names constructors. super refers to a base-class context. override makes an overridden method explicit, abstract leaves an operation for a subclass, and final restricts overriding or inheritance as applicable. A union overlays alternatives in the same storage; use it only with a reliable tag recording the active alternative.

For a Framework C ABI, export opaque handles and plain documented fields instead of exposing a D class layout. A C consumer cannot initialize the D runtime merely by allocating a block of bytes of the right apparent size. A struct containing only scalars still requires checked layout, alignment and target agreement before direct interchange.


## Practice

Add a function returning pixel count using a wider integer before multiplication. Explain why valid nonzero dimensions may still request too much memory. Representation validity and resource policy are separate checks.


## Continue learning

[Previous: Choose paths and traverse D collections](14-control-flow-and-collections.md) · [Course contents](index.md) · [Next: Understand D memory management and safety attributes](16-garbage-collection-and-memory-contracts.md)
