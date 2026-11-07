<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/safer-c-programming/15-request-space-for-a-terminator.md

PURPOSE:
Explain the lesson: Reserve space for the end of a string.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Reserve space for the end of a string

## Prepare
Open the arena report example and find strlen(heading) + 1U. A C string ends with a zero-valued character. strlen counts the characters before that terminator.

The extra byte is part of the required storage, even though it does not appear in the printed report.

## Work a small example
For the text Note, draw five cells: N, o, t, e and zero. Four visible characters need five bytes in this ASCII example.

The source uses strcpy only after allocating the measured length plus the terminator. The source text is a fixed string that does not change between measuring and copying.

## Lab
Replace the heading with a short ASCII sentence in your exercise copy. Count the visible characters and predict the requested bytes. Compare that prediction with strlen plus one.

Expected: the destination has room for all characters and the final zero. Do not deliberately remove the extra byte and execute an overflowing copy.

## Exercise and explanation
Why is measuring an untrusted input pointer dangerous? strlen needs an accessible terminating zero. A pointer and no bound cannot prove that one exists. Bounded inputs need a separate length contract before they can be treated as strings.

## Troubleshoot
If the example refuses a very small workspace, inspect both strings and alignment padding. The allocation result must be checked before copying. A refusal is an expected boundary result, not permission to continue with an unchanged destination pointer.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/arena-allocator/main.c). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](14-borrow-storage-for-a-report.md) · [Next lesson](16-understand-alignment-padding.md)

