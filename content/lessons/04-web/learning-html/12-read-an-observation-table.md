<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-html/12-read-an-observation-table.md

PURPOSE:
Present records with a useful table

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Present records with a useful table

## Before you begin
You need the earlier page-structure lessons and a text editor. These are fictional records for learning HTML. They are not a recommended weight, a diagnosis or a treatment plan.

## Give rows and columns meaning
A table helps compare records that share the same fields. Its caption names the dataset. Column headings describe the values beneath them; a row heading identifies one observation.

~~~html
<table>
  <caption>Synthetic observations, mass in grams</caption>
  <thead>
    <tr><th scope="col">Date</th><th scope="col">Mass (g)</th>
        <th scope="col">Note</th></tr>
  </thead>
  <tbody>
    <tr><th scope="row">2024-02-28</th><td>80500</td><td>Fixture A</td></tr>
    <tr><th scope="row">2024-02-29</th><td>80250</td><td>Fixture B</td></tr>
  </tbody>
</table>
~~~

1. Identify the unit without relying on a colour or icon.
2. Read the second row independently of the first. Its date and mass remain understandable.
3. Add a third synthetic record using the same three columns.
4. Compare the source with the visible cells. Missing closing tags can produce a browser repair that differs from your intended structure.

## Expected result
Two initial observations produce two body rows. The caption and headings remain real text. No chart, prediction, sorting or filtering is implied by this static table.

## Exercise: represent absence honestly
Replace Fixture B with an empty note cell. Keep the mass unchanged. Then imagine a record whose mass is unavailable: write a design note describing how the product would represent that state. Do not insert zero just to make a numeric column look complete. The initial weight-log schema requires a known mass, so such an incomplete record is a draft rather than a submitted observation.

## Recovery
If a wide table is difficult to read on a small screen, preserve its semantics while reviewing the page's existing responsive styles. Do not turn the table into unrelated positioned text. If the row order is unexpected, inspect the data source and sorting contract; HTML does not infer chronological order.

The [HTML table specification](https://html.spec.whatwg.org/multipage/tables.html) describes captions, header cells and table structure. Test actual keyboard and assistive-technology behavior separately from reviewing the source.


[Course contents](index.md) · [Previous lesson](11-names-controls-and-submitted-values.md) · [Next lesson](13-display-untrusted-text-as-text.md)
