<!--
Umicom Bits2Banking
File: content/lessons/04-web/practical-web-and-data-foundations/02-put-rows-on-a-web-page.md

PURPOSE:
Put the entries on a web page in the Bits2Banking web and data course.

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

# Put the entries on a web page

[Course contents](index.md) · [Previous lesson · Read a statement as JSON](01-read-a-statement-as-json.md) · [Next lesson · Check a record with TypeScript](03-check-a-record-with-typescript.md)

Use HTML for a labelled table and JavaScript to add a row through the browser's document objects.

## Mark the parts a reader needs

A web browser opens an HTML file as a page. A table uses a caption for its name, column headings for what each value means and one row per entry. JavaScript is a language that can change the visible page after it opens.

The browser builds an internal representation of the page called the Document Object Model, or DOM. JavaScript can ask for an element by its `id`. Here `entries` names the table body, where the data rows go.

## Make a small complete page

Copy the example into a practice file named `statement.html` and open that file in a browser. Keep your existing lessons and use a separate folder for this experiment.

```html
<!doctype html>
<html lang="en">
<meta charset="utf-8">
<title>Practice statement</title>
<h1>Practice statement</h1>
<table>
  <caption>Reserve changes in cents</caption>
  <thead>
    <tr><th scope="col">Status</th><th scope="col">Cents</th></tr>
  </thead>
  <tbody id="entries"></tbody>
</table>
<script>
  const entries = [
    {status: "posted", cents: 2600},
    {status: "posted", cents: -850},
    {status: "pending", cents: 500}
  ];

  // The table owns its data rows. Add plain text under its headings.
  const table = document.getElementById("entries");
  for (const entry of entries) {
    const row = table.insertRow();
    row.insertCell().textContent = entry.status;
    row.insertCell().textContent = String(entry.cents);
  }
</script>
</html>
```

The square brackets hold three entries. Read `for (const entry of entries)` as “take the next entry, one at a time”. The code adds a row, then fills in status and cents. `String` turns a number into display text. `textContent` puts text in the cell so the browser leaves it as text.

## Trace and change one row

Before running it, say which entry will appear in the middle row. The answer is `posted`, `-850`. Change the last status from `pending` to `posted`, save and reload. The last row should say `posted` and `500`.

If all you see is a blank table, check that `id="entries"` matches the exact name passed to `getElementById` and that the script follows the table. If the browser shows the source as plain text, check the filename ends in `.html`.

## Connect to Umicom

A list in a Framework application also needs clear headings and separately named data. Try the complete browser exercise, then compare its table with the Umicom C form. The form sends a number to WebServer. This page builds rows from its own practice values.

- [Accessible Statement Review](../../../courses/accessible-statement-review/index.html)
- [Umicom WebServer practice form](../../../labs/statement-cvm-web/index.html)
- [DOM text-content rules](https://dom.spec.whatwg.org/#dom-node-textcontent)

[Open the HTML edition](../../../courses/practical-web-and-data-foundations/lessons/02-put-rows-on-a-web-page.html)
