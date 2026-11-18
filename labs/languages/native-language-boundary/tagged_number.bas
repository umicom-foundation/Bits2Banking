'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/tagged_number.bas
'
' PURPOSE:
'   Demonstrate explicit union selection and refusal without changing caller results.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'---------------------------------------------------------------------------

Enum NumberKind Explicit
    Invalid = 0
    Whole = 1
    Fractional = 2
End Enum

Union NumberPayload
    wholeValue As LongInt
    fractionalValue As Double
End Union

Type TaggedNumber
    kind As NumberKind
    payload As NumberPayload
End Type

' Construct one complete value. The tag describes which member was written.
Function MakeWhole(ByVal value As LongInt) As TaggedNumber
    Dim candidate As TaggedNumber
    candidate.payload.wholeValue = value
    candidate.kind = NumberKind.Whole
    Return candidate
End Function

Function MakeFractional(ByVal value As Double) As TaggedNumber
    Dim candidate As TaggedNumber
    candidate.payload.fractionalValue = value
    candidate.kind = NumberKind.Fractional
    Return candidate
End Function

' A mismatch is not a numeric conversion. The caller keeps its old result.
' The output variables are separate from the input record in this exercise.
Function TryWhole(ByRef value As Const TaggedNumber, ByRef result As LongInt) As Boolean
    If value.kind <> NumberKind.Whole Then Return False
    result = value.payload.wholeValue
    Return True
End Function

Function TryFractional(ByRef value As Const TaggedNumber, ByRef result As Double) As Boolean
    If value.kind <> NumberKind.Fractional Then Return False
    result = value.payload.fractionalValue
    Return True
End Function

Dim value As TaggedNumber = MakeWhole(42)
Dim wholeResult As LongInt = -7
Dim fractionalResult As Double = -8.5
If TryWhole(value, wholeResult) = False OrElse wholeResult <> 42 Then End 1
If TryFractional(value, fractionalResult) Then End 2
If fractionalResult <> -8.5 Then End 3

value = MakeFractional(12.5)
If TryFractional(value, fractionalResult) = False OrElse fractionalResult <> 12.5 Then End 4
If TryWhole(value, wholeResult) Then End 5
If wholeResult <> 42 Then End 6

' Deliberately bypass the construction protocol to exercise rejection.
value.kind = Cast(NumberKind, 99)
If TryWhole(value, wholeResult) OrElse TryFractional(value, fractionalResult) Then End 7
If wholeResult <> 42 OrElse fractionalResult <> 12.5 Then End 8

Dim unselected As TaggedNumber
unselected.kind = NumberKind.Invalid
If TryWhole(unselected, wholeResult) OrElse TryFractional(unselected, fractionalResult) Then End 9
Print "Umicom tagged-number checks passed."
Print "Wrong and unknown tags preserved both output values."
End 0
