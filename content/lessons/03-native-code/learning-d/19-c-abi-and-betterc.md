<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/19-c-abi-and-betterc.md

PURPOSE:
Separate C linkage from the BetterC subset

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Separate C linkage from the BetterC subset

[Course contents](index.md)

## Before you begin

Use [Install D and compile a first program](01-install-and-run.md) to check your compiler. Open `client.d` in `labs/languages/native-language-boundary` in the course checkout. Find the declaration for the function supplied by C. Copy its return type and parameter order, then check the corresponding C declaration before building.
extern(C) selects C linkage for a declaration. It does not automatically remove the D runtime from all surrounding code. BetterC is a restricted compilation mode for code that can operate with the C runtime alone. Choose it for a concrete integration requirement, not as a blanket claim that ordinary D is inefficient.

The companion native-language-boundary lab has a full D console client calling the same C function as FreeBASIC. It uses std.stdio and therefore is an ordinary D program. The C function receives scalar counts and a caller-owned output pointer. No exception or language-specific string descriptor crosses the boundary.

~~~d
extern(C) int bounded_progress(int completed, int total, int* percent) nothrow @nogc;
static assert(int.sizeof == 4);
~~~

1. Open labs/languages/native-language-boundary/README.md and read the ABI contract.
2. Build and run the C regression before trying a second-language client.
3. Select the D toolchain instructions matching your C object format. Follow the lab commands and expect 25 plus the D checks message.
4. Try total zero in the client and check both status and unchanged output. A nonzero status must not be ignored because an older output still looks plausible.

BetterC retains many compile-time facilities and can support allocation-free adapters. Runtime facilities such as garbage collection, ordinary D classes, exceptions and TypeInfo are not generally available there. A source file importing a module may still use declarations that compile without runtime support, but each used symbol must be checked. ImportC, which compiles C source, is a separate feature.

Before a production binding, specify who initializes any required runtime, which thread may call each API, how callbacks are retained, and what releases an owned result. Matching a symbol name is insufficient. Never cast a D array descriptor to a C array, or assume a D string has a trailing zero. Supply a pointer and explicit byte length when the C API permits it.


## Check

Why is the lab’s client not a BetterC example? It uses the ordinary D standard-library console path. Why is the C service still useful? Its fixed-width, allocation-free interface is consumable from multiple compatible native toolchains.


## Further reading

- [D BetterC reference](https://dlang.org/spec/betterc.html)
- [D interfacing to C](https://dlang.org/spec/interfaceToC.html)

## Continue learning

[Previous: Inspect fields with compile-time reflection](18-reflection-and-field-catalogues.md) · [Course contents](index.md) · [Next: Navigate D keywords and language concepts](20-keyword-and-concept-map.md)
