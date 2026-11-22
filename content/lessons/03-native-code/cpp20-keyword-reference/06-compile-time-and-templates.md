<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/cpp20-keyword-reference/06-compile-time-and-templates.md

PURPOSE:
Distinguish constant evaluation, static checks, reusable type templates and constraints.

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

# Ask the compiler to compute and check

[Course contents](index.md) · [Previous lesson — Read ownership, errors and conversions](05-memory-errors-and-conversions.md) · [Next lesson — Read modules, coroutines and reserved words](07-module-and-coroutine-spellings.md)

## What you will learn

Distinguish constant evaluation, static checks, reusable type templates and constraints.

## Read the words in context

**Compile time** is when the compiler analyses and translates the program. **Run time** is when the program executes. A **template** describes a family of definitions parameterised by values or types. A **constraint** states conditions that determine whether a template can be used in a particular case.

## Reserved keywords in this lesson

| Spelling | Meaning | Read this example |
| --- | --- | --- |
| `constexpr` | Declares a constant expression-capable entity. In this variable example the initializer is known during compilation. | `constexpr int cents_per_unit = 100;` |
| `consteval` | Declares an immediate function. An ordinary call of the kind shown must yield a constant expression. | `consteval int starter() { return 8; } int selected = starter();` |
| `constinit` | Requires constant initialization of this static or thread-storage variable. It does not give the variable const access. | `constinit int receipt_count = 0;` |
| `static_assert` | Checks a constant condition during compilation and stops successful translation if the condition fails. | `static_assert(2 + 3 == 5, "addition check");` |
| `template` | Begins a reusable definition whose parameter can stand for a type or value. | `template <typename T> T unchanged(T value) { return value; }` |
| `typename` | Declares a type parameter in this template. It can also mark a dependent name as a type in a different context. | `template <typename Item> struct Box { Item value; };` |
| `concept` | Names a constraint used to describe valid template arguments. | `template <typename T> concept HasCents = requires (T item) { item.cents; };` |
| `requires` | Introduces a requires-expression here. The expression tests whether the requested operation is well-formed for T. | `template <typename T> constexpr bool has_cents = requires (T item) { item.cents; };` |

## Try it and check

Change 2 + 3 == 5 to 2 + 3 == 7 in a practice copy. What point in the process should report the problem? Does constinit int receipt_count make the variable read-only?

**Check:** The compiler reports a failed static assertion before you run the program. constinit checks initialisation timing. The count in the example remains writable.

## Apply it to an Umicom project

Add a compile-time expected size or policy constant to an Umicom Studio practice build. Keep the message about what the requirement means so a learner can find the problem.

[Find the Umicom application repositories](../../../umicom/repositories.md).

[Open the browser lesson](../../../courses/cpp20-keyword-reference/lessons/06-compile-time-and-templates.html)

[Course contents](index.md) · [Previous lesson — Read ownership, errors and conversions](05-memory-errors-and-conversions.md) · [Next lesson — Read modules, coroutines and reserved words](07-module-and-coroutine-spellings.md)
