<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/cpp20-keyword-reference/03-declarations-and-storage.md

PURPOSE:
Distinguish declarations that infer a type, qualify access, control storage, or inspect an object's size.

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

# Declare names, storage and size

[Course contents](index.md) · [Previous lesson — Choose what happens next](02-decisions-and-loops.md) · [Next lesson — Organise data and actions into objects](04-objects-and-names.md)

## What you will learn

Distinguish declarations that infer a type, qualify access, control storage, or inspect an object's size.

## Read the words in context

A **declaration** introduces a name and gives the compiler information about it. **Storage duration** is how long storage exists. **Linkage** determines whether declarations can refer to the same entity across scopes or source files. **Alignment** places an object at an address that meets a boundary requirement.

## Reserved keywords in this lesson

| Spelling | Meaning | Read this example |
| --- | --- | --- |
| `auto` | Lets the compiler infer a type from an initializer in this example. | `auto movement = 25;` |
| `decltype` | Names the type determined from an expression or entity. The form can preserve references. | `int planned = 25; decltype(planned) actual = 24;` |
| `const` | Prevents modification through that const view. | `const int posted_cents = 1750;` |
| `volatile` | Marks accesses that must follow volatile rules. It provides neither atomic operations nor inter-thread synchronisation by itself. | `volatile int simulation_input = 0;` |
| `static` | Inside a function, gives a local variable static storage duration. Other uses include class members and file-level names. | `int next_id() { static int id = 0; return ++id; }` |
| `extern` | Can declare a variable defined elsewhere, allowing another file to use it. | `extern int saved_receipt_count;` |
| `inline` | Allows suitable identical definitions in multiple source-file translation units when the rules are met. The compiler chooses whether to inline calls. | `inline int one_cent() { return 1; }` |
| `thread_local` | Provides separate storage for each thread, an independently scheduled path of execution. | `thread_local int thread_receipt_count = 0;` |
| `mutable` | Allows an eligible member to change even through a const instance of its class. | `struct CacheCount { mutable int reads = 0; };` |
| `typedef` | Introduces another name for an existing type without creating a new type. | `typedef int CentCount;` |
| `using` | Can introduce a type alias, or bring a name into a scope in other forms. | `using CentCount = int;` |
| `alignas` | Requests an alignment for an object or type. The requested alignment must meet language and implementation constraints. | `alignas(int) unsigned char sample = 0;` |
| `alignof` | Reports a type's alignment requirement in bytes. | `auto boundary = alignof(int);` |
| `sizeof` | Reports a type or object's size in bytes. Different platforms can report different results. | `auto cents_bytes = sizeof(int);` |

## Try it and check

After calling next_id twice from the same thread in this simple program, what are the two results? What changes if the local variable stops using static?

**Check:** The results are 1 then 2. With a fresh automatic local variable initialised to zero on each call, both results are 1.

## Apply it to an Umicom project

Sketch an Umicom Studio example for a call counter and a constant configuration value. Use names that say which can change and print the values after two calls.

[Find the Umicom application repositories](../../../umicom/repositories.md).

[Open the browser lesson](../../../courses/cpp20-keyword-reference/lessons/03-declarations-and-storage.html)

[Course contents](index.md) · [Previous lesson — Choose what happens next](02-decisions-and-loops.md) · [Next lesson — Organise data and actions into objects](04-objects-and-names.md)
