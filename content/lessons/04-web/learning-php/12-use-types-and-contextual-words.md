<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-php/12-use-types-and-contextual-words.md

PURPOSE:
Use types and contextual words

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Use types and contextual words

A type tells a reader what a name may hold. PHP also reserves some names that refer to the current class, an older class, or values built into the language.

| Word | Small PHP example | What it does |
| --- | --- | --- |
| `int` | `function pennies(int $amount): int { return $amount; }` | Requires a whole number under the applicable type rules. |
| `float` | `function ratio(float $value): float { return $value; }` | Describes floating-point data. Use whole pennies for exact monetary inputs in this course. |
| `bool` | `function ready(bool $condition): bool { return $condition; }` | Describes either true or false. |
| `string` | `function label(string $name): string { return $name; }` | Describes a byte string. Use the earlier text lesson to distinguish bytes and characters. |
| `true` | `$ready = true;` | Records that a condition holds. It can also appear as a literal type in supported versions. |
| `false` | `$ready = false;` | Records that a condition does not hold. It can also appear in supported type declarations. |
| `null` | `$unknown = null;` | Records the null value. A type such as `?int` admits either an integer or null. |
| `void` | `function announce(): void { echo "saved"; }` | Declares a function that returns without a supplied result. |
| `iterable` | `function countRows(iterable $rows): int { /* use foreach */ }` | Accepts arrays and objects that implement the traversal contract. The body must supply the promised count. |
| `object` | `function sameObject(object $input): object { return $input; }` | Accepts an object regardless of its class. |
| `mixed` | `function keep(mixed $input): mixed { return $input; }` | Declares that any PHP value is admitted. A condition may still be needed before using it as a number. |
| `never` | `function fail(): never { throw new LogicException("stop"); }` | Declares that control never returns from the call normally. |
| `self` | Inside a class, `return self::LIMIT;` | Resolves a member in the class where the method is declared. |
| `parent` | Inside a subclass, `return parent::total();` | Calls or reads a member through the parent class scope. |
| `resource` | `if (is_resource($handle)) { /* use the resource */ }` | Names a PHP value category through a predicate. PHP has no native resource parameter type declaration. |
| `numeric` | `if (is_numeric($value)) { /* inspect the number */ }` | Describes a number or an accepted numeric string through a predicate. Validate the range and form separately. |

The PHP manual lists `resource` and `numeric` as soft reservations. The classes lesson explains `readonly`, and the composition lesson explains `enum` in its declaration context. `array` and `callable` have both language roles and type contexts. Pick clear domain names such as `TotalReader` instead of names that the language reserves.

~~~php
<?php
declare(strict_types=1);
function decide(?int $amount): string {
    if ($amount === null) {
        return "missing";
    }
    return $amount === 0 ? "zero" : "present";
}
echo decide(null), "/", decide(0), "/", decide(42), "\n";
~~~

Expect `missing/zero/present`. The caller sends three different facts. A literal zero stays a valid number throughout the exercise.

~~~c
/* A small C23 record represents the same optional integer explicitly. */
struct Amount { bool has_value; int pennies; };
const char *label = !input.has_value ? "missing" :
    input.pennies == 0 ? "zero" : "present";
~~~

~~~text
IF the amount is missing THEN label it missing
ELSE IF the amount equals zero THEN label it zero
ELSE label it present
~~~

In the C fragment `input` is a `struct Amount`. The native lab runs all three cases. A Umicom Bank report can decide how to display missing values separately from valid zero balances. [PHP type syntax](https://www.php.net/manual/en/language.types.declarations.php) · [PHP other reserved words](https://www.php.net/manual/en/reserved.other-reserved-words.php)

## Run the examples

1. Save the PHP example as `practice.php`. Keep the opening PHP tag. In a terminal with PHP available, run `php practice.php` and compare the output with the expected result above.
2. Open the C23 lab linked below and save it as `main.c`. From a terminal with GCC, run `gcc -std=c23 -Wall -Wextra -Wpedantic main.c -o native-keywords.exe`. In PowerShell run `.\native-keywords.exe` and find the `types` row.
3. If the shell cannot find a compiler or PHP, start with the pseudocode and compare your predicted result with the examples.

[Course contents](index.md) · [Previous lesson · Stream values and read source markers](11-stream-values-and-read-source-markers.md) · [HTML edition](../../../courses/learning-php/lessons/12-use-types-and-contextual-words.html) · [Complete C23 lab](../../../labs/native/php-keyword-comparison/main.c)
