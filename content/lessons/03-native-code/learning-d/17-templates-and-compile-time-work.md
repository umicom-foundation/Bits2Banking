<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/17-templates-and-compile-time-work.md

PURPOSE:
Use templates and compile-time evaluation

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Use templates and compile-time evaluation

[Course contents](index.md)
A template describes code parameterized by types or values. Instantiating a template asks the compiler to produce a concrete version. Compile-time function evaluation, often called CTFE, computes a permitted expression during compilation. Neither concept means that arbitrary program input can be evaluated before the program starts.

~~~d
T smaller(T)(T left, T right)
{
    return left < right ? left : right;
}
int square(int value) pure nothrow @safe @nogc
{
    return value * value;
}
enum tileArea = square(8);
static assert(tileArea == 64);
unittest
{
    assert(smaller(3, 7) == 3);
    assert(smaller(2.5, 1.5) == 1.5);
}
void main() {}
~~~

1. Save as compile_time.d and compile with dmd -w -unittest compile_time.d. Run the program.
2. Read T as a placeholder for a type. The two calls instantiate different comparisons.
3. Change the static assertion to expect 65. The compiler must reject it before an executable is produced. Restore 64.
4. Change square’s argument to a value read from a file in a separate program. Explain why that value is not generally available when compiling.

enum here defines a compile-time manifest constant; it can also define a set of named alternatives. static if chooses code at compile time. Ordinary if chooses a branch at runtime. alias supplies another name for a symbol or type; it is not necessarily a new independently distinct type. typeof inspects an expression’s type without requiring you to spell it twice.

Templates can reduce duplicated binding code but can also increase compile time and diagnostic complexity. Measure a representative build rather than assuming fewer source lines compile faster. A template-generated C ABI still needs stable exported names and a versioned layout contract.


## Exercise

Add a static assertion for square(0). Keep inputs small; compile-time evaluation does not make overflowing arithmetic conceptually correct. Document which cases the example supports before adapting it to size calculations.


## Continue learning

[Previous: Understand D memory management and safety attributes](16-garbage-collection-and-memory-contracts.md) · [Course contents](index.md) · [Next: Inspect fields with compile-time reflection](18-reflection-and-field-catalogues.md)
