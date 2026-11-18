'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/inspect_umc_header.bas
'
' PURPOSE:
'   Inspect only the bounded Umicom C wire envelope and preserve output when header admission fails.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'-----------------------------------------------------------------------------

Type EnvelopeInfo
    profile As ULong
    instructionCount As ULong
    encodedBytes As ULong
End Type

Function InspectEnvelope(bytes() As UByte, ByRef result As EnvelopeInfo) As Boolean
    ' Array descriptors are checked before reading any byte. This accepts one
    ' zero-based dimension and at most the current 256-record envelope.
    If UBound(bytes, 0) <> 1 Then Return False
    If LBound(bytes) <> 0 OrElse UBound(bytes) < 7 OrElse UBound(bytes) > 2311 Then Return False
    If bytes(0) <> &h55 OrElse bytes(1) <> &h4D OrElse _
       bytes(2) <> &h43 OrElse bytes(3) <> &h42 Then Return False
    If bytes(4) < 1 OrElse bytes(4) > 6 OrElse bytes(5) <> 0 Then Return False
    ' Widen each unsigned byte before shifting. Native UDT memory is never read.
    Dim As ULong count = CULng(bytes(6)) Or (CULng(bytes(7)) Shl 8)
    If count = 0 OrElse count > 256 Then Return False
    Dim As ULong needed = 8 + count * 9
    If CULng(UBound(bytes) + 1) <> needed Then Return False
    Dim candidate As EnvelopeInfo
    candidate.profile = bytes(4)
    candidate.instructionCount = count
    candidate.encodedBytes = needed
    result = candidate
    Return True
End Function

Sub Require(ByVal condition As Boolean, ByVal message As String)
    If Not condition Then
        Print message
        End 1
    End If
End Sub

Sub RequireRefusal(bytes() As UByte)
    Dim result As EnvelopeInfo
    result.profile = 99 : result.instructionCount = 77 : result.encodedBytes = 66
    Require(Not InspectEnvelope(bytes(), result), "Malformed envelope accepted")
    Require(result.profile = 99 AndAlso result.instructionCount = 77 AndAlso _
        result.encodedBytes = 66, "Refusal changed the previous result")
End Sub

' Literal format-1 fixture: PUSH 42, RETURN; both source offsets are zero.
' A full runtime decoder still owns opcode, stack and canonical-profile checks.
Dim fixture(0 To 25) As UByte = { _
    &h55, &h4D, &h43, &h42, 1, 0, 2, 0, _
    1, 42, 0, 0, 0, 0, 0, 0, 0, _
    7, 0, 0, 0, 0, 0, 0, 0, 0 }
Dim result As EnvelopeInfo
Require(InspectEnvelope(fixture(), result), "Literal envelope refused")
Require(result.profile = 1 AndAlso result.instructionCount = 2 AndAlso _
    result.encodedBytes = 26, "Wrong envelope facts")

Dim emptyBytes() As UByte
RequireRefusal(emptyBytes())
For length As Integer = 1 To 25
    ReDim prefix(0 To length - 1) As UByte
    For position As Integer = 0 To length - 1
        prefix(position) = fixture(position)
    Next position
    RequireRefusal(prefix())
Next length

Dim offsetBytes(1 To 26) As UByte
For position As Integer = 0 To 25
    offsetBytes(position + 1) = fixture(position)
Next position
RequireRefusal(offsetBytes())
Dim trailing(0 To 26) As UByte
For position As Integer = 0 To 25
    trailing(position) = fixture(position)
Next position
RequireRefusal(trailing())

Dim damaged(0 To 25) As UByte
For caseNumber As Integer = 0 To 6
    For position As Integer = 0 To 25
        damaged(position) = fixture(position)
    Next position
    Select Case caseNumber
        Case 0 : damaged(0) = 0
        Case 1 : damaged(4) = 0
        Case 2 : damaged(4) = 7
        Case 3 : damaged(5) = 1
        Case 4 : damaged(6) = 0
        Case 5 : damaged(6) = 1 : damaged(7) = 1 ' count 257, above the bound
        Case 6 : damaged(6) = 3 ' valid bounded count, but missing a record
    End Select
    RequireRefusal(damaged())
Next caseNumber

For position As Integer = 0 To 25
    damaged(position) = fixture(position)
Next position
damaged(8) = 255
Require(InspectEnvelope(damaged(), result), "Envelope reader inspected an opcode")
Print "Envelope facts: profile 1, instructions 2, bytes 26"
Print "Truncated and malformed envelope checks passed"
Print "Opcode 255 still passes this header-only reader: use the Umicom C runtime before execution"
