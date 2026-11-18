'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/fixed_ascii_fields.bas
'
' PURPOSE:
'   Format admitted ASCII fields without silently truncating an identifier.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'---------------------------------------------------------------------------

' LSet/RSet are formatting operations, not input validators. Build a candidate
' only after the whole input is admitted; publish it after formatting succeeds.
Function TryAsciiField(ByRef source As Const String, ByVal fieldWidth As Integer, _
    ByVal alignRight As Boolean, ByRef output As String) As Boolean
    If fieldWidth < 1 OrElse fieldWidth > 32 Then Return False
    If Len(source) > fieldWidth Then Return False
    For position As Integer = 1 To Len(source)
        Dim code As UInteger = Asc(source, position)
        If code < 32 OrElse code > 126 Then Return False
    Next position
    Dim candidate As String = Space(fieldWidth)
    If Len(candidate) <> fieldWidth Then Return False
    If alignRight Then
        RSet candidate, source
    Else
        LSet candidate, source
    End If
    output = candidate
    Return True
End Function

Dim leftField As String = "old-left"
Dim rightField As String = "old-right"
If Not TryAsciiField("AB7", 6, False, leftField) Then End 1
If Not TryAsciiField("42", 6, True, rightField) Then End 2
If leftField <> "AB7   " OrElse rightField <> "    42" Then End 3
Print "Left field: [" & leftField & "]"
Print "Right field: [" & rightField & "]"

Dim saved As String = leftField
If TryAsciiField("ACCOUNT7", 6, False, leftField) Then End 4
If leftField <> saved Then End 5
If TryAsciiField(Chr(9), 6, False, leftField) Then End 6
If leftField <> saved Then End 7
If TryAsciiField("A", 0, False, leftField) Then End 8
If TryAsciiField("A", 33, False, leftField) Then End 9
If leftField <> saved Then End 10
Print "Refused fields keep: [" & leftField & "]"

Dim blank As String = "previous"
If Not TryAsciiField("", 4, False, blank) Then End 11
If blank <> "    " Then End 12
Print "Empty input becomes: [" & blank & "]"

' This deliberate counterexample shows why admission belongs before LSet.
Dim clipped As String = Space(4)
LSet clipped, "LONGER"
If clipped <> "LONG" OrElse Len(clipped) <> 4 Then End 13
Print "Raw LSet truncates: [" & clipped & "]"
End 0
