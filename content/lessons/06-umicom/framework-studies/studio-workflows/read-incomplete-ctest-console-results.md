![Umicom](../../../../assets/branding/umicom-wordmark.svg)

[Umicom icon](../../../../assets/branding/umicom.ico)

# Read incomplete CTest console results

A saved test console can end while its parent job still has work to do. Use the selected run’s planned count and its complete result rows to work out which coverage is present. A registration number, marked Test # in the output, identifies a configured test. It can be larger than the planned count when a test filter selects a few cases from a larger project.

## Classify a short saved transcript

Build `umicom-build-review` in the full Framework configuration. Open PowerShell and choose a disposable directory. Create a two-test transcript with one observed row.

```powershell
New-Item -ItemType Directory -Path ./console-evidence -Force | Out-Null
Set-Content -LiteralPath ./console-evidence/partial.log -Value "1/2 Test #17: sample.first ........ Passed 0.01 sec"
$log = (Resolve-Path -LiteralPath ./console-evidence/partial.log).Path
umicom-build-review ctest-summary "$log" 2
$LASTEXITCODE
```

The report shows two planned and one observed. Exit 3 records incomplete coverage. The one observed pass still tells you something useful about the file.

Add the second row and inspect the same snapshot again.

```powershell
Add-Content -LiteralPath ./console-evidence/partial.log -Value "2/2 Test #31: sample.second ........***Skipped 0.00 sec"
umicom-build-review ctest-summary "$log" 2
$LASTEXITCODE
```

The report now has two observed results with one pass and one skip. Exit 4 marks complete observed rows with an adverse or unexecuted result. The selected product still needs a run that exercises the skipped case.

## Make your own checks

1. Change the last outcome to Passed and run the inspection. The saved rows should now give exit 0.
2. Try a separate empty log with the same planned count. Record exit 3 and the unrecorded coverage before comparing it with the partial file.
3. Locate `tests/build_review/ctest_console_cli.cmake` in Framework. Explain how the fixture preserves the original file bytes and checks an exact outcome.

If the command rejects a transcript, check for missing or repeated numbered rows and compare its planned count with the selected run. Keep the original CTest process exit, log and exact build identity alongside your report.

[Previous lesson](read-a-32-bit-debugger-status.md) · [HTML edition](../../../../courses/framework-and-finance/studio-workflows/lessons/read-incomplete-ctest-console-results.html)
