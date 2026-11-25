<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/121-keep-the-last-accepted-script-value.md

PURPOSE:
Keep the last accepted script value

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Keep the last accepted script value

Imagine keeping a tally on paper. You write down a value after checking it. When a proposed change fails, your last checked value is still on the page. The `umicom-c script` command lets you try the same idea with a signed integer.

## Build up a value one line at a time

Open a terminal with the current Umicom C tool and run `umicom-c script`. Enter each line and press Enter.

~~~c
signed total = 2;
total *= 21;
return total;
~~~

Expect `ok`, `ok`, then `42`. `*=` multiplies the current value by 21 and stores the answer back under `total`. In a script session, `return total;` displays the value and leaves the session open. A **session** is one run of the command. It remembers the names and values accepted in that run. When you finish, send end of input. In many Unix terminals this is Ctrl+D. In a Windows console use Ctrl+Z followed by Enter.

## Predict what happens on a bad line

Start a fresh session for this example. Keep both assignments and their braces together on the second physical line. The braces group them into one submission.

~~~c
int total = 42;
{ total = 0; total = 1 / 0; }
return total;
~~~

1. After line 1, write `42` in a box labelled **last accepted total**. The command shows `ok`.
2. On a separate piece of paper, write the proposed value `0` from the first assignment on line 2. The next assignment asks for division by zero, so the submission fails as a whole. Cross out the proposed value on the separate paper. The accepted box still holds `42`.
3. For terminal input, line 3 still runs. It reads the accepted box and shows `42`. This is a new read of the existing value. When the input ends, the command still reports failure because line 2 was refused.

**Rollback** means discarding the changes attempted by the failed submission. The script engine keeps completed lines and publishes a new value only after the entire current line succeeds. The virtual machine slice from the earlier course lesson uses a different unit of work: it can report the instructions completed before a fault. Here the contract covers the script session's saved locals.

~~~text
FOR each input line
  try the line using the last accepted values
  IF the line succeeds
    keep its completed changes and show its reply
  ELSE
    keep the last accepted values and show a diagnostic
    IF reading a named file, finish with status 1
  END IF
END FOR
finish with status 1 if any line failed, otherwise status 0
~~~

## Send the same lines by two routes

Save the second example as a plain-text file named `total.ucs` in your working folder. In PowerShell, run the following commands one pair at a time. `Get-Content` reads the file and the pipe sends its lines as **standard input**, the stream the terminal normally supplies. The second command passes the filename itself. `$LASTEXITCODE` shows the program's exit status.

~~~powershell
Get-Content -LiteralPath .\total.ucs | umicom-c script --stdin
$LASTEXITCODE

umicom-c script .\total.ucs
$LASTEXITCODE
~~~

| How the same text reaches the command | Ordinary output | Diagnostic | Exit status |
| --- | --- | --- | --- |
| Standard input | `ok`, then `42` | Line 2 | 1 |
| Named file | `ok` | Line 2 | 1 |

The ordinary output column lists the command's successful replies. The diagnostic goes to the separate error stream. Both streams can appear in one terminal. The named file stops at its first error, so its final `return` is never reached. This is **fail-fast** behavior. Change `1 / 0` to `1 / 1` in your paper trace. Predict the replies for both routes. Each should now give `ok`, `ok`, then `1` and exit with status 0 because the whole second line succeeds.

If you are writing a complete program with `main`, use `umicom-c interpret source.c --step` to follow its statements. You can use Umicom Studio to edit the practice file and compare the two script runs in a terminal. The `script` command uses the checked integer language profile, with one complete submission on each line.

[Course contents](index.md) · [Previous lesson · Read equivalent signed local types](120-read-equivalent-signed-local-types.md) · [Related lesson · Preserve progress when a slice fails](80-preserve-progress-when-a-slice-fails.md) · [Related lesson · Separate admission checks from source steps](119-separate-admission-checks-from-source-steps.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/121-keep-the-last-accepted-script-value.html)

[Next lesson · Store a true-or-false value in a local](122-store-a-true-or-false-value-in-a-local.md)
