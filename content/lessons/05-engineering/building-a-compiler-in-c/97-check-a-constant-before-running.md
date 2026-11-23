<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/97-check-a-constant-before-running.md

PURPOSE:
Teach how C static assertions check constant calculations during source admission.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material.
-->

# Check a constant before running C

<p class="umicom-course-artwork"><span class="umicom-brand-mark"><img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom" width="180"></span> <a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="30"></a></p>

[Course contents](index.md) · [Previous lesson](96-read-versioned-interpreter-reports.md)

Imagine four groups of six chairs. You can check on paper that this arrangement needs 24 chairs. C can perform the same constant check while it prepares your source. A static assertion asks for a condition that evaluates to a nonzero integer.

## Check the source, then run it

1. Predict the result and save the program as **chairs.c**.
2. Use the current Umicom C tool to check the source. Expect **Source accepted for interpretation.**
3. Run it normally. Expect a step for the declaration of **groups**, a return step and **Result: 24**.

~~~c
static_assert(4 * 6 == 24);

int main(void) {
    int groups = 4;
    static_assert(6 > 0);
    return groups * 6;
}
~~~

~~~powershell
umicom-c interpret chairs.c --check-only
umicom-c interpret chairs.c
~~~

The first assertion appears before the function. The second appears inside it. Both use fixed integer expressions, so the compiler can check them during source admission. The result events describe the program's execution.

## Change one thing at a time

1. Set **groups** to **5** and keep both assertions as written. Predict the result, then run it again. The source still passes the constant checks and the returned value becomes **30**.
2. In a fresh copy, put **if (0) { static_assert(0); }** before the return. Run with **--check-only**. Expect a diagnostic that the static assertion evaluated to zero. The compiler checks the declaration while preparing the source, even inside a branch execution would skip.
3. Explain the preparation in your own words. A plan can say “check the fixed calculation, stop if it fails, then prepare the instructions that will run later.”

Use a fixed expression in **static_assert**. This Umicom C profile accepts the form without a message at file scope or inside a C block. [C23 working draft, section 6.7.11](https://www.open-std.org/jtc1/sc22/wg14/www/docs/n3096.pdf)

[Next lesson on naming fixed values](98-name-values-before-the-entry.md)
