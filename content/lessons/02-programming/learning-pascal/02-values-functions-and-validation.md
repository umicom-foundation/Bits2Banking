<!--
Umicom Bits2Banking
File: content/lessons/02-programming/learning-pascal/02-values-functions-and-validation.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Values, functions and input validation

[Course contents](index.md) · [Previous: Write and run a Pascal program](01-write-and-run-a-program.md) · [Next: Loops and checkable results](03-loops-and-checkable-results.md)

## The problem
A course has five practice items. A learner enters how many are complete. We want to display the remaining count while rejecting impossible values. This introduces a variable, a function, a condition and validation.

A variable is named storage for a value. A type states what kind of value it can hold. Integer holds whole numbers within the implementation's supported range. A function performs an operation and returns a value.

## Setup recap
Install Free Pascal and build the progress lab using [the course setup](index.md). Open labs/languages/pascal-progress/progress.pas. Run the built progress executable with argument 2. An argument is text supplied after a program's name in the terminal.

## Read the function
~~~pascal
function RemainingLessons(Total, Done: Integer): Integer;
begin
  if (Total < 0) or (Done < 0) or (Done > Total) then
    RemainingLessons := -1
  else
    RemainingLessons := Total - Done;
end;
~~~
Total and Done are parameters: named inputs supplied by a caller. The result type follows the closing parenthesis. In this example, assigning to the function's name supplies its result. The assignment symbol := stores a value; the comparison symbols ask a question.

For Total = 5 and Done = 2, all three invalid conditions are false, so the result is 3. Done = 7 makes Done > Total true, producing -1. That negative value is this function's chosen error signal, not a valid remaining count.

## Convert text before using a number
The terminal supplies text. Val attempts to convert it:
~~~pascal
Val(ParamStr(1), Completed, Code);
if Code <> 0 then
begin
  WriteLn('Enter a whole number.');
  Halt(1);
end;
~~~
Code is zero on success. On failure Completed is not a usable result. The program must check Code before passing Completed to RemainingLessons. This separates text conversion from checking the allowed range.

Free Pascal's Val accepts more numeric forms than these decimal exercises use. A real input format may need stricter rules. Do not describe this example as a universal decimal parser.

## Try the boundaries
1. Run progress with 0: expect five remaining items.
2. Run it with 5: expect zero remaining items.
3. Try -1 and 6: expect a range error and an unsuccessful exit.
4. Try abc: expect a conversion error.
5. Omit the argument: expect the usage message.

In PowerShell, inspect $LASTEXITCODE immediately after a run. In Bash, use echo $? immediately afterwards. Zero means the program reports success; this example uses one for rejected input.

## Exercise and explanation
Would checking only Done > Total be enough? No. A negative Done also represents an invalid completed count. The function checks both lower and upper bounds before subtraction.

## Connect to Umicom
Validation is useful in every application: learning progress, media clip lengths and account quantities all have rules. Read the C counts.c lab alongside this function and identify the same input checks without assuming the language syntax is identical.

## Source map
Read `labs/languages/pascal-progress/progress.pas` in the Bits2Banking checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Previous: Write and run a Pascal program](01-write-and-run-a-program.md) · [Next: Loops and checkable results](03-loops-and-checkable-results.md)
