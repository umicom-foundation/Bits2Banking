'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/parse_count.bas
'
' PURPOSE:
'   Validate a complete bounded decimal input before publishing a BASIC value.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'-----------------------------------------------------------------------------

Function TryParseCount(ByRef text As Const String, ByRef output As ULong) As Boolean
    Const As ULong maximum = 1000000
    Dim As Integer length = Len(text)
    If length < 1 OrElse length > 7 Then Return False
    Dim As ULong candidate = 0
    For position As Integer = 1 To length
        Dim As Integer code = Asc(text, position)
        If code < Asc("0") OrElse code > Asc("9") Then Return False
        Dim As ULong digit = code - Asc("0")
        ' Check before multiplication, not after a value might have wrapped.
        If candidate > (maximum - digit) \ 10 Then Return False
        candidate = candidate * 10 + digit
    Next position
    ' Only a complete valid input changes the caller's output variable.
    output = candidate
    Return True
End Function

Sub CheckAccepted(ByVal text As String, ByVal expected As ULong)
    Dim As ULong value = 77
    If Not TryParseCount(text, value) OrElse value <> expected Then
        Print "Unexpected rejection: "; text
        End 1
    End If
End Sub
Sub CheckRejected(ByVal text As String)
    Dim As ULong value = 77
    If TryParseCount(text, value) OrElse value <> 77 Then
        Print "Unexpected acceptance or changed output: "; text
        End 1
    End If
End Sub

CheckAccepted("0", 0)
CheckAccepted("0000123", 123)
CheckAccepted("1000000", 1000000)
CheckRejected("")
CheckRejected("1000001")
CheckRejected("12jobs")
CheckRejected("-1")
CheckRejected("+1")
CheckRejected("1.5")
CheckRejected(" 12")
CheckRejected("12 ")
CheckRejected("00000000")
Print "Strict count checks passed"
