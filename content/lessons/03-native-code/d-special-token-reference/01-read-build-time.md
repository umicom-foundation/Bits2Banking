<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/d-special-token-reference/01-read-build-time.md

PURPOSE:
Use three D special tokens to learn which information is chosen when the compiler reads a program.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Read the date and time of a build

[Course contents](index.md) · [Next lesson: Record which compiler read a program](02-record-compiler-identity.md)

Use three D special tokens to learn which information is chosen when the compiler reads a program.

## Distinguish build time from run time

A compiler reads your source text and prepares a program that you can run later. The scanner is the part that reads characters and groups them into tokens. D replaces the three special tokens shown here while scanning. If you run the same executable again without compiling, these strings keep the same values.

## Check the shape of the result

Expect three labelled lines, with actual values filled in by your compiler. The sample output below is illustrative. The text represents the build's clock, so treat it as a clue when comparing classroom builds. Use a fixed, reviewed build identity if you require results that can be reproduced.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `__DATE__` | `writeln(__DATE__);` | Print the date chosen at compilation in the documented month, day and year form. |
| `__TIME__` | `writeln(__TIME__);` | Print the time chosen at compilation in the documented hour, minute and second form. |
| `__TIMESTAMP__` | `writeln(__TIMESTAMP__);` | Print the documented combined timestamp, which also includes a weekday. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
AT COMPILE TIME, capture date and time text
AT RUN TIME, show the captured text
```

## Run the complete example

Save the whole program as `practice.d`. Open a terminal in that folder, then enter the command shown for your language.

```d
import std.stdio : writeln;

void main()
{
    writeln("date ", __DATE__);
    writeln("time ", __TIME__);
    writeln("stamp ", __TIMESTAMP__);
}
```

```text
dmd -run practice.d
```

Expected output

```text
date Nov 22 2026
time 09:30:00
stamp Sun Nov 22 09:30:00 2026
```

If the terminal cannot find dmd, check the D compiler installation for your operating system. If your course uses another documented D compiler, use its build and run instructions. You can still trace the example without installing a compiler.

## Try a change

Imagine compiling this program twice, one minute apart. Then imagine running the first executable twice. Which action can change the embedded values?

**Check your answer**

A new compile can embed different clock values. Running one unchanged executable again does not substitute new text.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Continue Learning D](../../../courses/learning-d/index.html)
- [D language specification, Special Tokens](https://dlang.org/spec/lex.html#specialtokens)
