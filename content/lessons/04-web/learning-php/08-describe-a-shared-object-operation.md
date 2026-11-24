<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-php/08-describe-a-shared-object-operation.md

PURPOSE:
Describe a shared object operation

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Describe a shared object operation

A class groups data with operations. An interface allows different classes to promise the same operation. The boundary is useful in a ledger that can read totals from more than one source.

| Word | Small PHP example | What it does |
| --- | --- | --- |
| `interface` | `interface TotalReader { public function total(): int; }` | Records the method that an implementation must supply. |
| `class` | `class FixedTotal { public function total(): int { return 42; } }` | Defines a class and its methods. |
| `implements` | `class FixedTotal implements TotalReader { /* total goes here */ }` | Declares a class's agreement with the interface. It must supply all required methods. |
| `abstract` | `abstract class Reader { abstract public function total(): int; }` | Defines an incomplete base that cannot be instantiated. |
| `extends` | `class FixedTotal extends Reader { /* implement total */ }` | Builds a subtype from a base class. |
| `final` | `final class FixedTotal { /* methods */ }` | Prevents subclassing. A final method cannot be overridden. |
| `public` | `public function total(): int { return 42; }` | Makes a member callable from outside the class. |
| `protected` | `protected int $total = 42;` | Makes a property available within the class and permitted related classes. |
| `private` | `private int $total = 42;` | Limits direct access to the declaring class. |
| `var` | Inside a class, `var $legacy = 0;` | Declares a public property with older spelling. Prefer an explicit visibility word. |
| `readonly` | `public readonly int $amount;` | Declares a typed property with restricted reassignment after initialization. The property form starts in PHP 8.1. |
| `new` | `$reader = new FixedTotal();` | Creates an instance. |
| `instanceof` | `$reader instanceof TotalReader` | Checks whether the object satisfies a named type. |
| `clone` | `$next = clone $reader;` | Creates a shallow copy, then invokes `__clone` if defined. Referenced objects can still be shared. |

~~~php
<?php
interface TotalReader {
    public function total(): int;
}

final class FixedTotal implements TotalReader {
    public function total(): int {
        return 42;
    }
}

$reader = new FixedTotal();
if ($reader instanceof TotalReader) {
    echo $reader->total(), "\n";
}
~~~

Expect `42`. Change the returned number and run again. Remove the method temporarily. The incomplete implementation fails before showing a total. Restore the method before trying the next exercise.

~~~c
/* C makes a reusable operation and its context explicit in the type. */
struct TotalReader {
    int (*read_total)(const void *context);
    const void *context;
};
~~~

~~~text
REQUIRE each reader to have a read total operation
CREATE the reader with its own data
ASK the reader for the total
~~~

Umicom Framework can define a C contract like this without recreating class syntax. In a real report distinguish the result of the call from the amount it returns. An unavailable source should be distinguishable from a source whose total is zero. [PHP classes and objects](https://www.php.net/manual/en/language.oop5.php)

## Run the examples

1. Save the PHP example as `practice.php`. Keep the opening PHP tag. In a terminal with PHP available, run `php practice.php` and compare the output with the expected result above.
2. Open the C23 lab linked below and save it as `main.c`. From a terminal with GCC, run `gcc -std=c23 -Wall -Wextra -Wpedantic main.c -o native-keywords.exe`. In PowerShell run `.\native-keywords.exe` and find the `objects` row.
3. If the shell cannot find a compiler or PHP, start with the pseudocode and compare your predicted result with the examples.

[Course contents](index.md) · [Previous lesson · Pass an operation to a function](07-pass-an-operation-to-a-function.md) · [Next lesson · Choose between named implementations](09-choose-between-named-implementations.md) · [HTML edition](../../../courses/learning-php/lessons/08-describe-a-shared-object-operation.html) · [Complete C23 lab](../../../labs/native/php-keyword-comparison/main.c)
