<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/39-separate-local-names-from-retained-storage.md

PURPOSE:
Separate local names from retained storage

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Separate local names from retained storage

[Course contents](index.md)

## A name can be local while its value survives

A function can hide a variable name from the rest of the program without discarding that variable after every call. This lesson separates visibility, lifetime and ownership. Visibility describes where you can write a name in source. Lifetime describes how long its stored value exists. Ownership describes which part of your application is responsible for that state. None of those words means that the value has been saved to disk.


## Read the three experiments


| Function | Where its counter comes from | Two calls produce |
| --- | --- | --- |
| NextAutomatic | Creates and resets a Counter on each call | 1, then 1 |
| NextHidden | Uses a Static Counter inside the function | 1, then 2 |
| NextOwned | Receives the caller's Counter through ByRef | Depends on which owner you pass |


## Begin with the ordinary local

~~~freebasic
Function NextAutomatic(ByRef outputValue As ULong) As Boolean
    Dim state As Counter
    state.value = 0
    Return NextOwned(state, outputValue)
End Function
~~~


## Follow the first call

1. Dim declares state inside this function. The name does not become a global name.
2. The explicit assignment sets this call's counter value to zero.
3. NextOwned admits the update and changes it to one. ByRef outputValue refers to the caller's output variable.
4. Return passes the Boolean success result back. The automatic state is no longer available after this call returns.
5. Call the function again. It creates a fresh state and sets that state to zero, so the next result is one again.


## Keep one local variable between calls

~~~freebasic
Function NextHidden(ByRef outputValue As ULong) As Boolean
    Static state As Counter
    Return NextOwned(state, outputValue)
End Function
~~~


## What Static changes

Static retains this variable between calls, although the name state is still local to the function. The numeric field starts at zero. The first call changes it to one; the second sees that retained value and changes it to two. This is one hidden state object for that function, not a new counter for every window, document or caller. Restarting the executable starts a new process; this example does not save the counter to a file. Static can also appear in other FreeBASIC contexts, including procedure and member declarations; this example uses the variable declaration form.


## Prefer an explicit owner when callers need independence

~~~freebasic
Type Counter
    value As ULong
End Type

Function NextOwned(ByRef state As Counter, ByRef outputValue As ULong) As Boolean
    If state.value >= 3 Then Return False
    Dim candidate As ULong = state.value + 1
    state.value = candidate
    outputValue = candidate
    Return True
End Function
~~~


## Read each part of the bounded update

Type names a record containing a value field. ULong is an unsigned 32-bit FreeBASIC integer. ByRef permits the function to refer to the caller's actual variable. Boolean communicates success separately from the numeric output. The cap of three is deliberately small so you can reach refusal quickly. The function checks the cap before adding. candidate names the admitted next value. If the cap is reached, neither assignment executes, so both state and the output remain unchanged. This is a teaching counter, not a bank transaction ID generator.


## Trace two independent owners


| Step | Owner passed | Left value | Right value | Returned output |
| --- | --- | --- | --- | --- |
| Start | None | 0 | 0 | Not yet used |
| 1 | Left | 1 | 0 | 1 |
| 2 | Right | 1 | 1 | 1 |
| 3 | Left | 2 | 1 | 2 |
| 4 | Left | 3 | 1 | 3 |
| 5 | Left at its cap | 3 | 1 | Unchanged sentinel 99; False result |


## Build the complete example

1. Open the repository's labs/languages/native-language-boundary directory. Use local_storage.bas as the complete program, not just a fragment from this page.
2. Check Get-Command fbc and fbc -version in PowerShell. If the compiler is absent, return to the setup lesson and choose the approved FreeBASIC toolchain.
3. Compile in the modern fb dialect with additional runtime checks. Run the resulting program only after compilation succeeds.
4. Compare the three printed lines with the expectations below.
5. Run the executable again. The new process should repeat the same output; the Static value was retained between calls, not across process restarts.


## Commands and expected output

~~~powershell
fbc -lang fb -exx local_storage.bas -o local_storage.exe
.\local_storage.exe
~~~

~~~text
Automatic calls: 1, 1
Static calls: 1, 2
Owned counters: left 3, right 1; refusal preserved 99
~~~


## Inspect the failure case

The complete program sets the output to 99 before asking a capped owner for another value. A sentinel is a recognizable value chosen to reveal an unwanted write. False plus an unchanged 99 proves the intended refusal path for this fixture. It does not prove every possible application state or concurrent call is safe. The source also checks that the other owner's value remains one.


## Compare with C and D carefully

The adjacent local_storage.c program is a host C23 comparison. Its static local is shared storage; the example is single-threaded and supplies no locking. FreeBASIC's retained local also needs a synchronization design if multiple threads mutate it. D's ordinary mutable static local is thread-local by default. The same word therefore does not imply the same cross-thread ownership in all languages. These examples do not start threads or measure concurrency.


## Using this idea in Umicom projects

A Studio document, a Media job and a Trader data view can each need their own progress state. An explicit owner object makes that relationship visible, permits independent tests and gives cleanup a clear home. A hidden static counter can accidentally couple two callers. Reusable production services still belong in native Framework with their existing ownership and synchronization rules. This FreeBASIC program teaches the distinction; it is not a replacement product service or a supported compiler extension in Umicom C.


## Exercises

1. Predict three calls to NextAutomatic, then add the third call: expect 1, 1, 1.
2. Predict three calls to NextHidden within one execution: expect 1, 2, 3. A fourth call must return False without overwriting the caller's output.
3. Create a third explicit Counter owner and interleave updates. Write down its state before running the example.
4. Explain why declaring a Static variable inside a function does not create a separate value for every caller.
5. Explain why a local variable that contains a pointer needs a separate pointed-to-object lifetime analysis. A pointer's visibility alone does not establish ownership.


## Qualification and troubleshooting

The C comparison has its own CMake/CTest path in the laboratory README. A passing C check does not compile or validate FreeBASIC. Treat this BASIC source as an authored example until you run it with the selected FreeBASIC compiler. If output differs, check the file, selected dialect, compiler version and whether you are repeatedly calling a function in one process or restarting the program. Do not repair a failed test by changing the expected values without understanding the storage lifetime.


## Further reading


- [FreeBASIC STATIC variable declarations](https://www.freebasic.net/wiki/KeyPgStatic)
- [FreeBASIC introduction to scope](https://www.freebasic.net/wiki/TutIntroScope)
- [FreeBASIC storage classes](https://www.freebasic.net/wiki/ProPgStorageClasses)


[Previous: Observe which conditional expression runs](38-observe-which-conditional-expression-runs.md)

[Next: Read nested comments and logical lines](40-read-nested-comments-and-logical-lines.md)
