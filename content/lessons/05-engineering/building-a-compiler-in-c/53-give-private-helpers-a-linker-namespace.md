<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/53-give-private-helpers-a-linker-namespace.md

PURPOSE:
Give private C helpers a linker namespace

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Give private C helpers a linker namespace

## Preparation and outcome

Read the earlier build-stage lessons and open the native c-library-composition lab in the Bits2Banking repository. You need an installed C23 compiler, CMake and Ninja. This lesson follows a failure that appears only when two otherwise useful libraries enter one executable. You will distinguish file organization, header visibility and external linkage.

## Why a private header is not a linker boundary

A translation unit is the source text after preprocessing, including the headers it incorporates. An ordinary function definition has external linkage unless its declaration gives it internal linkage, commonly with static. Placing its declaration in a file named internal.h does not change that rule. The linker still sees the function's symbol.

In the lab, scanner.c defines Count(bytes) to count 256-byte pages. Catalogue code defines Count(entries, width) to count bytes. These are different operations. The public entry points have distinct names, but both archive members contain Count. Linking both together without private prefixes produces duplicate definitions. Reordering libraries cannot establish the intended ownership.

## Follow the correction

The source component retains its local spelling through a private alias:

~~~c
#define Count BtbSourceInternalCount
size_t Count(size_t bytes);
~~~

The catalogue uses BtbCatalogueInternalCount. Preprocessing changes declarations, definitions and calls consistently. Public API names remain stable. A component that spreads helpers across several source files can place these aliases in its private header. Every participating translation unit must include that header before declaring or defining the helpers.

A function used only within one translation unit can simply be static. Do not use static when other translation units genuinely need the same implementation, and do not copy the function into each file to avoid a link error. Choose visibility based on ownership.

## Build and prove composition

From the Bits2Banking repository root, run these commands separately:

~~~powershell
cmake -S labs/native/c-library-composition -B build/c-library-composition -G Ninja
cmake --build build/c-library-composition --parallel 2
ctest --test-dir build/c-library-composition -R composition --output-on-failure --no-tests=error
~~~

Expect two passing tests. Both executable variants call both services, including size boundaries. An archive is a collection of object files; a linker commonly extracts members needed to resolve references. A test that calls only one service can therefore miss a collision hidden in the other archive. This explains why isolated tests are necessary but insufficient.

## Apply the reasoning to Framework

Framework's Source Contracts and Setup Centre both historically used names including ScRead and ScCopy. Their signatures and meanings differ. Source Contracts now maps its private helpers to UmiSourceContractInternal names through its own internal header. The source implementations stay in place. The public UmiSourceContract API and Setup Centre API remain separate.

The authored Framework composition regression calls both public services from one executable and registers both archive orders. A successful configuration only creates its build rules. It does not prove the executable linked or its assertions passed; capture those results separately when running the Framework qualification suite.

## Exercise and recovery

Use the separate collision build documented in the lab README. Enable BTB_TEACH_UNQUALIFIED_HELPERS and expect the build to fail during linking. Save the exact command and first duplicate-symbol diagnostic. Return to the valid build directory afterward. Never conceal this failure with an allow-multiple-definitions option: the two helper contracts are incompatible.

Explain in your notes why an include guard prevents repeated declarations within one translation unit but does not rename symbols across libraries. Your explanation should identify the public APIs, private implementations and evidence that both libraries actually participated.

[Course contents](index.md) · [Previous lesson](52-prove-capabilities-with-real-operations.md) · [Next lesson](54-check-the-bytes-of-a-c-test-fixture.md)
