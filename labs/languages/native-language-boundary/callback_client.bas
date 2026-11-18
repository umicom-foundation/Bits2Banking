'-----------------------------------------------------------------------------
' Umicom Bits2Banking
' File: labs/languages/native-language-boundary/callback_client.bas
'
' PURPOSE:
'   Pass a synchronous FreeBASIC callback and explicit context to the C lesson.
'
' AUTHOR AND ORGANISATION:
' Sammy Hegab
' Umicom Foundation
'
' LICENCE:
' MIT
'-----------------------------------------------------------------------------
Type ProgressVisitor As Function Cdecl (ByVal rowIndex As Long, _
    ByVal percent As Long, ByVal context As Any Ptr) As Long
Extern "C"
    Declare Function bounded_progress_visit Cdecl Alias "bounded_progress_visit" _
        (ByVal completed As Const Long Ptr, ByVal totals As Const Long Ptr, _
         ByVal count As Long, ByVal visitor As ProgressVisitor, _
         ByVal context As Any Ptr, ByVal accepted As Long Ptr) As Long
End Extern
Type CallbackState
    calls As Long
    stopAt As Long
End Type
Function OnProgress Cdecl (ByVal rowIndex As Long, ByVal percent As Long, _
    ByVal context As Any Ptr) As Long
    If context = 0 Then Return 99
    Dim As CallbackState Ptr state = CPtr(CallbackState Ptr, context)
    If rowIndex <> state->calls Then Return 99
    state->calls += 1
    Print "Row "; rowIndex; " percent "; percent
    If rowIndex = state->stopAt Then Return 17
    Return 0
End Function
Dim As Long completed(0 To 2) = {1, 2, 3}
Dim As Long totals(0 To 2) = {4, 4, 4}
Dim As CallbackState state = (0, 1)
Dim As Long accepted = -1
Dim As Long status = bounded_progress_visit(@completed(0), @totals(0), 3, _
    @OnProgress, @state, @accepted)
If status <> 2 OrElse accepted <> 1 OrElse state.calls <> 2 Then End 1
Print "FreeBASIC callback checks passed"
End 0
