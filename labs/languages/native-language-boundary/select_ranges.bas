'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/select_ranges.bas
'
' PURPOSE:
'   Classify boundary values with ordered BASIC cases and explicit refusal.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'---------------------------------------------------------------------------

' This is an invented display-scale exercise, not a financial risk policy.
' Publish the band only after the raw score has matched the accepted domain.
Function TryBand(ByVal score As Integer, ByRef band As Integer) As Boolean
    Select Case score
    Case Is < 0, Is > 100
        Return False
    Case 0 To 24
        band = 0
    Case 25 To 74
        band = 1
    Case 75 To 100
        band = 2
    Case Else
        Return False
    End Select
    Return True
End Function

Function BandName(ByVal band As Integer) As String
    Select Case As Const band
    Case 0
        Return "low"
    Case 1
        Return "middle"
    Case 2
        Return "high"
    Case Else
        Return "unknown"
    End Select
End Function

Function ReadSample(ByRef samples As Integer) As Integer
    samples += 1
    Return 25
End Function

Sub Require(ByVal condition As Boolean, ByRef description As Const String)
    If Not condition Then
        Print "FAILED: "; description
        End 1
    End If
End Sub

Dim scores(0 To 5) As Integer = {0, 24, 25, 74, 75, 100}
Dim expected(0 To 5) As Integer = {0, 0, 1, 1, 2, 2}
For index As Integer = 0 To 5
    Dim actual As Integer = -9
    Require(TryBand(scores(index), actual), "accepted endpoint")
    Require(actual = expected(index), "endpoint band")
Next
Dim kept As Integer = 77
Require(Not TryBand(-1, kept), "below lower boundary")
Require(kept = 77, "refusal keeps prior output")
Require(Not TryBand(101, kept), "above upper boundary")
Require(kept = 77, "second refusal keeps prior output")
Require(BandName(0) = "low", "constant case zero")
Require(BandName(1) = "middle", "constant case one")
Require(BandName(2) = "high", "constant case two")
Require(BandName(99) = "unknown", "constant dispatch fallback")

Dim samples As Integer = 0
Dim chosen As Integer = 0
Select Case ReadSample(samples)
Case 0 To 50
    chosen = 1
Case 25
    chosen = 2
Case Else
    chosen = 3
End Select
Require(samples = 1, "selector evaluated once")
Require(chosen = 1, "first matching case wins without fall-through")

Dim afterSelect As Integer = 0
Select Case 1
Case 1
    afterSelect = 4
    Exit Select
    afterSelect = 99
End Select
Require(afterSelect = 4, "Exit Select skips remaining case body")
Print "Umicom BASIC selection: six endpoints and two refusals checked."
Print "One sample, one matching branch, prior output preserved on refusal."
