<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/daily-cash-practice/04-mark-an-estimate-with-scipy-and-matplotlib.md

PURPOSE:
Calculate a linear estimate and plot it with a distinctive symbol.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Mark an estimate with SciPy and Matplotlib

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }


**Goal.** Make a day 3 estimate while keeping the reported observations available as they were.

1. Use the observed totals on days 2 and 4. Day 3 is halfway between them, so the straight-line estimate is `(1700 + 2500) / 2 = 2100` cents.
2. Check that `python -c "import numpy, scipy, matplotlib"` succeeds. Run the [plot exercise](../../../labs/data/daily-cash-practice/show_gap.py), using a new output name. It imports the helper from the [NumPy lesson](02-select-a-day-with-numpy.md) and uses the same table.

~~~powershell
$Lab = './content/labs/data/daily-cash-practice'
$Plot = Join-Path $env:TEMP ('cash-gap-' + [guid]::NewGuid().ToString('N') + '.png')
python "$Lab/show_gap.py" "$Lab/daily_cash.csv" $Plot
Get-Item -LiteralPath $Plot
~~~

3. Open the new PNG. Expect three circle markers at days 1, 2 and 4, and a cross at day 3. The legend describes observed and estimated values. The vertical axis shows cents.
4. Read `make_interp_spline(..., k=1)` as a straight-line rule between observed days. Matplotlib uses two calls to `scatter` so that the estimated point has a different symbol as well as a different legend entry. [SciPy interpolation reference](https://docs.scipy.org/doc/scipy/reference/generated/scipy.interpolate.make_interp_spline.html) · [Matplotlib scatter reference](https://matplotlib.org/stable/api/_as_gen/matplotlib.axes.Axes.scatter.html)

~~~text
day 3: 2100 cents (estimated)
~~~

**Try it.** In a separate copy of the CSV, change the day 4 reserve entry to 3500. Calculate the midpoint before running again with that copy and a new image filename. The changed day 4 total is 2700, so the new estimate is 2200 cents. Keep the estimated value labelled in any report that uses it.

[Previous lesson](03-refuse-duplicate-entries-with-pandas.md) · [Course contents](index.md)
