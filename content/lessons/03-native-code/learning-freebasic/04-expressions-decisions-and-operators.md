<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/04-expressions-decisions-and-operators.md

PURPOSE:
Expressions, comparisons and decisions

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Expressions, comparisons and decisions

[Course contents](index.md)
An expression computes a value. An operator combines or changes values. Arithmetic operators, comparisons and logical operators solve different problems. In BASIC, context determines whether = assigns a value or compares two values. In an If expression it asks whether values are equal.

~~~basic
Dim As Long count = 7
Print count \ 3
Print count Mod 3
Print count / 3
If count >= 1 AndAlso count <= 10 Then
    Print "Small positive batch"
End If
Dim As Long divisor = 0
If divisor <> 0 AndAlso count \ divisor > 1 Then
    Print "Quotient is above one"
End If
~~~

Integer division, written with a backslash, gives a whole-number quotient. Mod gives the remainder. Ordinary / performs division with a fractional result. The first outputs therefore represent 2, 1 and approximately 2.333. >= and <= include the boundary; <> means not equal. AndAlso stops evaluating when its left side is false. That is why the last condition does not divide by zero.

1. Compile the example as expressions.bas. Predict each result on paper before running.
2. Change count to 10 and check the boundary condition. Change it to 11 and confirm that the batch message disappears.
3. Leave divisor at zero and keep AndAlso. Then explain why replacing it with a non-short-circuit operator would be unsafe. Do not execute intentionally unsafe division.
4. Add parentheses to make a mixed arithmetic expression’s intended order visible. Check (2 + 3) * 4 against 2 + 3 * 4.

And, Or, Xor and Not also operate on integer bits. Do not confuse bit masks with a sentence about true and false. FreeBASIC’s comparison result is not a portable C boolean representation to export without conversion. Use explicitly documented status values at the C boundary.

Select Case can express several alternatives for one value. Use Case Else for unknown choices. Decisions should cover invalid values as well as ordinary ones; accepting an unknown mode silently is particularly dangerous in a download, trading or media-generation workflow.

~~~basic
Dim As Long mode = 2
Select Case mode
Case 1
    Print "Preview"
Case 2
    Print "Validate"
Case Else
    Print "Unknown mode"
End Select
~~~


## Check

A batch limit of ten includes ten. A divisor check must happen before division. Parentheses document intent but do not enlarge the range of a number type. These are separate correctness concerns.


## Continue learning

[Previous: Text input, strings and validation](03-text-input-and-validation.md) · [Course contents](index.md) · [Next: Loops, arrays and bounds](05-loops-arrays-and-bounds.md)
