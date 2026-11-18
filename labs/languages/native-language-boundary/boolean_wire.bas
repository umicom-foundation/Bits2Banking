'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/boolean_wire.bas
'
' PURPOSE:
'   Convert Boolean values to explicit byte flags and reject noncanonical input before publishing.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'-----------------------------------------------------------------------------

Function EncodeFlag(ByVal value As Boolean) As UByte
    ' The wire contract is 0 or 1, independent of Boolean-to-integer conversion.
    If value Then Return 1
    Return 0
End Function

Function DecodeFlag(ByVal raw As UByte, ByRef value As Boolean) As Boolean
    ' Refuse before assignment, so the caller can distinguish failure from false.
    If raw > 1 Then Return False
    value = (raw = 1)
    Return True
End Function

Sub Require(ByVal condition As Boolean, ByRef description As Const String)
    If Not condition Then
        Print "FAILED: "; description
        End 1
    End If
End Sub

Dim enabled As Boolean = True
Dim disabled As Boolean = False
Require(CInt(enabled) = -1, "FreeBASIC true converted to integer")
Require(CInt(disabled) = 0, "FreeBASIC false converted to integer")
Require(EncodeFlag(enabled) = 1, "explicit true byte")
Require(EncodeFlag(disabled) = 0, "explicit false byte")
For raw As UInteger = 0 To 255
    Dim destination As Boolean = True
    Dim accepted As Boolean = DecodeFlag(CUByte(raw), destination)
    If raw <= 1 Then
        Require(accepted, "canonical flag admitted")
        Require(destination = (raw = 1), "decoded logical value")
    Else
        Require(Not accepted, "noncanonical byte refused")
        Require(destination, "refusal preserves true destination")
        destination = False
        accepted = DecodeFlag(CUByte(raw), destination)
        Require(Not accepted AndAlso Not destination, "refusal preserves false destination")
    End If
Next raw
Print "Umicom Boolean wire: all 256 bytes checked."
Print "Explicit encoding: false=0, true=1."
