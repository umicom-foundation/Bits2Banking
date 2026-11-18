'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/comments.bas
'
' PURPOSE:
'   Distinguish BASIC comment statements from quoted text and executable code.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'-----------------------------------------------------------------------------

Dim As Integer total = 2
REM This is comment text, including ?> and <?java.
total = total + 3 : rEm The colon begins another statement; this one is a comment.
' An apostrophe starts a comment too. total = 999 does not execute here.
Dim As String label = "REM ?> is text inside a string"
If total <> 5 OrElse label <> "REM ?> is text inside a string" Then
    Print "Unexpected comment or string behavior"
    End 1
End If
Print label
Print "Comment checks passed"
