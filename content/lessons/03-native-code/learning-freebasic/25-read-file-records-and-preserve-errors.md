<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/25-read-file-records-and-preserve-errors.md

PURPOSE:
Read file records and preserve errors

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Read file records and preserve errors

[Course contents](index.md)

## What this program will do

A text file stores bytes on disk. A program opens it, reads information through a file number, then closes it. In this lesson you will count lines in a small supplied ASCII file, distinguish an empty line from the end of a file, and keep the first nonempty line. You will also check each input operation and preserve an error before another operation can replace it. The program reads only the path you supply; it does not rewrite or delete that file.

This is a FreeBASIC language exercise using the fb dialect. It is not the production Umicom dataset importer. The source is supplied for you to compile with the real FreeBASIC compiler. If you have not installed and verified that compiler, return to the course setup lesson first. A successful C build elsewhere does not establish that this BASIC source compiled.


## Inspect the fixture before writing code

Open labs/languages/native-language-boundary/line-fixture.txt in a text editor. It contains apple, an empty line, pear and plum, in that order. There is a line ending after plum. Count four records, three nonempty records and thirteen text bytes excluding line separators. All letters are ASCII, so each letter uses one byte in this fixture. That equality is not a rule for arbitrary Unicode text.

~~~text
apple

pear
plum

~~~

A line separator marks the boundary between records. Windows text files commonly use a carriage return followed by a line feed; other files commonly use a line feed alone. File Line Input reads a record without including those delimiters in the returned string. A zero-length string can therefore be a valid empty record. It does not mean that no record was read.


## Give the program a filename

~~~basic
Dim filename As String = Command(1)
If filename = "" OrElse Command(2) <> "" Then
    Print "Usage: line_records path-to-small-ascii-file"
    End 2
End If
~~~

Command(1) is the first argument after the executable name. An argument is a value supplied when starting a program. Quotes around a path with spaces keep that path together as one argument. OrElse short-circuits: the second condition is evaluated only when needed. End 2 stops with process status two, which this example uses for incorrect usage. This status is a convention chosen by the program, not a FreeBASIC keyword meaning.


## Open for input and check the returned status

