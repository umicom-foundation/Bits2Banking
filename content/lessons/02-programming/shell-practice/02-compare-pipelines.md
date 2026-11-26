<!--
Umicom Bits2Banking
File: content/lessons/02-programming/shell-practice/02-compare-pipelines.md

PURPOSE:
Count matching text lines and inspect named properties on PowerShell file objects.

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

# 2. Filter lines and file properties

Continue in the directory from [lesson 1](01-navigate-and-quote.md). The checklist contains two identical `Approved` lines. Keep the capital letter just as it appears in the file so that each shell counts the same entries.

## Bash

```bash
grep -x 'Approved' 'closing notes.txt' | wc -l
```

1. `grep -x` sends each whole line that matches `Approved` through the pipe.
2. The program on the right, `wc -l`, counts the newline characters it receives.
3. Read the result `2`. Some versions show a few spaces before the number.

## PowerShell 7

```powershell
Get-Content -LiteralPath 'closing notes.txt' |
    Where-Object { $_ -ceq 'Approved' } |
    Measure-Object |
    Select-Object -ExpandProperty Count
```

1. `Get-Content` supplies the lines as strings. `$_` means the line currently being checked.
2. `-ceq` compares the whole string with case-sensitive equality.
3. `Measure-Object` counts the matches. The final stage reads only its `Count` property. Expect `2`.

Try the next command in the same PowerShell session.

```powershell
Get-ChildItem -File |
    Where-Object { $_.Extension -eq '.txt' } |
    Select-Object -ExpandProperty Name
```

Here `Get-ChildItem` provides file objects. Each value carries named properties, including `Extension` and `Name`. The filter checks the extension before the final stage displays the name `closing notes.txt`.

**Practise.** Replace `Approved` with `Pending` in each shell's first pipeline. Predict the result before you run it. The checklist contains one matching line.

[Previous lesson](01-navigate-and-quote.md) · [Next lesson](03-check-command-status.md) · [Bash pipelines](https://www.gnu.org/software/bash/manual/html_node/Pipelines.html) · [PowerShell pipelines](https://learn.microsoft.com/en-us/powershell/module/microsoft.powershell.core/about/about_pipelines)
