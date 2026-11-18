'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/virtual_rules.bas
'
' PURPOSE:
'   Trace abstract and virtual dispatch through borrowed base pointers without heap allocation.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'-----------------------------------------------------------------------------

Type BatchRule Extends Object
    Declare Abstract Function Admit(ByVal items As UInteger) As Boolean
    Declare Virtual Function Limit() As UInteger
End Type

Function BatchRule.Limit() As UInteger
    Return 4
End Function

Type PositiveRule Extends BatchRule
    Declare Function Admit(ByVal items As UInteger) As Boolean Override
End Type
Function PositiveRule.Admit(ByVal items As UInteger) As Boolean
    Return items > 0 AndAlso items <= This.Limit()
End Function

Type EmptyAllowedRule Extends BatchRule
    Declare Function Admit(ByVal items As UInteger) As Boolean Override
    Declare Function Limit() As UInteger Override
End Type
Function EmptyAllowedRule.Admit(ByVal items As UInteger) As Boolean
    Return items <= This.Limit()
End Function
Function EmptyAllowedRule.Limit() As UInteger
    ' Base. explicitly calls the retained base implementation, not this override.
    Return Base.Limit() - 2
End Function

Sub Require(ByVal condition As Boolean, ByRef message As String)
    If Not condition Then
        Print "Check failed: "; message
        End 1
    End If
End Sub

' The concrete values own their lifetimes. These pointers borrow them; no New,
' Delete, pointer escape or polymorphic heap destruction is used in this lab.
Dim positive As PositiveRule
Dim emptyAllowed As EmptyAllowedRule
Dim rules(0 To 1) As BatchRule Ptr = {@positive, @emptyAllowed}
Require(rules(0)->Admit(0) = False, "positive rule rejects zero")
Require(rules(0)->Admit(1), "positive rule accepts one")
Require(rules(0)->Admit(4), "positive rule accepts its boundary")
Require(rules(0)->Admit(5) = False, "positive rule rejects excess")
Require(rules(1)->Admit(0), "empty rule accepts zero")
Require(rules(1)->Admit(2), "empty rule accepts its boundary")
Require(rules(1)->Admit(3) = False, "empty rule rejects excess")
Require(rules(0)->Limit() = 4 AndAlso rules(1)->Limit() = 2, "overrides choose different limits")
Print "Umicom virtual rules: all checks passed"
