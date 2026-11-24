<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-php/07-pass-an-operation-to-a-function.md

PURPOSE:
Pass an operation to a function

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Pass an operation to a function

A function groups a task behind a name. Its inputs and its returned value are different from the information a program writes to the screen.

| Word | Small PHP example | What it does |
| --- | --- | --- |
| `function` | `function total(int $x, int $y): int { return $x + $y; }` | Defines a named function. It can also start an anonymous function. |
| `fn` | `fn (int $x): int => $x + 1` | Builds a short expression-bodied function. Requires PHP 7.4 or later. |
| `callable` | `function apply(callable $f, int $n): int { return $f($n); }` | Accepts a value that can be called as a function. |
| `return` | `return $x + $y;` | Finishes the current function and publishes its value to the caller. |
| `global` | `global $limit;` | Binds a global name inside a function. A parameter makes input dependencies easier to see in new code. |
| `static` | Inside a function, `static $calls = 0;` | Keeps local storage between calls. The word also has class and closure forms. |
| `use` | `function (int $x) use ($tax): int { return $x + $tax; }` | Captures a value in a closure. Outside this example the word also imports names or applies traits. |
| `namespace` | `namespace Lessons\Totals;` | Gives declarations a qualified name. Declare it at the start of the file after any permitted declaration. |
| `declare` | `declare(strict_types=1);` | Sets file-specific strict typing. Put this declaration at the beginning of the file. |
| `enddeclare` | `declare(ticks=1): echo "sample"; enddeclare;` | Ends the colon form for a scoped directive such as ticks. |

~~~php
<?php
declare(strict_types=1);

function apply(callable $operation, int $amount): int {
    return $operation($amount);
}

$surcharge = 2;
echo apply(fn (int $amount): int => $amount + $surcharge, 40), "\n";
~~~

Expect `42`. Replace `40` with the string `"40"`. A strict call to this integer parameter raises an error. Restore the integer before continuing.

~~~c
/* A function pointer and a context value make the dependency explicit. */
int add(int amount, int surcharge) { return amount + surcharge; }
int apply(int (*operation)(int, int), int amount, int context) {
    return operation(amount, context);
}
~~~

~~~text
GIVE the operation an amount and a surcharge
RETURN the result to the caller
~~~

The C function pointer receives its data explicitly. When you build a configurable native calculation in Umicom Trader, pass both the validated operation and the values it needs. For the exercise, hold the starting amount at 40 and compare surcharge 2 with 0. [PHP user-defined functions](https://www.php.net/manual/en/functions.user-defined.php) · [PHP arrow functions](https://www.php.net/manual/en/functions.arrow.php)

## Run the examples

1. Save the PHP example as `practice.php`. Keep the opening PHP tag. In a terminal with PHP available, run `php practice.php` and compare the output with the expected result above.
2. Open the C23 lab linked below and save it as `main.c`. From a terminal with GCC, run `gcc -std=c23 -Wall -Wextra -Wpedantic main.c -o native-keywords.exe`. In PowerShell run `.\native-keywords.exe` and find the `functions` row.
3. If the shell cannot find a compiler or PHP, start with the pseudocode and compare your predicted result with the examples.

[Course contents](index.md) · [Previous lesson · Keep zero and missing separate](06-keep-zero-and-missing-separate.md) · [Next lesson · Describe a shared object operation](08-describe-a-shared-object-operation.md) · [HTML edition](../../../courses/learning-php/lessons/07-pass-an-operation-to-a-function.html) · [Complete C23 lab](../../../labs/native/php-keyword-comparison/main.c)
