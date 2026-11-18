'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/text_bytes.bas
'
' PURPOSE:
'   Distinguish counted string bytes, UTF-8 sequences and narrow ASCII boundary policies.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'-----------------------------------------------------------------------------
Option Explicit

Sub Require(ByVal condition As Boolean, ByRef message As String)
    If Not condition Then
        Print "Check failed: "; message
        End 1
    End If
End Sub

' A deliberately narrow teaching policy, not a Unicode validator.
' Printable ASCII labels have 1..32 bytes; spaces are permitted.
Function IsPlainAsciiLabel(ByRef value As String) As Boolean
    If Len(value) = 0 OrElse Len(value) > 32 Then Return False
    For position As Integer = 1 To Len(value)
        Dim As Integer byteValue = Asc(Mid(value, position, 1))
        If byteValue < 32 OrElse byteValue > 126 Then Return False
    Next
    Return True
End Function

Dim As String asciiText = "Umicom"
' Encode U+00E9 explicitly so the fixture does not depend on source-file encoding.
Dim As String utf8Text = "caf" & Chr(&HC3) & Chr(&HA9)
Dim As String embeddedZero = "A" & Chr(0) & "B"
Dim As String brokenPrefix = Left(utf8Text, 4)
Dim As String completePrefix = Left(utf8Text, 3)

Require(Len(asciiText) = 6, "six ASCII bytes")
Require(Len(utf8Text) = 5, "five UTF-8 bytes represent four code points here")
Require(Asc(Mid(utf8Text, 4, 1)) = 195, "the first byte of the final code point")
Require(Asc(Mid(utf8Text, 5, 1)) = 169, "the second byte of the final code point")
Require(Len(embeddedZero) = 3, "a counted String retains the embedded zero")
Require(Asc(Mid(embeddedZero, 2, 1)) = 0, "the middle byte is zero")
Require(Mid(embeddedZero, 3, 1) = "B", "the byte after zero remains present")
Require(Len(brokenPrefix) = 4, "a byte prefix can split a UTF-8 code point")
Require(Asc(Right(brokenPrefix, 1)) = 195, "the split leaves only a leading byte")
Require(completePrefix = "caf", "this known boundary preserves complete code points")
Require(IsPlainAsciiLabel(asciiText), "the ASCII teaching label is admitted")
Require(Not IsPlainAsciiLabel(utf8Text), "this narrow policy does not accept non-ASCII")
Require(Not IsPlainAsciiLabel(embeddedZero), "embedded zero is refused")
Dim As String emptyText = ""
Require(Not IsPlainAsciiLabel(emptyText), "empty labels are refused")
Dim As String tooLong = Space(33)
Require(Not IsPlainAsciiLabel(tooLong), "the declared byte limit is enforced")

Print "Umicom text-byte exercise"
Print "ASCII bytes:"; Len(asciiText)
Print "UTF-8 fixture bytes:"; Len(utf8Text)
Print "Final UTF-8 bytes:"; Asc(Mid(utf8Text, 4, 1)); Asc(Mid(utf8Text, 5, 1))
Print "Counted bytes with embedded zero:"; Len(embeddedZero)
Print "The byte after zero:"; Mid(embeddedZero, 3, 1)
Print "Safe known prefix:"; completePrefix
Print "A general UTF-8 boundary check needs a real decoder."
End 0
