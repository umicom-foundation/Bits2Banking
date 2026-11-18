<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/06-procedures-and-value-ownership.md

PURPOSE:
Procedures, ByVal and ByRef

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Procedures, ByVal and ByRef

[Course contents](index.md)
A procedure names a reusable operation. A Sub performs an operation without returning a result value. A Function returns a value. Parameters are the names in a declaration; arguments are the values supplied by a caller. Keeping these ideas separate makes compiler messages easier to understand.

~~~basic
Function AddCents(ByVal left As Long, ByVal right As Long) As Long
    Return left + right
End Function
Sub ResetCount(ByRef value As Long)
    value = 0
End Sub
Dim As Long count = 4
Print AddCents(100, 25)
ResetCount(count)
Print count
~~~

1. Compile procedures.bas and expect 125 followed by 0. The addition uses deliberately small values.
2. Change ResetCount to ByVal and rebuild. Explain why the caller’s count stays 4.
3. Add a Declare Function line before code that calls a function defined later. Keep the declaration and definition signatures identical.
4. Write down which parameters may change and which values are returned. This is the start of an API contract.

ByVal gives the procedure its own parameter value. ByRef refers to the caller’s variable, so assignment changes that variable. Neither keyword by itself transfers ownership of allocated storage. A copied pointer still points to the same allocation. Returning a pointer to a local variable is invalid because that local storage does not outlive the call.

Scope is the region where a name is visible. Lifetime is the period during which its storage is valid. They are related but different. A local name may disappear after a function call; a heap allocation can remain until explicitly released. Shared global variables make dependencies less obvious, so prefer passing the small set of inputs an operation requires.

FreeBASIC supports overloaded procedures, but a C ABI export should normally have one unambiguous name and a fixed parameter list. A stable ABI also specifies integer widths, string encoding, ownership and error handling. A function that works inside one BASIC source file is not automatically safe for a C application.


## Exercise

Design a function that rejects an item count outside 0 through 100 before computing a bounded total. Decide how it reports failure without confusing failure with a valid zero. A status return plus an output parameter is one common C-friendly design. The interoperability lesson provides a small example.


## Continue learning

[Previous: Loops, arrays and bounds](05-loops-arrays-and-bounds.md) · [Course contents](index.md) · [Next: Records, reusable modules and files](07-records-modules-and-files.md)
