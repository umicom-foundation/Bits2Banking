<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/21-resize-a-bounded-dynamic-array.md

PURPOSE:
Resize a bounded dynamic array and follow its lifetime

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Resize a bounded dynamic array and follow its lifetime

[Course contents](index.md)

## A collection with a changing number of entries

Imagine a small application collecting daily review counts. At first there are no entries. Later there are three, then six. A separate variable for every possible entry would make loops and shared code awkward. An array groups values of one type so that an index selects an element. A dynamic array can change its bounds while the program runs. In this lesson you will grow and shrink a one-dimensional numeric array, refuse an oversized request and observe what happens to removed values.

The practical file is dynamic_entries.bas in the native-language-boundary lab. It uses ordinary FreeBASIC, not Umicom C’s bounded BASIC source-region scanner. Read the earlier lessons about types, loops, procedures and pointers first. You need a supported FreeBASIC compiler for execution. The example is supplied for compiler qualification and has not been compiled in the current authoring environment; follow the checks below on your own toolchain.


## 1. Distinguish an index from an entry count

An index identifies a position. A count says how many positions exist. Our convention keeps the lower bound at zero. Three entries therefore occupy indices zero, one and two. Six occupy zero through five. Replacing the upper bound with the count would create an extra entry. Write the list of indices on paper before changing the code.

~~~freebasic
Dim amounts() As Long
ReDim amounts(0 To 2)
amounts(0) = 10
amounts(1) = 20
amounts(2) = 30
~~~

Dim declares the named array. Empty parentheses declare a dynamic array without allocating this example’s elements yet. As Long selects the element type; each stored value is a Long. ReDim supplies bounds for the dynamic storage. The parentheses after amounts in an assignment select one element; they are not a procedure call in this context. These are ordinary small integer counters, not money amounts or a complete financial representation.


## 2. Introduce the resizing policy

A language mechanism can allocate a large amount of memory, but an application should first decide how much work it accepts. Our example uses MaximumEntries = 8. ResizeEntries checks that a requested count is between one and eight before resizing. It returns False for a count outside that policy. This is a deliberate application bound for a teaching exercise, not a platform-wide maximum.

~~~freebasic
Function ResizeEntries(values() As Long, ByVal requested As Integer) As Boolean
    If requested < 1 OrElse requested > MaximumEntries Then Return False
    ReDim Preserve values(0 To requested - 1)
    Return True
End Function
~~~

Function names a procedure that returns a result. Boolean describes True or False. The array parameter refers to the caller’s array, so resizing affects that array. ByVal requested passes the count as a value. OrElse joins two refusal conditions with short-circuit evaluation. Return False exits before any resizing occurs. This policy refusal leaves existing entries alone; it is not a promise that every runtime allocation failure is recoverable in the same way.


## 3. Keep the lower bound fixed

ReDim Preserve requests resized storage while retaining the existing prefix in this one-dimensional, fixed-lower-bound exercise. Newly added numeric elements start at zero. Changing lower bounds or reshaping multidimensional arrays introduces additional rules; do not infer those behaviors from this example. The linked language manual documents those restrictions. We deliberately keep the lower bound at zero and change only the upper bound.

After growing from three to six entries, the paper trace should contain 10, 20, 30, 0, 0, 0. The new zeros are values, not evidence that those entries have been reviewed by a user. If your application needs an unknown or unreviewed state, represent that state separately. Treating zero as both a valid count and a missing value creates ambiguity, just as a missing dictionary key differs from a present zero.


## 4. Observe shrink followed by growth

The program next shrinks six entries to two. The remaining values are 10 and 20; the old third value 30 is outside the new bounds. Growing back to three entries adds a new numeric element initialized to zero. The old 30 does not return. Preserve is not an undo history or a backup. If you need recoverable edits, keep a separate reviewed history before changing the collection.


## 5. Inspect bounds before reading

