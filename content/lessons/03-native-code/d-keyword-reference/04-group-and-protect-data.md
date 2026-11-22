<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/d-keyword-reference/04-group-and-protect-data.md

PURPOSE:
Distinguish a structure, a union, a class and an interface using familiar parts of a statement.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Group and protect related data

[Course contents](index.md) · [Previous lesson: Pass values and describe function promises](03-pass-values-and-promises.md) · [Next lesson: Organise source and name a boundary](05-organise-source-and-boundaries.md)

Distinguish a structure, a union, a class and an interface using familiar parts of a statement.

## Keep facts that belong together in one value

A practice entry carries an amount and a posted flag. A `struct` gives names to both fields. A union can represent alternatives in shared storage. Read the member appropriate to the value it currently represents.

## Compare class words across languages

D and Java use a `class` keyword and class references. Their inheritance, memory and interface rules remain language-specific. D also has a separate value-type `struct` form. Choose the simplest data grouping that represents the example.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `struct` | `struct Entry { int cents; bool posted; }` | Group fields into a value type. |
| `union` | `union Reading { int integer; float ratio; }` | Give fields views of overlapping storage. Keep track of the view currently in use. |
| `enum` | `enum Phase { draft, posted }` | Define named alternatives as an enumeration. D also uses enum for manifest constants. |
| `class` | `class Label { string name; }` | Declare a reference type with fields or methods. |
| `interface` | `interface Named { string name(); }` | Describe operations an implementing type must provide. |
| `abstract` | `abstract class Task { abstract int count(); }` | Define a class intended for derived types to complete. |
| `final` | `final class SealedLabel { }` | Prevent extension of this class. The same word also has method and final switch uses. |
| `super` | `override int count() { return super.count() + 1; }` | Use the base-class implementation from inside a derived class. |
| `this` | `this(int cents) { this.cents = cents; }` | Spell a constructor and refer to the current object’s field. |
| `override` | `override int count() { return 3; }` | Ask the compiler to check that a method overrides an inherited method. |
| `new` | `auto label = new Label;` | Create a new class instance. |
| `const` | `const(int)* view = &amount;` | Expose a view through which the int cannot be changed. |
| `immutable` | `immutable int seed = 425;` | Declare a value that remains unchanged through all permitted references. |
| `invariant` | `invariant { assert(cents >= 0); }` | State a class invariant that enabled contract checks test at prescribed boundaries. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
GROUP an amount and a flag as one entry
IF the flag is yes, return the amount
OTHERWISE return zero
```

## Run the complete example

Save the whole program as `practice.d`. Open a terminal in that folder, then enter the command shown for your language.

```d
import std.stdio : writeln;

struct Entry
{
    int cents;
    bool posted;
}

int posted_cents(Entry entry)
{
    return entry.posted ? entry.cents : 0;
}

void main()
{
    auto payment = Entry(425, true);
    writeln(posted_cents(payment));
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

Change true to false. Which field changes, and what does the function return?

**Check your answer**

The posted flag changes. The amount is still stored as 425, and the function returns zero.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Continue Learning D](../../../courses/learning-d/index.html)
- [D language specification, Lexical grammar and Keywords](https://dlang.org/spec/lex.html)
