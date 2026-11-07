<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-css/08-focus-print-and-reduced-motion.md

PURPOSE:
Explain the lesson: Read focus, print and reduced-motion styles.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read focus, print and reduced-motion styles

## Prepare
Use an existing Bits2Banking course page in a browser. Open its shared stylesheet and locate `:focus-visible`, `@media print` and `prefers-reduced-motion`. These rules describe different ways the same lesson is used.

## Follow keyboard focus
Press Tab and watch which control receives focus. The stylesheet draws an outline for links, buttons and summaries. A focus indicator helps a person know where keyboard activation will occur.

Find the skip link. It is positioned outside ordinary view until focused, then becomes visible. Check that its destination exists in the page.

## Inspect printing
Open print preview. Observe whether navigation is hidden, code wraps appropriately and content remains legible. Printing has different space constraints from a scrolling screen. A print stylesheet cannot guarantee that every long table fits without inspection.

## Inspect motion preference
The stylesheet changes smooth scrolling to automatic scrolling for reduced-motion preference. This preference can be emulated in browser tools or set in the operating system. Record how you tested it.

## Exercise
Write one expected/observed row for keyboard focus, skip navigation, print preview and reduced motion. If one was not checked, mark it unexecuted.

## Recover
An invisible focus outline may be clipped by an ancestor's overflow or overridden by another rule. Inspect the computed style and surrounding boxes. Avoid removing focus indicators merely because they differ from a mouse-hover appearance.

These presentation checks support the lesson's usability. They do not replace verifying that links lead to the intended course, code remains copyable and the associated practical example behaves correctly.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/courses/assets/umicom-learning.css). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](07-grid-columns-and-overflow.md)

