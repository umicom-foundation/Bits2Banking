<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/d-keyword-reference/03-pass-values-and-promises.md

PURPOSE:
Trace a call, then see what parameter words tell the person reading it.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Pass values and describe function promises

[Course contents](index.md) · [Previous lesson: Choose, repeat and stop in D](02-choose-repeat-and-stop.md) · [Next lesson: Group and protect related data](04-group-and-protect-data.md)

Trace a call, then see what parameter words tell the person reading it.

## Follow the caller’s value

A function is a group of steps with a name. Parameters label the values supplied for a call. A plain integer parameter receives its own value. The program uses `ref` to pass access to the caller’s variable. This resembles a reference parameter in C++. C can express the same update using a pointer, which has different spelling and rules.

## Read a promise separately from a test

Words such as `pure` and `nothrow` describe restrictions the compiler checks. `assert` is useful for a condition that should hold when the program is correct. Some compiler modes remove assertion checks. A regular validation branch remains necessary when accepting data from people or files.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `void` | `void log_view() { }` | Define a function with no result value. |
| `return` | `int opening() { return 425; }` | Finish a function and give its result to the caller. |
| `ref` | `void add_five(ref int cents) { cents += 5; }` | Let this function work on the caller’s object through the parameter. |
| `in` | `int read_cents(in int cents) { return cents; }` | Declare an input parameter. Check the selected compiler mode for the extra scope and passing rules. |
| `out` | `void reset(out int cents) { cents = 0; }` | Use a result parameter that is initialized to its type’s default as the call begins. |
| `inout` | `inout(int)* same(inout(int)* p) { return p; }` | Relate qualifiers of the return type to those passed in through the parameter. |
| `lazy` | `int calculate(lazy int amount) { return amount; }` | Pass a deferred expression. Using amount requests evaluation; repeated uses can evaluate it again. |
| `pure` | `pure int double_cents(int cents) { return cents * 2; }` | Declare the language’s restriction on access to external mutable state. |
| `nothrow` | `int count_rows() nothrow { return 3; }` | Declare that the function does not propagate exceptions of type Exception. |
| `function` | `alias Calculator = int function(int);` | Name the type of a pointer to a function taking and returning an int. |
| `delegate` | `alias Calculator = int delegate(int);` | Name a callable type that can carry a context as well as code. |
| `deprecated` | `deprecated("use count_rows") int old_count() { return 3; }` | Mark a declaration for migration. A compiler can report use of the older API. |
| `assert` | `assert(total == 425);` | Check a program assumption in a build that executes assertions. Validate normal input in ordinary code too. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
START reserve at 425
CALL add with access to the same reserve
UPDATE reserve by -25
SHOW reserve
```

## Run the complete example

Save the whole program as `practice.d`. Open a terminal in that folder, then enter the command shown for your language.

```d
import std.stdio : writeln;

void add(ref int target, int amount)
{
    target += amount;
}

void main()
{
    int reserve = 425;
    add(reserve, -25);
    writeln(reserve);
}
```

```text
dmd -run practice.d
```

Expected output

```text
400
```

If the terminal cannot find dmd, check the D compiler installation for your operating system. If your course uses another documented D compiler, use its build and run instructions. You can still trace the example without installing a compiler.

## Try a change

Remove ref from the definition and trace where the addition happens. What does the call print?

**Check your answer**

The function updates its own integer parameter. The caller’s reserve remains 425.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Continue Learning D](../../../courses/learning-d/index.html)
- [D language specification, Lexical grammar and Keywords](https://dlang.org/spec/lex.html)
