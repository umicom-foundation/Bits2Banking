<!--
Umicom Bits2Banking
File: content/lessons/04-web/practical-web-and-data-foundations/04-read-the-file-with-node.md

PURPOSE:
Read a local statement with Node.js in the Bits2Banking web and data course.

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

# Read a local statement with Node.js

[Course contents](index.md) · [Previous lesson · Check a record with TypeScript](03-check-a-record-with-typescript.md) · [Next lesson · Add posted cents in a spreadsheet](05-add-posted-cents-in-a-spreadsheet.md)

Use Node.js to read a practice text file and check values before adding cents.

## Understand what will happen

JavaScript can run inside a browser. Node.js also runs JavaScript on your computer, where built-in tools can read files. This example uses a file next to the program. It displays a total in the terminal, which is a window for reading and writing commands. No web service or real account data is needed.

The name `statement.json` must match the practice file from lesson one. Save the next example as `statement.mjs` in the same practice folder. The `.mjs` ending tells Node.js to treat the file as a module, so it can use `import` and wait for a reading operation.

## Read, check and total the entries

```javascript
import { readFile } from "node:fs/promises";

try {
  // Look beside this program even if the terminal starts elsewhere.
  const file = new URL("./statement.json", import.meta.url);
  const text = await readFile(file, "utf8");
  const report = JSON.parse(text);
  const entries = report?.entries;
  if (!Array.isArray(entries)) {
    throw new Error("Expected a list named entries");
  }

  let total = 0;
  for (const entry of entries) {
    // Protect the count before arithmetic. Only these states are in the lesson.
    if (!entry ||
        (entry.status !== "posted" && entry.status !== "pending") ||
        !Number.isSafeInteger(entry.cents)) {
      throw new Error("Expected a known status and whole cents");
    }
    if (entry.status === "posted") {
      const next = total + entry.cents;
      if (!Number.isSafeInteger(next)) {
        throw new Error("Posted total is too large");
      }
      total = next;
    }
  }
  console.log(`Posted: ${total} cents`);
} catch (error) {
  console.error(error.message);
  process.exitCode = 1;
}
```

`await` waits for file reading to finish. `JSON.parse` turns the text into data. `Number.isSafeInteger` checks that JavaScript can represent the amount exactly as a whole number. This calculator uses status and cents, so those are the entry fields it checks. The practice ID is for human reading.

```text
node statement.mjs
```

The terminal should show `Posted: 1750 cents`. Trace the changes in total on paper. Start at `0`, then write `2600`, then `1750`. The pending entry leaves the total at `1750`.

## Practise reading a refusal

In a practice copy, put quotes around `500` in the JSON file and run the program again. The output should say `Expected a known status and whole cents` because the new value is text. Remove the quotes after the check. If the terminal reports that it cannot find the JSON file, make sure `statement.json` is beside the program. A parser error means you should check quotes, commas and the matching braces.

## Connect to Umicom

Compare this small program with the native statement calculation. Both add posted amounts and leave pending amounts alone unless a practice rule explicitly includes them. In a Framework exercise, keep the calculation in a small function whose result you can check without opening a window.

- [Native statement calculations](../../../courses/native-statement-calculations/index.html)
- [Node.js file reading](https://nodejs.org/api/fs.html#fspromisesreadfilepath-options)

[Open the HTML edition](../../../courses/practical-web-and-data-foundations/lessons/04-read-the-file-with-node.html)
