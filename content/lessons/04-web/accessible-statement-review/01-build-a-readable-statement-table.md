<!--
Umicom Bits2Banking
File: content/lessons/04-web/accessible-statement-review/01-build-a-readable-statement-table.md

PURPOSE:
Teach Build a readable statement table through original worked exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom">
</picture>

# Build a readable statement table

[Course contents](index.md) · [Next: Filter posted rows with a status message](02-filter-posted-rows-with-a-status-message.md)

## What you will learn

Describe a statement as a captioned table with explicit column headers and inspect it in a narrow window.

## Keep the amount and state together

The table shows transaction references, signed cents and the posted state. A caption names the table. Header cells with scope="col" associate a column’s name with its data. The state appears as text so colour is never the only clue.

## Create the local page

Save the following as statement.html in a practice folder and open it in your browser. This is an educational HTML example. It has no account login, data connection or server requirement.

```html
<!doctype html>
<html lang="en">
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Training statement</title>
<style>
body { font-family: "Segoe UI", sans-serif; margin: 1rem; }
.statement-region { overflow-x: auto; }
.statement-region:focus-visible { outline: 3px solid #16716c; }
table { border-collapse: collapse; }
th, td { border: 1px solid #52636f; padding: .5rem; }
td.amount { text-align: end; font-variant-numeric: tabular-nums; }
</style>
<main>
  <h1>Training statement</h1>
  <div class="statement-region" role="region"
       aria-labelledby="reserve-caption" tabindex="0">
    <table>
      <caption id="reserve-caption">Reserve account movements</caption>
      <thead>
        <tr><th scope="col">Reference</th><th scope="col">Cents</th>
            <th scope="col">State</th></tr>
      </thead>
      <tbody id="statement-rows">
        <tr data-state="posted"><td>101</td><td class="amount">2600</td><td>Posted</td></tr>
        <tr data-state="posted"><td>102</td><td class="amount">-850</td><td>Posted</td></tr>
        <tr data-state="pending"><td>103</td><td class="amount">500</td><td>Pending</td></tr>
      </tbody>
    </table>
  </div>
</main>
</html>
```

Expect all three rows and their state labels. Press Tab to focus the table’s scroll region and look for its outline. Make the browser narrower and confirm the references and amounts stay next to their own state.

## Practice and check your answer

Hide the stylesheet temporarily by removing the style block in a practice copy. What information still identifies an amount and its state?

**Worked answer**

The caption and header cells still describe the table. Each row still has its reference, amount and state text. Styling can improve visual scanning while the markup still communicates those relationships.

[Read this lesson as HTML](../../../courses/accessible-statement-review/lessons/01-build-a-readable-statement-table.html)

## Continue learning

- [Learning HTML](../../../courses/learning-html/index.html)
- [Learning CSS](../../../courses/learning-css/index.html)
- [Learning JavaScript](../../../courses/learning-javascript/index.html)

## Further reading

- [Tech Sustainify course catalogue](https://techsustainify.com/)
- [W3Schools HTML accessibility tutorial](https://www.w3schools.com/html/html_accessibility.asp)


[Course contents](index.md) · [Next: Filter posted rows with a status message](02-filter-posted-rows-with-a-status-message.md)
