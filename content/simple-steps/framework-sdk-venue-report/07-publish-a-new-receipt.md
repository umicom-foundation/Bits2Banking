<!--
Bits2Banking
File: content/simple-steps/framework-sdk-venue-report/07-publish-a-new-receipt.md

PURPOSE:
Use exclusive file creation and inspect input failures before output is opened.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Create a receipt without overwriting earlier work

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Use a directory you control. The application takes an absolute path for the CSV and a separate absolute path for the new receipt. It validates the complete CSV before opening a receipt.

1. Choose a new path under your build folder and publish the report. Check that the file contains the four lines you saw in the console.

```powershell
$receipt = Join-Path $build ('venue-receipt-' + [guid]::NewGuid().ToString('N') + '.txt')
& "$build\btb-venue-report.exe" $sample $receipt
Get-Content -LiteralPath $receipt
$before = (Get-FileHash -LiteralPath $receipt).Hash
```

2. Pass the same receipt path again and inspect the exit code and fingerprint.

```powershell
& "$build\btb-venue-report.exe" $sample $receipt
$LASTEXITCODE
$before -eq (Get-FileHash -LiteralPath $receipt).Hash
```

3. Give the refused input a different new destination. Check if any file appeared.

```powershell
$refusedReceipt = Join-Path $build ('refused-' + [guid]::NewGuid().ToString('N') + '.txt')
& "$build\btb-venue-report.exe" $rejected $refusedReceipt
Test-Path -LiteralPath $refusedReceipt
```

**Check your result.** The second attempt reports a receipt failure and the hash comparison prints `True`. The bad input reports record 3 and the final existence check prints `False`.

`publish.c` keeps the status of the first write failure and closes the file even when the write fails. A storage failure after creation can leave a partial receipt. Review a partial file separately and choose a new path for a retry.

[Previous — Render a complete report](06-render-a-complete-report.md) · [Next — Run and change a check](08-run-and-change-one-check.md)
