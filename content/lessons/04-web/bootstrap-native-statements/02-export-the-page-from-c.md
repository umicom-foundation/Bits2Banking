<!--
Umicom Bits2Banking
File: content/lessons/04-web/bootstrap-native-statements/02-export-the-page-from-c.md

PURPOSE:
Use the shared native producer to generate a static, branded HTML report from admitted fictional records.

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

# Export the page from C23

[Course contents](index.md) · [Previous · Lay out a readable statement table](01-lay-out-a-readable-statement-table.md) · [Next · Display native validation feedback](03-display-native-validation-feedback.md) · [Browser edition](../../../courses/bootstrap-native-statements/lessons/02-export-the-page-from-c.html)

Use the shared native producer to generate a static, branded HTML report from admitted fictional records.

## Follow a record into output

The C program checks ascending positive IDs, defined states and the signed 32-bit running sum. A valid result feeds either the JSON writer or the HTML writer. The HTML helper only inserts integers and a status from an application-owned list. A program that adds customer names or messages would also need an HTML escaping boundary.

- [C23 statement reporter](../../../labs/native/web-statement-contract/statement-report.c)
- [Three-row practice snapshot](../../../labs/native/web-statement-contract/statement-report.json)
- [Empty practice snapshot](../../../labs/native/web-statement-contract/statement-report-empty.json)

## Prepare an optional local practice folder

1. Copy `statement-report.c` into your practice folder. Find the approved logo, icon and branding stylesheet in the Bits2Banking `content/assets/branding` directory.
2. Copy those three files to a new `assets` subfolder. Place an approved local Bootstrap 5.3 minified stylesheet there as `bootstrap.min.css`.
3. Open PowerShell 7 in the practice folder with your configured C23 toolchain. The following commands compile the example and create a preview only after successful output.

```powershell
$brandAssets = 'C:\umicom\Umicom-Bits2Banking\content\assets\branding'
New-Item -ItemType Directory -Path ./assets -Force | Out-Null
Copy-Item -LiteralPath "$brandAssets/umicom-wordmark.svg",
    "$brandAssets/umicom.ico","$brandAssets/umicom-brand.css" -Destination ./assets/
gcc -std=c23 -Wall -Wextra -Werror statement-report.c -o statement-report.exe
if ($LASTEXITCODE -ne 0) { throw 'Report compiler refused the source.' }
$previewLines = & ./statement-report.exe --html
if ($LASTEXITCODE -ne 0) { throw 'Report generation failed.' }
$previewLines | Set-Content -LiteralPath ./report-preview.html -Encoding utf8NoBOM
```

If protection software blocks the practice executable, stop and use the paper trace. The expected heading is Synthetic statement and the paragraph reads `Posted total: 1750 cents in 2 entries.`. The file contains rows 101, 102 and 103, a Bootstrap CSS link, the logo and the icon.

## Identify the failure owner

- Missing CSS changes presentation. It should leave all three rows and status text available.
- A refused calculation produces a diagnostic and a nonzero program exit before any successful preview is written.
- An output write error comes from the file or console writer. Capture its failure and preserve the last accepted preview.

For an Umicom WebServer exercise, document the static folder as a serving boundary. The native program here produces the file offline. The existing Framework example can serve compatible static resources after owner qualification.

- [Native statement lab on Umicom WebServer](../../../umicom/native-statement-web-lab.md)
- [Bootstrap 5.3 table classes](https://getbootstrap.com/docs/5.3/content/tables/)

## Follow another path

- [Learning Bootstrap](../../../courses/learning-bootstrap/index.html)
- [Native Statement Calculations](../../../courses/native-statement-calculations/index.html)
- [React and Native Statement Data](../../../courses/react-native-statements/index.html)
- [Native statement lab on Umicom WebServer](../../../umicom/native-statement-web-lab.md)
- [Applied native courses](../../../start/applied-native-courses.md)

[Course contents](index.md) · [Previous · Lay out a readable statement table](01-lay-out-a-readable-statement-table.md) · [Next · Display native validation feedback](03-display-native-validation-feedback.md) · [Browser edition](../../../courses/bootstrap-native-statements/lessons/02-export-the-page-from-c.html)
