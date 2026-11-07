<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-algorithms/02-insertion-sort-and-invariants.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Insertion sort and a promise kept at every step

[Course contents](index.md) · [Previous: Linear search and counting work](01-linear-search-and-cost.md) · [Next: Binary search and its sorted-input promise](03-binary-search-and-preconditions.md)

## Put values in order
Sorting rearranges elements according to a rule. Here the rule is ascending integer order. Insertion sort builds a sorted prefix, inserting each next value into its proper place.

An invariant is a statement that remains true at a particular point in every loop iteration. Here: before iteration i, the elements before i are already sorted.

## Setup recap
Build the collections lab from [the course contents](index.md). Read the arrays introduction if indices are unfamiliar. Open BtbListSort in collections.c.

## Follow one example
~~~text
[7 | 2 9 2]    first item is a sorted prefix
[2 7 | 9 2]    insert 2 before 7
[2 7 9 | 2]    9 already belongs at the end
[2 2 7 9 |]    move 9 and 7, then insert the final 2
~~~
The implementation saves the next value before moving larger values right. Otherwise those moves could overwrite the value being inserted. The test j > 0 appears before reading j - 1, preventing subtraction below zero.

## Lab
1. Write down the initial array 7, 2, 9, 2.
2. For each outer iteration, record saved and j.
3. Mark the sorted prefix after placing saved.
4. Run btb-collections. Expect "2 2 7 9" and then "7 is at index 2".
5. Read the test's frequency counts. They check that sorting retains every value, not just that output looks ordered.

## Stability and cost
This implementation shifts only values greater than saved. Equal values keep their relative order, a property called stability. You cannot observe that order using equal bare integers, but it matters when records have equal keys and different identities.

In a reversed list, insertion sort can move about n times n elements across its iterations: O(n²) growth. It remains useful for small inputs and teaching. Calling an algorithm simple does not make it suitable for every data size.

## Exercise and worked answer
Suppose the input is 1, 1, 1. The inner loop performs no shifts because no earlier value is greater. A comparison using >= would move equal elements and lose the stability argument.

## Umicom connection and limits
Sorted price or event displays must choose explicit key and tie rules. This lab does not sort live market data or replace Framework's catalogue services. It teaches a reasoning technique you can use when reviewing those services.

## Troubleshooting
Never compare integers by subtracting them to decide ordering when extremes are possible; subtraction can overflow. The implementation compares with > directly, and the tests include INT_MIN and INT_MAX.

## Source map
Read `labs/native/collections/collections.c` in the Bits2Banking checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Previous: Linear search and counting work](01-linear-search-and-cost.md) · [Next: Binary search and its sorted-input promise](03-binary-search-and-preconditions.md)
