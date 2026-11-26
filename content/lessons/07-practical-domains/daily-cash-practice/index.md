<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/daily-cash-practice/index.md

PURPOSE:
Connect original R, Python and C23 exercises on signed daily totals.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow daily cash movements with data tools

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }


Two fictional desks report their cash movements in integer cents. Your job is to group the submitted rows, notice one day without any records, and show an estimate for that day clearly. You can use pencil and paper first. There are only six rows.

| Day | Reserve desk | Operations desk | Observed total |
| --- | ---: | ---: | ---: |
| 1 | 1500 | 600 | 2100 |
| 2 | 2100 | -400 | 1700 |
| 3 | No row | No row | No observation |
| 4 | 3300 | -800 | 2500 |

A signed amount can be positive or negative. The movement is the sum of the submitted changes. A balance would also need an opening amount. Read the [practice file](../../../labs/data/daily-cash-practice/daily_cash.csv). CSV means comma-separated values. Each line after the header has a day, a desk and a movement.

1. [Group rows with base R](01-group-observed-days-in-r.md). Read integer columns and group the observed days.
2. [Select values with a NumPy mask](02-select-a-day-with-numpy.md). Use a True or False array to pick every row for one day.
3. [Check duplicates before grouping with pandas](03-refuse-duplicate-entries-with-pandas.md). Explain which fields identify a desk report and test an accidental copy.
4. [Show an estimated day using SciPy and Matplotlib](04-mark-an-estimate-with-scipy-and-matplotlib.md). Estimate a gap and mark it separately in a plot.

Run a single lesson in an environment that already has the tool it names. The R example uses base R. The other lessons use the specific Python libraries in their titles. The [simple steps](../../../simple-steps/course-guides/daily-cash-practice.md) give a native C23 cross-check and all of the command lines.

This original practice uses the short-example and exercise pattern from the W3Schools subject tutorials. [R tutorial](https://www.w3schools.com/r/) · [NumPy tutorial](https://www.w3schools.com/python/numpy/) · [Pandas tutorial](https://www.w3schools.com/python/pandas/) · [SciPy tutorial](https://www.w3schools.com/python/scipy/) · [Matplotlib introduction](https://www.w3schools.com/python/matplotlib_intro.asp)
