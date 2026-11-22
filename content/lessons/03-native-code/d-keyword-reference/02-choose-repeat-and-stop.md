<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/d-keyword-reference/02-choose-repeat-and-stop.md

PURPOSE:
Trace a decision and a loop over a short practice statement before reading the whole program.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="420" height="103" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="420" height="103" }

# Choose, repeat and stop in D

[Course contents](index.md) · [Previous lesson: Name values and choose D types](01-name-values-and-choose-types.md) · [Next lesson: Pass values and describe function promises](03-pass-values-and-promises.md)

Trace a decision and a loop over a short practice statement before reading the whole program.

## Translate a repeated instruction

Start with three amounts on paper. Mark a row to skip, then total the others. In the D program, `foreach` provides the position and the value. In C, a common form counts positions explicitly. In Go, `range` can supply both parts of a slice iteration.

## Read branch boundaries

A branch controls which block runs. In the loop, `continue` skips the remainder of that turn. In an ordinary switch, use a default and make each branch’s intended ending clear. A whole list or branch explanation is easier to check than memorising punctuation by itself.

## Keywords and examples

Each row shows a separate example. Some belong inside a function, and some use a name introduced earlier. The full program below is the first one to copy.

| Word | Example | Meaning |
| --- | --- | --- |
| `if` | `if (count > 0) total += 5;` | Run a step when its condition is true. |
| `else` | `if (count > 0) total += 5; else total = 0;` | Choose a second branch when the if condition is false. |
| `for` | `for (int i = 0; i < 3; ++i) total += i;` | Write setup, a condition and an update. This resembles the C, C++ and Java form. |
| `while` | `while (count > 0) --count;` | Test before each turn. |
| `do` | `do { --count; } while (count > 0);` | Run one turn before the first test. D also uses do in function-contract syntax. |
| `foreach` | `foreach (cents; amounts) total += cents;` | Read one element per turn from the sequence. |
| `foreach_reverse` | `foreach_reverse (cents; amounts) writeln(cents);` | Visit these array elements from the last position to the first. |
| `break` | `while (true) { break; }` | Exit the nearest loop or switch. D also has labelled forms. |
| `continue` | `if (cents == 0) continue;` | Inside a loop, skip the rest of the current turn. |
| `switch` | `switch (code) { case 1: total = 5; break; default: total = 0; }` | Select a labelled clause using a matching value. |
| `case` | `case 1: total = 5; break;` | Mark one choice in a switch. Use goto case or goto default for an explicit transfer where needed. |
| `default` | `default: total = 0;` | Give an ordinary switch a fallback. |
| `goto` | `if (complete) goto done; total++; done: return total;` | Jump to a permitted label in the same function. Ordinary branches are easier to follow for this pattern. |
| `with` | `with (entry) { writeln(cents); }` | Look up names such as cents through the selected object inside the block. |

## Trace the steps on paper

Pseudocode uses ordinary words to show the order of steps. Read the plan one line at a time before reading the program.

```text
START total at zero
FOR each position and amount
    IF position is 1, skip the rest of this turn
    ADD the amount
SHOW total
```

## Run the complete example

Save the whole program as `practice.d`. Open a terminal in that folder, then enter the command shown for your language.

```d
import std.stdio : writeln;

void main()
{
    int[] amounts = [425, -25, 100];
    int total = 0;
    foreach (position, cents; amounts) {
        if (position == 1) {
            continue;
        }
        total += cents;
    }
    writeln(total);
}
```

```text
dmd -run practice.d
```

Expected output

```text
525
```

If the terminal cannot find dmd, check the D compiler installation for your operating system. If your course uses another documented D compiler, use its build and run instructions. You can still trace the example without installing a compiler.

## Try a change

Change the skipped position from 1 to 2. Name the two amounts that reach total.

**Check your answer**

The first and second entries contribute 425 and -25. The result is `400`.

## Keep learning

- [Compare programs across languages](../../../courses/programming-across-languages/index.html)
- [Continue Learning D](../../../courses/learning-d/index.html)
- [D language specification, Lexical grammar and Keywords](https://dlang.org/spec/lex.html)
