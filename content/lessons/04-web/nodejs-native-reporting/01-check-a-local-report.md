<!--
Umicom Bits2Banking
File: content/lessons/04-web/nodejs-native-reporting/01-check-a-local-report.md

PURPOSE:
Use Node.js to read one native JSON snapshot and verify the version, cents unit and stable row IDs.

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

# Check a local report

[Course contents](index.md) · [Next · Connect a known native producer](02-connect-a-known-native-producer.md) · [Browser edition](../../../courses/nodejs-native-reporting/lessons/01-check-a-local-report.html)

Use Node.js to read one native JSON snapshot and verify the version, cents unit and stable row IDs.

## Name the two jobs

Use fictional entries 101, 102 and 103 in this order. The C23 reporter counts posted entries 101 and 102. Their 2600 and −850 cents sum to 1750. Entry 103 contributes 500 cents only to the pending rows displayed on the page.

C validates the sample entries and calculates a checked 32-bit total. Node.js is a runtime for JavaScript outside the browser. Its boundary code reads the report, checks field types and produces a short summary. Keep all pricing and posting logic in C.

- [C23 statement reporter](../../../labs/native/web-statement-contract/statement-report.c)
- [Three-row practice snapshot](../../../labs/native/web-statement-contract/statement-report.json)
- [Empty practice snapshot](../../../labs/native/web-statement-contract/statement-report-empty.json)

## Write the boundary

```javascript
import { readFile } from "node:fs/promises";

function int32(value) {
  return Number.isInteger(value) && value >= -2147483648 &&
    value <= 2147483647;
}

export function decodeReport(text) {
  const report = JSON.parse(text);
  // Reject an incompatible envelope before accessing any rows.
  if (!report || report.version !== 1 || !Array.isArray(report.rows) ||
      report.rows.length > 256 || !int32(report.postedCents) ||
      !int32(report.postedCount) || report.postedCount < 0 ||
      report.postedCount > report.rows.length) {
    throw new Error("Incompatible statement envelope");
  }
  let lastId = 0;
  for (const row of report.rows) {
    if (!row || !int32(row.id) || row.id <= lastId || !int32(row.cents) ||
        !["posted", "pending"].includes(row.status)) {
      throw new Error("Invalid statement row");
    }
    lastId = row.id;
  }
  return report;
}

export async function readTrainingReport() {
  // Resolve this known fixture next to the module.
  const file = new URL("./statement-report.json", import.meta.url);
  return decodeReport(await readFile(file, "utf8"));
}
```

```javascript
import { readTrainingReport } from "./report-shape.mjs";

try {
  const report = await readTrainingReport();
  console.log(report.postedCount + " posted, " + report.postedCents + " cents");
} catch {
  // Write a brief error to stderr and keep stdout free of partial output.
  console.error("Training statement unavailable.");
  process.exitCode = 1;
}
```

1. Save the two code blocks as `report-shape.mjs` and `read-report.mjs`. A module is a file that exports values one other file can import.
2. Copy the snapshot beside those files as `statement-report.json`. In that practice folder, run `node read-report.mjs` if you choose to try the local example. Expect `2 posted, 1750 cents`.
3. Try the empty snapshot. Expect `0 posted, 0 cents` with success. Change `version` to 2 in a disposable copy. Expect Training statement unavailable on the error stream, with exit code 1.

This limited exercise reads known small fixtures. It validates the envelope and row shapes. The authenticity of a report and the correctness of its posted calculations require a separately trusted producer.

- [Node.js promise-based file reading](https://nodejs.org/api/fs.html#fspromisesreadfilepath-options)

## Follow another path

- [Practical Web and Data Foundations](../../../courses/practical-web-and-data-foundations/index.html)
- [React and Native Statement Data](../../../courses/react-native-statements/index.html)
- [Native statement lab on Umicom WebServer](../../../umicom/native-statement-web-lab.md)
- [Applied native courses](../../../start/applied-native-courses.md)

[Course contents](index.md) · [Next · Connect a known native producer](02-connect-a-known-native-producer.md) · [Browser edition](../../../courses/nodejs-native-reporting/lessons/01-check-a-local-report.html)