LBound and UBound report an array dimension’s lower and upper bounds. For this empty dynamic array, the lower bound is zero and the upper bound is minus one. The comparison LBound(amounts) > UBound(amounts) therefore detects the empty case before any element is read. For a nonempty one-dimensional array, count the entries as upper minus lower plus one. Keep empty handling explicit and avoid unsigned conversions that turn minus one into a huge positive number.

~~~freebasic
If LBound(amounts) > UBound(amounts) Then
    Print "No entries yet"
Else
    For index As Integer = LBound(amounts) To UBound(amounts)
        Print index; ": "; amounts(index)
    Next
End If
~~~


## 6. Do not keep stale element pointers

A pointer can remember the address of an element. Resizing may move the backing storage. Even if a particular run appears to keep the same address, a future resize, allocator or platform can behave differently. Finish any synchronous C call borrowing the elements before resizing. After a resize, obtain a fresh pointer only after checking the new bounds. Never use a pointer into the removed tail or after Erase.

This is a lifetime rule, not a stylistic preference. A borrowed pointer does not keep the array alive or stop another part of the program from changing its storage. A shared Framework boundary should receive an explicit pointer and element count for the duration it needs them, together with a clear rule about copying or retaining data. FreeBASIC’s array descriptor is not automatically a portable C structure. Do not pass that descriptor as if it were an array of Long values.


## 7. Run the complete exercise

1. Open the native-language-boundary lab folder in your editor and terminal. Read dynamic_entries.bas from top to bottom.
2. Check fbc -version and record the reported compiler and target. The executable must match your operating system.
3. Compile with runtime checks enabled using the commands below. Stop if compilation reports an error.
4. Run the executable. Expect retained values 10, 20 and 0, followed by the completion message. Formatting spaces around numbers can differ.
5. Read Require. It stops with a nonzero exit code when an expectation fails, so the final message should appear only after the stated checks.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary"
fbc -version
fbc -exx dynamic_entries.bas -x dynamic_entries.exe
& .\dynamic_entries.exe
~~~

A compile failure may indicate a compiler dialect or version difference, a changed source file or a genuine mistake. Preserve the first diagnostic and compiler identity. Do not remove bounds checks merely to make a failing example run. For a controlled experiment, copy the file into your own exercise folder and change the maximum accepted count to six. Predict which requests still succeed before running that copy.


## 8. Release dynamic storage deliberately

Erase amounts releases the elements of this dynamic array. The program then verifies that it is empty. That operation does not erase files on disk and is not a secure-data wiping guarantee. The word erase has different meanings in different contexts, so tie every explanation to the object being changed. Do not generalize this dynamic-array behavior to every fixed-size or user-defined array without reading its documented rules.


## How this helps Umicom projects

A BASIC client can collect a small list of reviewed user inputs, check its bounds and call a native Framework service with a stable borrowed buffer. The shared service should continue to own reusable validation and processing; an example in another language is not a reason to duplicate the Framework engine. Dynamic storage is useful when the count changes, but fixed arrays or bounded pools can be a better fit for some embedded workloads. Choose from the workload and lifetime requirements rather than from a language slogan.


## Trace the collection across operations

| Stage | Valid indices | Values to expect |
| --- | --- | --- |
| Empty declaration | None | No element may be read |
| Three entries | 0..2 | 10, 20, 30 |
| Grow to six | 0..5 | 10, 20, 30, 0, 0, 0 |
| Refuse nine | 0..5 | Same six entries |
| Shrink to two | 0..1 | 10, 20 |
| Grow to three | 0..2 | 10, 20, 0 |
| Erase dynamic storage | None | Do not dereference a former element |

## Further reading

- [Complete dynamic-entry exercise](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/native-language-boundary/dynamic_entries.bas)
- [FreeBASIC ReDim reference and restrictions](https://www.freebasic.net/wiki/KeyPgRedim)
- [FreeBASIC UBound reference](https://www.freebasic.net/wiki/KeyPgUbound)
- [FreeBASIC array reference index](https://www.freebasic.net/wiki/CatPgArray)

[Previous: Name fixed rules with Const](20-name-fixed-rules-with-const.md)

[Next: Keep temporary values inside a scope](22-keep-temporary-values-inside-a-scope.md)
