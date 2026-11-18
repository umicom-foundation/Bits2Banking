'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/dynamic_entries.bas
'
' PURPOSE:
'   Trace bounded one-dimensional dynamic array resizing without retaining element pointers.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'-----------------------------------------------------------------------------
Option Explicit

Const As Integer MaximumEntries = 8

Sub Require(ByVal condition As Boolean, ByRef message As String)
    If Not condition Then
        Print "Check failed: "; message
        End 1
    End If
End Sub

Function ResizeEntries(values() As Long, ByVal requested As Integer) As Boolean
    If requested < 1 OrElse requested > MaximumEntries Then Return False
    ' The lower bound remains zero. ReDim may move storage, so callers must
    ' release borrowed element pointers before requesting a size change.
    ReDim Preserve values(0 To requested - 1)
    Return True
End Function

Dim amounts() As Long
Require(LBound(amounts) > UBound(amounts), "initially empty")
Require(ResizeEntries(amounts(), 3), "allocate three")
amounts(0) = 10 : amounts(1) = 20 : amounts(2) = 30
Require(ResizeEntries(amounts(), 6), "grow to six")
Require(amounts(0) = 10 AndAlso amounts(2) = 30, "retained prefix")
For index As Integer = 3 To 5
    Require(amounts(index) = 0, "new numeric elements start at zero")
Next
Require(Not ResizeEntries(amounts(), 9), "refuse application limit")
Require(UBound(amounts) = 5 AndAlso amounts(2) = 30, "refusal keeps values")
Require(ResizeEntries(amounts(), 2), "shrink to two")
Require(ResizeEntries(amounts(), 3), "grow after shrink")
Require(amounts(0) = 10 AndAlso amounts(1) = 20 AndAlso amounts(2) = 0, "removed tail does not return")
Print "Retained values: "; amounts(0); ", "; amounts(1); ", "; amounts(2)
Erase amounts
Require(LBound(amounts) > UBound(amounts), "dynamic array empty after Erase")
Print "Dynamic entries: expected checks completed"
