'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/local_storage.bas
'
' PURPOSE:
'   Separate a local name from retained storage and caller-owned state.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'---------------------------------------------------------------------------

Type Counter
    value As ULong
End Type

Function NextOwned(ByRef state As Counter, ByRef outputValue As ULong) As Boolean
    ' The three-step cap makes refusal observable without waiting for overflow.
    If state.value >= 3 Then Return False
    Dim candidate As ULong = state.value + 1
    state.value = candidate
    outputValue = candidate
    Return True
End Function

Function NextAutomatic(ByRef outputValue As ULong) As Boolean
    Dim state As Counter
    state.value = 0
    Return NextOwned(state, outputValue)
End Function

Function NextHidden(ByRef outputValue As ULong) As Boolean
    ' This name is local, but its value is retained between calls. It is not
    ' one counter per application window, document or caller.
    Static state As Counter
    Return NextOwned(state, outputValue)
End Function

Dim As ULong firstValue = 99, secondValue = 99
If Not NextAutomatic(firstValue) Then End 1
If Not NextAutomatic(secondValue) Then End 1
If firstValue <> 1 OrElse secondValue <> 1 Then End 1
Print "Automatic calls: 1, 1"
If Not NextHidden(firstValue) Then End 1
If Not NextHidden(secondValue) Then End 1
If firstValue <> 1 OrElse secondValue <> 2 Then End 1
Print "Static calls: 1, 2"

Dim As Counter leftOwner, rightOwner
leftOwner.value = 0 : rightOwner.value = 0
If Not NextOwned(leftOwner, firstValue) Then End 1
If Not NextOwned(rightOwner, secondValue) Then End 1
If Not NextOwned(leftOwner, firstValue) Then End 1
If leftOwner.value <> 2 OrElse rightOwner.value <> 1 Then End 1
If Not NextOwned(leftOwner, firstValue) Then End 1
firstValue = 99
If NextOwned(leftOwner, firstValue) Then End 1
If leftOwner.value <> 3 OrElse rightOwner.value <> 1 OrElse firstValue <> 99 Then End 1
Print "Owned counters: left 3, right 1; refusal preserved 99"
