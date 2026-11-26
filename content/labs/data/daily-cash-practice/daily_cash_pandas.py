# Umicom Bits2Banking
# File: content/labs/data/daily-cash-practice/daily_cash_pandas.py
#
# PURPOSE:
#   Refuse repeated observations before using pandas to group the rows.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT

import argparse
from pathlib import Path

import pandas as pd


def main() -> None:
    parser = argparse.ArgumentParser(description="Check desk entries and total each day.")
    parser.add_argument("csv", type=Path)
    args = parser.parse_args()
    entries = pd.read_csv(args.csv, dtype={
        "day": "Int64", "desk": "string", "change_cents": "Int64"
    })
    expected_columns = ["day", "desk", "change_cents"]
    if list(entries.columns) != expected_columns or entries.empty or entries.isna().any().any():
        raise SystemExit("Expected a complete day, desk and change_cents table.")
    # In this fixture, each desk submits one net movement per observed day.
    if entries.duplicated(subset=["day", "desk"]).any():
        raise SystemExit("A desk appears twice on the same day.")
    for day, cents in entries.groupby("day", sort=True)["change_cents"].sum().items():
        print(f"day {day}: {cents} cents")


if __name__ == "__main__":
    main()
