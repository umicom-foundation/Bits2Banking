<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-php/06-keep-zero-and-missing-separate.md

PURPOSE:
Keep zero and missing separate

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Keep zero and missing separate

An application can receive a field that is missing, a field containing zero or a field containing no usable text. Learn to ask which condition applies before deciding what the field means.

| Word | Small PHP example | What it does |
| --- | --- | --- |
| `array` | `$row = array("total" => 0);` | Creates an ordered map. The shorter literal `["total" => 0]` is also available. |
| `list` | `list($debit, $credit) = [15, 27];` | Unpacks elements into separate variables. |
| `isset` | `isset($row["total"])` | Is true when the field exists and its value is other than null. A valid zero passes this check. |
| `empty` | `empty($row["total"])` | Treats a missing field and several false-like values, including zero, as empty. |
| `unset` | `unset($row["draft"]);` | Removes the named entry. |
| `const` | `const UNIT = 100;` | Defines a constant. Inside a class the access form is `ClassName::UNIT`. |
| `and` | `($ready and $valid)` | Requires both conditions. Parenthesize when assigning this result. |
| `or` | `($ready or $override)` | Requires at least one condition. Parentheses make its low precedence visible. |
| `xor` | `($debit xor $credit)` | Requires exactly one true condition. |
| `echo` | `echo $total, "\n";` | Writes output and can accept several expressions. |
| `print` | `print "saved";` | Writes one expression and also returns 1. |

Assignment binds more tightly than the three word operators. Use parentheses or `&&` and `||` when that is the clearer condition. In PHP, `empty` and `isset` answer different questions.

~~~php
<?php
$row = ["total" => 0];
list($first, $second) = [15, 27];
if (isset($row["total"])) {
    $row["total"] = $first + $second;
}
echo $row["total"], "\n";
~~~

Expect `42`. Set `total` to `null` and predict whether the addition is admitted. Restore zero and change `isset` to `!empty`. Watch how the two variants treat zero.

~~~c
/* A presence flag and integer value model two different facts. */
struct Total { bool present; int pennies; };
struct Total row = {true, 0};
if (row.present) row.pennies = 15 + 27;
~~~

~~~text
IF the total field has a value THEN
    ADD the first and second amounts
    SAVE the result
END IF
~~~

This C23 structure can represent a usable zero without giving zero two meanings. Apply the same separation when admitting data for a Umicom Bank report. A nullable input needs a decision about whether it is unknown, absent, or invalid before counting it. [PHP arrays](https://www.php.net/manual/en/language.types.array.php) · [PHP logical operators](https://www.php.net/manual/en/language.operators.logical.php)

## Run the examples

1. Save the PHP example as `practice.php`. Keep the opening PHP tag. In a terminal with PHP available, run `php practice.php` and compare the output with the expected result above.
2. Open the C23 lab linked below and save it as `main.c`. From a terminal with GCC, run `gcc -std=c23 -Wall -Wextra -Wpedantic main.c -o native-keywords.exe`. In PowerShell run `.\native-keywords.exe` and find the `values` row.
3. If the shell cannot find a compiler or PHP, start with the pseudocode and compare your predicted result with the examples.

[Course contents](index.md) · [Previous lesson · Repeat with a bounded list](05-repeat-with-a-bounded-list.md) · [Next lesson · Pass an operation to a function](07-pass-an-operation-to-a-function.md) · [HTML edition](../../../courses/learning-php/lessons/06-keep-zero-and-missing-separate.html) · [Complete C23 lab](../../../labs/native/php-keyword-comparison/main.c)
