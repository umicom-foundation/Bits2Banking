'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/rounding_policy.bas
' 
' PURPOSE:
'   Compare explicit rounding rules and admit a bounded numeric value before changing a caller-owned integer.
' 
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
' 
' LICENCE:
' MIT
'-----------------------------------------------------------------------------


Function TryTruncateLong(ByVal value As Double, ByRef destination As Long) As Boolean
    ' This deliberately conservative contract checks the ORIGINAL value.
    ' It does not accept a fractional overshoot merely because truncation
    ' could later bring that value back inside the signed 32-bit interval.
    If Not (value >= -2147483648.0 AndAlso value <= 2147483647.0) Then Return False
    destination = CLng(Fix(value))
    Return True
End Function

Sub Require(ByVal condition As Boolean, ByRef description As Const String)
    If Not condition Then
        Print "FAILED: "; description
        End 1
    End If
End Sub

' Exact halves reveal tie rules without a decimal representation ambiguity.
Dim values(0 To 5) As Double = {2.5, 3.5, -2.5, -3.5, 1.75, -1.75}
Dim nearestEven(0 To 5) As Integer = {2, 4, -2, -4, 2, -2}
Dim towardZero(0 To 5) As Integer = {2, 3, -2, -3, 1, -1}
Dim downward(0 To 5) As Integer = {2, 3, -3, -4, 1, -2}
For i As Integer = 0 To 5
    Require(CInt(values(i)) = nearestEven(i), "nearest with even halfway result")
    Require(Fix(values(i)) = towardZero(i), "truncate toward zero")
    Require(Int(values(i)) = downward(i), "floor toward negative infinity")
Next i

Dim destination As Long = 77
Require(TryTruncateLong(-3.5, destination), "small finite input")
Require(destination = -3, "published truncated integer")
destination = 77
Require(Not TryTruncateLong(2147483647.5, destination), "original upper bound")
Require(destination = 77, "failed upper bound preserves destination")
Require(Not TryTruncateLong(-2147483648.5, destination), "original lower bound")
Require(destination = 77, "failed lower bound preserves destination")
Require(Not TryTruncateLong(1.0e100, destination), "large finite input refused before cast")
Require(destination = 77, "large refusal preserves destination")
Require(TryTruncateLong(2147483647.0, destination), "exact upper endpoint")
Require(destination = 2147483647, "upper endpoint stored")
Require(TryTruncateLong(-2147483648.0, destination), "exact lower endpoint")
Require(destination = -2147483647 - 1, "lower endpoint stored")
Print "Umicom BASIC rounding: six rows checked."
Print "Refused conversions preserve the caller's integer."
