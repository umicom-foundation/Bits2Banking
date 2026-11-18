'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/read_only_properties.bas
'
' PURPOSE:
'   Expose a bounded request budget through a read-only property and checked mutations.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'-----------------------------------------------------------------------------

Type RequestBudget
Private:
    remaining_ As UInteger
Public:
    Declare Constructor()
    Declare Property Remaining() As UInteger
    Declare Function TryReset(ByVal requested As UInteger) As Boolean
    Declare Function TryConsume(ByVal count As UInteger) As Boolean
End Type

Constructor RequestBudget()
    remaining_ = 0
End Constructor

Property RequestBudget.Remaining() As UInteger
    Return remaining_
End Property

Function RequestBudget.TryReset(ByVal requested As UInteger) As Boolean
    If requested > 1024 Then Return False
    remaining_ = requested
    Return True
End Function

Function RequestBudget.TryConsume(ByVal count As UInteger) As Boolean
    ' Check before subtraction: unsigned wraparound must not create capacity.
    If count > remaining_ Then Return False
    remaining_ -= count
    Return True
End Function

Dim As RequestBudget budget
If budget.Remaining <> 0 Then End 1
If Not budget.TryReset(5) Then End 1
If Not budget.TryConsume(2) Then End 1
If budget.Remaining <> 3 Then End 1
If budget.TryConsume(4) Then End 1
If budget.TryReset(1025) Then End 1
If budget.Remaining <> 3 Then End 1
If Not budget.TryConsume(3) Then End 1
If Not budget.TryConsume(0) Then End 1
If budget.Remaining <> 0 Then End 1
Print "Read-only property: refused updates preserved 3; exact consumption reached 0."
' budget.Remaining = 7 would require a setter, which this type does not declare.
End 0
