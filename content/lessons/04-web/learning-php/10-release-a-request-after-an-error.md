<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-php/10-release-a-request-after-an-error.md

PURPOSE:
Release a request after an error

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Release a request after an error

Errors leave a normal code path. Write down which facts are ready to publish, which actions are still open and where temporary resources are released.

| Word | Small PHP example | What it does |
| --- | --- | --- |
| `try` | `try { process(); }` | Starts a protected block. Follow it with a catch, finally, or both. |
| `throw` | `throw new InvalidArgumentException("negative");` | Raises an exception carrying information about the failure. |
| `catch` | `catch (InvalidArgumentException $e) { echo $e->getMessage(); }` | Handles the specified failure type. |
| `finally` | `finally { echo "checked"; }` | Runs when leaving the try and catch sequence in its normal language control flow. |
| `exit` | `exit(2);` | Ends a PHP command-line program with status 2. Place this at the command boundary. |
| `die` | `die("invalid input");` | Another spelling of exit. A string is printed and the default exit status remains zero. Choose a numeric failure code in a CLI when callers need it. |

~~~php
<?php
try {
    $cents = -1;
    if ($cents < 0) {
        throw new InvalidArgumentException("negative");
    }
    echo "saved\n";
} catch (InvalidArgumentException $error) {
    echo $error->getMessage(), "\n";
} finally {
    echo "checked\n";
}
~~~

Expect `negative` followed by `checked`. Restore a nonnegative amount and expect `saved` followed by `checked`. Each path reports the same final observation.

~~~c
/* The function returns its status to the caller after normal cleanup. */
int status = check_amount(cents);
if (status == 0) status = save_amount(cents);
release_request();
return status;
~~~

~~~text
CHECK the amount
IF the amount is valid THEN try to save it
RELEASE the request in either path
RETURN the status
~~~

The C example uses project-specific helper names as placeholders. In a Umicom Bank or Trader CLI, return a failure status from the command boundary and keep native request handling callable. Test cleanup on a refused sample and on a saved sample. In PHP, a call to `exit` is a different control operation from returning or throwing. Check command termination rules before using it in reusable code. [PHP exceptions](https://www.php.net/manual/en/language.exceptions.php) · [PHP exit](https://www.php.net/manual/en/function.exit.php)

## Run the examples

1. Save the PHP example as `practice.php`. Keep the opening PHP tag. In a terminal with PHP available, run `php practice.php` and compare the output with the expected result above.
2. Open the C23 lab linked below and save it as `main.c`. From a terminal with GCC, run `gcc -std=c23 -Wall -Wextra -Wpedantic main.c -o native-keywords.exe`. In PowerShell run `.\native-keywords.exe` and find the `cleanup` row.
3. If the shell cannot find a compiler or PHP, start with the pseudocode and compare your predicted result with the examples.

[Course contents](index.md) · [Previous lesson · Choose between named implementations](09-choose-between-named-implementations.md) · [Next lesson · Stream values and read source markers](11-stream-values-and-read-source-markers.md) · [HTML edition](../../../courses/learning-php/lessons/10-release-a-request-after-an-error.html) · [Complete C23 lab](../../../labs/native/php-keyword-comparison/main.c)
