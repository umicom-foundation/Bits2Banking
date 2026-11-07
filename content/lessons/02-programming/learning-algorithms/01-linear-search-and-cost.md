<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-algorithms/01-linear-search-and-cost.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Linear search and counting work

[Course contents](index.md) · [Next: Insertion sort and a promise kept at every step](02-insertion-sort-and-invariants.md)

## A procedure for finding a value
An algorithm is a precise sequence of steps for solving a problem. Linear search compares elements from the beginning until it finds a match or reaches the end. It works without sorting.

## Setup recap
Follow [the collections setup](index.md). An array stores values at numbered indices, starting at zero. A loop repeats a comparison. The course [Learning Data Structures](../learning-data-structures/index.md) explains the storage if you need a recap.

## Trace before running
~~~text
values: 7 2 9 2
target 9: compare 7, compare 2, compare 9 -> index 2
target 4: compare every value -> not found
target 2: compare 7, compare 2 -> index 1
~~~
The contract returns the first match. That decision matters when values repeat.

## Read BtbListFind
The loop condition is i < list->count. -> accesses a field through a pointer. A successful comparison writes the index and returns BTB_OK. Reaching the end returns BTB_NOT_FOUND without changing the output index.

## Lab
1. Open collections.c and locate BtbListFind.
2. Count comparisons for finding the first, last and absent value in four elements.
3. Read the tests where the output index begins at 42.
4. Explain why 42 should remain unchanged when the value is absent.
5. Build and run the tests through the course commands.

## Understanding O(n)
If there are n elements, an unsuccessful search performs n comparisons. Doubling the input can double the work. O(n), read "order n", describes that growth for large inputs. It is not a timing measurement and does not say each comparison takes one second.

An empty list needs no element comparisons. Finding the first element needs one. Worst-case and best-case descriptions refer to different inputs.

## Exercise and worked answer
A list has 100 elements and the requested value is absent. Linear search compares 100 elements. If the value is first, it compares one. Both behaviours belong to the same algorithm.

## Connect to Umicom
A small selection list can be searched linearly without adding an index structure. For large document or asset catalogues, Framework services may maintain indexes. Choose using measured workloads and required behaviour, including duplicates and updates.

## Troubleshooting
A "not found" status is not an instruction to read index 42. Check the status before accessing an element. The lab's capacity is eight to keep traces readable; the reasoning applies to longer lists.

## Source map
Read `labs/native/collections/collections.c` in the Bits2Banking checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Next: Insertion sort and a promise kept at every step](02-insertion-sort-and-invariants.md)
