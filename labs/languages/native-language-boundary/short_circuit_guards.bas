'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/short_circuit_guards.bas
'
' PURPOSE:
'   Count operand evaluation and guard array reads with AndAlso and OrElse.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'---------------------------------------------------------------------------

Function Probe(ByVal answer As Integer, ByRef calls As Integer) As Integer
    calls += 1
    Return answer
End Function

' The array has explicit inclusive bounds: 2, 3 and 4 are the valid indices.
Dim values(2 To 4) As Integer = {10, 20, 30}
Dim calls As Integer = 0
Dim leftFalse As Integer = 0
Dim leftTrue As Integer = -1
Dim accepted As Integer

accepted = leftFalse AndAlso Probe(-1, calls)
If accepted <> 0 OrElse calls <> 0 Then End 1
accepted = leftFalse And Probe(-1, calls)
If accepted <> 0 OrElse calls <> 1 Then End 2
calls = 0
accepted = leftTrue OrElse Probe(0, calls)
If accepted = 0 OrElse calls <> 0 Then End 3
accepted = leftTrue Or Probe(0, calls)
If accepted = 0 OrElse calls <> 1 Then End 4

Dim matches As Integer = 0
For index As Integer = 0 To 6
    ' Parentheses expose the left-to-right guards. No array element is read
    ' until both bounds have passed. Ordinary And is not this contract.
    If (index >= LBound(values)) AndAlso (index <= UBound(values)) AndAlso (values(index) = 20) Then
        matches += 1
        Print "Matching index:"; index
    End If
Next
If matches <> 1 Then End 5
Print "AndAlso skips the right side after false; OrElse skips it after true."
Print "The guarded array scan found one match."
End 0
