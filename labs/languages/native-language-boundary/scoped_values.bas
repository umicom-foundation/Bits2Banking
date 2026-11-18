'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/scoped_values.bas
'
' PURPOSE:
'   Distinguish a shadowing local from an outer result and keep temporary calculations inside explicit scopes.
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

Dim As Integer selectedCount = 4
Dim As Integer reviewedTotal = 0

Scope
    ' This reads the outer count before a separate local hides that name.
    Dim As Integer originalCount = selectedCount
    Dim As Integer selectedCount = 7
    reviewedTotal = originalCount + selectedCount
    Require(selectedCount = 7, "the temporary count must be seven")
    Require(reviewedTotal = 11, "the explicit result copy must be eleven")
    Print "Inner count:"; selectedCount
End Scope

Require(selectedCount = 4, "the outer count must remain four")
Require(reviewedTotal = 11, "the copied result must remain available")
Print "Outer count:"; selectedCount
Print "Reviewed total:"; reviewedTotal

Scope
    ' A separate temporary calculation uses a distinct scope.
    Dim As Integer originalCount = selectedCount
    reviewedTotal += originalCount
End Scope
Require(reviewedTotal = 15, "the second calculation must add four")
Print "Final total:"; reviewedTotal
End 0
