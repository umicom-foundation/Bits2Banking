'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/conditional_selection.bas
'
' PURPOSE:
'   Observe selected-expression evaluation separately from ordinary argument evaluation.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'---------------------------------------------------------------------------

Function Probe(ByVal value As Integer, ByRef calls As Integer) As Integer
    calls += 1
    Return value
End Function

Function ProbeCondition(ByVal choice As Boolean, ByRef calls As Integer) As Boolean
    calls += 1
    Return choice
End Function

Function ChooseValues(ByVal choice As Boolean, ByVal leftValue As Integer, ByVal rightValue As Integer) As Integer
    If choice Then Return leftValue
    Return rightValue
End Function

Function CheckSelection(ByVal choice As Boolean) As Boolean
    Dim As Integer leftCalls = 0, rightCalls = 0, conditionCalls = 0
    Dim As Integer expected
    If choice Then
        expected = 11
    Else
        expected = 22
    End If
    ' IIf is a compiler-supported selective expression, not an ordinary call
    ' that receives two already-computed values. Keep both probes harmless.
    Dim As Integer selected = IIf(ProbeCondition(choice, conditionCalls), Probe(11, leftCalls), Probe(22, rightCalls))
    If selected <> expected OrElse conditionCalls <> 1 Then Return False
    If choice Then
        If leftCalls <> 1 OrElse rightCalls <> 0 Then Return False
    Else
        If leftCalls <> 0 OrElse rightCalls <> 1 Then Return False
    End If

    leftCalls = 0 : rightCalls = 0 : conditionCalls = 0
    ' ByVal arguments are computed before ChooseValues can choose between
    ' their values. This check does not depend on which argument runs first.
    selected = ChooseValues(ProbeCondition(choice, conditionCalls), Probe(11, leftCalls), Probe(22, rightCalls))
    If selected <> expected Then Return False
    Return leftCalls = 1 AndAlso rightCalls = 1 AndAlso conditionCalls = 1
End Function

If Not CheckSelection(True) Then End 1
If Not CheckSelection(False) Then End 1
Print "Umicom FreeBASIC selective expression and eager argument checks passed."
