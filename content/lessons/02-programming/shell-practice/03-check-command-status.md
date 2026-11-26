<!--
Umicom Bits2Banking
File: content/lessons/02-programming/shell-practice/03-check-command-status.md

PURPOSE:
Recognise command completion, missing data and missing-file errors in Bash and PowerShell.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom Foundation">
</picture>

# 3. Check what happened

An empty screen can mean there were no matches. It can also mean the command could not read its input. Use a known example to tell the difference. Keep working in the temporary directory from [lesson 1](01-navigate-and-quote.md).

## Bash

1. Search for a line that the checklist does not contain.
2. Observe that `grep` prints no matching lines.
3. Read its exit status immediately. The example captures it before another command can change it.

```bash
grep -x 'Needs review' 'closing notes.txt'
status=$?
printf 'Search exit status %s\n' "$status"
```

Expect `Search exit status 1`. Run the same example with `Approved` and expect two matching lines and status `0`. Run it with a missing path such as `'missing notes.txt'` to see an error and a status greater than `1`. These meanings belong to `grep`.

Keep the `grep` command on its own for this check. In an ordinary Bash pipeline, `$?` commonly reports the last command's status. A pipeline that ends in `wc` can finish with status `0` even when `grep` found no lines. Bash's `pipefail` option changes which failure a pipeline reports.

## PowerShell 7

1. Check the existing file and save the truth value.
2. Repeat with a missing file. This example suppresses the known error message so the two truth values are easy to compare.

```powershell
Get-Item -LiteralPath 'closing notes.txt' -ErrorAction SilentlyContinue
$present = $?
Get-Item -LiteralPath 'missing notes.txt' -ErrorAction SilentlyContinue
$missing = $?
$present
$missing
```

The existing file's information appears first. Expect `True` and `False` on the final two lines. Capture `$?` directly after the command you intend to check when troubleshooting your own results.

PowerShell records native executable statuses in `$LASTEXITCODE`. Try a child PowerShell process that exits with a deliberately chosen number.

```powershell
pwsh -NoProfile -NonInteractive -Command 'exit 7'
$nativeStatus = $LASTEXITCODE
$nativeStatus
```

Expect `7`. If the command is unavailable, review the [PowerShell setup steps](../../../simple-steps/powershell-setup.md) before trying again.

[Previous lesson](02-compare-pipelines.md) · [Course overview](index.md) · [GNU grep exit status](https://www.gnu.org/software/grep/manual/html_node/Exit-Status.html) · [PowerShell automatic variables](https://learn.microsoft.com/en-us/powershell/module/microsoft.powershell.core/about/about_automatic_variables)
