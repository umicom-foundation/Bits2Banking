<!--
Umicom Bits2Banking
File: content/lessons/02-programming/introduction-to-programming/02-values-and-decisions.md

PURPOSE:
Explain one concept through a practical example and an observable result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Values, variables and decisions

[Course contents](index.md) · [Previous: Instructions, source files and results](01-instructions-source-and-results.md) · [Next: Repeat work and name a reusable operation](03-loops-and-functions.md)

## The idea
A value is one piece of information, such as the number 5. A variable is a named place for a value. A type describes the kind of value permitted. In C, int represents whole numbers within the implementation's integer range.

A course progress screen might know there are five activities and two are finished. Its remaining count is three. Before subtracting, it must reject impossible counts.

## Setup recap
Use [the course setup](index.md) to install the compiler and build the first-c-programs lab. Open values.c and decisions.c in a text editor. These are small console examples; no account, network or Framework installation is needed.

## Read the rule before the code
~~~text
total = 5, completed = 2 -> remaining = 3
total = 5, completed = 7 -> invalid progress
~~~
The symbol = assigns a value in C. Equality testing uses ==. The expression completed > total is a question whose answer is true or false.
~~~c
const int total = 5;
const int completed = 7;
if (completed > total) {
    puts("Counts do not fit the rule.");
} else {
    printf("Remaining: %d\n", total - completed);
}
~~~
This is a fragment from the decision idea, not a complete file. Use the repository's complete decisions.c when compiling; it also rejects negative and excessive totals. const means this variable cannot be reassigned through that name. %d is a placeholder for a signed integer; \n ends the output line.

## Lab
1. Run btb-first-decisions using the course build directory. The repository example uses completed = 7.
2. Expect "Counts do not fit the rule." Rejection is the intended outcome for these values.
3. In your own practice copy, change completed to 2 and predict "Remaining: 3".
4. Compile that copy and compare the result.
5. Try total = 0 and completed = 0. Zero is a valid count; the answer is zero.

## Trace a branch
~~~text
read counts -> valid?
                yes -> subtract -> display remaining
                no  -> explain the invalid counts
~~~
Only one branch runs. The display is a consequence of the rule, not a substitute for checking it.

## Exercise
What should happen for total = 5, completed = -1? Write the expectation before editing the program.

## Worked answer
The full example refuses negative completed counts. Subtracting first would produce 6, an answer that looks plausible but represents invalid input. Validation must happen before using the values.

## Umicom connection
The shared count function in labs/native/first-c-programs/counts.c separates the rule from display. Framework services use this separation too: the same validated result can support a desktop window, terminal or web interface.

## Troubleshooting and limits
A source edit in the repository changes the exercise for later lessons; keep experiments in your own copy or record the change. This program uses fixed numbers, not keyboard input. Input conversion is a separate problem covered in [Learning Pascal](../learning-pascal/index.md) and [Safer C Programming](../../03-native-code/safer-c-programming/index.md).

## Source map
Read `labs/native/first-c-programs/decisions.c` in the Bits2Banking checkout. The lesson names the specific functions to study; you do not need to understand every file at once.

[Course contents](index.md) · [Previous: Instructions, source files and results](01-instructions-source-and-results.md) · [Next: Repeat work and name a reusable operation](03-loops-and-functions.md)
