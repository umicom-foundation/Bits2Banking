# Umicom Bits2Banking
# File: content/labs/data/daily-cash-practice/daily_cash_numpy.py
#
# PURPOSE:
#   Use integer arrays and Boolean masks to sum observed cash entries.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT

import argparse
from pathlib import Path

import numpy as np


def daily_totals(path: Path) -> tuple[np.ndarray, np.ndarray]:
    # These two numeric columns are the day and the signed movement in cents.
    table = np.loadtxt(path, delimiter=",", skiprows=1, usecols=(0, 2),
                       dtype=np.int64, ndmin=2)
    if table.size == 0:
        raise ValueError("The practice table needs at least one row.")
    days, changes = table[:, 0], table[:, 1]
    observed_days = np.unique(days)
    # Each True value in the mask selects a movement for the current day.
    totals = np.array([changes[days == day].sum() for day in observed_days],
                      dtype=np.int64)
    return observed_days, totals


def main() -> None:
    parser = argparse.ArgumentParser(description="Print observed daily totals.")
    parser.add_argument("csv", type=Path)
    args = parser.parse_args()
    days, totals = daily_totals(args.csv)
    for day, cents in zip(days, totals):
        print(f"day {day}: {cents} cents")


if __name__ == "__main__":
    main()
