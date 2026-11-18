'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/thread_counter.bas
'
' PURPOSE:
'   Keep a borrowed counter and mutex alive until every successfully created worker has finished.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'---------------------------------------------------------------------------

Const Iterations As ULong = 10000

Type CounterState
    gate As Any Ptr
    completed As ULong
End Type

Sub CountWorker(ByVal raw As Any Ptr)
    ' ThreadCreate borrows this address. The caller joins both workers before
    ' destroying the lock or allowing the pointed-to record to leave its scope.
    Dim state As CounterState Ptr = CPtr(CounterState Ptr, raw)
    For stepIndex As ULong = 1 To Iterations
        MutexLock(state->gate)
        state->completed += 1
        MutexUnlock(state->gate)
    Next
End Sub

Dim state As CounterState
state.completed = 0
state.gate = MutexCreate()
If state.gate = 0 Then
    Print "Could not create the counter mutex."
    End 1
End If

Dim handles(0 To 1) As Any Ptr
For workerIndex As Integer = 0 To 1
    handles(workerIndex) = ThreadCreate(@CountWorker, @state)
    If handles(workerIndex) = 0 Then
        ' A partial start still owns every earlier successful handle. Joining
        ' those finite workers preserves their borrowed context during failure.
        For earlier As Integer = 0 To workerIndex - 1
            ThreadWait(handles(earlier))
        Next
        MutexDestroy(state.gate)
        Print "Could not create both workers; completed workers were joined."
        End 1
    End If
Next

For workerIndex As Integer = 0 To 1
    ThreadWait(handles(workerIndex))
Next

' The joins have ended every writer. Use the same lock for the final snapshot
' to keep the synchronization convention visible if the exercise is extended.
MutexLock(state.gate)
Dim observed As ULong = state.completed
MutexUnlock(state.gate)
MutexDestroy(state.gate)
state.gate = 0

If observed <> 2 * Iterations Then
    Print "Unexpected completed count: "; observed
    End 1
End If
Print "Completed increments: "; observed
Print "Both workers joined before mutex destruction."
End 0
