'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/overloaded_byte_count.bas
'
' PURPOSE:
'   Compare typed overload selection with checked byte-count publication.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'---------------------------------------------------------------------------

Const MAX_WIRE_BYTES As ULongInt = 4294967295

' The overloads differ in the input parameter type, not in return type.
Declare Function TryByteCount Overload(ByVal amount As ULongInt, ByRef result As ULong) As Integer
Declare Function TryByteCount Overload(ByRef text As String, ByRef result As ULong) As Integer

Function TryByteCount(ByVal amount As ULongInt, ByRef result As ULong) As Integer
    If amount > MAX_WIRE_BYTES Then Return 0
    ' Publish only after admission. The conversion is now representable.
    result = CULng(amount)
    Return -1
End Function

Function TryByteCount(ByRef text As String, ByRef result As ULong) As Integer
    ' A counted String reports bytes, not Unicode characters or LLM tokens.
    ' The explicit conversion selects the numeric overload.
    Return TryByteCount(CULngInt(Len(text)), result)
End Function

Dim payload As String = "Umicom"
Dim result As ULong = 71
Dim requested As ULongInt = 42
If TryByteCount(payload, result) = 0 OrElse result <> 6 Then End 1
Print "Text bytes:"; result
If TryByteCount(requested, result) = 0 OrElse result <> 42 Then End 2
Print "Requested bytes:"; result
requested = MAX_WIRE_BYTES
If TryByteCount(requested, result) = 0 OrElse result <> CULng(MAX_WIRE_BYTES) Then End 3
result = 71
requested = MAX_WIRE_BYTES + 1
If TryByteCount(requested, result) <> 0 OrElse result <> 71 Then End 4
Print "Refused oversized count; preserved:"; result
payload = ""
If TryByteCount(payload, result) = 0 OrElse result <> 0 Then End 5
Print "Empty text bytes:"; result
