'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/client.bas
'
' PURPOSE:
'   Call the bounded C service from a FreeBASIC console client.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'-----------------------------------------------------------------------------
Extern "C"
    Declare Function bounded_progress Cdecl Alias "bounded_progress" _
        (ByVal completed As Long, ByVal total As Long, _
         ByVal percent As Long Ptr) As Long
End Extern
Dim As Long percent = -1
If bounded_progress(2, 8, @percent) <> 0 Then End 1
If percent <> 25 Then End 2
Print percent
' Check the contract, not only the successful result.
If bounded_progress(1, 0, @percent) <> 1 Then End 3
If percent <> 25 Then End 4
Print "FreeBASIC boundary checks passed"
End 0
