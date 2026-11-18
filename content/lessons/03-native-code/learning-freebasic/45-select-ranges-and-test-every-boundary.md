<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/45-select-ranges-and-test-every-boundary.md

PURPOSE:
Select ranges and test every boundary

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Select ranges and test every boundary

[Course contents](index.md)

## Start with one small decision

A display needs to turn an invented score from 0 through 100 into one of three bands. A band is simply a named group of values. This example uses low, middle and high; it is not a trading rule or a medical assessment. Before writing code, decide what each boundary means. A program cannot choose a useful rule for you merely because it compiles.

1. Review the earlier lessons on Integer, Boolean, functions, ByVal and ByRef. You will use those same ideas here.
2. Open labs/languages/native-language-boundary/select_ranges.bas in your editor. Keep the complete file available while reading.
3. Write down the expected answer for 24, 25, 74 and 75 before looking at the program. These adjacent values reveal gaps and overlaps.


## Define the accepted domain on paper

The domain is the set of inputs the function promises to handle. Each interval below includes both endpoints. The output is a small identifier, not the score itself. A separate function converts that identifier to display text.


| Input score | Accepted? | Output band |
| --- | --- | --- |
| Less than 0 | No | Previous output retained |
| 0 through 24 | Yes | 0: low |
| 25 through 74 | Yes | 1: middle |
| 75 through 100 | Yes | 2: high |
| Greater than 100 | No | Previous output retained |


## Read the selection syntax

Select Case computes its selector once. It tries Case alternatives in order, runs the first match, and then continues after End Select. To includes a range; Is introduces a comparison; a comma provides another alternative. Case Else catches an unmatched value. BASIC does not continue into the next matching case as C can without break.

~~~basic
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

~~~


## Trace an accepted boundary

1. The caller gives TryBand the score 25 and a reference to its output variable. ByVal makes score a local value; ByRef makes band refer to the caller’s storage.
2. The first case rejects scores outside 0 through 100. Neither comparison matches 25.
3. The next interval ends at 24, so it cannot match 25.
4. The interval 25 through 74 matches. The assignment writes 1 into the caller’s band variable.
5. Execution leaves the selection and reaches Return True. The caller now has both a success result and a meaningful output.


## Trace a refusal without damaging old data

Suppose a screen already shows an accepted band, and a new score of 101 arrives. The function returns False before any band assignment. The screen can report the invalid input while retaining the old value. This is a useful publication rule: decide whether a result is valid before changing caller-owned state. It does not make the old value current; a real screen should also show that the new request failed.

~~~basic
Dim kept As Integer = 77
Require(Not TryBand(101, kept), "above upper boundary")
Require(kept = 77, "refusal keeps prior output")
~~~


## Use constant dispatch for a small identifier

BandName translates identifiers 0, 1 and 2 into words. Select Case As Const accepts integer constants and enumerators, including constant To ranges, but not Is comparisons. The compiler can use a jump table. Keep this form for a suitable compact set of values; it is not a promise that any larger program becomes faster.

~~~basic
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

~~~


## Observe the selector exactly once

ReadSample increments a counter and returns 25. The counter makes evaluation visible without accessing a file, sensor or network. The first interval deliberately overlaps the later Case 25. This is an experiment about ordering, not a recommended way to define the three production bands.

~~~basic
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
~~~


## Distinguish leaving a selection from returning a value

Exit Select leaves only the enclosing selection. Return leaves the function and supplies its result. In the final experiment, afterSelect becomes 4 and Exit Select bypasses the later assignment to 99. The assertion after End Select still runs. An editor may warn that the skipped line is unreachable; it is included deliberately to make the exercise visible.


## Build and run the complete experiment

These commands use an installed FreeBASIC compiler in its fb dialect. The source is authored but has not been compiled in the current mirror environment. Stop after a compiler error; otherwise an older executable might run and mislead you. The -exx option requests additional runtime checks, and -w all enables warnings.

~~~powershell
Set-Location C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary
fbc -lang fb -exx -w all select_ranges.bas -x select_ranges.exe
.\select_ranges.exe
~~~


## Read the expected outcome

Require is the test helper: a false condition prints FAILED and exits with code 1. The complete example checks six accepted endpoints, two rejected inputs, unchanged output on refusal, four labels, one evaluation, first-match ordering and Exit Select. The text below is expected output, not a claim of an executed compiler check.

~~~text
Umicom BASIC selection: six endpoints and two refusals checked.
One sample, one matching branch, prior output preserved on refusal.
~~~


## Use the idea around an Umicom C service

A BASIC client can classify local display data before calling a native Framework API. Keep the shared service authoritative: it must validate its own input and report its own status. Do not copy this score policy into several applications or assume BASIC Integer is the correct C ABI width. For a boundary between languages, use the explicit types and reviewed declarations from the earlier interoperability lessons. This laboratory does not call Framework or launch an application.


## Practice, diagnose and extend

1. Change the middle interval to start at 26. The test for 25 should fail because no interval admits it. Restore 25 afterward.
2. Change the first interval to end at 25. The test for 25 should fail because the earlier case now assigns band 0. Restore 24.
3. Swap the overlapping experiment’s two branches and predict the new chosen value. Update only that experiment’s expected result after explaining the change.
4. Add score 50 to the accepted table. It should be middle, but an interior example is not a substitute for testing the endpoints.
5. If fbc is not found, return to the setup lesson and check the compiler path. If As Const rejects an Is expression, keep the general selection for comparisons and the constant form for the label lookup.


## Language reference


- [FreeBASIC manual: SELECT CASE](https://www.freebasic.net/wiki/KeyPgSelectcase)


[Previous: Give operators a clear domain meaning](44-give-operators-a-clear-domain-meaning.md)
