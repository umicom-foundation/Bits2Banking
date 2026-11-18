<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/15-parse-a-complete-bounded-number.md

PURPOSE:
Validate every input character before accepting a number

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Validate every input character before accepting a number

[Course contents](index.md)
A program often asks for a number: a lesson count, a queue size or a number of samples. The user types characters, however, not an already-validated integer. Converting a numeric prefix can hide a typo such as 12jobs. In this lesson you will write a small function that accepts only a complete documented spelling and publishes a result only after all checks succeed. The function is a teaching exercise; production applications should reuse the appropriate Framework conversion and validation service through a reviewed binding.


## 1. Define the accepted language before coding

Our input rule accepts one to seven ASCII decimal digits and a value from zero through one million, inclusive. Leading zeros are permitted within that seven-character limit. Spaces, signs, decimal points, exponent notation and trailing words are rejected. ASCII is the character encoding in which the digits 0 through 9 have consecutive numeric codes. This deliberately narrow grammar is easy to explain and test. It does not claim to recognize every way a person can write a number in every language.

A grammar is a rule for arranging symbols. A range is the set of values the application permits. They are separate: 1000001 uses only valid digits but is outside the range; 12jobs contains invalid symbols even though its beginning resembles a number. Do not automatically remove bad characters until an input passes. If your interface chooses to trim surrounding spaces, perform and document that as a separate step so the parser contract remains clear.


## 2. Prepare the example

1. Complete the compiler setup in lesson 1. Open a terminal, enter fbc -version, and confirm that FreeBASIC is discoverable. If it is not, fix the installation or terminal PATH before editing the example.
2. From the Bits2Banking repository, change into labs/languages/native-language-boundary. Open parse_count.bas in your editor. This is a separate BASIC exercise; it does not require boundary.o or a model.
3. Read the code below. The lines beginning with an apostrophe are comments for readers and are not executed. Save your learning edits in a separate copy.
4. Compile with the command below. Warnings are useful evidence; do not suppress them merely to get an executable. Run only after compilation succeeds.

~~~powershell
Set-Location labs/languages/native-language-boundary
fbc -version
fbc -lang fb -w all -exx parse_count.bas -x parse-count.exe
.\parse-count.exe
~~~

Expect Strict count checks passed and an exit status of zero. In PowerShell, $LASTEXITCODE reports the last native command’s exit status. A nonzero status means a check failed. On a supported Unix target, choose parse-count as the output filename and run ./parse-count. The C boundary test in this directory does not compile BASIC; record the actual FreeBASIC version and target used for this separate exercise.


## 3. Read the complete function

~~~basic
Function TryParseCount(ByRef text As Const String, ByRef output As ULong) As Boolean
    Const As ULong maximum = 1000000
    Dim As Integer length = Len(text)
    If length < 1 OrElse length > 7 Then Return False
    Dim As ULong candidate = 0
    For position As Integer = 1 To length
        Dim As Integer code = Asc(text, position)
        If code < Asc("0") OrElse code > Asc("9") Then Return False
        Dim As ULong digit = code - Asc("0")
        ' Check before multiplication, not after a value might have wrapped.
        If candidate > (maximum - digit) \ 10 Then Return False
        candidate = candidate * 10 + digit
    Next position
    ' Only a complete valid input changes the caller's output variable.
    output = candidate
    Return True
End Function

Sub CheckAccepted(ByVal text As String, ByVal expected As ULong)
    Dim As ULong value = 77
    If Not TryParseCount(text, value) OrElse value <> expected Then
        Print "Unexpected rejection: "; text
        End 1
    End If
End Sub
Sub CheckRejected(ByVal text As String)
    Dim As ULong value = 77
    If TryParseCount(text, value) OrElse value <> 77 Then
        Print "Unexpected acceptance or changed output: "; text
        End 1
    End If
End Sub

CheckAccepted("0", 0)
CheckAccepted("0000123", 123)
CheckAccepted("1000000", 1000000)
CheckRejected("")
CheckRejected("1000001")
CheckRejected("12jobs")
CheckRejected("-1")
CheckRejected("+1")
CheckRejected("1.5")
CheckRejected(" 12")
CheckRejected("12 ")
CheckRejected("00000000")
Print "Strict count checks passed"

