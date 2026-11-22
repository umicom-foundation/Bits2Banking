<!--
Umicom Bits2Banking
File: content/lessons/04-web/nodejs-native-reporting/02-connect-a-known-native-producer.md

PURPOSE:
Let a local Node.js adapter call the reviewed C reporter with no shell and reject incomplete results.

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

# Connect a known native producer

[Course contents](index.md) · [Previous · Check a local report](01-check-a-local-report.md) · [Next · Diagnose a refused or empty result](03-diagnose-a-refused-or-empty-result.md) · [Browser edition](../../../courses/nodejs-native-reporting/lessons/02-connect-a-known-native-producer.html)

Let a local Node.js adapter call the reviewed C reporter with no shell and reject incomplete results.

## Trace what crosses the boundary

The operator chooses a known local executable built from the course source. The process receives a fixed list of arguments. Its standard output is used only if the command succeeds and the JSON parser and shape checks accept it. An exit code is a number that tells the caller whether work succeeded.

```javascript
import { execFile } from "node:child_process";
import { isAbsolute } from "node:path";
import { promisify } from "node:util";
import { decodeReport } from "./report-shape.mjs";

const runFile = promisify(execFile);

try {
  const producer = process.argv[2];
  if (!producer || !isAbsolute(producer))
    throw new Error("Set the approved native executable path");

  // The exercise uses a fixed argument list and a bounded result.
  const { stdout } = await runFile(producer, [], {
    shell: false, encoding: "utf8", maxBuffer: 16384,
    timeout: 3000, windowsHide: true,
  });
  const report = decodeReport(stdout);
  console.log(report.postedCount + " posted, " + report.postedCents + " cents");
} catch {
  console.error("Training statement unavailable.");
  process.exitCode = 1;
}
```

## Prepare an optional local run

1. Place the C source and `report-shape.mjs` together in a practice folder. Save the adapter as `call-report.mjs`.
2. Open a configured PowerShell 7 window where `gcc` denotes your trusted C toolchain. Compile with `gcc -std=c23 -Wall -Wextra -Werror statement-report.c -o statement-report.exe`. Stop if the compiler fails.
3. With your own reviewed result, try `node call-report.mjs (Resolve-Path ./statement-report.exe).Path`. Expect `2 posted, 1750 cents`.
4. Read `$LASTEXITCODE` before another native command. A missing approved file or an incomplete result should produce the documented unavailable message and exit code 1. If security software blocks the file, stop the exercise and complete the paper trace.

The absolute path checks how the operator specified the command. It does not establish trust by itself. Keep the executable choice under workspace control and outside any future browser request input. The timeout and buffer limit are classroom bounds for the adapter.

For an Umicom Command practice exercise, specify the executable, argument list, expected output and exit policy for a read-only test runner. Node.js is the adapter in this course because its runtime owns the process API.

- [Node.js execFile API](https://nodejs.org/api/child_process.html#child_processexecfilefile-args-options-callback)
- [C23 statement reporter](../../../labs/native/web-statement-contract/statement-report.c)

## Follow another path

- [Practical Web and Data Foundations](../../../courses/practical-web-and-data-foundations/index.html)
- [React and Native Statement Data](../../../courses/react-native-statements/index.html)
- [Native statement lab on Umicom WebServer](../../../umicom/native-statement-web-lab.md)
- [Applied native courses](../../../start/applied-native-courses.md)

[Course contents](index.md) · [Previous · Check a local report](01-check-a-local-report.md) · [Next · Diagnose a refused or empty result](03-diagnose-a-refused-or-empty-result.md) · [Browser edition](../../../courses/nodejs-native-reporting/lessons/02-connect-a-known-native-producer.html)
