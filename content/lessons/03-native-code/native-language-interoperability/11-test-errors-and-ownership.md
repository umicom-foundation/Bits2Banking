<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/native-language-interoperability/11-test-errors-and-ownership.md

PURPOSE:
Teach test errors, lifetimes and realistic performance.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Test errors, lifetimes and realistic performance

[Course contents](index.md) · [Previous](10-forward-a-call-in-assembly.md) · [Next](12-use-the-course-in-studio.md)

## Separate four kinds of evidence
A source review asks whether the declarations and logic agree. A compile checks syntax and target rules. A link checks that required symbols can be resolved. An executed test checks behaviour for its actual inputs and environment. None substitutes for all the others.

## Make a test record
1. Record the source revision or file hashes, compiler version, operating system and target.
2. Build with warnings enabled. Read the first diagnostic before repeating a full build.
3. Run negative input, the lowest valid input, an ordinary value, the last valid input and the rejected boundary.
4. Run the same calls repeatedly and in different orders. A stateless value function should not retain the previous result.
5. Record failures and unavailable compilers separately. A skipped language is not a passed language.

## Why this example is memory-simple
The boundary passes one integer value and returns one integer value. The C implementation keeps no caller pointer and performs no heap allocation. That makes its ownership review small. Larger Framework APIs still need explicit create/destroy pairs, borrowed-buffer lifetimes, capacity checks and failure paths that leave outputs unchanged.

A native implementation can still leak, read freed storage or corrupt memory. Rewriting Python in C or assembly does not automatically remove those bugs. For supported toolchains, use sanitizers and repeated workload measurements. Measure peak memory and retained memory after cleanup separately; model weights and caches are not necessarily leaks.

## Compare performance fairly
Use the same algorithm, input, target and optimisation level. Separate compilation time, startup time, foreign-call overhead and steady-state throughput. Run several trials and report their variation. A five-call activity demonstration is for correctness; its timing does not rank languages.

## Exercise and worked answer
A client compiles successfully but crashes on the first call. Which facts should you inspect first? Check the linked library identity, argument and return types, calling convention and target architecture. Do not begin by removing runtime checks. A client gives 1001 for input 1000: verify that it actually calls the shared implementation rather than a duplicate rule.

For the next real API, write an ownership table before code: who allocates, who may mutate, who frees and whether the callee retains data. Keep unknown answers explicit.

## Read the complete source

[labs/native/activity-adapters/test_bridge.c](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/activity-adapters/test_bridge.c)
