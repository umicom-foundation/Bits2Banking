<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/98-name-values-before-the-entry.md

PURPOSE:
Practise declaration order with constexpr integers, anonymous enum and static_assert.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Name values before the entry

[Course contents](index.md) · [Previous lesson](97-check-a-constant-before-running.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/98-name-values-before-the-entry.html)

Suppose a grid has six columns and seven rows. Each cell takes one step, followed by one step to finish. Giving each quantity a name makes the final number easier to check.

## Write the quantities in the order you need them

~~~c
constexpr int COLUMNS = 6;
constexpr int ROWS = 7;
enum { GRID_STEPS = COLUMNS * ROWS, FINAL_STEP };
static_assert(FINAL_STEP == 43, "Expect 42 cells and one final step");

int main(void) {
    return FINAL_STEP;
}
~~~

The word `constexpr` introduces a fixed value. An `enum` names related integers. The expression for `GRID_STEPS` gives it the value 42. The next name has no written value, so it gets 43. The compiler learns those values before the entry begins. [WG14 C23 working draft, sections 6.7.1 and 6.7.2.2](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3096.pdf)

## Run and change one thing

1. Save the program as `grid.c`. Run `umicom-c interpret grid.c` and expect `Result: 43`.
2. Change `ROWS` to 8. Run `umicom-c interpret grid.c --check-only`. Read the assertion message and calculate the new value of `FINAL_STEP` on paper. It is 49.
3. Restore `ROWS` to 7. Move its declaration below the enumeration. Repeat the check and find the earlier use of `ROWS` in the diagnostic. Restore the original order.

## Express the same calculation in pseudocode

~~~text
BEGIN
LET cells = 6 * 7;
RETURN cells + 1;
END
~~~

Save this as `grid.pseudo` and run `umicom-c pseudocode grid.pseudo`. It also returns 43. Here the calculation is an executed statement, so the interpreter can report it as a step. The C example resolves the named constants during admission and executes the return.

Use one signed integer per `constexpr int` declaration in this Umicom C profile. The file-scope table holds up to 32 combined enumeration and fixed integer names. It supports reading those values in calculations. Address operations and block-scope `constexpr` require a wider profile.

[Next lesson on counting bytes](99-count-bytes-from-an-admitted-type.md)
