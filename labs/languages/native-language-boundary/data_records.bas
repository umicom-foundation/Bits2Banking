'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/data_records.bas
'
' PURPOSE:
'   Traverse a fixed compile-time fixture with Data, Read and Restore without reading beyond its admitted record count.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'-----------------------------------------------------------------------------

Const RECORD_COUNT As Integer = 4
Const MAX_COUNT As ULongInt = 4294967295

Function TryArea(ByVal width As ULong, ByVal height As ULong, ByRef result As ULong) As Boolean
    If width = 0 OrElse height = 0 Then Return False
    If CULngInt(width) > MAX_COUNT \ CULngInt(height) Then Return False
    result = width * height
    Return True
End Function

' This count belongs to the trusted embedded fixture. Never read until a guessed
' sentinel: reading past the module's Data list has undefined behavior.
Restore AreaCases
For row As Integer = 1 To RECORD_COUNT
    Dim width As ULong, height As ULong, expectedArea As ULong
    Dim expectedAccepted As Integer
    Read width, height, expectedAccepted, expectedArea
    Dim result As ULong = 71
    Dim accepted As Boolean = TryArea(width, height, result)
    If (accepted <> 0) <> (expectedAccepted <> 0) Then End 1
    If result <> expectedArea Then End 2
    Print "Case"; row; ": accepted="; expectedAccepted; ", area="; result
Next

' Restore rewinds the Data cursor; it does not reset existing variables.
Dim firstWidth As ULong, firstHeight As ULong, firstStatus As Integer, firstArea As ULong
Restore AreaCases
Read firstWidth, firstHeight, firstStatus, firstArea
If firstWidth <> 640 OrElse firstHeight <> 360 OrElse firstArea <> 230400 Then End 3
Print "Restored first record:"; firstWidth; " x"; firstHeight
End 0

AreaCases:
Data 640, 360, 1, 230400
Data 1920, 1080, 1, 2073600
Data 0, 720, 0, 71
Data 65536, 65536, 0, 71
