# Design a small programming language in C

Creating a language means deciding what programs mean, not just accepting familiar-looking words. **Syntax** describes how a program is written. **Semantics** describes what it does. An implementation needs both, together with rules for failure and resource use.

## Begin with a small contract

The current Umicom C language accepts one return expression with signed 32-bit arithmetic. This makes its rules small enough to explain and test. Write those rules before adding another feature: which spellings are accepted, how values are represented, how operators group and what happens on an error.

For example, the current literal reader treats leading-zero numbers as decimal. That is a deliberate description of this prototype, not a claim of complete ISO C compatibility. Its grammar also has no variable declarations, loops, pointers, function calls or garbage collector.

## Walk through a proposed feature

Suppose you want a remainder operator written `%`. This is a design exercise; it is not currently implemented.

1. Specify its accepted operands and its grouping with multiplication and division.
2. Specify behaviour for zero divisors and negative inputs. Explain the choice with examples.
3. Add a token in the lexer and a parsing rule at the correct precedence level.
4. Define an instruction and its validation and execution rules. Do not bypass the arithmetic checks.
5. Decide how the serialized format changes and how older runtimes reject unsupported instructions.
6. Add tests for normal results, boundaries, malformed bytecode and source diagnostics.
7. Update the public language and bytecode references, examples and teaching material.

A feature is incomplete if the parser accepts it but the runtime cannot execute it, or if a file format silently changes without a compatibility rule.

## Reuse through Framework

The shared preview adapter in `Umicom-Applications/framework/src/toolchain/cvm_preview.c` calls the compiler and runtime through their public interface. It tracks whether an attempt is compiling, executing or complete. That reusable service can support application interfaces without each application inventing its own result-handling rules.

The present adapter is a standalone example. It is not yet a fully integrated Studio compiler, debugger or project builder. Keep those integration steps separate from the language's own correctness.

## Why adding another language is a larger task

Two languages can use similar symbols but disagree about number conversion, exceptions, object lifetime and libraries. A tag saying “this section is another language” cannot resolve those differences by itself. A design needs an explicit subset, translation rules and a boundary between runtime systems.

Likewise, garbage collection is a policy for finding and reclaiming unused managed memory. It does not automatically protect native pointer accesses, device registers or foreign-library calls. Start by defining ownership and capabilities for each kind of value.

## Exercise

Write a one-page proposal for named integer variables. Define declaration, assignment, use-before-definition, scope, storage limits and error messages. Which of the existing compiler stages would need to change?

<details>

<summary>Explanation</summary>

The lexer needs general names, the parser needs statements, and semantic analysis needs a table of names and their meaning. The runtime needs storage and instructions for loading and storing values. Limits, diagnostics, serialization and tests must change together. A few new keywords alone would not finish the feature.

</details>

## Find the implementation

Open `umicom-c/docs/language.md` in your Umicom source collection. Read the named functions alongside this lesson. Source reading and the expected outcomes below are not evidence of an executed build.

---

[Read this lesson in HTML](../../../courses/building-a-compiler-in-c/lessons/09-designing-a-language.html) · [Learning sequence](../../../start/learning-sequence.md)
