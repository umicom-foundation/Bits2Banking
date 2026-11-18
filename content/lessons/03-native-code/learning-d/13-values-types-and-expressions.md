<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/13-values-types-and-expressions.md

PURPOSE:
Read D values, types and expressions

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Read D values, types and expressions

[Course contents](index.md)
D is a compiled language with C-like punctuation, its own type system and an optional runtime. A type describes a value’s representation and permitted operations. A statement performs a step. An expression produces a value. The introductory lessons showed how to install DMD; use that same terminal and practice folder here.

~~~d
import std.stdio : writeln;
void main()
{
    int completed = 2;
    immutable int total = 8;
    auto percent = completed * 100 / total;
    bool finished = completed == total;
    writeln(percent);
    writeln(finished);
}
~~~

1. Save the code as values.d. Compile with dmd -w -g values.d and run the generated program. On Windows use .\values.exe.
2. Expect 25 and false. Write down the intermediate values 200 and 25.
3. Change completed to 8 and rebuild. Expect 100 and true.
4. Replace == with = in the boolean expression and inspect the diagnostic or changed expression meaning; restore the equality comparison. Assignment and equality are different operations.

D int is signed 32-bit; long is signed 64-bit. The unsigned partners begin with u, such as uint and ulong. auto asks the compiler to infer a type from the initializer; it does not make the variable dynamically typed. immutable says the value cannot change through any permitted alias. A const view is read-only through that view but can refer to mutable storage elsewhere.

Integer division discards the fractional part. Floating-point float and double approximate values and can represent fractions; real has platform-specific precision. A decimal spelling is not a guarantee of exact financial arithmetic. Validate total before dividing when it comes from input. The small constants here are chosen to avoid overflow; use the companion C boundary for a bounded percentage contract.


## Check and recover

If the compiler reports an undefined identifier, check its spelling and scope. D names are case sensitive. If the terminal says dmd is unknown, repair compiler discovery before changing the source. Read the first diagnostic and preserve a working copy before experimenting.


## Continue learning

[Course contents](index.md) · [Next: Choose paths and traverse D collections](14-control-flow-and-collections.md)
