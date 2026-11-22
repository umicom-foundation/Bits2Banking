<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/d-special-token-reference/03-stop-reading-at-a-marker.md

PURPOSE:
Compare an end-of-source marker with the return statement in a tiny D program.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Stop reading source at an explicit marker

[Course contents](index.md) · [Previous lesson: Record which compiler read a program](02-record-compiler-identity.md) · [Next lesson: Map a diagnostic back to source](04-map-a-diagnostic-back-to-source.md)

Compare an end-of-source marker with the return statement in a tiny D program.

## Find where reading stops

`__EOF__` marks the scanner's end of input. It belongs in the source text and affects what the compiler reads. A `return` statement belongs inside a function and affects what happens when that function runs.

## Try a visible check

The sample below has two functions with the same name and signature on opposite sides of the marker. Only the first definition reaches the compiler. Keep this a disposable teaching file. Moving the marker can change the compiled program even though the later text remains visible in the editor.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `__EOF__` | `__EOF__` | Stop the scanner at this token. Later text is left outside the program's token stream. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
READ source until the marker
BUILD only the code the scanner passed along
RUN the first main function
```

## Run the complete example

Save the whole program as `practice.d`. Open a terminal in that folder, then enter the command shown for your language.

```d
import std.stdio : writeln;

void main()
{
    writeln("scanner stopped");
}

__EOF__

void main()
{
    writeln("second body");
}
```

```text
dmd -run practice.d
```

Expected output

```text
scanner stopped
```

If the terminal cannot find dmd, check the D compiler installation for your operating system. If your course uses another documented D compiler, use its build and run instructions. You can still trace the example without installing a compiler.

## Try a change

Remove just the line that contains the marker. Predict what a compiler will report before trying the change. Restore the marker afterwards.

**Check your answer**

Now both definitions enter the source program. A compiler should reject the duplicate `main` definitions.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Continue Learning D](../../../courses/learning-d/index.html)
- [D language specification, Special Tokens](https://dlang.org/spec/lex.html#specialtokens)
