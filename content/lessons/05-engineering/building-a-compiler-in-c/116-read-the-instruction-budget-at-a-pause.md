<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/116-read-the-instruction-budget-at-a-pause.md

PURPOSE:
Read the instruction budget at a pause

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read the instruction budget at a pause

When a source program is paused, you can ask how many machine instructions it has used. An **instruction budget** is the number of those small operations the interpreter is allowed to finish. In this lesson you will read the budget without advancing the program, then compare the observation with the ordinary execution trace.

## 1. Separate a question from a step

Use this exact practice program. The first declaration spans two lines. The next statement multiplies the value by seven.

~~~c
int main(void) {
  int x =
    6; x *= 7;
  return x;
}
~~~

On paper, imagine the source interpreter is paused before the declaration with an allowance of 20 instructions. The existing session form for a file called `practice.c` is shown below. The paper exercise needs only the command list that follows it.

~~~powershell
umicom-c interpret practice.c --step --max-steps 20
~~~

Write the prompt commands down in order.

~~~text
budget
budget
next
budget
run
~~~

The first two commands ask the same question while the next statement is still waiting. The command `next` lets one source statement finish. Its declaration uses two machine instructions. The next observation therefore shows 2 used and 18 remaining.

| Prompt action | Used | Remaining | Where execution is paused |
| --- | --- | --- | --- |
| First `budget` | 0 | 20 | Before the declaration |
| Second `budget` | 0 | 20 | Before the same declaration |
| `next`, then `budget` | 2 | 18 | Before the multiplication |

The saved test required the first message twice and checked for the final message after the declaration.

~~~text
Instructions used: 0. Instructions remaining: 20.
Instructions used: 0. Instructions remaining: 20.
Instructions used: 2. Instructions remaining: 18.
~~~

## 2. Read the right stream

The `budget` messages go to the diagnostic stream, where the console also writes its prompts. The normal output stream records each completed source step and the final result. When the prompt gets `run`, the practice program reaches its return and produces `Result: 42`. The test compares the full normal output against an ordinary run of the same program and requires an exact match. A person can ask for the budget while a tool reads the normal trace.

~~~text
AT a pause, read used and remaining
DISPLAY those numbers beside the prompt
LEAVE the current source position alone
WAIT for a command that advances execution
~~~

Imagine a fresh session with an allowance of exactly two instructions. Once the declaration has finished, a budget reading can show 2 used and 0 remaining. Predict what the next instruction attempt will report. The next instruction needs fuel, so it reports exhaustion. A budget reading itself leaves the allowance in place.

## 3. Explain what the saved check covers

The checked interpreter fixture verifies the three prompt readings and the unchanged normal trace. Its result was among 47 selected passing Umicom C tests. That gives evidence for the tested sources and selected cases. For a Studio IDE pause panel, keep the same distinction between observing the current allowance, taking a source step, and reporting a completed result. An instruction figure describes interpreter operations. A separate host deadline measures how long the surrounding process may take.

[Course contents](index.md) · [Previous lesson · Translate short-circuit conditions across C23 and D](115-translate-short-circuit-conditions-across-c-and-d.md) · [Related lesson · Watch one integer slot](114-watch-one-integer-slot.md) · [Related lesson · Separate instruction fuel from wall-clock time](59-separate-instruction-fuel-from-wall-clock-time.md) · [Related lesson · Read child and fixture deadlines](../learning-build-systems/32-read-child-and-fixture-deadlines.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/116-read-the-instruction-budget-at-a-pause.html)

[Next lesson · Resolve a fixed name in its block](117-resolve-a-fixed-name-in-its-block.md)
