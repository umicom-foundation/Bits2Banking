<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-php/03-count-text-at-the-right-boundary.md

PURPOSE:
  Present "Count text at the right boundary" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Count text at the right boundary

A text field has both bytes and characters. The PHP task validator uses two limits for different reasons. This lesson follows the order of those checks and the difference between accepting text and displaying it.

Source to open: `Umicom-Bits2Banking/content/labs/php-tasks/task_input.php`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath 'content\labs\php-tasks\task_input.php'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' 'content/labs/php-tasks/task_input.php'
```

## Understand the idea

UTF-8 represents a Unicode code point using one to four bytes. strlen counts bytes; mb_strlen with UTF-8 counts code points. A displayed symbol can contain several code points, so this is not a perfect count of visual symbols. The early 480-byte bound limits decoding work before checking a 120-code-point title.

```text
type → byte budget → decoder availability → valid UTF-8 → trimmed text → code-point budget
```

## Work through the lab

1. Find the is_string check. A submitted field can be an array in a crafted request, so type admission happens before string operations.
2. Trace the byte-size check, availability checks for mbstring, UTF-8 validation, trimming and the final character-count limit in order.
3. Make paper inputs: an empty string, spaces, a short plain title, an array and invalid UTF-8 bytes. Match each rejected input to the earliest applicable check.
4. Find the comment naming index.php as the HTML output boundary. Follow that file to see how a returned message becomes page text; accepting a string does not make it HTML-safe.

## Expected result

The validator returns an explanatory message for each refused case. A valid nonblank title within the limits returns Received task: followed by the trimmed text.

## If the result differs

If every title reports that validation is unavailable, enable the runtime's mbstring extension using the PHP installation guide. Do not remove the UTF-8 checks to hide the configuration problem. Escaping belongs where text is inserted into HTML.

## Explain it yourself

Why not cast an incoming array to a string and continue?

<details>
<summary>Worked explanation</summary>

Casting changes the input instead of proving it satisfies the contract. It can produce an unintended representation and warnings. Explicit rejection gives the caller a clear, predictable result.

</details>

## Use the idea in Umicom

Record inputs, expected outputs and refusal cases before extending the example. Reusable production behaviour belongs in Umicom Framework; applications translate user actions and show the service result. A traced example explains a contract. It does not establish that every application using a similar idea has been integrated or tested.

[HTML edition](../../../courses/learning-php/lessons/03-count-text-at-the-right-boundary.html)

[Terminal and editor setup guide](../../learning-c/terminal-to-visual-studio.md)

[Previous lesson](02-validation-and-html-output.md) · [Course contents](index.md)

