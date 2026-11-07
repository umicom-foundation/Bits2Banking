<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-css/05-use-shared-theme-variables.md

PURPOSE:
Explain the lesson: Use shared theme variables.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Use shared theme variables

## Prepare a reading copy
Open an existing Bits2Banking course page and its stylesheet in an editor. Use the browser's developer tools for temporary changes. No C compiler is needed for this CSS exercise. Keep the original course files unchanged while experimenting.

A **custom property** is a named CSS value. The shared stylesheet declares values such as `--navy`, `--teal` and `--code` in `:root`. Rules refer to them through `var(...)`.

## Trace one value
1. Find the declaration of `--ink`.
2. Find the body rule that uses it for text.
3. Find `--body` and its use as the font family.
4. Temporarily change one value in developer tools.
5. Observe which elements change and which use their own rule.

The browser experiment disappears on reload unless you save a source change. That makes it useful for learning without producing accidental repository edits.

## Exercise
Create a table with property name, intended role and two consumers. Expected result: a small vocabulary of colour and typography roles, rather than unrelated values copied into every component.

A variable gives consistency, but its name does not prove adequate contrast. Check the actual foreground/background combination at the size used.

## Reuse branding
The site references the existing Umicom SVG asset. Changing a theme should not redraw the logo with text characters or substitute an invented icon. Preserve its transparent background and aspect ratio.

## Troubleshoot
If a variable appears ineffective, inspect the computed style and more specific rules. A later declaration can override an earlier one. Avoid adding repeated `!important` declarations before understanding the cascade.

For product work, keep shared design tokens and reusable presentation behaviour centralized so improvements can reach multiple clients.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/content/courses/assets/umicom-learning.css). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Next lesson](06-understand-the-box-model.md)


[Previous: Test a layout with long content](04-test-a-layout-with-long-content.md)
