<!--
Bits2Banking
File: content/simple-steps/framework-sdk-venue-report/05-check-the-source-fingerprint.md

PURPOSE:
Compare a report fingerprint with an independently measured SHA-256 digest.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check which file supplied the totals

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A file fingerprint is a short value calculated from the file’s bytes. The report uses SHA-256 so a reader can check whether the input file still matches the report.

1. Run the report on the sample and calculate the digest with PowerShell.

```powershell
& "$build\btb-venue-report.exe" $sample
(Get-FileHash -LiteralPath $sample -Algorithm SHA256).Hash
```

2. Compare the 64 hexadecimal characters. PowerShell commonly prints uppercase and the program prints lowercase. The values match when you compare them without regard to case.
3. Read the `UmiSha256Buffer` call in `venue_report.c`. This call hashes the source bytes, so a change in line endings or quoting can alter the fingerprint even if every total stays the same.
4. Make a private practice copy. Change a room name without changing its numbers. Re-run both calculations on that copy and compare the results with the original.

```powershell
$changed = Join-Path $build 'venue-fingerprint-practice.csv'
if (Test-Path -LiteralPath $changed) { throw 'Choose a new practice filename' }
Copy-Item -LiteralPath $sample -Destination $changed
notepad $changed
```

   Save and close the editor before running the next two commands.

```powershell
& "$build\btb-venue-report.exe" $changed
(Get-FileHash -LiteralPath $changed -Algorithm SHA256).Hash
```

**Check your result.** The totals stay the same and a changed source produces a different fingerprint. The fingerprint checks byte identity. Establish the source through a trusted record if you need to know who supplied it.

[Previous — Preserve the report](04-preserve-the-last-report.md) · [Next — Render a complete report](06-render-a-complete-report.md)
