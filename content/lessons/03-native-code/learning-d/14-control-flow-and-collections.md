<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/14-control-flow-and-collections.md

PURPOSE:
Choose paths and traverse D collections

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Choose paths and traverse D collections

[Course contents](index.md)

## Before you begin

Write down three transaction amounts, including one below zero. Trace one pass through the list and mark where a condition should reject an amount.
Control flow is the order in which statements execute. if chooses a branch, while repeats while a condition is true, and foreach visits a sequence. An array has elements; a slice describes a range of them. D uses a half-open range: the starting index is included and the ending index is excluded.

~~~d
import std.stdio : writeln;
void main()
{
    int[3] counts = [3, 5, 2];
    int sum = 0;
    foreach (value; counts)
        sum += value;
    foreach (index, value; counts)
        writeln(index, ": ", value);
    if (sum == 10)
        writeln("Expected total");
    foreach (value; counts[1 .. 3])
        writeln(value);
}
~~~

1. Save as collections.d, compile and run. Expect the indexed values 0:3, 1:5 and 2:2, followed by the total message and values 5 and 2.
2. Draw three boxes labelled 0, 1 and 2. Mark the slice from 1 up to 3; there is no element at index 3 to read.
3. Replace a value and predict the changed sum.
4. Add an empty slice counts[1 .. 1]. Explain why its loop body is never executed.

A static array such as int[3] owns three elements as part of its value. A dynamic array variable stores a length and pointer to elements. A slice can share storage, so writing through a mutable slice may change another view. An associative array uses keys rather than consecutive positions, for example int[string]; it has different runtime and memory requirements.

break exits a loop; continue advances to its next iteration. switch selects cases. foreach_reverse visits in reverse order. A for loop explicitly writes initialization, condition and update. Prefer the form that makes the bound easiest to see. Do not keep an element pointer after the storage has been resized or released.


## Exercise

Count how many entries are greater than two. The answer for the original array is two. Then test an all-zero array. A correct traversal handles both without special access to a first element. Keep runtime bounds checks enabled while learning.


## Continue learning

[Previous: Read D values, types and expressions](13-values-types-and-expressions.md) · [Course contents](index.md) · [Next: Choose a struct, class or interface](15-structs-classes-and-interfaces.md)
