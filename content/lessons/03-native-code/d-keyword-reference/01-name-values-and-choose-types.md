<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/d-keyword-reference/01-name-values-and-choose-types.md

PURPOSE:
Give a value a name and choose words that fit numbers, truth flags and text units.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Name values and choose D types

[Course contents](index.md) · [Next lesson: Choose, repeat and stop in D](02-choose-repeat-and-stop.md)

Give a value a name and choose words that fit numbers, truth flags and text units.

## Read a type and a value

A type describes the values a name can hold. Read `int cents = 425;` as giving the name cents a whole-number value of 425. D’s `int` is 32 bits. C also spells its ordinary signed integer `int` and lets the implementation choose its width within the standard’s requirements.

## Choose a type that preserves meaning

Keep signed integer amounts for these practice balances so a refund can be negative. Choose a floating type for an approximate measurement. UTF-8 and UTF-16 strings can need more than one code unit to represent a character, so a single character type does not model every letter or symbol.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `auto` | `auto cents = 425;` | Let the initializer determine the local variable’s type. |
| `bool` | `bool posted = true;` | Store one of the two truth values. |
| `true` | `bool visible = true;` | Set a flag to yes. |
| `false` | `bool checked = false;` | Set a flag to no. |
| `byte` | `byte adjustment = -25;` | Use an 8-bit signed integer. |
| `ubyte` | `ubyte count = 25;` | Use an 8-bit unsigned integer. |
| `short` | `short temperature = -25;` | Use a 16-bit signed integer. |
| `ushort` | `ushort shelf = 425;` | Use a 16-bit unsigned integer. |
| `int` | `int movement = -425;` | Use a 32-bit signed integer. |
| `uint` | `uint count = 425;` | Use a 32-bit unsigned integer. |
| `long` | `long total = 5_000_000_000;` | Use a 64-bit signed integer. |
| `ulong` | `ulong units = 5_000_000_000;` | Use a 64-bit unsigned integer. |
| `float` | `float measure = 1.25f;` | Use a 32-bit binary floating point value for a measurement. |
| `double` | `double measure = 1.25;` | Use a 64-bit binary floating point value. |
| `real` | `real measure = 1.25L;` | Use the implementation’s highest-precision built-in binary floating type. |
| `char` | `char latin = 'A';` | Store one UTF-8 code unit. This basic Latin character takes a single unit. |
| `wchar` | `wchar latin = 'A';` | Store one UTF-16 code unit. |
| `dchar` | `dchar latin = 'A';` | Store one UTF-32 code unit. |
| `cast` | `int whole = cast(int) 4.75;` | Request a conversion. This conversion truncates the fractional part. |
| `null` | `int* selected = null;` | Store a pointer value that names no object. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
START at 425 cents
ADD a signed adjustment of -25
SHOW the resulting cents and the posted flag
```

## Run the complete example

Save the whole program as `practice.d`. Open a terminal in that folder, then enter the command shown for your language.

```d
import std.stdio : writeln;

void main()
{
    int cents = 425;
    byte adjustment = -25;
    bool posted = true;
    writeln(cents + adjustment, " ", posted ? "yes" : "no");
}
```

```text
dmd -run practice.d
```

Expected output

```text
400 yes
```

If the terminal cannot find dmd, check the D compiler installation for your operating system. If your course uses another documented D compiler, use its build and run instructions. You can still trace the example without installing a compiler.

## Try a change

Choose a type for a counter that may reach 300 and a type for an adjustment of -25. Explain why the two choices can differ.

**Check your answer**

An unsigned `ushort` fits 300, while a signed `byte` fits -25. An 8-bit unsigned value reaches at most 255.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Continue Learning D](../../../courses/learning-d/index.html)
- [D language specification, Lexical grammar and Keywords](https://dlang.org/spec/lex.html)
