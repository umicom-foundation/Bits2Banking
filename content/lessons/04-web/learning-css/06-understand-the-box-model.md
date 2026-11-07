<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-css/06-understand-the-box-model.md

PURPOSE:
Explain the lesson: Understand content, padding, border and margin.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Understand content, padding, border and margin

## Set up
Open a Bits2Banking course page and its shared stylesheet. Use browser developer tools to inspect a lesson card or reading panel. The page is the real example; no additional application or build is required.

A rendered element occupies a **box**. From inside outward, its relevant parts are content, padding, border and margin. Padding separates content from its border. Margin separates the box from neighbouring boxes.

## Inspect a panel
1. Select a `.reading` element.
2. Find its padding, border and width rules.
3. Locate the global `box-sizing:border-box` rule.
4. Temporarily increase one padding value.
5. Observe the remaining space for the text.

With border-box sizing, the specified box width includes padding and border. Margin still contributes outside that box.

## Draw the measurement
Sketch nested rectangles for content, padding and border, then mark margin outside. Label a hypothetical 300-pixel box with 20 pixels padding on each side and 1-pixel borders. Its inner content width is 258 pixels.

**Exercise:** explain why adding large padding to a narrow column can make code lines require horizontal scrolling. Expected answer: the available content area becomes smaller even though the outer panel may keep the same width.

## Check responsiveness
Resize the browser and inspect long headings, code and tables. Do not use a single screenshot to conclude that the layout is usable at every width.

## Recover
If neighbouring panels overlap, inspect their computed widths, minimum sizes, padding and overflow. Reducing every font is not a reliable first repair. Identify which box cannot fit and decide whether it should wrap, scroll or change arrangement.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/courses/assets/umicom-learning.css). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](05-use-shared-theme-variables.md) · [Next lesson](07-grid-columns-and-overflow.md)

