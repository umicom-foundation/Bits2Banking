<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/d-keyword-reference/08-recognise-reserved-and-historical-words.md

PURPOSE:
Read an older source listing and choose a current teaching form for new code.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Recognise reserved and historical D words

[Course contents](index.md) · [Previous lesson: Handle a failure and plan shared work](07-handle-failures-and-shared-work.md) · [Continue to Continue Learning D](../../../courses/learning-d/index.html)

Read an older source listing and choose a current teaching form for new code.

## Recognise the status before copying a line

The keyword list in D’s lexical reference strikes through ten historical spellings. This table keeps those entries visible to help you read older examples. The separate unstruck `macro` spelling is reserved. Treat the examples here as reading practice and use the supported whole program below for a run.

## Use a current contract body

A contract can explain what a caller promises. The current sample writes an `in` condition followed by `do`, then supplies the function body. For complex values in new work, consult the current standard library’s complex type and confirm target support. Keep basic practice amounts as signed whole cents.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `macro` | `int macro = 1;` | Deliberate invalid-name example. The lexical reference reserves this spelling without supplying a usable macro language feature. |
| `body` | `int f(int n) in (n >= 0) body { return n; }` | Historical contract-body spelling. Current D source uses do in this position. |
| `delete` | `delete item;` | Historical deletion statement. Check current lifetime rules and library facilities such as destroy for the actual object contract. |
| `cent` | `cent total;` | Historical signed 128-bit type spelling marked deprecated in the D type reference. Use a supported type or library with a stated range. |
| `ucent` | `ucent total;` | Historical unsigned 128-bit type spelling marked deprecated in the D type reference. |
| `cfloat` | `cfloat signal = 2.0f + 1.0fi;` | Historical complex floating type with float components. |
| `cdouble` | `cdouble signal = 2.0 + 1.0i;` | Historical complex floating type with double components. |
| `creal` | `creal signal = 2.0L + 1.0Li;` | Historical complex floating type with real components. |
| `ifloat` | `ifloat component = 1.0fi;` | Historical imaginary floating type with a float scalar component. |
| `idouble` | `idouble component = 1.0i;` | Historical imaginary floating type with a double scalar component. |
| `ireal` | `ireal component = 1.0Li;` | Historical imaginary floating type with a real scalar component. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
CHECK that the practice count is at least zero
RUN the function’s main block
RETURN the count and show it
```

## Run the complete example

Save the whole program as `practice.d`. Open a terminal in that folder, then enter the command shown for your language.

```d
import std.stdio : writeln;

int validate_count(int count)
in (count >= 0)
do
{
    return count;
}

void main()
{
    writeln(validate_count(3));
}
```

```text
dmd -run practice.d
```

Expected output

```text
3
```

If the terminal cannot find dmd, check the D compiler installation for your operating system. If your course uses another documented D compiler, use its build and run instructions. You can still trace the example without installing a compiler.

## Try a change

In the old contract fragment, underline the word to update. Which current keyword starts the function’s main block?

**Check your answer**

Replace the historical `body` spelling with `do` for this contract syntax.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Continue Learning D](../../../courses/learning-d/index.html)
- [D language specification, Lexical grammar and Keywords](https://dlang.org/spec/lex.html)
