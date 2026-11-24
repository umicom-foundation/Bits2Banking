<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-php/05-repeat-with-a-bounded-list.md

PURPOSE:
Repeat with a bounded list

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Repeat with a bounded list

A loop repeats a task. For a list of amounts, decide whether you are walking a collection, counting a fixed number of steps or repeating until a condition changes.

| Word | Small PHP example | What it does |
| --- | --- | --- |
| `for` | `for ($i = 0; $i < 3; ++$i) { echo $i; }` | Performs setup, tests before each iteration and advances after it. |
| `foreach` | `foreach ($amounts as $amount) { echo $amount; }` | Visits each value in an array or iterable object. |
| `as` | `foreach ($amounts as $key => $value) { echo $key; }` | Names what each iteration receives. |
| `while` | `while ($remaining > 0) { --$remaining; }` | Tests before each pass. |
| `do` | `do { --$remaining; } while ($remaining > 0);` | Runs the body once before its first test. |
| `continue` | `if ($amount < 0) { continue; }` | Skips the remainder of the current iteration. |
| `endfor` | `for ($i = 0; $i < 2; ++$i): echo $i; endfor;` | Ends a colon-delimited counter loop. |
| `endforeach` | `foreach ($amounts as $amount): echo $amount; endforeach;` | Ends a colon-delimited collection loop. |
| `endwhile` | `while ($remaining > 0): --$remaining; endwhile;` | Ends a colon-delimited while loop. |
| `goto` | Inside one function, `goto finished; finished: return 0;` | Transfers to a label in the same context. PHP limits jumps into loops or switches. Read this form when maintaining older code. |

~~~php
<?php
$total = 0;
foreach ([100, -8, 40] as $amount) {
    if ($amount < 0) {
        continue;
    }
    $total += $amount;
}
echo $total, "\n";
~~~

Expect `140`. Move the negative entry to the start and the end. Neither position should alter the result.

~~~c
/* C walks the same bounded list with an explicit index and element count. */
int amounts[] = {100, -8, 40};
int total = 0;
for (size_t i = 0; i < sizeof amounts / sizeof amounts[0]; ++i) {
    if (amounts[i] < 0) continue;
    total += amounts[i];
}
~~~

~~~text
FOR EACH amount in the list
    IF amount is negative THEN skip this amount
    ADD amount to the total
RETURN the total
~~~

The C fragment needs `<stddef.h>` for `size_t` in a standalone file. In a Umicom Framework batch validator, count validated entries and bound the accumulated total before publishing it. Add a zero entry and an empty collection to the PHP practice. An empty collection should yield zero because the accumulator starts at zero. [PHP loops and jumps](https://www.php.net/manual/en/language.control-structures.php)

## Run the examples

1. Save the PHP example as `practice.php`. Keep the opening PHP tag. In a terminal with PHP available, run `php practice.php` and compare the output with the expected result above.
2. Open the C23 lab linked below and save it as `main.c`. From a terminal with GCC, run `gcc -std=c23 -Wall -Wextra -Wpedantic main.c -o native-keywords.exe`. In PowerShell run `.\native-keywords.exe` and find the `loops` row.
3. If the shell cannot find a compiler or PHP, start with the pseudocode and compare your predicted result with the examples.

[Course contents](index.md) · [Previous lesson · Choose a payment state](04-choose-a-payment-state.md) · [Next lesson · Keep zero and missing separate](06-keep-zero-and-missing-separate.md) · [HTML edition](../../../courses/learning-php/lessons/05-repeat-with-a-bounded-list.html) · [Complete C23 lab](../../../labs/native/php-keyword-comparison/main.c)
