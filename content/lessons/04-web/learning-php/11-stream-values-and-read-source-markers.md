<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-php/11-stream-values-and-read-source-markers.md

PURPOSE:
Stream values and read source markers

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Stream values and read source markers

Some PHP words belong to a specialised workflow. Generators stream values as the caller asks for them. Another group of spellings exposes the location of source or changes how a file is handled.

| Word | Small PHP example | What it does |
| --- | --- | --- |
| `yield` | `function one(): Generator { yield 42; }` | Suspends the function and provides a value to its iterator. |
| `yield from` | `function three(): Generator { yield from [1, 2, 3]; }` | Relays values from another iterable. |
| `eval` | `eval('return 40 + 2;')` | Evaluates a string as PHP. This fixed teaching string shows the syntax. Keep data as data in real request handling. |
| `__halt_compiler` | At file scope, `__halt_compiler();` followed by literal data | Ends PHP compilation of that file and leaves a byte offset for the trailing data. It belongs in specialised archive formats. |
| `__FILE__` | `echo basename(__FILE__);` | Describes the current source file. |
| `__DIR__` | `$local = __DIR__;` | Describes the directory containing that file. |
| `__LINE__` | `$position = __LINE__;` | Supplies the use site's line number. |
| `__FUNCTION__` | `function sample(): string { return __FUNCTION__; }` | Supplies the function name in its source context. |
| `__CLASS__` | In a class method, `return __CLASS__;` | Supplies the class name for that location. |
| `__METHOD__` | In a method, `return __METHOD__;` | Supplies the method's qualified name. |
| `__NAMESPACE__` | After a namespace declaration, `echo __NAMESPACE__;` | Supplies the current namespace name. |
| `__TRAIT__` | Inside a trait method, `return __TRAIT__;` | Supplies the trait name for its defining location. |
| `__PROPERTY__` | Inside a property hook, `get { return __PROPERTY__; }` | Supplies the property name in the hook context. This form requires PHP 8.4 or later. |

~~~php
<?php
function amounts(): Generator {
    yield 12;
    yield from [15, 15];
}
$total = 0;
foreach (amounts() as $amount) {
    $total += $amount;
}
echo $total, "\n";
~~~

Expect `42`. Remove one amount to see the total change while the generator continues to use the values written in the program.

~~~c
/* A native iterator keeps its progress and uses a separate end state. */
while (next_amount(&iterator, &pennies)) {
    total += pennies;
}
~~~

~~~text
ASK the source for its next number
WHILE a next number exists
    ADD it to the total
    ASK for the next number
RETURN the total
~~~

The C example passes the iterator state explicitly. Umicom Framework source steps also preserve a source location separately from the value they report. Test an empty iterator, one item and three items. Keep private source paths out of externally visible web responses. [PHP generators](https://www.php.net/manual/en/language.generators.syntax.php) · [PHP magic constants](https://www.php.net/manual/en/language.constants.magic.php) · [PHP halt compiler](https://www.php.net/manual/en/function.halt-compiler.php)

## Run the examples

1. Save the PHP example as `practice.php`. Keep the opening PHP tag. In a terminal with PHP available, run `php practice.php` and compare the output with the expected result above.
2. Open the C23 lab linked below and save it as `main.c`. From a terminal with GCC, run `gcc -std=c23 -Wall -Wextra -Wpedantic main.c -o native-keywords.exe`. In PowerShell run `.\native-keywords.exe` and find the `generators` row.
3. If the shell cannot find a compiler or PHP, start with the pseudocode and compare your predicted result with the examples.

[Course contents](index.md) · [Previous lesson · Release a request after an error](10-release-a-request-after-an-error.md) · [Next lesson · Use types and contextual words](12-use-types-and-contextual-words.md) · [HTML edition](../../../courses/learning-php/lessons/11-stream-values-and-read-source-markers.html) · [Complete C23 lab](../../../labs/native/php-keyword-comparison/main.c)
