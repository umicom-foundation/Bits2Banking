<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/cpp20-keyword-reference/07-module-and-coroutine-spellings.md

PURPOSE:
Recognise module and coroutine syntax and tell when an example requires a configured toolchain or intentionally fails.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom">
</picture>

# Read modules, coroutines and reserved words

[Course contents](index.md) · [Previous lesson — Ask the compiler to compute and check](06-compile-time-and-templates.md) · [Next lesson — Read word forms of operators](08-alternative-operator-tokens.md)

## What you will learn

Recognise module and coroutine syntax and tell when an example requires a configured toolchain or intentionally fails.

## Read the words in context

A **module** groups declarations with an interface other source files can import. A **coroutine** is a function whose execution can suspend and resume. Its return type and associated promise type describe how suspension, results and cleanup work. Each coroutine line below is a fragment from a coroutine with a suitable return type and promise. Module declarations go in appropriately configured module source files.

## Reserved keywords in this lesson

| Spelling | Meaning | Read this example |
| --- | --- | --- |
| `export` | In C++20 modules, can make a declaration visible to importers. The declaration example goes inside a module interface unit. | `export int count_receipts();` |
| `co_await` | Awaits an operation in a coroutine. With the coroutine header, this example chooses an awaitable that does not suspend. | `co_await std::suspend_never{};` |
| `co_return` | Ends a coroutine and follows the promise's completion protocol. Here the promise provides return_void. | `co_return;` |
| `co_yield` | Sends a value to the promise's yield_value operation as part of coroutine suspension handling. | `co_yield 25;` |
| `asm` | A conditionally supported declaration. An empty instruction string here is shown as syntax only. Actual meaning depends on the compiler and target. | `asm("");` |
| `register` | Reserved and unused in C++20. The historical storage-class declaration is intentionally invalid in C++20. | `register int count = 3;` |

## Contextual spellings

| Spelling | Meaning | Read this example |
| --- | --- | --- |
| `module` | Declares the named module in this lexical context. The word also has ordinary identifier uses outside the special context, subject to the module-name rules. | `export module receipt_totals;` |
| `import` | Makes the exported module declarations available here. The word can also have ordinary identifier uses outside the special syntax. | `import receipt_totals;` |

## Check the entry context

final and override have special meaning in suitable class declarations. import and module have special lexical forms in the module grammar. The ordinary declaration `int import = 1, module = 2;` is allowed. C++20 counting keeps these two special spellings separate from the unconditionally reserved Table 5 inventory. The spelling export is already in Table 5.

## Try it and check

Write the order of work if one file declares export module receipt_totals and another uses import receipt_totals. Which one must the build make available first?

**Check:** Build or register the module interface first so the importing file can use its exported declarations. The representation used by the toolchain for the interface can vary. The register declaration in this lesson is an intentionally rejected check in strict C++20.

## Apply it to an Umicom project

Sketch an Umicom Studio build graph with two source files and a dependency from the importer to the module interface. Use a C++20-enabled practice project and compare the actual compiler documentation before choosing module flags.

[Find the Umicom application repositories](../../../umicom/repositories.md).

[Open the browser lesson](../../../courses/cpp20-keyword-reference/lessons/07-module-and-coroutine-spellings.html)

[Course contents](index.md) · [Previous lesson — Ask the compiler to compute and check](06-compile-time-and-templates.md) · [Next lesson — Read word forms of operators](08-alternative-operator-tokens.md)