~~~basic
Dim fileNumber As Integer = FreeFile
Dim openStatus As Long = Open(filename For Input As #fileNumber)
If openStatus <> 0 Then
    Print "Open failed with runtime code "; openStatus
    End 1
End If
~~~

FreeFile supplies an available runtime file number. It does not open a file. Open associates that number with the supplied filename; For Input requests sequential text reading. The function form returns zero for success and a nonzero runtime error code for failure. The # marks a file-number operand in this syntax. Long stores the returned error code. After a successful open, this program owns the responsibility to close that file number.

A relative filename is resolved from the process working directory. It is not automatically relative to the source file or executable. The commands below deliberately start in the lab directory so that line-fixture.txt refers to the supplied file. In a desktop application, prefer an explicitly selected absolute path and a Framework-owned file service.


## Check end of file before reading a record

~~~basic
Err = 0
Dim atEnd As Integer = Eof(fileNumber)
Dim readStatus As Long = Err()
If readStatus <> 0 Then
    failure = readStatus
    Exit Do
End If
If atEnd Then Exit Do
~~~

Eof asks whether the current file position is at the end. The program clears the runtime error number immediately before the operation and copies it immediately afterwards. An error and end-of-file are separate outcomes. Exit Do leaves the current Do loop. It does not stop the whole program, so execution can still reach the close operation after the loop.


## Read one line and preserve its error

~~~basic
Dim row As String
Err = 0
Line Input #fileNumber, row
readStatus = Err()
If readStatus <> 0 Then
    failure = readStatus
    Exit Do
End If
~~~

The file form includes #fileNumber. The keyboard form does not read this file. String is a managed, variable-length value here. The runtime can allocate space for the line. Err() returns the current runtime error number; subsequent runtime operations, including printing, can replace it. Copying it into readStatus and then failure makes the original outcome available to the later cleanup and reporting code.

This exercise uses inline error checks. Compile it without -e, -ex or -exx, which enable QB-style runtime error handling behavior that can change how an error reaches this code. The -g option supplies debug information; it is not a substitute for input validation. Other lessons may intentionally use different flags. Match the error model to the example instead of treating one set of flags as universal.


## Apply a small acceptance policy

MaxLines is sixteen and MaxLineBytes is 128. Const gives those rules names. The loop refuses a seventeenth record or a returned line longer than 128 bytes. It increments lineCount for every accepted record, including empty records. It increments nonemptyCount only when Len(row) is not zero. The first nonempty string is assigned to firstNonempty for use after the loop.

~~~basic
If lineCount = MaxLines OrElse Len(row) > MaxLineBytes Then
    failure = 1001
    Exit Do
End If
lineCount += 1
textBytes += Len(row)
~~~

The custom failure value 1001 means a teaching limit was exceeded. It is not presented as an official FreeBASIC runtime error code. With at most sixteen accepted records of at most 128 bytes, the accepted text-byte total cannot exceed 2048. This arithmetic gives the counter a simple bound. It says nothing about allocations made before a line is rejected.


## Do not confuse rejection with a memory ceiling

The dynamic string has already received the line before Len(row) is checked. A very large line can therefore cause a large allocation before this program refuses it. The line limit is a rule for accepted records, not a strict process-memory limit. Use only the small supplied fixture for this exercise. A production importer needs bounded reads and a complete policy for oversized records, interrupted input and total storage; use the shared native Framework import services for that work.


## Close once, after the loop

~~~basic
Dim closeStatus As Long = Close(fileNumber)
If failure = 0 AndAlso closeStatus <> 0 Then failure = closeStatus
~~~

Close releases the open file resource. AndAlso short-circuits just as OrElse does for its corresponding logical operation. The code records a close error only if no earlier failure has already been saved. It then prints either the saved failure or the successful counters. The first failure remains the explanation for a refused read; cleanup must not silently replace it with a success.


## Compile and run step by step

1. Open PowerShell and move to the native-language-boundary lab folder shown below.
2. Compile line_records.bas with the fb dialect and debug information. If fbc is not found, resolve the compiler setup; do not run a stale executable from another folder.
3. Run the executable with line-fixture.txt as its single argument. Read the process status immediately afterwards.
4. Repeat with a filename that does not exist. The program should report an open failure and return a nonzero status.
5. Do not point the exercise at private documents or a growing application log. Keep experiments in a separate copy of the tiny fixture.

~~~powershell
Set-Location C:\umicom\Umicom-Bits2Banking\labs\languages\native-language-boundary
fbc -lang fb -g line_records.bas -x line-records-basic.exe
& ".\line-records-basic.exe" ".\line-fixture.txt"
$LASTEXITCODE
& ".\line-records-basic.exe" ".\missing-fixture.txt"
$LASTEXITCODE
~~~

For the supplied fixture, expect values of four lines, three nonempty lines and thirteen text bytes, followed by First nonempty=apple. BASIC Print may add spaces around numeric values. The successful process status is zero. No exact platform-specific runtime error number is promised for the missing file.


## Practice and connect the result to Umicom

1. Make a copy with only an empty file. Predict zero records and no first nonempty value.
2. Make a copy with one blank line. Predict one record and zero nonempty records.
3. Create a seventeen-line copy. Explain why sixteen records may have been accepted before the custom limit failure, and why no successful total is published.
4. Create a small 129-letter line. Explain why refusal happens after reading and cannot be called an allocation bound.
5. Explain why counting lines does not validate JSON syntax, tokenize text, split training data or train a model.

The useful design idea is explicit ownership and error preservation. A BASIC teaching client can call a verified C interface when it needs reusable Framework behavior. Keep byte-level import limits, dataset validation and training logic in Framework rather than duplicating this small reader inside each application. The example is intentionally narrow and its compiler/runtime results remain to be established on the learner system.


## Further reading

- [Original BASIC reader](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/languages/native-language-boundary/line_records.bas)
- [FreeBASIC OPEN](https://www.freebasic.net/wiki/KeyPgOpen)
- [FreeBASIC file LINE INPUT](https://www.freebasic.net/wiki/KeyPgLineinputPp)
- [FreeBASIC ERR](https://www.freebasic.net/wiki/KeyPgErr)

[Previous: Inspect a bounded binary header](24-inspect-a-bounded-binary-header.md)
<!-- The initial exercise commands shared line_records.exe across two languages. Distinct output names below prevent accidental cross-language executable reuse. Earlier output name: line_records.exe. -->

[Next: Follow construction and destruction through a scope](26-follow-construction-and-destruction.md)
