<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/64-handle-comparison-exits-without-hiding-errors.md

PURPOSE:
Handle comparison exits without hiding errors

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Handle comparison exits without hiding errors

A read-only comparison has three useful outcomes: same, different, and unable to compare. Treating the last two as one state can hide malformed source behind an ordinary difference. This lesson follows the native command's explicit exit contract and the tests that protect it.

## Before you begin

Complete the operation-comparison lesson and keep left.uc and right.uc in a disposable exercise directory. Use the actual built command from your configured Umicom C preset. You should know how to inspect PowerShell's LASTEXITCODE immediately after a native command.

## Read the command-specific contract

Exit zero means both inputs compiled and their validated opcodes and operands matched. Exit one means both compiled but the operations differed. Exit two means usage, reading, compilation, validation or reporting failed. These meanings belong to compare-operations; existing run and check commands retain their own error behavior.

~~~powershell
.\build\windows-ucrt64-debug\bin\umicom-c.exe compare-operations .\left.uc .\right.uc
$comparisonExit = $LASTEXITCODE
switch ($comparisonExit) {
    0 { 'The validated operations match.' }
    1 { 'The validated operations differ.' }
    2 { 'Comparison failed; inspect the diagnostic.' }
    default { 'Unexpected process result; investigate before continuing.' }
}
~~~

This optional shell example interprets the native result. It does not implement comparison or authorize any follow-up build, copy or publication operation.

## Make a failure visible

1. Leave left.uc valid and remove the expression after return in right.uc.
2. Run the command and expect exit two.
3. Check that the diagnostic names right.uc with a line and byte-column location.
4. Confirm that no operations=same or operations=different report appeared.
5. Restore the right file, then repeat with malformed left source.

Missing paths and a source larger than the supported limit also fail with exit two. A path containing spaces is still one argument when quoted. An execution-budget option is invalid because this command does not execute programs.

## Inspect independent regression evidence

~~~powershell
ctest --test-dir build/windows-ucrt64-debug -R '^umicom[.]c[.]cli-operation-identity[.]' --output-on-failure --no-tests=error
~~~

Expected result: twelve groups pass. The test file supplies independent source pairs and expected process exits. It also hashes both existing input files before and after invocation and compares the directory inventory. These checks would catch an accidental rewrite or newly created output.

Each invocation has its own timeout. An exit caused by timeout is not the same as an expected semantic difference; the test compares the exact process result. Keeping separate CTest groups also identifies which input category failed instead of hiding all cases behind one aggregate result.

## Exercise and recovery

A workflow uses if comparisonExit is nonzero to rebuild, then discards every diagnostic. Explain how that can conceal a missing source file or compiler rejection. Change the workflow design so errors stop for investigation, while an ordinary difference is reported distinctly. Do not add automatic repository publication to the exercise.

If a test fails, retain stdout, stderr, the case name and the exact executable identity. Review the source pair and expected contract before changing assertions. A passed comparison remains evidence only about the two admitted operation sequences; it is not evidence that a program ran or that an older artifact can safely be reused.

[Course contents](index.md) · [Previous lesson](63-compare-operations-without-running-programs.md) · [Next lesson](65-test-buffered-report-failures.md)
