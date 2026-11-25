<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/119-separate-admission-checks-from-source-steps.md

PURPOSE:
Separate admission checks from source steps

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Separate admission checks from source steps

Lesson 97, *Check a constant before running C*, introduced a `static_assert` that can stop compilation. Here you will distinguish those checks from the work the interpreter does after the compiler accepts the source. **Admission** is the compiler phase that reads and checks the source before handing a program to the interpreter.

Think of a practice stock count with six packs of seven items. `PACKS` names a fixed value before the entry function. `ANSWER` belongs to the main block. The assertion checks the calculation during admission.

~~~c
constexpr int PACKS = 6;
int main(void) {
  constexpr int ANSWER = PACKS * 7;
  static_assert(ANSWER == 42);
  return ANSWER;
}
~~~

## Keep two counts on paper

1. Write `PACKS = 6` and `ANSWER = 42` in an admission column. Mark the assertion as passed.
2. In a source-step column, write one action, the return on line 5. The fixed declarations and the assertion have already been checked.
3. In a virtual machine column, write `PUSH 42` and then `RETURN`. A virtual machine runs the compiler's smaller instructions. The first instruction puts 42 on the machine's stack, where it keeps working values. The second finishes the function with that value.
4. Repeat the two counts for the previous lesson's enumeration. `BASE + 1` gives `FIRST = 40`, so `SECOND = 41` and `THIRD = 42`. The assertion and the numbers are checked before the interpreter reaches the return.

A source step follows a piece of the written program. An instruction budget limits how many of the machine's smaller instructions the interpreter may execute. For these two examples, the fixture checks that the next source step is the return on line 5 and that the compiler emits exactly two instructions. It initializes the interpreter with a budget of two.

## Check a branch that would be skipped

Trace these as separate programs. At runtime the condition `0` would skip the block. During admission the compiler still checks the constant declarations inside it.

~~~c
int main(void) { if(0) { constexpr int A=1/0; } return 42; }
~~~

~~~c
int main(void) { if(0) { enum { VALUE=1/0 }; } return 42; }
~~~

| Source | Admission result | What the fixture checks |
| --- | --- | --- |
| `constexpr` stock count | Accepted with value 42 available to the return | The first source step is the return. The two instructions are `PUSH 42` and `RETURN`. |
| Enumeration from the previous lesson | Accepted with value 42 available to the return | The same first step and the same two instructions. |
| `constexpr` with division by zero | `UMC_ARITHMETIC_ERROR` | The diagnostic contains `division by zero`. The reported instruction count is zero. |
| Enumeration with division by zero | `UMC_ARITHMETIC_ERROR` | The same diagnostic text and zero reported instruction count. |

Explain why `return 42` cannot repair either invalid declaration. Then change `1/0` to `1/1` on paper and predict which admission error disappears. Base the prediction on valid arithmetic and keep it separate from the four outcomes checked in the compiler fixtures.

[Course contents](index.md) · [Previous lesson · Number enumeration members inside a block](118-number-enumeration-members-inside-a-block.md) · [Check a constant before running C](97-check-a-constant-before-running.md) · [Count reached source statements](107-count-reached-source-statements.md) · [Read the instruction budget at a pause](116-read-the-instruction-budget-at-a-pause.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/119-separate-admission-checks-from-source-steps.html)

[Next lesson · Read equivalent signed local types](120-read-equivalent-signed-local-types.md)
