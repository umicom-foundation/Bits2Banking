<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-cpp/04-understand-append-and-repeated-save.md

PURPOSE:
  Present "Understand append and repeated saves" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Understand append and repeated saves

A successful save does not tell us whether a file was replaced or extended. The existing notes program opens its output in append mode. We will predict what repeated saves mean before deciding what behaviour a user needs.

Source to open: `Umicom-Bits2Banking/content/labs/cpp-notes/notes.cpp`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath 'content\labs\cpp-notes\notes.cpp'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' 'content/labs/cpp-notes/notes.cpp'
```

## Understand the idea

std::ofstream represents an output file stream. std::ios::app asks it to append output at the end of the file. The vector keeps the notes collected by Add in memory. Save visits every stored note each time it is called; it does not clear the vector or remember which entries were already written. That behaviour is appropriate to investigate, rather than assume that a second save is harmless.

```text
memory: [note A, note B]
first Save:  file [A, B]
second Save: file [A, B, A, B]
```

## Work through the lab

1. Read Add and list the two messages inserted by main. An empty string is ignored; a string containing spaces is not empty.
2. Find std::ios::app in Save. On paper draw an empty notes.txt and append the two lines in program order.
3. Draw a second call to Save on the same journal. Append both lines again. Compare this with a replace-the-document operation.
4. In a personal copy of the lab, repeat Save and inspect the chosen output file. Use a disposable folder so the example cannot append to a real notes file. Record line count before and after.

## Expected result

Two successful saves of the same two-note journal append four lines in total. The stream check reports write success, not whether duplication was intended.

## If the result differs

If the file seems missing, inspect the program's working directory: notes.txt is relative. If Save returns false, inspect the directory and permissions before repeating. An earlier partial write may still exist after a later error.

## Explain it yourself

Specify a safer user-facing contract for a Save command and a separate Append to journal command.

<details>
<summary>Worked explanation</summary>

Save can replace the selected document using a reviewed atomic-write service. Append can explicitly add entries and report their identity. Both need a user-selected location and clear failure handling; changing only the button label is insufficient.

</details>

## Use the idea in Umicom

Record inputs, expected outputs and refusal cases before extending the example. Reusable production behaviour belongs in Umicom Framework; applications translate user actions and show the service result. A traced example explains a contract. It does not establish that every application using a similar idea has been integrated or tested.

[HTML edition](../../../courses/learning-cpp/lessons/04-understand-append-and-repeated-save.html)

[Terminal and editor setup guide](../../learning-c/terminal-to-visual-studio.md)

[Previous lesson](03-check-a-file-operation.md) · [Course contents](index.md)

[Continue: Call an existing C model from C++](05-call-a-framework-c-boundary.md)
