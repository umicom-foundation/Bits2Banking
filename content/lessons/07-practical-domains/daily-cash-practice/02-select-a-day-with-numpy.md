<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/daily-cash-practice/02-select-a-day-with-numpy.md

PURPOSE:
Select matching cells with a Boolean mask and keep exact cents.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Select a day with NumPy

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }


**Goal.** Use a mask to find both entries for day 2.

1. Open PowerShell from your Bits2Banking checkout. Check the environment with `python -c "import numpy"`. If the import fails, select a Python environment with NumPy available or trace the sample by hand.
2. Run the [NumPy exercise](../../../labs/data/daily-cash-practice/daily_cash_numpy.py) on the [same CSV](../../../labs/data/daily-cash-practice/daily_cash.csv).

~~~powershell
$Lab = './content/labs/data/daily-cash-practice'
python "$Lab/daily_cash_numpy.py" "$Lab/daily_cash.csv"
~~~

3. Find `loadtxt` in the source. It skips the header and selects columns 0 and 2. Column 0 holds days and column 2 holds signed integer cents. In NumPy, the first column is numbered 0. [NumPy loadtxt reference](https://numpy.org/doc/stable/reference/generated/numpy.loadtxt.html)
4. For day 2, read the expression `days == day` as six yes-or-no comparisons. The two matching amounts are `2100` and `-400`. Indexing `changes` with the mask picks just those two amounts.

~~~text
day 1: 2100 cents
day 2: 1700 cents
day 4: 2500 cents
~~~

**Try it.** Find the mask for day 4 on paper. It should be false for the first four rows and true for the last two. Add their amounts and compare with the output. The exercise uses small whole numbers that stay within the chosen fixed-width integer range.

[Previous lesson](01-group-observed-days-in-r.md) · [Course contents](index.md) · [Next lesson](03-refuse-duplicate-entries-with-pandas.md)
