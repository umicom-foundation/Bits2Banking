<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/38-observe-which-conditional-expression-runs.md

PURPOSE:
Observe which conditional expression runs

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Observe which conditional expression runs

[Course contents](index.md)

## The question behind a short expression

An expression computes a value. A function call can compute a value and also change state, such as increasing a counter or reading a file. If you choose between two expressions, does the program compute both values first, or only the value it needs? That difference affects work, ownership and error handling. This lesson makes evaluation visible with small counters. It uses no invalid memory accesses, no intentional crashes and no network requests.


## Read the syntax in three parts

The current FreeBASIC keyword reference describes IIf as evaluating the selected expression only. The condition is tested first; nonzero selects the true expression and zero selects the false expression. IIf is compiler-supported syntax even though its parentheses resemble an ordinary function call. Do not transfer behavior from another BASIC dialect based only on the name. The complete example will test both choices on your selected FreeBASIC compiler.

~~~basic
result = IIf(condition, valueWhenTrue, valueWhenFalse)
~~~


## Separate statements from expressions


| Form | Purpose |
| --- | --- |
| If ... Then ... Else ... End If | Choose a block of statements. Useful when a branch has several actions. |
| IIf(test, a, b) | Choose a value inside an expression. Keep alternatives short and compatible. |
| ChooseValues(test, a, b) | An ordinary function declared in this exercise. Its ByVal parameters receive computed values. |
| AndAlso / OrElse | Short-circuit Boolean combinations introduced earlier; they do not replace all conditional expressions. |


## Understand an observable probe

Probe is an ordinary function. value is passed ByVal, so the function receives a copy. calls is passed ByRef, so incrementing it changes the caller’s counter. The return value and the counter change are different effects. Each counter starts at zero and is incremented at most once in one phase. This makes the observed number easy to predict and avoids using timing as a proxy for whether code ran.

~~~basic
Function Probe(ByVal value As Integer, ByRef calls As Integer) As Integer
    calls += 1
    Return value
End Function
~~~


## Use independent counters

The program keeps leftCalls, rightCalls and conditionCalls separately. A left probe changes only leftCalls and a right probe changes only rightCalls. We want to observe which expressions ran, not depend on an assumed order between ordinary function arguments. Separate counters also make a failure easier to interpret. A single counter used for several purposes could hide which branch was responsible.


## Predict the selected expression

ProbeCondition records one condition evaluation and returns the requested Boolean choice. For True, expect result eleven, leftCalls one, rightCalls zero and conditionCalls one. For False, expect result twenty-two, leftCalls zero, rightCalls one and conditionCalls one. The full example uses an ordinary If statement to calculate its expected result, keeping that check separate from the IIf being tested.

~~~basic
Dim As Integer selected = IIf(ProbeCondition(choice, conditionCalls), _
    Probe(11, leftCalls), Probe(22, rightCalls))
~~~


## Now pass already-computed values

ChooseValues has three ordinary ByVal parameters. Before its body can choose between the integer values, the caller evaluates the arguments. Both value probes therefore increment their respective counters. The function can choose a returned value, but it cannot undo work already done by its caller. This is why replacing a selective expression with a helper function may change behavior even when the final numeric result remains the same.

~~~basic
selected = ChooseValues(ProbeCondition(choice, conditionCalls), _
    Probe(11, leftCalls), Probe(22, rightCalls))
~~~


## Compare the expected observations


| Operation | Choice | Result | Left calls | Right calls | Condition calls |
| --- | --- | --- | --- | --- | --- |
| IIf | True | 11 | 1 | 0 | 1 |
| IIf | False | 22 | 0 | 1 | 1 |
| ChooseValues | True | 11 | 1 | 1 | 1 |
| ChooseValues | False | 22 | 1 | 1 | 1 |


## Build the complete example

1. Open the native-language-boundary laboratory directory in PowerShell.
2. Read conditional_selection.bas from top to bottom. Locate the two phases and the counter reset between them.
3. Confirm that your FreeBASIC compiler is available with fbc -version. Record its version for your own test results.
4. Compile in the fb dialect with runtime checking, using the commands below.
5. Run the generated program only after compilation succeeds. A nonzero exit means one of the expected observations was not met.

~~~powershell
fbc -version
fbc -lang fb -exx conditional_selection.bas -o conditional_selection.exe
.\conditional_selection.exe
$LASTEXITCODE
~~~


## Expected output and validation limits

A successful execution prints “Umicom FreeBASIC selective expression and eager argument checks passed.” and exits with zero. The source is provided as a complete example, but FreeBASIC compilation and execution have not been verified in the current authoring environment. A passing C comparison does not validate this BASIC program. If your compiler behaves differently, preserve its version, command, output and source before changing the lesson assumptions.


## Selection does not hide invalid declarations

An unselected runtime branch is not a general place to put code that the compiler cannot understand. The compiler still needs to parse and type-check the expression. Keep this exercise’s alternatives as Integer values. Mixed numeric types introduce conversion rules, and object alternatives introduce lifetime questions; study those separately instead of inferring them from two small integers. A runtime condition is also different from a preprocessor directive that includes or excludes source.


## Use this knowledge at an Umicom boundary

A thin BASIC client may select a label, a default scalar or a reviewed option before calling a C API. Keep operations that allocate, mutate state, open files or start jobs in clear statement blocks. Do not assume that a function named Choose, Select or GetOrElse is lazy. Inspect its parameter contract. Reusable resource ownership and validation still belong to the native Framework service rather than being duplicated in the client language.


## Investigate without a crash

1. Change the two returned values while preserving independent counters. Predict every row of the observation table again.
2. Temporarily print the counters after each phase. Confirm that resetting them matters.
3. Write the same selected-value operation using If ... Then ... Else and compare its effects.
4. Do not replace the probes with division by zero or an invalid pointer. A counter proves evaluation without introducing undefined or dangerous behavior.
5. Explain why measuring elapsed time is less reliable than these direct observations for such a small program.


## Further reading


- [FreeBASIC IIf keyword reference](https://www.freebasic.net/wiki/KeyPgIif)
- [FreeBASIC short-circuit AndAlso](https://www.freebasic.net/wiki/KeyPgOpAndalso)


[Previous: Select a union value with an explicit tag](37-select-a-union-value-with-an-explicit-tag.md)

[Next: Separate local names from retained storage](39-separate-local-names-from-retained-storage.md)
