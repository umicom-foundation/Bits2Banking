'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/record_drafts.bas
'
' PURPOSE:
'   Explain nested With field access and publish a checked record candidate without mutating the original on refusal.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'---------------------------------------------------------------------------


Type PixelSize
    width As ULong
    height As ULong
End Type

Type FramePlan
    inputSize As PixelSize
    outputSize As PixelSize
End Type

Const MAX_PIXELS As ULongInt = 1048576

Function TryOutput(ByRef plan As FramePlan, ByVal width As ULong, ByVal height As ULong) As Boolean
    If width = 0 OrElse height = 0 Then Return False
    If CULngInt(width) > MAX_PIXELS \ CULngInt(height) Then Return False
    ' This plain value record owns no pointer or dynamic array. The candidate
    ' is independent value storage; With itself neither copies nor validates.
    Dim candidate As FramePlan = plan
    With candidate.outputSize
        .width = width
        .height = height
    End With
    plan = candidate
    Return True
End Function

Dim plan As FramePlan
With plan
    .inputSize.width = 640
    .inputSize.height = 360
    With .outputSize
        .width = 320
        .height = 180
    End With
End With
If plan.inputSize.width <> 640 OrElse plan.outputSize.width <> 320 Then End 1
If Not TryOutput(plan, 800, 600) Then End 2
If plan.outputSize.width <> 800 OrElse plan.outputSize.height <> 600 Then End 3
If TryOutput(plan, 2000, 1000) Then End 4
If TryOutput(plan, 800, 0) Then End 5
If plan.outputSize.width <> 800 OrElse plan.outputSize.height <> 600 Then End 6
If plan.inputSize.width <> 640 OrElse plan.inputSize.height <> 360 Then End 7
Print "input stays 640 by 360; output is 800 by 600"
Print "oversized and empty requests refused; accepted record preserved"
End 0
