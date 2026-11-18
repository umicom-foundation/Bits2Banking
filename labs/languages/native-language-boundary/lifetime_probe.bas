'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/lifetime_probe.bas
'
' PURPOSE:
'   Observe ordinary scoped construction and destruction without owning native resources.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'-----------------------------------------------------------------------------

' Counters belong only to this single-threaded exercise, not an application API.
Dim Shared As Integer createdCount = 0, destroyedCount = 0, liveCount = 0

Type LifetimeProbe
    identifier As Integer
    Declare Constructor()
    Declare Destructor()
End Type

Constructor LifetimeProbe()
    createdCount += 1
    liveCount += 1
    This.identifier = createdCount
    Print "Create "; This.identifier; " live="; liveCount
End Constructor

Destructor LifetimeProbe()
    destroyedCount += 1
    liveCount -= 1
    Print "Destroy "; This.identifier; " live="; liveCount
End Destructor

Function LeaveEarly() As Integer
    Dim localProbe As LifetimeProbe
    If liveCount <> 2 Then Return 1
    ' An ordinary procedure return leaves the local variable's lifetime.
    Return 0
End Function

Function Exercise() As Integer
    Dim outerProbe As LifetimeProbe
    If liveCount <> 1 Then Return 1
    Scope
        Dim innerProbe As LifetimeProbe
        If liveCount <> 2 Then Return 1
    End Scope
    If liveCount <> 1 OrElse destroyedCount <> 1 Then Return 1
    If LeaveEarly() <> 0 Then Return 1
    If liveCount <> 1 OrElse destroyedCount <> 2 Then Return 1
    Return 0
End Function

Dim result As Integer = Exercise()
If result <> 0 OrElse liveCount <> 0 OrElse createdCount <> 3 OrElse destroyedCount <> 3 Then
    Print "Lifetime observation failed"
    End 1
End If
Print "Umicom lifetime observation: three created, three destroyed, none live"
End 0
