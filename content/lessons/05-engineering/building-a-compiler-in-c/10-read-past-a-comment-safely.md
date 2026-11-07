<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/10-read-past-a-comment-safely.md

PURPOSE:
  Present "Read past a comment without crossing the input" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read past a comment without crossing the input

A compiler first separates source text into small pieces called tokens. This lesson follows the Umicom C lexer as it skips a comment. You will use character positions to explain why checking the end of the input must happen before reading another character.

Source to open: `umicom-c/src/lexer.c`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath '..\umicom-c\src\lexer.c'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' '../umicom-c/src/lexer.c'
```

## Understand the idea

A buffer is a region of memory. Its length tells us how many characters belong to the input; position tells us which character comes next. In this lexer, position may equal length when reading is complete, but it must not be used as an array index then. A two-character marker such as /* needs two available characters. The check length - position >= 2 is safe here because the loop already establishes that position is below length. A comment is ignored as a token, but its boundary still needs careful validation.

```text
Input:       / * x * /
Index:       0 1 2 3 4
Position:    0 -> 2 -> 3 -> 5
Length:      5
At position 5: check the end; do not read source[5].
```

## Work through the lab

1. Open umc_lex_next and find the end-of-input check above the comment handling. Draw five boxes for the characters in /*x*/ and number them 0 to 4. Set length to 5 and position to 0.
2. Follow the opening marker: position advances to 2. The x is not a closing marker, so position advances to 3. Two characters remain, allowing the lexer to inspect */. It advances to 5 and marks the comment closed.
3. Repeat with /*x. The loop reaches position 3 without finding a closing marker. The lexer reports UMC_SYNTAX_ERROR using the saved starting offset. Explain why returning a successful end token here would hide an incomplete program.
4. Now inspect // followed by text and a newline. Follow the line-comment loop until the newline and then the outer loop. Record why line and block comments use different stopping conditions. Do not change the production lexer during this reading exercise.

## Expected result

Your trace should stop exactly at length for a completed comment. An unfinished block comment should take the error path, with its opening position available for a useful diagnostic. The current lexer also rejects an embedded zero byte encountered within these comment loops.

## If the result differs

If your trace reaches length + 1, check whether you read the second marker character before testing the remaining length. If an error points to the end instead of the opening slash, inspect the saved start variable. When comparing a newer checkout, follow the actual branches rather than assuming its accepted language is unchanged.

## Explain it yourself

The input consists of /* followed immediately by the end of the buffer. How many characters remain after the opening marker, and which result should the current code return?

<details>
<summary>Worked explanation</summary>

After consuming two characters, zero remain. The inner loop cannot run, closed remains false, and UMC_SYNTAX_ERROR is returned at the saved opening offset. Nothing after the buffer needs to be read.

</details>

## Use the idea in Umicom

A source editor can use the diagnostic offset to highlight an unfinished comment. Umicom C owns its language parser; an IDE should display its diagnostic through shared document and problem services rather than creating a second parser with different rules.

[HTML edition](../../../courses/building-a-compiler-in-c/lessons/10-read-past-a-comment-safely.html)

[Terminal and editor setup guide](../../learning-c/terminal-to-visual-studio.md)

[Previous lesson](09-designing-a-language.md) · [Course contents](index.md) · [Next: Build a small programming-language project](11-project-a-small-language.md)

