<!--
Umicom Bits2Banking
File: content/lessons/ai/native-local-ai-and-media/19-language-translation-and-runtime-contracts.md

PURPOSE:
Teach why Python or Java to C needs a language contract.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Why Python or Java to C needs a language contract

Translating a language means preserving its observable behavior, including errors and resource ownership. Replacing familiar-looking syntax is insufficient. A compiler needs a parser, semantic rules, an intermediate representation, code generation and whatever runtime services the language requires.

## Choose a small supported subset

Umicom C currently documents a bounded integer language and bytecode runtime. It supports specified arithmetic, comparisons, local integer values and forward-expression control flow. Its capability profile reports the linked implementation. It is not yet a general native C23 compiler with all headers, external symbols, object files and system-library linkage.

Making Framework easier to find is a toolchain integration task: include paths, package discovery, library selection and ABI checks. It should remain an explicit SDK dependency. Automatically injecting every Framework library into every program would hide size, platform and dependency choices. It also would not implement Python or Java semantics.

## Use a counterexample before designing a translator

```text
Python integer: 2147483647 + 1 -> 2147483648
Java int addition at runtime: 2147483647 + 1 -> -2147483648
C signed 32-bit overflow: undefined behavior
```

Those expressions look similar but require different lowering rules. A Python-compatible implementation needs arbitrary-precision arithmetic for that case. A Java-compatible implementation needs the specified wrap behavior. A bounded educational language may reject overflow instead. Choose and document the language rather than silently borrowing the host C behavior. See the [Python numeric types](https://docs.python.org/3/library/stdtypes.html#numeric-types-int-float-complex) and [Java integer operations](https://docs.oracle.com/javase/specs/jls/se25/html/jls-4.html#jls-4.2.2) specifications.

## Plan a staged implementation

1. Publish a subset grammar and explicitly reject unsupported constructs with source locations. Start with pure typed expressions, not arbitrary libraries.
2. Define integer widths, overflow, booleans, evaluation order and exceptions before emitting C.
3. Lower to a typed intermediate representation whose operations have explicit semantics.
4. Generate C that implements those semantics using checked or defined operations. Keep a source map for diagnostics.
5. Compile the generated C with an identified native compiler. Link only the required runtime and optional Framework components.
6. Compare source-interpreter and generated-program results over both valid and rejected cases. Include failures, not just successful arithmetic.

## Runtime questions

For a larger Python subset, decide how objects, reference lifetimes, imports and dynamic dispatch work. For Java, address classes, initialization, garbage collection, exceptions and library behavior. Converting TensorFlow or PyTorch model artifacts is a different project from preserving every behavior of their Python authoring programs.

## Exercise

Specify a translator for a function taking two signed 32-bit integers and returning their sum. List its accepted syntax, overflow outcome, generated function ABI and diagnostic location rules. Do not implement a regex-based source rewrite and call it a compiler. The expected deliverable is a precise, testable contract; this lesson does not claim an implemented Python or Java frontend.

[Course contents](index.md) · [Previous lesson](18-pytorch-export-and-target-runtimes.md) · [Next lesson](20-plan-shared-ai-services.md)
