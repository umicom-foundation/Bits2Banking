<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/d-special-token-reference/02-record-compiler-identity.md

PURPOSE:
Separate a compiler's vendor name and encoded version from the version of your teaching example.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Record which compiler read a program

[Course contents](index.md) · [Previous lesson: Read the date and time of a build](01-read-build-time.md) · [Next lesson: Stop reading source at an explicit marker](03-stop-reading-at-a-marker.md)

Separate a compiler's vendor name and encoded version from the version of your teaching example.

## Read the report as evidence

A vendor is whoever supplies the compiler. A version identifies an edition of that compiler. D lets an implementation choose the text and integer used here. A number such as 2100 is an illustration, rather than a number every compiler must print.

## Write a short troubleshooting note

When a keyword example behaves differently in Umicom Studio and a terminal, save the command, compiler identity, exact output and source filename together. A version printed inside this program describes the compiler that built it. The program has its own source history and might be unchanged.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `__VENDOR__` | `writeln(__VENDOR__);` | Print an implementation-defined description of the compiler vendor. |
| `__VERSION__` | `writeln(__VERSION__);` | Print the integer version supplied by the compiler implementation. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
ASK the scanner for the tool's vendor text and version integer
SHOW them as two clearly labelled results
```

## Run the complete example

Save the whole program as `practice.d`. Open a terminal in that folder, then enter the command shown for your language.

```d
import std.stdio : writeln;

void main()
{
    writeln("vendor ", __VENDOR__);
    writeln("version ", __VERSION__);
}
```

```text
dmd -run practice.d
```

Expected output

```text
vendor a compiler-provided description
version 2100
```

If the terminal cannot find dmd, check the D compiler installation for your operating system. If your course uses another documented D compiler, use its build and run instructions. You can still trace the example without installing a compiler.

## Try a change

Would you compare the exact version line against 2100 in a lesson meant to run on many D compilers? Explain your choice.

**Check your answer**

Check that the result is an integer and record its actual value. Use an exact literal only when a particular documented compiler version is part of the exercise.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Continue Learning D](../../../courses/learning-d/index.html)
- [D language specification, Special Tokens](https://dlang.org/spec/lex.html#specialtokens)
