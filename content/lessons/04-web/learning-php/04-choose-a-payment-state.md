<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-php/04-choose-a-payment-state.md

PURPOSE:
Choose a payment state

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Choose a payment state

A keyword is a word the language already uses. For example, `if` introduces a choice. In this lesson a price is expressed as whole pennies, so the examples do not round a floating-point value.

## Make two kinds of choice

| Word | Small PHP example | What it does |
| --- | --- | --- |
| `if` | `if ($paid === 0) { echo "unpaid"; }` | Checks the first condition. |
| `elseif` | `elseif ($paid < 4200) { echo "partial"; }` | Checks a second condition if the first was false. Keep it in the same chain. |
| `else` | `else { echo "complete"; }` | Runs when the preceding tests were false. |
| `switch` | `switch ($status) { case "open": break; default: break; }` | Chooses among labelled paths. Its equality rule can coerce values. |
| `case` | `case "open": echo "Review"; break;` | Marks a value to match within a switch. |
| `break` | `break;` | Leaves the switch or enclosing loop at that point. |
| `default` | `default: echo "Unknown";` | Supplies the fallback in a switch or match. |
| `match` | `match ($status) { "open" => "Review", default => "Unknown" }` | Produces a value and uses strict identity for its arms. Requires PHP 8.0 or later. |
| `endif` | `if ($ready): echo "Ready"; endif;` | Ends the colon-delimited form of an if statement. |
| `endswitch` | `switch ($status): case "open": break; endswitch;` | Ends the colon-delimited switch. |

Do not mix braces and colon endings for a single statement. A switch case keeps running into the next case unless control leaves it. A match expression chooses one result. For data that enters an application, normalize the type at the boundary, then choose the control form that expresses your intent.

~~~php
<?php
$paid = 2100;
if ($paid === 0) {
    echo "unpaid\n";
} elseif ($paid < 4200) {
    echo "partial\n";
} else {
    echo "complete\n";
}
~~~

Expect `partial`. Change 2100 to 0, then to 4200. Predict the output before each run.

## Compare three forms

~~~c
/* An integer boundary makes these cases deliberate in C23 as well. */
int paid = 2100;
const char *state = paid == 0 ? "unpaid" : paid < 4200 ? "partial" : "complete";
~~~

~~~text
IF paid equals zero THEN state is unpaid
ELSE IF paid is below 4200 THEN state is partial
ELSE state is complete
~~~

The C example already has an integer type. When reviewing a route in Umicom WebServer, first establish that the input bytes represent the whole permitted number. The choice can then stay in a small C function. If your PHP output surprises you, echo a newline after each result and check whether the input was a string before comparing it. [PHP control structures](https://www.php.net/manual/en/language.control-structures.php)

## Run the examples

1. Save the PHP example as `practice.php`. Keep the opening PHP tag. In a terminal with PHP available, run `php practice.php` and compare the output with the expected result above.
2. Open the C23 lab linked below and save it as `main.c`. From a terminal with GCC, run `gcc -std=c23 -Wall -Wextra -Wpedantic main.c -o native-keywords.exe`. In PowerShell run `.\native-keywords.exe` and find the `choices` row.
3. If the shell cannot find a compiler or PHP, start with the pseudocode and compare your predicted result with the examples.

[Course contents](index.md) · [Previous lesson · Count text at the right boundary](03-count-text-at-the-right-boundary.md) · [Next lesson · Repeat with a bounded list](05-repeat-with-a-bounded-list.md) · [HTML edition](../../../courses/learning-php/lessons/04-choose-a-payment-state.html) · [Complete C23 lab](../../../labs/native/php-keyword-comparison/main.c)
