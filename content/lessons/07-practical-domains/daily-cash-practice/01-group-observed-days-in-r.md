<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/daily-cash-practice/01-group-observed-days-in-r.md

PURPOSE:
Read signed integer-cent entries and total the observed days in base R.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Group the observed days in R

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }


**Goal.** Explain why day 2 totals 1700 cents and why day 3 has no total.

1. Look at the [practice table](../../../labs/data/daily-cash-practice/daily_cash.csv). Find both rows labelled day 2. Write `2100 + (-400)` on a piece of paper.
2. In PowerShell, from your Bits2Banking checkout, check that `Rscript --version` can find your R installation. Run the [base R exercise](../../../labs/data/daily-cash-practice/daily_cash.R).

~~~powershell
$Lab = './content/labs/data/daily-cash-practice'
Rscript "$Lab/daily_cash.R" "$Lab/daily_cash.csv"
~~~

3. Read the three output lines. The script uses `read.csv` to load a table. The formula `change_cents ~ day` tells `aggregate` to split the movements into groups with the same day. The `sum` function adds the values inside each group. [R aggregate reference](https://stat.ethz.ch/R-manual/R-devel/library/stats/html/aggregate.html)

~~~text
day 1: 2100 cents
day 2: 1700 cents
day 4: 2500 cents
~~~

If you see a file error, run `Get-Item "$Lab/daily_cash.csv"` and check your current folder. If `Rscript` is unavailable, compare the result by hand or with NumPy in the next lesson.

**Try it.** In a separate copy of the CSV, add `3,reserve,0`. Run the script with that copy. The output should include day 3 with an observed total of zero. The original file left the day unobserved.

[Course contents](index.md) · [Next lesson](02-select-a-day-with-numpy.md)
