<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/cpp20-keyword-reference/01-values-and-types.md

PURPOSE:
Read C++20 type and literal keywords and predict which values they represent.

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

# Name the kind of value

[Course contents](index.md) · [Next lesson — Choose what happens next](02-decisions-and-loops.md)

## What you will learn

Read C++20 type and literal keywords and predict which values they represent.

## Read the words in context

A **type** tells the compiler what kind of value you intend to store or return. A **literal** represents a value written directly in source code. Read each example separately. Some examples use a name that a surrounding program would read later.

## Reserved keywords in this lesson

| Spelling | Meaning | Read this example |
| --- | --- | --- |
| `bool` | Stores one of two truth values. | `bool has_receipt = true;` |
| `true` | The positive truth value of type bool. | `bool receipt_saved = true;` |
| `false` | The other truth value of type bool. | `bool report_ready = false;` |
| `void` | A function returning void gives its caller no result value. | `void pause_preview() { }` |
| `char` | Stores one ordinary character code unit. Use single quotes for a character literal. | `char initials = 'B';` |
| `char8_t` | Stores one UTF-8 code unit. A visible character can require more than one code unit. | `char8_t letter = u8'B';` |
| `char16_t` | Stores one UTF-16 code unit. | `char16_t letter = u'B';` |
| `char32_t` | Stores one UTF-32 code unit. | `char32_t letter = U'B';` |
| `wchar_t` | The wide character type. Its size and encoding depend on the implementation. | `wchar_t letter = L'B';` |
| `short` | A signed integer type by default, with at least 16 bits of width. | `short ticket_count = 26;` |
| `int` | The usual choice for a small whole number that may be negative. | `int movement = -8;` |
| `long` | An integer type with at least 32 bits of width. Its actual width varies across platforms. | `long record_count = 80000L;` |
| `signed` | Explicitly chooses a signed integer type. The value can be negative, zero or positive. | `signed int change = -8;` |
| `unsigned` | Chooses an unsigned integer type. Arithmetic is modulo the range size. | `unsigned int item_count = 4u;` |
| `float` | A floating-point type. Use f after a decimal literal to make it a float literal. | `float step = 0.25f;` |
| `double` | A floating-point type with at least as much precision and range as float. | `double rate = 0.05;` |
| `enum` | Declares a set of named values. enum class places the names inside the chosen type. | `enum class ReceiptState { Pending, Posted };` |
| `nullptr` | An empty pointer value. A pointer can hold the location of an object or hold no location. | `int* receipt_total = nullptr;` |

## Compare with C23

C23 and C++20 share spellings such as bool, true, false, nullptr and int. They still have different type rules and libraries. C++20's char8_t is a builtin type keyword, while C23 provides char8_t as a typedef from its standard header. Use the keyword catalogue for the language of the file you are reading.

## Try it and check

Choose types for a posted flag, a signed movement of −25 cents and a value that identifies no selected row.

**Check:** Use bool for the flag, int for this small signed movement and a suitable pointer initialised with nullptr for the missing row. A money amount in whole cents can use an integer with an explicitly chosen range.

## Apply it to an Umicom project

Sketch fields for a synthetic Umicom Bank receipt. Write the type, unit and two sample values for each field before entering code in Umicom Studio.

[Find the Umicom application repositories](../../../umicom/repositories.md).

[Open the browser lesson](../../../courses/cpp20-keyword-reference/lessons/01-values-and-types.html)

[Course contents](index.md) · [Next lesson — Choose what happens next](02-decisions-and-loops.md)
