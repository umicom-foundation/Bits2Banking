<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/52-prove-capabilities-with-real-operations.md

PURPOSE:
Prove capability declarations with real operations

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Prove capability declarations with real operations

## Before you begin
Complete the profile-query lesson. Build the Umicom C tests and read tests/test_compiler_profile.c and tests/test_runtime_profile.c. The runtime test links only UmicomC::Runtime.

## Avoid a circular feature test
A test that merely compares a feature constant with itself says little about behavior. These tests compile real expressions for each advertised source feature. The runtime test starts with fixed instruction arrays so it does not need the compiler to manufacture its expectations.

1. Follow the arithmetic fixture: 7 multiplied by 6 returns 42.
2. Follow the comparison fixture: 7 greater than 6 returns 1.
3. Observe that encoding selects format 1 or 2 respectively.
4. Verify the encoded version's bit is advertised by the runtime.
5. Decode, inspect and trace each program.
6. Change the fixture's wire version to 3 and expect refusal.

~~~powershell
ctest --test-dir build -R "umicom.c.(profile|cli-profile)" --output-on-failure --no-tests=error
~~~

Expect three tests. A zero-test run is an error because the command includes --no-tests=error. The separate CLI case also rejects an extra filename before attempting file access.

## Bound reports are not allocations
The source limit is a ceiling, not permission to read beyond your buffer. The compiler test submits an oversized declared length with a short literal only because the contract rejects that length before scanning. Ordinary accepted spans must still point to valid storage.

The runtime's instruction and stack limits describe this implementation. A caller with a smaller array must use its actual capacity. Never allocate an unbounded amount merely because an untrusted remote report contains a large number.

## Extend carefully
When adding a real operation, append stable query IDs or feature bits rather than renumbering them. Add a behavioral example and an explicit unsupported case. Keep old wire identities intact.

If a declaration passes but the operation fails, preserve both observations and investigate. Do not redefine the feature as available merely because a menu item or header constant exists.


[Course contents](index.md) · [Previous lesson](51-query-the-linked-compiler-and-runtime.md) · [Next lesson](53-give-private-helpers-a-linker-namespace.md)
