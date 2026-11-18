'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/flag_operators.bas
' 
' PURPOSE:
'   Use explicit bit-set operators while keeping external-value admission separate.
' 
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
' 
' LICENCE:
' MIT
' ---------------------------------------------------------------------------

Type FlagSet
    bits As ULong
End Type

' These global operators return independent values; neither operand changes.
' Bit-set union/intersection are the domain meanings of Or and And here.
Operator Or(ByVal lhs As FlagSet, ByVal rhs As FlagSet) As FlagSet
    Return Type<FlagSet>(lhs.bits Or rhs.bits)
End Operator
Operator And(ByVal lhs As FlagSet, ByVal rhs As FlagSet) As FlagSet
    Return Type<FlagSet>(lhs.bits And rhs.bits)
End Operator

Function TryAdmitFlags(ByVal raw As ULong, ByRef destination As FlagSet) As Boolean
    Dim allowed As ULong = 7
    If (raw And (Not allowed)) <> 0 Then Return False
    destination.bits = raw
    Return True
End Function
Sub Require(ByVal condition As Boolean, ByRef description As Const String)
    If Not condition Then
        Print "FAILED: "; description
        End 1
    End If
End Sub

Dim readFlag As FlagSet = Type<FlagSet>(1)
Dim writeFlag As FlagSet = Type<FlagSet>(2)
Dim inspectFlag As FlagSet = Type<FlagSet>(4)
Dim combined As FlagSet = readFlag Or inspectFlag
Dim common As FlagSet = combined And readFlag
Require(combined.bits = 5, "union uses bits, not addition")
Require(common.bits = 1, "intersection retains only the common flag")
Dim repeated As FlagSet = readFlag Or readFlag
Require(repeated.bits = 1, "repeating a flag does not double it")
Require(readFlag.bits = 1 AndAlso inspectFlag.bits = 4, "operands stay unchanged")
Dim saved As FlagSet = writeFlag
Require(Not TryAdmitFlags(8, saved), "unknown external bit refused")
Require(saved.bits = 2, "refusal preserves prior output")
Require(TryAdmitFlags(7, saved), "all defined bits accepted")
Require(saved.bits = 7, "accepted value published")
Print "Umicom BASIC flags: union 5, intersection 1, repeated flag 1."
Print "Unknown input refused; operator syntax does not grant permission."
