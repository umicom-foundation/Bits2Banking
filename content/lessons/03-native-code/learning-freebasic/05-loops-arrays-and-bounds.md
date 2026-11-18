<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/05-loops-arrays-and-bounds.md

PURPOSE:
Loops, arrays and bounds

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Loops, arrays and bounds

[Course contents](index.md)
A loop repeats instructions. An array stores several values of one element type, indexed by integers. An index identifies a position; it is not the value stored at that position. This example uses an explicit lower and upper bound so no default needs to be guessed.

~~~basic
Dim As Long counts(0 To 2) = {3, 5, 2}
Dim As Long total = 0
For i As Integer = LBound(counts) To UBound(counts)
    total += counts(i)
Next i
Print total
Dim As Integer remaining = 3
Do While remaining > 0
    Print remaining
    remaining -= 1
Loop
~~~

1. Save as loops.bas. Compile with fbc -lang fb -w all -exx loops.bas -x loops.exe. The extra runtime checks are useful while learning.
2. Run the program. Expect 10 followed by 3, 2 and 1.
3. Explain why the array loop visits three elements even though its last index is 2.
4. Add a fourth element by changing both the upper bound and initializer. Predict the new sum. Keep LBound and UBound rather than duplicating the bounds in the loop.

For declares a counted iteration, To includes the final value, and Next advances it. LBound and UBound query the declared array bounds. += adds to the current value. Do While checks a condition before each iteration. If remaining were never reduced, the condition would stay true and the loop would never finish.

Exit For and Exit Do leave their respective loops. Continue For and Continue Do skip to the next iteration. Use them sparingly and explain the condition; too many hidden exits make a loop difficult to reason about. A While/Wend loop is another precondition form. Do/Loop Until can place a condition at the bottom, so its body executes at least once.

A bounds error is a memory correctness problem, not a harmless extra item. Compiler checks help catch mistakes; they do not replace input validation. Do not derive an allocation size directly from an untrusted count without a maximum and overflow checks. Framework services should return clear capacity errors rather than writing beyond a caller’s buffer.


## Practice

Calculate the largest count using the same loop, initializing the maximum from a known existing element. Explain what your algorithm should do for an empty collection before adapting it to a dynamic array. An empty array has no first element to read.


## Continue learning

[Previous: Expressions, comparisons and decisions](04-expressions-decisions-and-operators.md) · [Course contents](index.md) · [Next: Procedures, ByVal and ByRef](06-procedures-and-value-ownership.md)
