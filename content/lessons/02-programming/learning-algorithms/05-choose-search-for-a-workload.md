<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-algorithms/05-choose-search-for-a-workload.md

PURPOSE:
Explain the lesson: Choose a search strategy for the work you actually do.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Choose a search strategy for the work you actually do

## An algorithm has a workload

A workload describes how much data you handle and which operations you repeat. A single search in a small unsorted list is different from thousands of searches in a stable catalogue. Choosing an algorithm means including preparation and updates, not just its most attractive step.

## Setup recap

Read and build the [collections lab](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/collections/README.md) using its C23 and CMake instructions. You need only its small integer list. Linear search checks elements in sequence. Binary search repeatedly discards part of a sorted interval.

## Count the preparation

For an eight-item unsorted list, linear search examines at most eight items for one request. Sorting first costs extra work. Binary search can then use fewer comparisons per query, but the sort has not become free.

~~~text
one query:
    unsorted data -> linear search -> answer

many queries, stable data:
    unsorted data -> sort once -> binary searches -> answers

frequent additions:
    addition -> maintain order or sort again -> search
~~~

The lab uses insertion sort for clarity. Its worst-case work grows quadratically with list length. Do not extrapolate a tiny teaching model into a claim about a large production catalogue.

## Lab on paper, then in source

1. Use the list 9,7,2,2 and target 9.
2. Count the element comparisons in linear search.
3. Trace insertion sort and count each value comparison separately from moves.
4. Trace binary search on the sorted result.
5. Repeat the search ten times without sorting again.
6. Explain which costs are paid once and which repeat.

Run the supplied program and tests to check answers, not to claim meaningful performance measurements from such a tiny workload.

## Consistency matters too

Both search functions return the first matching index. Binary search requires ascending input. If a caller appends an unsorted value and immediately calls FindSorted, it has broken the precondition even if a few searches still happen to work.

## Exercise with an answer

A catalogue changes once each morning and is searched all day. Is sorting once a reasonable candidate? Yes. Measure it against the real query pattern and data size. A catalogue that changes after every lookup may need a different data structure.

## Application connection

Framework should own reusable indexing and query policy. A UI may request an item without knowing which algorithm is used. Document the ordering and duplicate rules so changing the implementation does not silently change visible results.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/collections/collections.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](04-test-order-and-preservation.md)


[Next: Find the first matching duplicate](06-find-the-first-duplicate.md)
