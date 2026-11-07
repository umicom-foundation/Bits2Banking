<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-css/07-grid-columns-and-overflow.md

PURPOSE:
Explain the lesson: Understand grid columns and long content.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Understand grid columns and long content

## Prepare
Open a course page with the shared stylesheet and use developer tools. Find `.reading-shell` and `.feature-grid`. Reading and temporary style experiments need only a browser.

CSS Grid arranges children into rows and columns. The reading shell declares a fixed sidebar and a flexible content column:
~~~css
grid-template-columns: 262px minmax(0, 1fr);
~~~
The `fr` unit distributes remaining space. `minmax(0, 1fr)` allows the flexible track to shrink below its content's natural minimum width.

## Trace the constraint
1. Inspect the shell's available width.
2. Account for sidebar, gap and outer padding.
3. Inspect the remaining reading column.
4. Locate `min-width:0` on the reading panel.
5. Inspect how code blocks and tables handle horizontal overflow.

Long code should remain readable without forcing the whole page beyond the viewport. The stylesheet gives code blocks their own overflow behaviour.

## Exercise
In developer tools, temporarily replace `minmax(0,1fr)` with `1fr` and inspect a long unbroken line. Record the result rather than assuming it changes in every browser/content case. Restore the rule afterward.

Expected explanation: intrinsic content sizing can affect a grid's minimum dimensions.

## Check narrow screens
Find the responsive media-query rules and note when the arrangement changes. Test long navigation labels as well as short sample content. Layout problems often appear with real words, translated text or large fonts.

## Troubleshoot
If a page still overflows, identify the exact element in the inspector. Check images, tables and long inline code before changing unrelated grid settings. A local overflow rule is more understandable when it addresses the element that actually requires it.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/courses/assets/umicom-learning.css). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](06-understand-the-box-model.md) · [Next lesson](08-focus-print-and-reduced-motion.md)

