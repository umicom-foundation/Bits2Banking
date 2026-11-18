<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/13-enums-and-state-transitions.md

PURPOSE:
Use Enum and Select Case to model job states

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Use Enum and Select Case to model job states

[Course contents](index.md)
An application job might be waiting, running, completed or cancelled. Representing those states with unrelated numbers makes code hard to review. An enumeration names a small set of integer values. It improves readability, but does not by itself enforce every valid transition: your code must still decide whether a requested change is allowed.


## Create a complete console exercise

Save the following as states.bas in your practice folder. The function does not start a thread, contact a provider or process money. It answers whether one state is allowed to follow another.

~~~basic
Enum JobState
    Waiting = 0
    Running = 1
    Completed = 2
    Cancelled = 3
End Enum

Function CanMove(ByVal current As JobState, ByVal requested As JobState) As Boolean
    Select Case current
    Case Waiting
        Return requested = Running OrElse requested = Cancelled
    Case Running
        Return requested = Completed OrElse requested = Cancelled
    Case Else
        Return False
    End Select
End Function

If Not CanMove(Waiting, Running) Then End 1
If CanMove(Completed, Running) Then End 2
If Not CanMove(Running, Cancelled) Then End 3
Print "Three transition checks passed"
End 0
~~~

~~~powershell
fbc -lang fb -w all -exx states.bas -x states.exe
if ($LASTEXITCODE -ne 0) { throw "Compilation failed" }
.\states.exe
$LASTEXITCODE
~~~

1. Read Enum JobState as a declaration of named values. End Enum closes that declaration; it does not end the program.
2. Trace CanMove(Waiting, Running). Select Case evaluates current, chooses Case Waiting and returns True.
3. Trace CanMove(Completed, Running). There is no explicit Completed branch, so Case Else refuses the change.
4. Run the program after a successful compilation. Expect the three-check message and exit status 0.
5. Add a check for Waiting to Completed. It should be refused because no work has run. Then add a check for Running to Running and explain whether your application wants an idempotent no-op or a refusal.

ByVal gives the function its own parameter values. As Boolean declares a truth result. OrElse short-circuits: if the first comparison is true, the second need not execute. Case Else handles all remaining values. A native C caller could still supply an integer outside the named enumeration, so validate that boundary instead of trusting a cast.


## Connect the idea to Umicom

Framework jobs already have owning services and lifecycle rules. A FreeBASIC frontend should translate the service's public state and status values into its display; it should not keep an independent job engine that contradicts the native owner. This exercise teaches how to make transitions explicit before writing an adapter. It is not a claim that the Framework exposes these particular names or numeric values.

For each state machine, draw arrows for permitted transitions, list who owns the state and define what happens after failure. A cancelled request may still own buffers until its worker has stopped. Do not equate the word Cancelled with permission to free every object immediately. The local exercise has been authored; running it requires your chosen FreeBASIC release.


## Read the new syntax

| Word | Meaning here |
| --- | --- |
| Enum / End Enum | Introduce and close named integer values |
| Select Case / Case / Case Else / End Select | Choose a branch from one expression |
| ByVal / As / Boolean | Declare copied parameters and a truth result |
| Return | Finish this function with a value |
| End | Terminate this small console program with an exit code |

## Continue practice

[Previous: Navigate FreeBASIC keywords, library functions and dialects](12-keyword-library-and-dialect-map.md) · [Next: Grow an array while preserving its contents](14-dynamic-arrays-and-preservation.md)
