<!--
Umicom Bits2Banking
File: content/lessons/02-programming/shell-practice/01-navigate-and-quote.md

PURPOSE:
Practise a working directory, a three-line file and a path with a space.

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

# 1. Find and open a file with a space in its name

A terminal starts in a working directory. Confirm where you are before reading or writing. This example creates a fresh temporary directory, writes a short checklist and reads it back.

## Bash

1. Open Bash. Paste the block below. The setup stops if a temporary directory cannot be created or entered.
2. Read the path printed by `pwd`. It varies between sessions.
3. Check that the three lines printed below the path are `Approved`, `Pending` and `Approved`.

```bash
practice=$(mktemp -d) && cd "$practice" && {
    printf '%s\n' 'Approved' 'Pending' 'Approved' > 'closing notes.txt' &&
    pwd &&
    cat 'closing notes.txt'
}
```

In `cd "$practice"`, double quotes keep the value of the variable together as one argument. Single quotes in `'closing notes.txt'` keep the space in the literal name. The shell sends the name to `cat` as one argument.

## PowerShell 7

1. Open PowerShell 7. Paste the block below. The generated directory name keeps the exercise separate from earlier runs.
2. Read the path shown by `Get-Location`.
3. Check the same three lines below it.

```powershell
$practice = Join-Path ([System.IO.Path]::GetTempPath()) ('btb-shell-' + [guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $practice -ErrorAction Stop | Out-Null
Set-Location -LiteralPath $practice -ErrorAction Stop
Set-Content -LiteralPath 'closing notes.txt' -Value 'Approved', 'Pending', 'Approved' -Encoding utf8 -ErrorAction Stop
Get-Location
Get-Content -LiteralPath 'closing notes.txt'
```

The single quotes make the file name one argument. `-LiteralPath` tells the cmdlet to use the name exactly as written. If the file is missing, check the working directory again before repeating the setup.

[Course overview](index.md) · [Next lesson](02-compare-pipelines.md) · [Bash quoting reference](https://www.gnu.org/software/bash/manual/html_node/Quoting.html)
