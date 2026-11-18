<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/11-tests-errors-and-record-contracts.md

PURPOSE:
Test errors and define record contracts

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Test errors and define record contracts

[Course contents](index.md)
A test states an expected behavior and fails when it is not observed. Include ordinary values, boundary values and invalid values. A warning is a compiler observation that may indicate a defect even if an executable is produced. Do not hide warnings merely to make the terminal quieter.

~~~basic
Function ValidProgress(ByVal done As Long, ByVal total As Long) As Long
    If total <= 0 OrElse done < 0 OrElse done > total Then Return 0
    Return 1
End Function
If ValidProgress(2, 8) <> 1 Then End 1
If ValidProgress(0, 8) <> 1 Then End 2
If ValidProgress(8, 8) <> 1 Then End 3
If ValidProgress(9, 8) <> 0 Then End 4
If ValidProgress(1, 0) <> 0 Then End 5
Print "Progress checks passed"
End 0
~~~

1. Save as progress_tests.bas. Compile with fbc -lang fb -w all -exx progress_tests.bas -x progress_tests.exe.
2. Run it and inspect $LASTEXITCODE. Expect the checks message and zero.
3. Change the invalid total test’s expectation deliberately. Confirm a nonzero result, then restore it.
4. Write a short result record containing compiler version, command, source identity and actual exit status. An expected result written in a lesson is not executed evidence.

OrElse short-circuits a logical alternative. Return exits a function with a result. The explicit End codes in this small test identify which assertion failed. Production errors need useful messages and structured status, not unexplained termination in a reusable service.

Enum names a group of constants. Type groups fields and may define methods. Constructor and Destructor support initialization and cleanup for user-defined types. Operator overloads define operations for those types. Property presents controlled access syntax. These features can improve a local model, but a binary C interface should expose explicit reviewed layouts or opaque handles rather than assuming every language understands those constructs.


## Recovery

When a test fails, first distinguish compiler failure, linker failure, startup failure and assertion failure. Capture the earliest meaningful diagnostic and the source used. Re-running an old executable after a failed compilation can create a false pass. Do not mark a product fixed until the relevant source and regression have been executed together.


## Continue learning

[Previous: Separate declarations, implementations and namespaces](10-declarations-includes-and-namespaces.md) · [Course contents](index.md) · [Next: Navigate FreeBASIC keywords, library functions and dialects](12-keyword-library-and-dialect-map.md)
