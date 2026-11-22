<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/49-constrain-operator-templates-and-test-their-meaning.md

PURPOSE:
Constrain operator templates and test their meaning

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Constrain operator templates and test their meaning

[Course contents](index.md)

## Before you begin

Use [Install D and compile a first program](01-install-and-run.md) to check your compiler. Open `flag_operators.d` in `labs/languages/native-language-boundary` in the course checkout. Write a small truth table for two flags. Include an unsupported operator and find the template condition that rejects it.

## Start from an ordinary value type

An operator such as | is a compact request for an operation. A type can define that operation, but the syntax alone does not guarantee a useful meaning. This original exercise uses a FlagSet struct with one uint field. A uint is a 32-bit unsigned integer in D. The bits represent three independent labels, valued 1, 2 and 4. Union combines present labels and intersection keeps only labels present on both sides.

1. Review the earlier D template, reflection and bit-mask lessons.
2. Open labs/languages/native-language-boundary/flag_operators.d. This is an independent D teaching program, not a new implementation language for Framework.
3. Write down the expected answers: 1 | 4 is 5, 5 & 1 is 1, and 1 | 1 is still 1. These expectations describe the domain before you inspect the code.


## Read the operator template in small parts

The member name opBinary participates in D’s operator rewriting. The string template parameter op identifies the requested operator at compile time. The separate runtime parameter rhs is the right-hand value. The constraint after if admits only | and &. static if selects the corresponding implementation before the program runs. The example does not build source code strings or evaluate user input as code.

~~~d
struct FlagSet
{
    uint bits;
    FlagSet opBinary(string op)(FlagSet rhs) const @safe pure nothrow @nogc
        if (op == "|" || op == "&")
    {
        static if (op == "|") return FlagSet(bits | rhs.bits);
        else return FlagSet(bits & rhs.bits);
    }
}
~~~


## Follow the compile-time and runtime work


| Stage | Input | Result |
| --- | --- | --- |
| Compile time | Operator spelling \| or & | Select a permitted specialization and its body |
| Runtime | Two FlagSet values | Calculate a union or intersection |
| Runtime | Raw external integer | Admit known bits before publishing a trusted value |
| Application policy | Caller identity and requested action | Decide whether a real operation is allowed |


## Understand the attributes without overclaiming

const prevents this method from changing its receiver through this. @safe requests D’s checked memory-safety subset for the method. pure restricts the effects permitted by D’s purity rules; nothrow disallows throwing an Exception; @nogc disallows garbage-collector allocation in this method. These declarations describe this small operation. The complete demonstration uses writeln and an exception-throwing test helper, so the whole program is not claimed to be @nogc, nothrow or BetterC. Attributes do not prove business correctness or a speed advantage.


## Reflection can check availability, not meaning

The three static assertions in the example ask different questions. hasMember finds a declaration named opBinary. compiles checks whether a specific expression can be compiled. Neither evaluates all future values or establishes that a union has the right mathematical behavior. Runtime examples still check the actual results and preservation rules.

~~~d
static assert(__traits(hasMember, FlagSet, "opBinary"));
static assert(__traits(compiles, FlagSet(1) | FlagSet(2)));
static assert(!__traits(compiles, FlagSet(1) + FlagSet(2)));
~~~

1. The first check documents that the type exposes the operator hook.
2. The second checks that union syntax is available for these operands.
3. The third checks that the unsupported addition expression is rejected at compile time.
4. Run the ordinary checks as well: an implementation that returned zero for every union could still satisfy the first two reflection queries.


## Keep admission separate from convenient syntax

The public bits field allows arbitrary values, so the type name alone is not proof of validation. tryAdmitFlags accepts only bits inside mask 7. It returns false before changing its ref destination when raw contains another bit. ref is used deliberately: an out parameter would have different entry-initialization behavior and would not express the same preservation contract. A value of 8 is refused while the previous destination remains 2.

~~~d
bool tryAdmitFlags(uint raw, ref FlagSet destination) @safe pure nothrow @nogc
{
    if ((raw & ~7u) != 0) return false;
    destination = FlagSet(raw);
    return true;
}
~~~


## Why tests include a repeated member

Both addition and bitwise union give 5 for 1 and 4. That one example cannot distinguish them. With 1 and 1, addition gives 2 while union gives 1. Repeating a member should not introduce another label. The program also checks that its operands remain unchanged and that unknown raw input does not overwrite the caller’s prior result. These observations test a useful contract, rather than relying on a reflection result as a substitute for execution.


## Compile and run when a D compiler is available

These commands use DMD from the earlier setup lesson. The source has not been compiled in the current mirror environment. Run each line separately in PowerShell and stop on an error. The -unittest option includes the unittest block; main also calls the exercise so its checks remain part of the ordinary run.

~~~powershell
Set-Location C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary
dmd -unittest -checkaction=context flag_operators.d -of=flag_operators.exe
.\flag_operators.exe
~~~


## Expected output and diagnostics

~~~text
Umicom D flags: union 5, intersection 1, repeated flag 1.
Unknown input refused; reflection does not grant permission.
~~~

1. If the rejected-addition static assertion fails, inspect which overload or implicit conversion unexpectedly made + available.
2. If the operator constraint rejects |, check that the template string is the operator spelling and the runtime parameter is a FlagSet.
3. If a runtime check fails, inspect the bit calculation and destination assignment order. A successful compile is not evidence that the operation is correct.
4. Keep side-effecting calls outside assert expressions. The example saves the result of tryAdmitFlags and then checks it with a helper that remains active.


## Use the idea around a native Framework service

A D application layer could use typed operators for local flags or units while calling a reviewed C interface with explicit fixed-width values. Framework remains the reusable C/Assembly implementation owner. A shared C validator should determine which options are legal and which combinations are supported. Compile-time reflection can help generate field catalogues or bindings, but generated declarations still need ABI and ownership tests. This exercise does not establish installed-SDK interoperability or give a caller permission to access a file, device or network.


## Extend deliberately

1. Add an exclusive-or operation only after writing down its meaning and tests. Repeating a flag with exclusive-or should remove it, unlike union.
2. Before adding comparison operators, decide whether your domain has a meaningful ordering. Two unrelated sets need not have a useful less-than relationship.
3. Keep expensive operations explicit. An innocent-looking operator should not unexpectedly download a model, allocate a large tensor or write a file.
4. Use reflection to find declarations and reject unsupported syntax, then test values and effects separately.


## Language reference


- [D specification: operator overloading and binary operator templates](https://dlang.org/spec/operatoroverloading.html)
- [D specification: compile-time traits](https://dlang.org/spec/traits.html)


[Previous: Separate rounding from checked integer conversion](48-separate-rounding-from-checked-integer-conversion.md)

[Next: Follow comment and string boundaries](50-follow-comment-and-string-boundaries.md)
