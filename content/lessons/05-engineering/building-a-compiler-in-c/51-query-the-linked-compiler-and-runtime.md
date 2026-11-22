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

<!-- The first course edition used the early two-format build. Its example is retained for readers comparing that build with the current linked profile.
Replace build with your configured build directory. Expect key=value lines, including compiler.features=103 and runtime.features=27. The compiler now adds hexadecimal (32) and binary (64) spelling to its earlier mask of 7. These numbers are bitmasks, not counts. The wire-format mask 6 contains bits 1 and 2; it does not advertise wire format 6.
-->
Replace `build` with your configured directory. Look for `compiler.features`, `runtime.features` and `runtime.wire-versions`. A bitmask stores a different answer at each bit position. For example, mask `6` sets bits 1 and 2, so it represents versions 1 and 2. Use the names in `profile.h` to decode the feature bits from the build you actually ran.

1. Find the feature-bit definitions in profile.h.
2. Decode compiler.features by hand.
3. Find the runtime switch in status.c.
4. Explain why its source-byte and parse-depth queries return zero.
5. Query a made-up property value in a scratch consumer and expect zero.

## Check the bytecode format before opening a file

1. Ask the current runtime whether it understands format 7. The wire format defines the layout of the saved bytecode.

   ~~~powershell
   .\build\bin\umicom-c.exe profile --require-wire 7
   $LASTEXITCODE
   ~~~

2. Expect `profile.wire-version=7`, `profile.wire-supported=true` and status `0` on the current build. Repeat with `8`. The current runtime reports `false` and status `1` because its version mask lacks bit 8. A value outside the accepted range, such as `32`, produces a diagnostic and status `2`.
3. When a valid version returns status `1`, choose the matching runtime or build the bytecode for a version your runtime supports. After the requirement succeeds, use `inspect-bytecode` to check the actual file before execution.

## Recovery
An older library may not contain the new symbols even when your editor finds the new header. An unresolved-symbol error is then evidence of a mismatched SDK selection. Inspect include and library paths; rebuild or choose the matching SDK. Removing the query hides the mismatch rather than repairing it.

Continue checking every compile and execution status. A capability declaration does not promise that a particular program has valid syntax or enough execution fuel.


[Course contents](index.md) · [Previous lesson](50-qualify-negation-through-the-cli.md) · [Next lesson](52-prove-capabilities-with-real-operations.md)
