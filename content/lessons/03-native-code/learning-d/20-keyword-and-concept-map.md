<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/20-keyword-and-concept-map.md

PURPOSE:
Navigate D keywords and language concepts

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Navigate D keywords and language concepts

[Course contents](index.md)

## Before you begin

Choose three terms from earlier lessons and find one place each appears in a code example. Start the concept map with those examples and pick a family of terms to revisit.
A keyword is a reserved token recognized by the language grammar. A library function is a named operation supplied by a module. An attribute can constrain a declaration. These categories overlap in everyday discussion but should not be confused when reading diagnostics. writeln is a library function; @safe and @nogc are attributes; string is a commonly used type alias.

Use this map as a reading aid after the practical lessons, not as a program to paste into the compiler. For each family, find a small example in the preceding lessons, explain the purpose in your own words, then change one input and predict the result. The compiler edition and official reference determine current acceptance; some historical reserved words are deprecated or unavailable.

The names __DATE__, __TIME__, __TIMESTAMP__, __VENDOR__, __VERSION__ and __EOF__ have special lexical roles. They are not ordinary variables. Embedding compilation dates can make otherwise identical builds differ. A reserved name does not guarantee an implemented feature; macro is an example to investigate in the lexical specification rather than use as a template substitute.


## A useful study routine

1. Pick one family, such as control flow. Write a five-line example using if and return.
2. Explain each punctuation mark: parentheses group conditions, braces delimit a block, semicolons terminate statements.
3. Add one test that takes each branch.
4. Look up an unfamiliar token in the official language reference and record the compiler version used. Avoid copying obsolete examples without checking.

This course provides a progressive introduction, not complete expertise in every target-specific facility. SIMD vectors, inline assembly, concurrent memory ordering, advanced template constraints and binary compatibility require their own extended labs before production use.


## Language families

| Family | Tokens | Purpose |
| --- | --- | --- |
| Values and built-in types | bool byte ubyte short ushort int uint long ulong char wchar dchar float double real void true false null | Represent typed values and absence |
| Names and declarations | alias auto enum module import | Name symbols, infer types and organize modules |
| Control flow | if else switch case default for foreach foreach_reverse while do break continue goto return with | Select and repeat statements |
| Aggregate and object model | struct union class interface this super abstract final override invariant | Describe data and object contracts |
| Visibility and linkage | public private protected package export extern align | Control access and external layout/linkage |
| Qualifiers and parameter behavior | const immutable shared inout ref in out lazy scope | Express views, sharing and calling contracts |
| Functions and effects | function delegate pure nothrow | Describe callable values and effects |
| Type inspection and conversion | typeid cast | Inspect runtime type metadata and request explicit conversions; see the checked-cast exercise |
| Compile-time work | template mixin static typeof is __traits __parameters | Generate and inspect typed code |
| Diagnostics and alternatives | assert unittest debug version pragma deprecated | Check behavior and select configurations |
| Errors and lifetime | try catch finally throw new synchronized | Handle exceptions, allocation and synchronization |
| Low-level facilities | asm __gshared __vector __rvalue | Target-specific or advanced operations |
| Source-location tokens | __FILE__ __FILE_FULL_PATH__ __FUNCTION__ __LINE__ __MODULE__ __PRETTY_FUNCTION__ | Identify source context |
| Historical or reserved spellings | body delete cent ucent cfloat cdouble creal ifloat idouble ireal macro | Consult edition/reference; do not introduce into new lessons blindly |

## Further reading

- [D lexical reference](https://dlang.org/spec/lex.html)
- [D language reference](https://dlang.org/spec/spec.html)

## Continue learning

[Previous: Separate C linkage from the BetterC subset](19-c-abi-and-betterc.md) · [Course contents](index.md)

## Continue practice

[Next: Distinguish function pointers, delegates and C callbacks](21-functions-delegates-and-callback-lifetimes.md)

## Apply these names to a complete exercise

[Practice enum, final switch and compile-time member inspection](33-admit-enumerated-states-before-dispatch.md). Read the source, predict refusals and keep the subject-language compiler evidence separate from C checks.
