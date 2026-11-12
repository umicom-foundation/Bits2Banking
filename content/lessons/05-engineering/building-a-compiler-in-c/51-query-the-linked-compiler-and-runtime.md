<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/51-query-the-linked-compiler-and-runtime.md

PURPOSE:
Query the linked compiler and runtime

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Query the linked compiler and runtime

## Before you begin
Build the current Umicom C compiler and complete the logical-negation CLI lesson. Open include/umicom_c/profile.h, src/compiler.c and src/status.c. Use a matching header and library from the same SDK build.

## Headers and linked code are different evidence
A macro is expanded while compiling your source. A function call reaches an implementation in the linked library. The new profile functions let that implementation report its own declared features and limits. They do not authenticate the library or prove which commit produced it.

~~~c
#include "umicom_c/profile.h"

uint32_t features = umc_compiler_profile(UMC_PROFILE_FEATURES);
if ((features & UMC_FEATURE_LOGICAL_NOT) != 0U) {
    /* Offer the documented ! expression feature. */
}
~~~

The compiler returns grammar features. The runtime reports arithmetic, comparisons, execution tracing and inspection. Logical negation lowers into existing operations, so it is not a runtime opcode.

## Read the CLI response
~~~powershell
.\build\bin\umicom-c.exe profile
~~~

Replace build with your configured build directory. Expect key=value lines, including compiler.features=103 and runtime.features=27. The compiler now adds hexadecimal (32) and binary (64) spelling to its earlier mask of 7. These numbers are bitmasks, not counts. The wire-format mask 6 contains bits 1 and 2; it does not advertise wire format 6.

1. Find the feature-bit definitions in profile.h.
2. Decode compiler.features by hand.
3. Find the runtime switch in status.c.
4. Explain why its source-byte and parse-depth queries return zero.
5. Query a made-up property value in a scratch consumer and expect zero.

## Recovery
An older library may not contain the new symbols even when your editor finds the new header. An unresolved-symbol error is then evidence of a mismatched SDK selection. Inspect include and library paths; rebuild or choose the matching SDK. Removing the query hides the mismatch rather than repairing it.

Continue checking every compile and execution status. A capability declaration does not promise that a particular program has valid syntax or enough execution fuel.


[Course contents](index.md) · [Previous lesson](50-qualify-negation-through-the-cli.md) · [Next lesson](52-prove-capabilities-with-real-operations.md)
