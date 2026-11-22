<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/cpp20-keyword-reference/02-decisions-and-loops.md

PURPOSE:
Recognise branches, repeated steps and ways to leave them, and trace a short repeated calculation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom">
</picture>

# Choose what happens next

[Course contents](index.md) · [Previous lesson — Name the kind of value](01-values-and-types.md) · [Next lesson — Declare names, storage and size](03-declarations-and-storage.md)

## What you will learn

Recognise branches, repeated steps and ways to leave them, and trace a short repeated calculation.

## Read the words in context

A **condition** is an expression read as true or false. A **block** groups statements between braces. The items below show short pieces you might put inside a function. The switch fragments take part in a larger switch statement, as noted in their explanations.

## Reserved keywords in this lesson

| Spelling | Meaning | Read this example |
| --- | --- | --- |
| `if` | Runs a statement or block when its condition is true. | `if (count == 0) return 0;` |
| `else` | Supplies a path for when a preceding if condition is false. | `if (count == 0) return 0; else return 1;` |
| `switch` | Chooses a statement based on a value and the available case labels. | `switch (code) { case 7: return 2; default: return 0; }` |
| `case` | Labels a switch path for a particular constant value. | `case 7: return 2;` |
| `default` | In a switch, labels the path used when no case matches. Other C++ uses include a defaulted member function. | `default: return 0;` |
| `for` | Runs setup once, then checks a condition, executes the body, and performs an update before the next check. | `for (int i = 0; i < 3; ++i) total += i;` |
| `while` | Checks the condition before each trip through the body. The body can run zero times. | `while (remaining > 0) --remaining;` |
| `do` | Starts a do-while loop. Its condition is checked after the body, so the body runs at least once. | `do { ++attempts; } while (attempts < 2);` |
| `break` | Leaves the nearest enclosing loop or switch. | `while (true) { if (limit_reached) break; }` |
| `continue` | Ends the current trip through the nearest loop and proceeds to its next update or check. | `for (int i = 0; i < 3; ++i) { if (i == 1) continue; total += i; }` |
| `goto` | Transfers control to a named label in the same function. Some jumps are prohibited, such as jumping into certain variable scopes. | `if (missing) goto no_record; return 1; no_record: return 0;` |
| `return` | Leaves the current function and supplies its result when its return type requires one. | `return count + 1;` |

## Write the loop in plain words

~~~text
SET total to zero
FOR each number from 0 through 2
    IF the number is 1
        GO TO the next number
    ADD the number to total
SHOW total
~~~

C and Java share the three-part for loop pattern with C++. Go can use a similar sequence without the parentheses. Python commonly puts the sequence in a range object and reads one item at a time. See the linked cross-language workshop for full programs and boundaries.

## Try it and check

Start total at zero and trace the continue example. Write the value of i each time the addition occurs.

**Check:** The addition runs for i equal to 0 and 2. Their sum is 2. With continue removed, i equal to 1 also contributes and the total is 3.

## Apply it to an Umicom project

For an Umicom Bank practice import, write a table that shows a row index, its state, and whether it contributes to a summary. Use the loop trace as an expected result for an Umicom Studio exercise.

[Find the Umicom application repositories](../../../umicom/repositories.md).

[Open the browser lesson](../../../courses/cpp20-keyword-reference/lessons/02-decisions-and-loops.html)

[Course contents](index.md) · [Previous lesson — Name the kind of value](01-values-and-types.md) · [Next lesson — Declare names, storage and size](03-declarations-and-storage.md)
