<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/14-dynamic-arrays-and-preservation.md

PURPOSE:
Grow an array while preserving its contents

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Grow an array while preserving its contents

[Course contents](index.md)
An array stores several values of one type. A fixed array's bounds are chosen when it is declared. A dynamic array can change its bounds later. That convenience does not remove memory limits, and a resized array may move to another address. Any pointer borrowed from its former storage can become invalid.


## Predict each bound and value

~~~basic
Dim samples() As Long
ReDim samples(0 To 2)
samples(0) = 10
samples(1) = 20
samples(2) = 30

ReDim Preserve samples(0 To 4)
For index As Long = 3 To 4
    samples(index) = 0
Next

Dim As Long total = 0
For index As Long = LBound(samples) To UBound(samples)
    total += samples(index)
Next
Print LBound(samples); UBound(samples); total
If total <> 60 Then End 1
Erase samples
End 0
~~~

Save this as arrays.bas and compile with fbc -lang fb -w all -exx arrays.bas -x arrays.exe. After compilation succeeds, run .\arrays.exe. Expect bounds 0 and 4 and a total of 60; Print may include spaces around numbers. This is a small bounded teaching allocation, not a policy for unlimited input.

1. Before running, draw three boxes and write 10, 20 and 30 inside them.
2. After ReDim Preserve, draw five boxes. Keep the first three values and fill the two new positions explicitly with zero.
3. Count the elements using upper bound minus lower bound plus one. Five elements have indexes 0 through 4.
4. Change the final upper bound to 3 and adjust the initialization loop to 3 To 3. Predict the total before rebuilding.
5. Keep the source folder and output executable separate from production data. If allocation fails or the runtime reports a bounds error, stop and inspect the requested bounds rather than disabling checks.

ReDim changes a dynamic array's storage. Preserve requests that compatible existing elements survive the resize. Do not assume it permits arbitrary changes to every dimension or lower bound; this lesson deliberately uses one dimension with the same lower bound. LBound and UBound are runtime queries. Erase releases this dynamic array's contents. A fixed array has different Erase behavior, so identify the declaration before applying the operation.


## A limit belongs before an allocation

Suppose a file requests ten million samples. Validate a documented maximum before ReDim, and check that the element count and element size can be represented by the target. A negative count converted to an unsigned type can become enormous. If the data source is untrusted or user-selected, parse the count into a checked representation and reject invalid values. Avoid repeatedly enlarging a large array by one element in a tight loop; that may copy substantial storage repeatedly.

At a C boundary, do not pass a FreeBASIC dynamic-array descriptor as if it were a C pointer. Use a reviewed pointer-and-element-count contract, keep the array alive for the entire call and prohibit resizing while C borrows it. If native Framework code retains data after return, use its documented copy or ownership-transfer operation. An address alone tells the native side neither the capacity nor how to release the memory.


## Check your understanding

Does Preserve keep old pointers valid? No: it preserves selected values, not the original storage address. Is UBound the number of elements? Not generally: a lower bound of 1 and an upper bound of 5 still describe five elements. This exercise is written for the FreeBASIC fb dialect and requires compiler/runtime qualification on your selected release.


## Continue practice

[Previous: Use Enum and Select Case to model job states](13-enums-and-state-transitions.md)

[Next: Validate every input character before accepting a number](15-parse-a-complete-bounded-number.md)
