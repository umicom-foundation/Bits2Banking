<!--
Umicom Bits2Banking
File: content/lessons/04-web/bootstrap-native-statements/01-lay-out-a-readable-statement-table.md

PURPOSE:
Read Bootstrap CSS classes alongside table semantics and the original native cents total.

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

# Lay out a readable statement table

[Course contents](index.md) · [Next · Export the page from C23](02-export-the-page-from-c.md) · [Browser edition](../../../courses/bootstrap-native-statements/lessons/01-lay-out-a-readable-statement-table.html)

Read Bootstrap CSS classes alongside table semantics and the original native cents total.

## Draw the table before styling it

Use fictional entries 101, 102 and 103 in this order. The C23 reporter counts posted entries 101 and 102. Their 2600 and −850 cents sum to 1750. Entry 103 contributes 500 cents only to the pending rows displayed on the page.

A caption names a table. Column headers describe the values below them. A row header gives one row a distinct name. A CSS class is a label a stylesheet can use to change appearance. Bootstrap classes add layout while these HTML roles explain the data.

```html
<div class="table-responsive" tabindex="0" role="region" aria-label="Statement rows">
  <table class="table table-striped">
    <caption>Fictional statement entries</caption>
    <thead><tr><th scope="col">Entry</th><th scope="col">Amount in cents</th>
      <th scope="col">State</th></tr></thead>
    <tbody>
      <tr><th scope="row">101</th><td class="text-end">2600</td><td>Posted</td></tr>
      <tr><th scope="row">102</th><td class="text-end">-850</td><td>Posted</td></tr>
      <tr><th scope="row">103</th><td class="text-end">500</td><td>Pending</td></tr>
    </tbody>
  </table>
</div>
```

1. Read the column names on paper, then find the negative row. Record entry 102 as −850 cents.
2. If you try the optional preview, put the fragment inside your existing local practice page with Bootstrap CSS linked. Read from a narrow screen and use the focusable statement region to check access to each column.
3. Temporarily omit the stylesheet in your practice copy. The table should still name columns and show Pending as text. A successful CSS appearance and a successful semantic check are separate observations.

## Apply it to Umicom WebServer

A read-only Bank or Trader report should expose the same cents, labels and IDs to both a table and an accessible text view. Keep the native snapshot as the source of those values.

- [Bootstrap 5.3 table classes](https://getbootstrap.com/docs/5.3/content/tables/)
- [Accessible tables tutorial](https://www.w3.org/WAI/tutorials/tables/)
- [Three-row practice snapshot](../../../labs/native/web-statement-contract/statement-report.json)

## Follow another path

- [Learning Bootstrap](../../../courses/learning-bootstrap/index.html)
- [Native Statement Calculations](../../../courses/native-statement-calculations/index.html)
- [React and Native Statement Data](../../../courses/react-native-statements/index.html)
- [Native statement lab on Umicom WebServer](../../../umicom/native-statement-web-lab.md)
- [Applied native courses](../../../start/applied-native-courses.md)

[Course contents](index.md) · [Next · Export the page from C23](02-export-the-page-from-c.md) · [Browser edition](../../../courses/bootstrap-native-statements/lessons/01-lay-out-a-readable-statement-table.html)
