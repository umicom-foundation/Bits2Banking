<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-algorithms/04-test-order-and-preservation.md

PURPOSE:
Explain the lesson: Test sorting without trusting another sort.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Test sorting without trusting another sort

## A sorted answer can still be wrong

Sorting should put values in order without losing or inventing them. A program that returns only zeros produces a nondecreasing sequence, but it has not correctly sorted most inputs. We need to check both order and preservation.

## Setup recap

Use the [collections lab guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/collections/README.md) to prepare the C23 tools and build the example. An array holds values in numbered positions. A test oracle is the rule used to decide whether an observed answer is correct.

## Two independent properties

First, compare each neighbouring pair: the left value must be less than or equal to the right value. Second, count how often each value occurred before and after. Both counts must agree.

~~~text
input:  2, 7, 2, 9
output: 2, 2, 7, 9

value     input occurrences    output occurrences
2                 2                    2
7                 1                    1
9                 1                    1
~~~

This checks a property of the result without calling a second copy of the same sorting algorithm.

The existing test enumerates four-element inputs using -1, 0 and 1. There are 3 × 3 × 3 × 3 = 81 combinations. This includes duplicates and different orders. It is exhaustive for that small domain, not for every integer list.

## Lab

1. Locate the frequency-count check in `test_collections.c`.
2. Explain how it would detect output `-1,0,0,1` for input `-1,-1,0,1`.
3. Check whether an empty list is accepted.
4. Build and run the tests.
5. In a separate exercise copy, deliberately replace one sorted value with another value.
6. Confirm the preservation check catches the change, then restore the exercise copy.

A deliberate fault is useful only if the test is expected to reject it. Never leave the fault in the original lab.

## Why several checks help

Comparison with linear search checks the binary-search result after sorting. It does not replace the sort's order and frequency properties. Each check answers a specific question.

## Troubleshooting

If a test is occasionally different, inspect whether the input generator uses randomness. This lab's finite enumeration should be repeatable. If a failure is hard to understand, print the input, output and failing property in a temporary exercise diagnostic.

## Next connection

A Framework transformation may reorder documents, trades or queued jobs. Its tests should define what may change and what must be preserved. An apparently tidy display is not enough evidence of correctness.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/collections/test_collections.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](05-choose-search-for-a-workload.md)


[Previous lesson](03-binary-search-and-preconditions.md)
