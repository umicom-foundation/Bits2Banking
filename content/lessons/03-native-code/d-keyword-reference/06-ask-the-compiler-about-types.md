<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/d-keyword-reference/06-ask-the-compiler-about-types.md

PURPOSE:
Use a short template, a compile-time assertion and keywords that report what the compiler sees.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Ask the compiler about a type

[Course contents](index.md) · [Previous lesson: Organise source and name a boundary](05-organise-source-and-boundaries.md) · [Next lesson: Handle a failure and plan shared work](07-handle-failures-and-shared-work.md)

Use a short template, a compile-time assertion and keywords that report what the compiler sees.

## Ask a question before the program runs

A template lets the compiler fill a pattern with a specific type. `CountType!int` supplies int to this pattern. The compile-time assertion checks that the resulting alias is really int. The learner can trace that substitution with pencil and paper.

## Separate compiler facts from runtime values

A compiler can report types, source locations and declarations while translating a file. A runtime value comes from executing the program. C has tools such as `typeof`, `static_assert` and predefined source-location macros. D’s reflection and template syntax have their own rules.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `alias` | `alias WholeCents = int;` | Give the existing type a second name. |
| `static` | `static assert(is(WholeCents == int));` | Require an assertion during compilation. static also has storage and conditional-declaration uses. |
| `template` | `template CountType(T) { alias CountType = T; }` | Define a declaration pattern using a parameter supplied when it is used. |
| `mixin` | `mixin("int total = 425;");` | Ask the compiler to read this fixed string as source text. Use trusted, reviewed literals in this example. |
| `is` | `static assert(is(typeof(425) == int));` | Ask a compile-time question about types. D also uses is to compare identity in expressions. |
| `typeof` | `typeof(425) cents = 25;` | Use the type of this expression in a declaration. |
| `typeid` | `writeln(typeid(int));` | Request type information for use by the running program. |
| `unittest` | `unittest { assert(expected_rows() == 3); }` | Define a test block that runs when the selected build enables D unit tests. |
| `__parameters` | `static assert(is(typeof(sample) == __parameters));` | Use the type-test form for a declared function, delegate or function pointer. Here sample names a function. |
| `__traits` | `static assert(__traits(isIntegral, int));` | Ask a supported compiler query about a declaration or type. |
| `__rvalue` | `auto next = __rvalue(value);` | Request rvalue treatment of a value with a location. Move-aware types and recent compiler support determine the effect. |
| `__vector` | `alias Lane = __vector(int[4]);` | Describe a built-in vector type when the compiler and CPU target support this shape. |
| `__FILE__` | `writeln(__FILE__);` | Ask for the source file name. Exact path presentation can vary. |
| `__FILE_FULL_PATH__` | `writeln(__FILE_FULL_PATH__);` | Ask for the absolute source path at this use. Inspect it in a local working copy. |
| `__FUNCTION__` | `writeln(__FUNCTION__);` | Ask for the qualified function name here. |
| `__LINE__` | `writeln(__LINE__);` | Ask for the current logical line number. A line mapping may change it. |
| `__MODULE__` | `writeln(__MODULE__);` | Ask for the module name here. |
| `__PRETTY_FUNCTION__` | `writeln(__PRETTY_FUNCTION__);` | Ask for a function description with details such as types and attributes. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
FILL the type pattern with int
CHECK that the resulting type is int
DURING the run, give that type a value of 425 and show it
```

## Run the complete example

Save the whole program as `practice.d`. Open a terminal in that folder, then enter the command shown for your language.

```d
import std.stdio : writeln;

template CountType(T)
{
    alias CountType = T;
}

alias WholeCents = CountType!int;
static assert(is(WholeCents == int));

void main()
{
    WholeCents amount = 425;
    writeln(amount);
}
```

```text
dmd -run practice.d
```

Expected output

```text
425
```

If the terminal cannot find dmd, check the D compiler installation for your operating system. If your course uses another documented D compiler, use its build and run instructions. You can still trace the example without installing a compiler.

## Try a change

Change CountType!int to CountType!long and leave the assertion as it is. Predict what the build reports.

**Check your answer**

The assertion expects an int alias, but the template now supplies long. Translation should stop with a failed assertion.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Continue Learning D](../../../courses/learning-d/index.html)
- [D language specification, Lexical grammar and Keywords](https://dlang.org/spec/lex.html)
