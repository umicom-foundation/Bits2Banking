<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/daily-cash-practice.md

PURPOSE:
Give short commands and expected results for the daily cash data exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Daily cash data practice in simple steps

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }


1. Open PowerShell from your Bits2Banking checkout. Set the location of the [practice files](../../labs/data/daily-cash-practice/daily_cash.csv).

   ~~~powershell
   $Lab = './content/labs/data/daily-cash-practice'
   Get-Item "$Lab/daily_cash.csv"
   ~~~

2. Choose one installed tool. Read the matching lesson if the command reports a missing runtime or package.

   ~~~powershell
   Rscript "$Lab/daily_cash.R" "$Lab/daily_cash.csv"
   python "$Lab/daily_cash_numpy.py" "$Lab/daily_cash.csv"
   python "$Lab/daily_cash_pandas.py" "$Lab/daily_cash.csv"
   ~~~

   Expect 2100, 1700 and 2500 cents for days 1, 2 and 4. Day 3 has no reported amount.

3. Use your existing C23 compiler for an independent check with the [C source](../../labs/data/daily-cash-practice/check_totals.c). Choose a new output location. Check that the compile succeeds before running the executable.

   ~~~powershell
   $Check = Join-Path $env:TEMP ('cash-check-' + [guid]::NewGuid().ToString('N') + '.exe')
   gcc -std=c23 -Wall -Wextra -pedantic "$Lab/check_totals.c" -o $Check
   if ($LASTEXITCODE -eq 0) { & $Check "$Lab/daily_cash.csv" }
   ~~~

4. Follow the [SciPy and Matplotlib steps](../../lessons/07-practical-domains/daily-cash-practice/04-mark-an-estimate-with-scipy-and-matplotlib.md) when those packages are available. Look for one labelled estimate at day 3. Its value should be 2100 cents.

**Check your result.** You can account for every row in the observed totals. The estimate has its own label.

[Read the full course](../../lessons/07-practical-domains/daily-cash-practice/index.md) · [All course guides](index.md)
