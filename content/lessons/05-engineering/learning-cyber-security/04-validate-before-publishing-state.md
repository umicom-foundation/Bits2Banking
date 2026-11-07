<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/04-validate-before-publishing-state.md

PURPOSE:
Keep failed input from changing valid state

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Keep failed input from changing valid state

Learn how application inputs, memory ownership and identity checks fit together. The examples use Umicom Framework and a small Bits2Banking consumer. Every chapter explains its vocabulary before the exercise.

## Start here

A source file is readable program text. A compiler turns that text into machine instructions. A library supplies reusable functions; this course calls the security library in Umicom Framework. A terminal accepts commands. You can read and trace every example without installing anything.

For the practical lab, install Git, a C23 compiler, CMake 3.26 or newer, Ninja, and a matching Framework SDK containing UmiLocalProfileNameBytes. In Windows PowerShell, open the repository with Set-Location and make the UCRT64 tools visible:

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/framework/profile-name-boundary -B build/profile-name -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework" -DBUILD_TESTING=ON
cmake --build build/profile-name
ctest --test-dir build/profile-name --output-on-failure --no-tests=error
& ".\build\profile-name\btb-profile-name.exe"
~~~

Run one command at a time and stop on an error. Change the SDK path to your installation. In bash, use cd to enter your checkout, the same three CMake/CTest commands, and ./build/profile-name/btb-profile-name to launch. The expected line is Canonical name: alice_7. A missing package means the SDK path is wrong or incomplete; a missing symbol means its header and library must be updated together. This lab does not collect credentials or write a password store. The [Learning C course](../../../courses/learning-c/index.html) explains basic syntax in more depth.


## A transaction in a small function

A transaction is a group of operations whose changes become visible together. The profile-name validator uses this idea without a database. It builds a candidate result in local storage, validates every character, then copies the complete result to the caller.

Suppose a destination initially contains the last valid name. If a function writes the first two accepted letters and then rejects a slash, the caller receives an error and a partially changed destination. That makes recovery harder and may accidentally alter which record another operation uses.

## Read the sequence

~~~text
check pointers and length
validate each byte into a temporary array
if any byte is invalid: return an error
copy the complete candidate to the output
return success
~~~

1. Find the first return in UmiLocalProfileNameBytes. It rejects impossible sizes before reading bytes.
2. Find the return inside the loop. No destination write precedes it.
3. Find memcpy after the loop. It is the publication point.
4. Explain why input and output may overlap: all input reads finish before that copy.

The temporary array is a small fixed allocation on the current call's stack. This approach is appropriate for a 49-byte result. Large media projects require a different storage plan; copying an entire video into a stack array would be inappropriate.

## Regression exercise

The test fills result with Q, copies all of it to saved, then submits invalid input. memcmp compares every destination byte with the snapshot. Checking only result[0] would miss a write farther into the array.

Add a rejected space at the final position in a test input. Keep the whole-output comparison. Then add a valid name with both '-' and '_'. The two cases distinguish rejection from an overly strict implementation that rejects every name.

## Review question

Should a failed registration erase a previously valid account record? No. The same principle applies at the backend boundary: create-if-absent must not overwrite an existing verifier. Its implementation must enforce that rule even when two requests race.

## Summary

Name the point where state changes. Before that point, prepare and validate. On failure, preserve the documented state. Tests should compare the full affected state rather than infer correctness from an error code alone.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/security/local_profile.c).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Recognise dangling pointers and define ownership](03-dangling-pointers-and-ownership.md) · [Next: Understand local password verification](05-passwords-and-local-profiles.md)
