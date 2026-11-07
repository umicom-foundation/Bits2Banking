<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-data-structures/01-arrays-length-and-capacity.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Arrays, length and capacity

[Course contents](index.md) · [Next: Stacks and the order of undo](02-stacks-and-undo.md)

## Organising several values
A data structure is a way to organise information so operations have predictable behaviour. An array stores a sequence of elements of one type. An index is a position: C arrays begin at zero.

The collections lab keeps up to eight integers. Its count tells us how many are currently used. Capacity tells us how many fit. Empty and full are different valid states.

## Setup recap
Follow [the setup and collections commands](index.md). You need a C23 compiler, CMake and Ninja. Read collections.h and main.c. If variables and functions are new, [Introduction to Programming](../introduction-to-programming/index.md) explains them with complete first programs.

## Read the representation
~~~c
typedef struct {
    int values[8];
    size_t count;
} BtbList;
~~~
A struct groups named fields. size_t is an unsigned integer type used for sizes and positions. The actual header names the capacity with BTB_COLLECTION_CAPACITY rather than repeating 8.
~~~text
index:     0  1  2  3  4  5  6  7
storage:  [7][2][9][ ][ ][ ][ ][ ]
count: 3                capacity: 8
~~~
Only indices less than count hold logical list elements. Storage beyond count belongs to the object but is not part of its current contents.

## Append one value
BtbListAppend checks the pointer, checks that count is not corrupt, and checks for space before writing. When count is 8 it returns BTB_FULL. It does not write a ninth element.
1. Open collections.c and locate BtbListAppend.
2. Mark the first line that changes the list.
3. Verify every rejection comes before that line.
4. Follow main.c as it appends 7, 2, 9, 2. Draw the array after each call.
5. Build and run the lab. The demonstration sorts these values, so its final output is "2 2 7 9".

## Exercise and worked answer
Why is the next insertion index count, not count + 1? With three elements, used indices are 0, 1 and 2. Index 3 is the first free slot. Using 4 would leave an unexplained hole and would reach the boundary too early.

## Umicom connection
A document tab list and a queue of jobs both need length rules. This fixed-size teaching list is deliberately small. Framework's document and job services own the richer production behaviour; applications should call those services instead of embedding this lab.

## Troubleshooting and limits
Initialise a list with = {0}. An uninitialised count has no usable meaning. This model has no dynamic allocation, thread safety or automatic growth. Reading values[count] while count equals 8 is outside the array.

## Source map
Read `labs/native/collections/collections.h` in the Bits2Banking checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Next: Stacks and the order of undo](02-stacks-and-undo.md)
