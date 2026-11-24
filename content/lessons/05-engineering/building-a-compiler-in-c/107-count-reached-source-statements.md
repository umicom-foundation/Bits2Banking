<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/107-count-reached-source-statements.md

PURPOSE:
Count reached source statements

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Count reached source statements

A source **statement** is an instruction a programmer writes, such as setting a variable or returning a value. A statement can span several lines. One line can also contain two statements. The Umicom C pause console counts statements that execution reaches.

## Predict where the next pause will be

Save the following complete program as <code>practice.c</code> in a fresh exercise folder. Count the source lines starting at one.

~~~c
int main(void) {
  int x =
    6; x *= 7;
  return x;
}
~~~

The declaration starts on line 2 and finishes on line 3 after <code>6;</code>. The multiplication starts later on line 3. The return is the third reached statement. On paper, write down the value of <code>x</code> after the first statement and after the second.

~~~text
START with the first reached statement ready
REPEAT up to 2 times
    RUN one reached statement
    REPORT its source location and outcome
    STOP if the program returns or reports an error
PAUSE before the next reached statement
~~~

## Use the same pause controls on one or several statements

1. Open PowerShell in the practice folder. Start the current Umicom C tool with <code>umicom-c interpret practice.c --step</code>. The first prompt should start with <code>Next 2:3</code>. The two numbers identify the source line and column.
2. Type <code>next 2</code> and press Enter. The tool reports the declaration and multiplication. The new prompt should start with <code>Next 4:3</code>. There is no prompt between the two reported statements.
3. Type <code>show</code> to preview the pending return. Type <code>next</code> to execute it and expect <code>Result: 42</code>. Starting again and choosing <code>quit</code> at the same pause leaves the return unexecuted.

Use a positive decimal after <code>next</code>. If <code>next 0</code> or <code>next -2</code> is refused, the console leaves the current statement pending. Try <code>next 99</code> at the first prompt. The program returns after its three statements, so the console finishes after printing the result.

The same command works with the pseudocode profile. The instruction allowance, which counts the smaller operations used to run the source, still applies to every request. Use <code>until LINE</code> when you know the exact source line you want to reach. Use <code>--jsonl</code> if another tool reads the events. The same step records go to standard output and the prompts stay on the diagnostic stream.

Studio can use counted steps to let a learner move through predictable parts of a program. It can still display each reached statement and show the pending location after the batch.

[Course contents](index.md) · [Previous lesson · Translate a checked local update](106-translate-a-checked-local-update.md) · [Related lesson · Pause before a reached source line](95-pause-before-a-reached-line.md) · [Earlier lesson · Read versioned interpreter reports](96-read-versioned-interpreter-reports.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/107-count-reached-source-statements.html)

[Next lesson · Translate one return between C and D](108-translate-one-return-between-c-and-d.md)
