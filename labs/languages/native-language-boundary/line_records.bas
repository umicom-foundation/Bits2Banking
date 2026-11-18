'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/line_records.bas
'
' PURPOSE:
'   Read a small ASCII fixture with explicit runtime error checks and a single file-close path.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'-----------------------------------------------------------------------------

' Compile without -e/-ex/-exx: this exercise handles Err inline.
' These are admission limits AFTER a dynamic line is read, not memory caps.
Const MaxLines As UInteger = 16
Const MaxLineBytes As UInteger = 128
Dim filename As String = Command(1)
If filename = "" OrElse Command(2) <> "" Then
    Print "Usage: line_records path-to-small-ascii-file"
    End 2
End If
Dim fileNumber As Integer = FreeFile
Dim openStatus As Long = Open(filename For Input As #fileNumber)
If openStatus <> 0 Then
    Print "Open failed with runtime code "; openStatus
    End 1
End If
Dim As UInteger lineCount = 0, nonemptyCount = 0, textBytes = 0
Dim As Long failure = 0
Dim firstNonempty As String
Do
    Err = 0
    Dim atEnd As Integer = Eof(fileNumber)
    Dim readStatus As Long = Err()
    If readStatus <> 0 Then
        failure = readStatus
        Exit Do
    End If
    If atEnd Then Exit Do
    Dim row As String
    Err = 0
    Line Input #fileNumber, row
    readStatus = Err()
    If readStatus <> 0 Then
        failure = readStatus
        Exit Do
    End If
    If lineCount = MaxLines OrElse Len(row) > MaxLineBytes Then
        failure = 1001
        Exit Do
    End If
    lineCount += 1
    textBytes += Len(row)
    If Len(row) <> 0 Then
        nonemptyCount += 1
        If firstNonempty = "" Then firstNonempty = row
    End If
Loop
' Preserve the first failure before Close or Print can change the runtime Err.
Dim closeStatus As Long = Close(fileNumber)
If failure = 0 AndAlso closeStatus <> 0 Then failure = closeStatus
If failure <> 0 Then
    Print "Read/limit/close failure code "; failure
    End 1
End If
Print "Lines="; lineCount; " Nonempty="; nonemptyCount; " Text bytes="; textBytes
Print "First nonempty="; firstNonempty
End 0
