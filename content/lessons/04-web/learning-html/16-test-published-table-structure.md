<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-html/16-test-published-table-structure.md

PURPOSE:
Test published table structure with native C

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Test published table structure with native C

## Before you begin

Read the earlier observation-table lesson and keep the distinction between a manuscript and its published HTML edition clear. You need the Bits2Banking checkout, a C23 compiler, CMake and a disposable build directory. The exercise checks source markup; a browser and assistive technology are separate later checks.

## Reproduce a misleading success

A course can pass link checks and still lose its table during conversion. Consider this generated HTML:

~~~html
<p>| Name | Value | | --- | --- | | Limit | 64 |</p>
~~~

The file exists and the text is visible, but it contains one paragraph. Neither a route inventory nor a matching download hash establishes that it contains table cells. A hash proves byte identity, including the identity of an incorrectly generated page.

## State the output contract

For a simple authored comparison, use an actual table with column headers and a body:

~~~html
<table>
  <thead><tr><th scope="col">Name</th><th scope="col">Value</th></tr></thead>
  <tbody><tr><td>Limit</td><td>64</td></tr></tbody>
</table>
~~~

A real published page also supplies surrounding context, approved Umicom branding and its existing styles. This fragment isolates the conversion problem. It does not replace the caption, row-heading and responsive-layout considerations from the observation-table lesson.

## Read the native checker

Open tests/content_integrity/test_lesson_tables.c. The executable accepts a page path, a column count and a body-row count. It reads at most one mebibyte, refuses embedded zero bytes and checks that the file read and close both succeeded. It owns and frees its input buffer.

The checker hides complete HTML comments before looking for the canonical table shape. Otherwise a preserved old table in a source comment could satisfy a check while the visible output remained wrong. It then requires one table, a header group, a body group, one header row with scoped column cells, and the expected number of complete data rows.

This is deliberately a narrow contract for these authored pages. It recognizes exact lowercase tags, one table, plain data cells and nonempty cell contents. It is not a general HTML parser, sanitizer or accessibility validator. Valid pages using row headings, attributes on table elements, several tables or intentionally empty cells need a different documented contract.

## Run the regression workflow

From the Bits2Banking repository, configure and build in a disposable directory:

~~~powershell
cmake -S .\tests\content_integrity -B .\build\content-tables -G Ninja
cmake --build .\build\content-tables --target btb-lesson-tables-test
ctest --test-dir .\build\content-tables -R "^btb[.]education[.]lesson_tables[.]" --output-on-failure --no-tests=error
~~~

Run each command separately and stop on an error. The registered group checks the native fixtures and three comparison lessons. The executable fixtures include a flattened paragraph, a table present only in a comment, missing scoped headers, unequal column counts, an incomplete table and an empty cell. Correct current pages should pass their declared shapes; this expectation is not a claim about an unbuilt checkout.

## Try an independent mutation

1. Copy a comparison lesson to a disposable file.
2. Run btb-lesson-tables-test.exe with that file and its documented column and row counts.
3. Replace one data row with a plain paragraph and run it again. Expect exit code one.
4. Restore the row, then place the whole table inside an HTML comment. Expect refusal again.
5. Restore the original copy. A passing check should agree with a manual reading of the active source.

The checker uses exit code two for command, file or memory errors. An unreadable file is not the same finding as a readable page with a malformed table. Preserve the diagnostic and command when investigating a refusal.

## Verify what the source check cannot see

Open the repaired page in the intended browser when presentation qualification is available. Inspect zoom, narrow-screen behavior, keyboard navigation, header relationships and the approved logo and fonts. A native source pass cannot establish those observations. When a page changes, refresh its offline resource hash only after checking the new content; otherwise the download catalogue will describe stale bytes.

## Recovery and extension

If a legitimate redesign fails the narrow check, inspect the new markup and revise the contract with both accepting and refusing fixtures. Do not weaken it to file existence or a search for the word table. Keep earlier course material and preserved output available for review, while ensuring comments cannot stand in for current visible content.

[Course contents](index.md) · [Previous lesson](15-connect-field-errors-to-the-shared-contract.md)
