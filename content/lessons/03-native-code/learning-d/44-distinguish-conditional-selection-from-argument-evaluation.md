<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-d/44-distinguish-conditional-selection-from-argument-evaluation.md

PURPOSE:
Distinguish conditional selection from argument evaluation

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Distinguish conditional selection from argument evaluation

[Course contents](index.md)

## Start with values and effects

An expression can return a value and cause an effect. A function that returns eleven while incrementing a counter does both. Choosing between values after they have been computed is different from choosing which computation to perform. This lesson uses D’s conditional expression and an ordinary helper function to expose that difference. The reasoning is useful when a client decides whether to request a Framework operation, construct an object or use a default value.


## Read the conditional expression

The question mark and colon form one conditional operator with three operands. D evaluates the condition and then the selected alternative. The result can be assigned or passed onward. Parentheses can clarify a larger expression. Use an ordinary if/else statement when a branch contains several actions.

~~~d
int selected = condition ? valueWhenTrue : valueWhenFalse;
~~~


## Build a harmless observation tool

private controls visibility through the module rules. int is the returned value type; uint is an unsigned counter. ref allows the function to update the caller’s counter. @safe requests memory-safety checking for this function, not mathematical correctness. nothrow and @nogc constrain exception and collector behavior. The bounded probe does not establish that standard output or the whole linked program has those same effects.

~~~d
private int probe(int value, ref uint calls) @safe nothrow @nogc
{
    ++calls;
    return value;
}
~~~


## Keep observations separate

The complete example uses leftCalls, rightCalls and conditionCalls. Each probe changes a different counter. The first phase begins with zero counters, evaluates the condition once and invokes one value probe. The second phase resets all three before calling an ordinary function. Without that reset, the observations would mix separate operations. This is a reasoning exercise, not a performance benchmark.


## Trace the selective phase

For true, expect eleven and one left call. For false, expect twenty-two and one right call. In each case the other value counter remains zero and the condition counter becomes one. The unselected operand still needs valid syntax and types; runtime selection is not conditional compilation. The alternatives here deliberately use the same integer type.

~~~d
int selected = probeCondition(choice, conditionCalls)
    ? probe(11, leftCalls) : probe(22, rightCalls);
~~~


## Trace the ordinary-call phase

chooseValues has ordinary by-value parameters. Both value probes run before its body chooses a result. Default D linkage specifies left-to-right argument evaluation; other linkage conventions have separate rules. The example checks only independent final counters, so its comparison does not depend on transferring D’s argument order to C.

~~~d
selected = chooseValues(probeCondition(choice, conditionCalls),
    probe(11, leftCalls), probe(22, rightCalls));
~~~


## Compare the observations

The returned integer alone cannot distinguish the operations. Their effects do. A function with a name such as Choose is not automatically selective. Read its parameter contract before placing expensive work inside its arguments.


| Operation | True result | False result | Work observed |
| --- | --- | --- | --- |
| Conditional expression | 11 | 22 | One condition and one value probe |
| Ordinary helper call | 11 | 22 | One condition and both value probes |


## Ordinary, lazy and delegate are different contracts

An ordinary integer parameter receives a computed value. A lazy parameter can defer an expression, and its function body may evaluate it repeatedly. A delegate carries callable behavior and may carry a context. Those mechanisms need their own lifetime analysis. This example uses neither. Revisit the earlier lazy-evaluation and callback lessons before using deferred work around borrowed native buffers.


## Compile the complete example

1. Open the native-language-boundary laboratory directory.
2. Read conditional_selection.d and locate the module declaration, probes, assertions, unittest block and main function.
3. Check the compiler version with dmd --version.
4. Compile with unit tests and debugging information enabled. Do not add release options that remove the checks you intend to observe.
5. Run only after compilation succeeds, then inspect the exit status.

~~~powershell
dmd --version
dmd -unittest -g -of=conditional_selection-d.exe conditional_selection.d
.\conditional_selection-d.exe
$LASTEXITCODE
~~~


## Expected result and current evidence

A successful run prints “Umicom D selective expression and eager argument checks passed.” The unittest block checks true and false choices; main exercises them during an ordinary run too. The D example is authored but uncompiled and unexecuted in the current authoring environment. A separately executed C comparison is evidence about C only. Preserve the subject-language compiler version and output when you qualify this example.


## What assertions establish

These assertions check the two choices and their counter values. They do not prove thread safety, interoperability, every conversion rule or the absence of all defects. Assertions are development checks rather than a replacement for input validation. A production C boundary still needs status returns, explicit sizes and ownership rules even when its D caller uses contracts and unit tests.


## Apply the lesson to Framework clients

A D client may select a scalar configuration value before calling a C23 Framework service. If two argument expressions each start a download or allocate a large buffer, an ordinary choosing helper receives their results only after both operations have happened. Prefer an explicit branch that admits and starts the intended operation. Keep reusable admission, cancellation and ownership in Framework. This is a control-flow improvement, not proof that any model workload will fit in memory.


## Keep reflection and execution separate

Reflection inspects declarations and types. Compile-time traits can report whether members exist, but do not by themselves report which runtime branch executed. These counters observe execution. Use type metadata for tasks such as building a field catalogue and use explicit runtime state or tests to record actions. Metadata is not a substitute for execution evidence.


## Extend the experiment

1. Change the returned constants and predict results and counters before running.
2. Rewrite the selective phase using if/else and compare its effects.
3. Explain how a lazy parameter differs from both an ordinary parameter and a cached result.
4. Explain why the C comparison intentionally avoids depending on argument order.
5. Keep the probes harmless; do not substitute invalid pointers or deliberate arithmetic faults.


## Further reading


- [D expression evaluation and conditional expressions](https://dlang.org/spec/expression.html)
- [D function parameters and linkage](https://dlang.org/spec/function.html)


[Previous: Separate union reflection from active-value state](43-separate-union-reflection-from-active-value-state.md)

[Next: Separate local static storage from caller ownership](45-separate-local-static-storage-from-caller-ownership.md)