~~~

Function begins a routine that returns a value; As Boolean means that its result is True or False. ByRef passes access to an existing variable. Const String prevents this routine from changing the input string through that parameter. The output is a ULong, an unsigned 32-bit integer in FreeBASIC. It is large enough for our chosen one-million limit. Const defines a named limit that the program does not change. Dim declares a variable. Len obtains the string length for this byte-oriented example.


## 4. Follow one character through the loop

For position As Integer = 1 To length visits each character position from one through the length. Asc(text, position) returns the character code at that position. The two comparisons reject anything below the code for 0 or above the code for 9. OrElse is short-circuit logical OR: when its left condition is already true, the right condition need not be evaluated. Subtracting Asc("0") turns the code for a digit into its numeric value from zero through nine.

candidate is a local temporary result. For the text 123, it starts at zero. After the first digit it becomes 1. After the second it becomes 12. After the third it becomes 123. Multiplication by ten shifts the existing decimal value one place, and adding digit supplies the new final place. Next position continues the loop. End Function closes the routine. This progression describes integer arithmetic; no floating-point rounding is needed.


## 5. Check the bound before multiplying

To keep the result at or below maximum, the next operation must satisfy candidate * 10 + digit <= maximum. Rearranging that condition gives candidate <= (maximum - digit) divided by 10. The backslash operator performs integer division. The program rejects a larger candidate before multiplication takes place. This pattern matters when a larger limit approaches the integer type’s maximum: checking only after arithmetic wraps can be too late.

Here maximum is at least every possible digit, so maximum - digit cannot underflow. If you generalize the function to accept a caller-supplied maximum smaller than nine, add an explicit digit > maximum check before that subtraction. Changing the contract requires reviewing the proof, not only replacing the constant. The seven-character length rule also bounds work, but it does not replace the value-range check.


## 6. Publish once and test both outcomes

Only output = candidate changes the caller’s result, and that line runs after every character is valid and the range checks pass. A failure returns False while leaving the old output unchanged. The two test procedures begin with the value 77 so that an accidental partial write is visible. They use explicit branches and End 1 rather than relying on an assertion that a compiler option might remove. A caller still must inspect the Boolean result; unchanged output is not a newly parsed value.

1. Trace 0000123 by hand. Explain why leading zeros are accepted and why the final value is 123.
2. Trace 1000001. Identify the final digit and the bound check that refuses it.
3. Trace 12jobs. The letters must cause rejection even though the earlier digits were valid. Verify that output remains 77.
4. Add rejection checks for a tab, a newline and 1e3. Explain why these belong to different grammars even if another conversion routine accepts them.
5. Change the maximum to 99 in a learning copy. Update accepted/rejected examples and explain which inputs now fail by range. Restore the original before comparing results with this lesson.


## 7. Connect the lesson to an Umicom application

A graphical form, a web endpoint and a command line can all supply text. Validate at the boundary where text becomes a count, then pass a typed value and an explicit success/error result into shared C services. Keep interface-specific error messages in the thin application layer. Never treat a parsed count as permission to allocate that many gigabytes or start that many jobs: resource limits and authorization are additional checks.

The portable lesson is that parsing, range checking, resource admission and action execution are distinct stages. A production binding must also agree on integer width, calling convention and output ownership. The FreeBASIC String descriptor cannot be passed as if it were a C char pointer. Reuse the earlier C-boundary lesson when connecting to Framework, and return a clear error instead of silently truncating input.


## Use a small acceptance table

| Input | Expected result | Reason |
| --- | --- | --- |
| 0 | Accept 0 | Smallest allowed value |
| 0000123 | Accept 123 | Seven digits with allowed leading zeros |
| 1000000 | Accept 1000000 | Largest allowed value |
| 1000001 | Reject; output unchanged | Outside application range |
| 12jobs | Reject; output unchanged | Trailing characters violate grammar |
| 00000000 | Reject; output unchanged | Eight characters exceed the input-length rule |

[Previous: Grow an array while preserving its contents](14-dynamic-arrays-and-preservation.md)

[Next: Pass a BASIC callback to C with an explicit lifetime](16-call-back-through-a-c-boundary.md)
