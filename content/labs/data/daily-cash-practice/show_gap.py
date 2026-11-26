# Umicom Bits2Banking
# File: content/labs/data/daily-cash-practice/show_gap.py
#
# PURPOSE:
#   Estimate one missing day and draw it separately from observations.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT

import argparse
from pathlib import Path

import matplotlib

matplotlib.use("Agg")  # Save a local file without a window system.

from matplotlib import pyplot as plt
from scipy.interpolate import make_interp_spline

from daily_cash_numpy import daily_totals


def main() -> None:
    parser = argparse.ArgumentParser(description="Plot observations and one estimate.")
    parser.add_argument("csv", type=Path)
    parser.add_argument("png", type=Path, help="Choose a new local output file.")
    args = parser.parse_args()
    days, cents = daily_totals(args.csv)
    gap = 3
    if not {2, 4}.issubset(days) or gap in days:
        raise SystemExit("This exercise needs observations on days 2 and 4 and a missing day 3.")
    # Degree one joins adjacent observations by straight segments.
    interpolator = make_interp_spline(days, cents, k=1)
    estimate = float(interpolator(gap))

    figure, chart = plt.subplots(layout="constrained")
    chart.scatter(days, cents, marker="o", label="Observed")
    chart.scatter([gap], [estimate], marker="x", label="Estimated")
    chart.set(xlabel="Practice day", ylabel="Movement (cents)", xticks=[1, 2, 3, 4])
    chart.legend()
    # Exclusive creation keeps an earlier result available for comparison.
    with args.png.open("xb") as output:
        figure.savefig(output, format="png")
    plt.close(figure)
    print(f"day {gap}: {estimate:.0f} cents (estimated)")

if __name__ == "__main__":
    main()
