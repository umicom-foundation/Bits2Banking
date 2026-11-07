<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-algorithms/03-binary-search-and-preconditions.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Binary search and its sorted-input promise

[Course contents](index.md) · [Previous: Insertion sort and a promise kept at every step](02-insertion-sort-and-invariants.md)

## Cut the search interval in half
Binary search uses the order of a sorted list to discard regions that cannot contain the answer. Without sorted input, the same decisions can discard the correct value.

## Setup recap
Use [the collections commands](index.md). Review the previous lesson's sort. Open BtbListFindSorted and its public contract in collections.h. The caller must supply ascending input; the function does not secretly sort or scan the entire list.

## A half-open interval
The active interval is [first,last): first is included and last is excluded. An empty interval has equal endpoints. This representation avoids computing count - 1 for an empty list.
~~~c
const size_t middle = first + (last - first) / 2U;
~~~
The distance is measured before adding to first. All positions stay inside the current interval.

For the sorted values 2, 2, 7, 9 and target 2:
~~~text
[0,4): middle 2 -> value 7; move last to 2
[0,2): middle 1 -> value 2; move last to 1
[0,1): middle 0 -> value 2; move last to 0
[0,0): stop; inspect index 0 -> first match
~~~
Keeping the left half when an equal value appears finds the first duplicate, consistent with linear search.

## Lab
1. Trace target 7 using the same array.
2. Trace target 10. The final index equals count and must not be dereferenced.
3. Read the tests enumerating all 81 four-element lists over -1, 0 and 1.
4. Observe that each list is sorted before comparing binary and linear search results.
5. Run the tests after building; record any disagreement with its input.

## Cost includes preparation
Each iteration roughly halves the interval: O(log n) comparisons after sorting. Sorting and maintaining order have their own cost. A one-off search in an unsorted tiny list may be simpler and cheaper with linear search. This function trusts its documented sortedness precondition; it is not an untrusted-input validator.

## Exercise and worked answer
Would it be correct to call FindSorted directly on 9, 2, 7? No. Sort first or use Find. The fact that a particular target sometimes succeeds does not establish the precondition.

## Connect to Umicom
Search contracts should state ordering, duplicate and absence behaviour. Framework adapters can then provide the same answer to different user interfaces. The tests here use different strategies as cross-checks, plus frequency counts as an independent sort oracle.

## Source map
Read `labs/native/collections/collections.c` in the Bits2Banking checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Previous: Insertion sort and a promise kept at every step](02-insertion-sort-and-invariants.md)

[Continue: Test sorting without trusting another sort](04-test-order-and-preservation.md)
