<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-css/04-test-a-layout-with-long-content.md

PURPOSE:
  Present "Test a layout with long content" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Test a layout with long content

A layout that fits a short title may fail with a long file name or a narrow window. This lesson extends the course-library exercise by treating content size as an input to the layout.

Source to open: `Umicom-Bits2Banking/content/courses/assets/umicom-learning.css`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath 'content\courses\assets\umicom-learning.css'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' 'content/courses/assets/umicom-learning.css'
```

## Understand the idea

CSS describes how HTML boxes are presented. Available width, font size and content all affect the result. A breakpoint applies different rules at a chosen width; it cannot predict every word length. Overflow happens when content needs more space than its box. A useful layout lets readers reach the content without hiding controls.

```text
content length + text size + viewport width → layout → reachable reading and controls
```

## Work through the lab

1. Open the shared course stylesheet and find rules containing max-width, overflow and @media. Beside each, write which element it controls.
2. In a disposable copy of a course page, replace a short title with a long course title. Add a long unbroken sample file name inside a code block.
3. Open the copy in a browser and narrow the window. Check whether text wraps, code can scroll and navigation remains reachable. Repeat with the browser's text zoom increased.
4. Navigate using Tab. Record whether the focus outline stays visible around links. Keep the original page and stylesheet untouched while comparing alternatives.

## Expected result

Ordinary paragraphs should remain readable at narrow widths. Code may need its own horizontal scrolling region. The whole page should not require horizontal travel just to find the next lesson.

## If the result differs

If a rule has no effect, inspect its selector and which stylesheet the page loaded. If an overflow rule fixes one panel but clips focus outlines, adjust spacing or the scroll container instead of hiding overflow everywhere.

## Explain it yourself

Why is a fixed screenshot insufficient to qualify a responsive course page?

<details>
<summary>Worked explanation</summary>

It captures one width and one set of content. Long labels, keyboard focus and zoom can reveal failures that the initial image cannot show. Record those conditions alongside the screenshot.

</details>

## Use the idea in Umicom

Record inputs, expected outputs and refusal cases before extending the example. Reusable production behaviour belongs in Umicom Framework; applications translate user actions and show the service result. A traced example explains a contract. It does not establish that every application using a similar idea has been integrated or tested.

[HTML edition](../../../courses/learning-css/lessons/04-test-a-layout-with-long-content.html)

[Terminal and editor setup guide](../../learning-c/terminal-to-visual-studio.md)

[Previous lesson](03-a-flexible-course-library.md) · [Course contents](index.md)


[Next: Use shared theme variables](05-use-shared-theme-variables.md)
