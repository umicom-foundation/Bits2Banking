# Check a function at its boundaries

[Course contents](index.md) · [Previous: Represent bytes with bits and hexadecimal](17-bits-and-hexadecimal.md) · [Next: Move from small programs to OS and Kernel source](08-connect-to-systems-lessons.md)

## Start with a question

Complete the lessons on functions, pointers and structures first. Suppose a learning application counts completed exercises, with a maximum of 1000. What happens at 999? At 1000? A boundary is a point where a rule changes. Checking only a normal value such as 5 leaves these important cases unexplored.

In the real activity example, `BtbActivityAdvance` returns a status and writes through an output pointer. A status is a named result explaining whether an operation succeeded. The pointer identifies storage supplied by the caller. On failure, that storage must remain unchanged.

## Trace the existing implementation

Open `labs/native/framework-activity/activity.h` and `activity.c`. Find the declaration, the definition and the three return paths. Read this table alongside the code; do not edit the shared checkout during the exercise.

```text
Current  Output storage     Status                 New output
0        valid, starts 42   OK                     1
999      valid, starts 42   OK                     1000
1000     valid, starts 42   CAPACITY_EXCEEDED      42
1001     valid, starts 42   INVALID_ARGUMENT      42
0        null              INVALID_ARGUMENT      no write
```

The value 42 is a sentinel: a recognisable starting value used to detect an unwanted write. It has no business meaning. `1000U` is an unsigned integer constant. `*next` accesses the caller's object; checking `next` before dereferencing it avoids accessing a null pointer.

## Read a regression check

```c
unsigned next = 42U;
UmiStatus status = BtbActivityAdvance(1000U, &next);
assert(status == UMI_STATUS_CAPACITY_EXCEEDED);
assert(next == 42U);
```

This is a fragment for the existing test environment, with `activity.h` and `<assert.h>` included. It is not a complete standalone program. The first assertion checks the reported result; the second checks the promised lack of mutation. Read `test_activity.c` to find how a complete test is arranged. Ordinary `assert` checks can be disabled by `NDEBUG`, so understand the build configuration before treating them as always active.

## Exercise and explanation

Predict the result for 998 and a valid output object. The answer is OK with 999. Then explain why returning OK with 1001 at the upper boundary would be a defect even if the window displays a number. A displayed result must satisfy the shared rule. If a check fails, record input, expected result and observed result before changing code. This makes the repair reproducible rather than a guess.

[Review the prerequisite course](../../courses/learning-computer-architecture/index.html).


## Source and further reading

[Read the related Umicom example](https://github.com/umicom-foundation/Bits2Banking/blob/bb0da4654632ab847ce7e729ced64f14cf230933/labs/native/framework-activity/activity.c). Path: `labs/native/framework-activity/activity.c`. This reference connects the topic to the codebase; it does not imply a language runtime or adapter is implemented in Umicom.

[Technical reference](https://en.cppreference.com/w/c/language.html). Check the version requirements in the lesson before practical work.

[Read this lesson as HTML](../../courses/learning-c/lessons/18-check-a-function-at-its-boundaries.html).

[Course contents](index.md) · [Previous: Represent bytes with bits and hexadecimal](17-bits-and-hexadecimal.md) · [Next: Move from small programs to OS and Kernel source](08-connect-to-systems-lessons.md)

Sammy Hegab · Umicom Foundation · Original learning material.
