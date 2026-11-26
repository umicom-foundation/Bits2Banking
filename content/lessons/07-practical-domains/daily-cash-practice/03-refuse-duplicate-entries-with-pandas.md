<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/daily-cash-practice/03-refuse-duplicate-entries-with-pandas.md

PURPOSE:
Check a desk and day identity before summing with pandas.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Refuse duplicate entries with pandas

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }


**Goal.** Identify a repeated submission before it changes the daily report.

1. Check that `python -c "import pandas"` succeeds in your practice environment.
2. Run the [pandas exercise](../../../labs/data/daily-cash-practice/daily_cash_pandas.py). The sample expects one net movement from each desk that reports on a day. The pair `day, desk` is the identity of that report.

~~~powershell
$Lab = './content/labs/data/daily-cash-practice'
python "$Lab/daily_cash_pandas.py" "$Lab/daily_cash.csv"
~~~

3. Find `duplicated` in the source. It checks the two identity columns. A repeated pair is refused before the script prints any amount. `groupby("day")` then adds the signed cents for the accepted records. [pandas duplicate reference](https://pandas.pydata.org/docs/reference/api/pandas.DataFrame.duplicated.html) · [pandas GroupBy user guide](https://pandas.pydata.org/docs/user_guide/groupby.html)

~~~text
day 1: 2100 cents
day 2: 1700 cents
day 4: 2500 cents
~~~

**Try it.** Make a new copy of the CSV outside the source folder. Add another `2,reserve,2100` row to that copy. Run the same script with the copy. Expect `A desk appears twice on the same day.` with no totals printed. One row can represent a different legitimate event in another data model. Confirm the real identity fields before using a similar rule there.

[Previous lesson](02-select-a-day-with-numpy.md) · [Course contents](index.md) · [Next lesson](04-mark-an-estimate-with-scipy-and-matplotlib.md)
