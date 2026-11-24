<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/automated-testing-with-umicom/01-write-the-expected-result.md

PURPOSE:
Write the expected result

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Write the expected result

A test is a small experiment with a result you can check. Start by writing the input and the observable outcome. A useful test says exactly which fact determines whether it passes.

## Classify two made-up amounts

Imagine a savings club that records whole pennies. For the test, use an ordinary positive input and one outside the admitted range.

| Input | Expected status | Expected output |
| --- | --- | --- |
| 42 pennies | Accepted | 42 |
| −1 penny | Refused | The previous output remains available |

~~~c
/* This rule can be checked without opening the interface or a database. */
static bool admit_pennies(int input, int *out)
{
    if (out == NULL || input < 0) return false;
    *out = input;
    return true;
}
~~~

Use the existing output value 77 before the refused input. If the test sees 77 afterward, it confirms the contract about preserving the caller’s result. A test that checks only the return value cannot demonstrate that second fact.

~~~text
SET result to 77
CALL admit with input -1 and result
EXPECT refusal
EXPECT result still equals 77
~~~

## Choose what to observe

A unit test calls one rule directly. A workflow test might check that an amount is validated, saved to a fake ledger, and shown after the save completes. Interface tests observe what appears on screen or what a control does. Keep the expected rule outcome clear before choosing the test environment.

1. Write one positive row and one refused row for a new rule.
2. Add a row exactly at the permitted boundary, such as zero.
3. Make the rule fail deliberately in a practice copy. Check that the expected row detects the changed result.
4. Restore the rule and rerun the checks. Keep recorded failures separate from an actual passing rerun.

Umicom Framework can run shared logic through the same contracts that application adapters use. A native rule with counted inputs can often be tested on the host before a desktop, mobile, Web or embedded interface is available.

[Course contents](index.md) · [Next lesson · Choose target operations before dispatch](02-choose-target-operations.md) · [HTML edition](../../../courses/automated-testing-with-umicom/lessons/01-write-the-expected-result.html) · [Native C23 lab source](../../../labs/native/automated-testing-preview/main.c) · [SDK build description](../../../labs/native/automated-testing-preview/CMakeLists.txt)
