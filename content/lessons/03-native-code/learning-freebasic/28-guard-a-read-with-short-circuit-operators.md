<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-freebasic/28-guard-a-read-with-short-circuit-operators.md

PURPOSE:
Guard a read with short-circuit operators

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Guard a read with short-circuit operators

[Course contents](index.md)

## Ask whether the next operation is allowed

An expression is code that produces a value. Evaluating an expression means doing the work needed to obtain that value. Sometimes evaluation also changes something: a function might increment a counter, read a file or perform a network request. That additional change is a side effect. When you combine conditions, you need to know whether every condition runs. This matters for correctness as well as speed. Reading values(index) is only valid when index belongs to the array. A condition that says the index is invalid must be evaluated before any dependent read occurs.



## Learn AndAlso and OrElse

AndAlso is short-circuit conjunction. Conjunction means both conditions must be true. It evaluates the left operand first. If that result is false, the overall condition is already false and the right operand is skipped. OrElse is short-circuit inclusive disjunction: at least one condition must be true. If its left operand is true, the result is already true and the right operand is skipped. An operand is a value or expression used by an operator. These rules describe runtime behavior, not merely a mathematical truth table.

| Operator | Left result | Right expression |
| --- | --- | --- |
| AndAlso | False | Skipped |
| AndAlso | True | Evaluated |
| OrElse | True | Skipped |
| OrElse | False | Evaluated |

## Compare ordinary And and Or carefully

FreeBASIC also has And and Or. They support logical or bitwise work according to their operands, but they do not provide these short-circuit evaluation rules. A bitwise operator combines individual binary positions; that is useful for option flags. It is a different purpose from protecting a dependent array read. Do not replace AndAlso with And just because a few values produce the same final true or false result. The expressions evaluated along the way can differ. Parentheses make grouping visible; parentheses alone do not turn an eager operator into a short-circuit operator.


## Observe a call instead of guessing

The example function Probe accepts an answer and a counter. ByVal gives it a value copy of answer. ByRef makes calls refer to the caller’s counter, so the increment is observable after the function returns. Probe then returns the requested answer. In the demonstration 0 is false and -1 is used as a true integer value. The lesson checks truth by comparing with zero rather than assuming every language represents Boolean true identically. With a false left operand, AndAlso leaves the counter at zero. Replacing it with And for the safe Probe experiment increments the counter once.

~~~basic
Function Probe(ByVal answer As Integer, ByRef calls As Integer) As Integer
    calls += 1
    Return answer
End Function

Dim calls As Integer = 0
Dim leftFalse As Integer = 0
Dim accepted As Integer
accepted = leftFalse AndAlso Probe(-1, calls)
If accepted <> 0 OrElse calls <> 0 Then End 1
~~~


## Read the array bounds before the element

Our array is declared with lower bound 2 and upper bound 4. Its legal indices are 2, 3 and 4; neither zero nor five is valid. LBound and UBound are library operations that inspect those bounds. The loop intentionally tries indices 0 through 6. Its first condition rejects values below the lower bound. Its second condition rejects values above the upper bound. Only after both conditions succeed does the final expression read values(index). The element equal to 20 is at index 3, so exactly one match should be counted. Keep the checks and read in this order.

~~~basic
Dim values(2 To 4) As Integer = {10, 20, 30}
For index As Integer = 0 To 6
    If (index >= LBound(values)) AndAlso (index <= UBound(values)) AndAlso (values(index) = 20) Then
        Print "Matching index:"; index
    End If
Next
~~~

1. For index 0, evaluate 0 >= 2: false. The later conditions do not run.
2. For index 5, the lower-bound check is true but 5 <= 4 is false. The element read does not run.
3. For index 3, both bounds pass and values(3) is read. Its value is 20, so the body runs.


## Build with checks enabled

Install a compatible open-source FreeBASIC compiler using the course setup lesson, then open PowerShell in your Bits2Banking checkout. The -lang fb option selects the modern FreeBASIC dialect. The -exx option enables additional runtime checking, useful while learning. Make the output directory explicitly. Stop after compiler errors; an older executable in the directory is not evidence that the edited program compiled. This example is supplied as source; availability of a compiler and successful execution must be checked on your machine.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
New-Item -ItemType Directory -Force build/learning-languages | Out-Null
fbc -lang fb -exx labs/languages/native-language-boundary/short_circuit_guards.bas -x build/learning-languages/short-circuit-guards.exe
& ".\build\learning-languages\short-circuit-guards.exe"
$LASTEXITCODE
~~~


## Predict and explain the result

The program prints one matching index, 3, followed by two explanatory lines. It returns zero when all internal checks succeed. Other return values identify a failed observation in the source. Run it again without changes: the same safe calls and array values should give the same result. To study ordinary And and Or, keep the Probe experiment where both operands are safe. Do not remove bounds protection from the array experiment merely to make a crash. Instead write down which forbidden index would be read and explain why runtime checking would need to reject it.

1. Change the searched value from 20 to 30 and predict the matching index before running. Adjust the expected count only if the number of matches changes.
2. Make Probe return false in the OrElse demonstration. Explain why the right side still does not run when the left side is already true.
3. Rewrite the three array guards as nested If blocks. Compare the conditions reached for indices 0, 3 and 5.
4. Explain why a nonzero pointer check cannot prove that its allocation is still alive.


## Further reading

- [FreeBASIC AndAlso reference](https://www.freebasic.net/wiki/KeyPgOpAndalso)
- [FreeBASIC short-circuit operator category](https://www.freebasic.net/wiki/CatPgOpShortCircuit)

[Previous: Select an overload by its arguments and preserve refused output](27-select-an-overload-by-its-arguments.md)

[Next: Expose state through a read-only property](29-expose-state-through-a-read-only-property.md)
