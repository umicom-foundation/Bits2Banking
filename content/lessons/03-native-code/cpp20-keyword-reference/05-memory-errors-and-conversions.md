<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/cpp20-keyword-reference/05-memory-errors-and-conversions.md

PURPOSE:
Recognise allocation, exception handling and named conversions, and predict the result of a checked conversion.

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

# Read ownership, errors and conversions

[Course contents](index.md) · [Previous lesson — Organise data and actions into objects](04-objects-and-names.md) · [Next lesson — Ask the compiler to compute and check](06-compile-time-and-templates.md)

## What you will learn

Recognise allocation, exception handling and named conversions, and predict the result of a checked conversion.

## Read the words in context

A **pointer** may refer to an object by its address. **Dynamic storage** holds objects created during execution until their lifetime ends. An **exception** transfers control to a matching handler by carrying a thrown value. A **cast** requests a conversion between types. Match the cast to the language rule shown.

## Reserved keywords in this lesson

| Spelling | Meaning | Read this example |
| --- | --- | --- |
| `new` | Creates an object with dynamic storage. This example transfers responsibility for releasing it to the code holding owned. | `int* owned = new int{5};` |
| `delete` | Destroys and releases a matching object allocated by scalar new. Do not use a pointer to read the released object. | `delete owned; owned = nullptr;` |
| `try` | Introduces a block whose exceptions can be handled by the following catch clauses. | `try { throw 7; } catch (int code) { observed = code; }` |
| `catch` | Introduces an exception handler. Here it matches a thrown int. | `catch (int code) { observed = code; }` |
| `throw` | Raises an exception. This example throws one int value from a try block. | `throw 7;` |
| `noexcept` | After a function declarator, can declare that exceptions do not escape the function. An escaping exception would terminate the program. | `int zero_cents() noexcept { return 0; }` |
| `const_cast` | Changes access qualifiers in specific conversions. Here the underlying object was already writable. | `int value = 3; const int& view = value; const_cast<int&>(view) = 4;` |
| `dynamic_cast` | Checks certain conversions within a polymorphic class hierarchy at runtime. An unsuccessful pointer form yields null. | `Base* base = &report; auto* view = dynamic_cast<Report*>(base);` |
| `reinterpret_cast` | Requests a low-level type reinterpretation. Use with the target type's access rules. This example creates a byte view of number. | `int number = 12; const auto* bytes = reinterpret_cast<const unsigned char*>(&number);` |
| `static_cast` | Requests an explicit conversion using the relevant language rules. A representable fractional value converted to int is truncated toward zero. | `int whole = static_cast<int>(2.75);` |
| `typeid` | Reports type information. Include the typeinfo header to compare the results in this example. | `bool equivalent = typeid(12) == typeid(int);` |

## Check who owns an object

Find the new and delete snippets. In a full program, these two statements belong to the same ownership plan. The C++ library supplies ownership types that can release an object automatically at the end of its lifetime. C programs commonly pair allocation and release calls such as malloc and free. The two families have different contracts.

For the dynamic_cast row, assume Base declares a virtual function and Report publicly derives from it. report is a live object of type Report. The unchecked cast to an unsigned character pointer serves a different purpose, and the byte order depends on the platform.

## Try it and check

What value does whole receive? Why is a null result useful when a base pointer does not refer to the requested derived report type?

**Check:** whole receives 2. A null result lets you handle a mismatched object without treating it as a Report. Check the result before accessing derived members.

## Apply it to an Umicom project

Sketch how a practice Umicom Studio report preview could describe a missing or incompatible report in plain language. Use a controlled fixture to compare an expected error with an unexpected outcome.

[Find the Umicom application repositories](../../../umicom/repositories.md).

[Open the browser lesson](../../../courses/cpp20-keyword-reference/lessons/05-memory-errors-and-conversions.html)

[Course contents](index.md) · [Previous lesson — Organise data and actions into objects](04-objects-and-names.md) · [Next lesson — Ask the compiler to compute and check](06-compile-time-and-templates.md)
