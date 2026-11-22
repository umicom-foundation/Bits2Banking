<!--
Umicom Bits2Banking
File: content/lessons/04-web/accessible-statement-review/02-filter-posted-rows-with-a-status-message.md

PURPOSE:
Teach Filter posted rows with a status message through original worked exercises.

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

# Filter posted rows with a status message

[Course contents](index.md) · [Previous: Build a readable statement table](01-build-a-readable-statement-table.md)

## What you will learn

Use a native checkbox to show only posted rows and announce the number of visible records.

## Start with all rows visible

Build on statement.html from the previous lesson. Add the controls immediately after the h1. Leave the checkbox disabled in the source. The script enables it once it can handle changes, so the unenhanced view remains readable.

```html
<p><label><input id="posted-only" type="checkbox" disabled>
  Show only posted rows</label></p>
<p id="review-status" role="status">3 rows shown.</p>
```

## Update the view from the checkbox

Place this script before the closing html tag, after the main element. The script reads the state stored with each row. The hidden property changes visibility. The status element receives plain text with the visible count.

```html
<script>
const postedOnly = document.getElementById("posted-only");
const status = document.getElementById("review-status");
const rows = document.querySelectorAll("#statement-rows tr");

function updateReview() {
  let visible = 0;
  for (const row of rows) {
    row.hidden = postedOnly.checked && row.dataset.state !== "posted";
    if (!row.hidden) visible += 1;
  }
  status.textContent = visible + " rows shown.";
}

postedOnly.addEventListener("change", updateReview);
updateReview();
postedOnly.disabled = false;
</script>
```

Reload and expect 3 rows shown. Press Tab to reach the checkbox and Space to select it. Two rows remain, the checkbox keeps focus, and the status reads 2 rows shown. Press Space again to restore all three rows.

## Practice and check your answer

Add a fourth row with data-state="pending", a new reference and an invented amount. Reload, select the checkbox again, then reload with scripting turned off.

**Worked answer**

With scripting enabled, the status updates from 4 rows shown to 2 rows shown. With scripting off, all four rows are visible and the checkbox remains disabled. Update the fallback status in the HTML to match the new row count.

## If the filter appears to do nothing

Check that every ID matches its spelling in the example and that the script follows the elements it uses. Open the browser console to read a reported error. Confirm that the row you expected to hide is marked pending in its data-state attribute.

[Read this lesson as HTML](../../../courses/accessible-statement-review/lessons/02-filter-posted-rows-with-a-status-message.html)

## Continue learning

- [Learning HTML](../../../courses/learning-html/index.html)
- [Learning CSS](../../../courses/learning-css/index.html)
- [Learning JavaScript](../../../courses/learning-javascript/index.html)

## Further reading

- [Tech Sustainify course catalogue](https://techsustainify.com/)
- [W3Schools HTML accessibility tutorial](https://www.w3schools.com/html/html_accessibility.asp)


[Course contents](index.md) · [Previous: Build a readable statement table](01-build-a-readable-statement-table.md)
