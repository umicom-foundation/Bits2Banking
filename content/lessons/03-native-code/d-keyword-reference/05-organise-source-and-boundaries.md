<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/d-keyword-reference/05-organise-source-and-boundaries.md

PURPOSE:
Separate helpers from interfaces and recognise words that depend on a build or target.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Organise source and name a boundary

[Course contents](index.md) · [Previous lesson: Group and protect related data](04-group-and-protect-data.md) · [Next lesson: Ask the compiler about a type](06-ask-the-compiler-about-types.md)

Separate helpers from interfaces and recognise words that depend on a build or target.

## Find the file boundary

A module is a named unit of source code. Use an import for a library operation. Keep a helper private when callers only need its public result. C uses headers and linkage for many related purposes, with different language and build rules.

## Recheck the target before using a tool-specific form

An ABI is a published agreement about how compiled code calls functions and lays out values. `extern(C)`, `export`, `align` and `asm` need the relevant agreement and compiler support. For an Umicom module, start with a tiny checked interface and a documented test rather than assuming that matching function names are enough.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `module` | `module practice;` | Give this source module a name, normally at the start of the file. |
| `import` | `import std.stdio : writeln;` | Make the named library operation available in this module. |
| `private` | `private int fixture_count() { return 3; }` | Limit this declaration’s visibility to the module. |
| `public` | `public int rows() { return 3; }` | Expose the declaration through the module’s public interface. |
| `protected` | `protected int limit;` | Inside a class, use access intended for its inheritance boundary. |
| `package` | `package int lookup() { return 3; }` | Limit access to the enclosing package according to D’s visibility rules. |
| `extern` | `extern(C) int add_cents(int left, int right);` | Declare the C calling and naming convention for the function. A matching definition must be linked. |
| `export` | `export extern(C) int lesson_count() { return 3; }` | Mark an external symbol for export on targets and build configurations that support it. |
| `pragma` | `pragma(msg, "checking lesson");` | Ask the compiler to apply this supported pragma. msg can display a message during compilation. |
| `debug` | `debug { writeln("checking fixture"); }` | Include a block in a build that enables this D debug condition. |
| `version` | `version(Workbook) { enum has_workbook = true; }` | Include a declaration if the selected version condition matches. |
| `align` | `align(8) struct Cell { int value; }` | Request an alignment for the aggregate. Verify layout for the chosen ABI. |
| `asm` | `asm { nop; }` | Embed one idle instruction in the compiler’s inline assembler when supported by the target. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
ASK the public row-count function
LET the private helper count the three fixture rows
SHOW the public result
```

## Run the complete example

Save the whole program as `practice.d`. Open a terminal in that folder, then enter the command shown for your language.

```d
module practice;

import std.stdio : writeln;

private int fixture_count()
{
    return 3;
}

public int expected_rows()
{
    return fixture_count();
}

void main()
{
    writeln("rows ", expected_rows());
}
```

```text
dmd -run practice.d
```

Expected output

```text
rows 3
```

If the terminal cannot find dmd, check the D compiler installation for your operating system. If your course uses another documented D compiler, use its build and run instructions. You can still trace the example without installing a compiler.

## Try a change

Which function would another module use to read the row count? Which function name can change without changing that public call?

**Check your answer**

Another module imports and calls `expected_rows`. The private `fixture_count` helper may be renamed along with its call inside this module.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Continue Learning D](../../../courses/learning-d/index.html)
- [D language specification, Lexical grammar and Keywords](https://dlang.org/spec/lex.html)
