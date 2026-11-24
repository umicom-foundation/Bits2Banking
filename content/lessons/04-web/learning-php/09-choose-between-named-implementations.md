<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-php/09-choose-between-named-implementations.md

PURPOSE:
Choose between named implementations

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Choose between named implementations

Different pieces of a PHP program can supply the same named method. The program needs an explicit rule for choosing a method and assembling its own code.

| Word | Small PHP example | What it does |
| --- | --- | --- |
| `trait` | `trait StableLabel { public function label(): string { return "stable"; } }` | Supplies members that another declaration can reuse. |
| `insteadof` | `use StableLabel, DraftLabel { StableLabel::label insteadof DraftLabel; }` | Resolves one collision between two methods with the same name. |
| `enum` | `enum State { case Ready; case Waiting; }` | Defines a closed set of cases. This PHP 8.1 contextual form is listed in the parser-token table. |
| `include` | `include __DIR__ . "/labels.php";` | Loads a known local program file. A failed inclusion reports a warning. |
| `include_once` | `include_once __DIR__ . "/labels.php";` | Loads the known file at most once during an execution. |
| `require` | `require __DIR__ . "/labels.php";` | Loads a file required to proceed. A missing file produces an error. |
| `require_once` | `require_once __DIR__ . "/labels.php";` | Requires the file while avoiding another inclusion of the same included file. |

~~~php
<?php
trait StableLabel {
    public function label(): string { return "stable"; }
}
trait DraftLabel {
    public function label(): string { return "draft"; }
}
final class Report {
    use StableLabel, DraftLabel {
        StableLabel::label insteadof DraftLabel;
        DraftLabel::label as draftLabel;
    }
}
$report = new Report();
echo $report->label(), "/", $report->draftLabel(), "\n";
~~~

Expect `stable/draft`. Swap the selected trait and alias the other method. If the two trait methods still collide, check that the `insteadof` clause names the exact same method on both traits.

~~~c
/* A closed choice can select one already compiled implementation. */
enum LabelChoice { label_stable, label_draft };
const char *text = choice == label_stable ? "stable" : "draft";
~~~

~~~text
REGISTER both known label providers
SET the default provider to stable
CALL the selected provider
~~~

The C fragment assumes `choice` holds an admitted `enum LabelChoice`. PHP includes execute source, so keep the examples' filenames fixed and reviewed. For a native Umicom WebServer application, select a compiled module through its declared route or handler contract. PHP includes and C headers serve different jobs. [PHP traits](https://www.php.net/manual/en/language.oop5.traits.php) · [PHP enumerations](https://www.php.net/manual/en/language.enumerations.php) · [PHP include](https://www.php.net/manual/en/function.include.php)

## Run the examples

1. Save the PHP example as `practice.php`. Keep the opening PHP tag. In a terminal with PHP available, run `php practice.php` and compare the output with the expected result above.
2. Open the C23 lab linked below and save it as `main.c`. From a terminal with GCC, run `gcc -std=c23 -Wall -Wextra -Wpedantic main.c -o native-keywords.exe`. In PowerShell run `.\native-keywords.exe` and find the `composition` row.
3. If the shell cannot find a compiler or PHP, start with the pseudocode and compare your predicted result with the examples.

[Course contents](index.md) · [Previous lesson · Describe a shared object operation](08-describe-a-shared-object-operation.md) · [Next lesson · Release a request after an error](10-release-a-request-after-an-error.md) · [HTML edition](../../../courses/learning-php/lessons/09-choose-between-named-implementations.html) · [Complete C23 lab](../../../labs/native/php-keyword-comparison/main.c)
