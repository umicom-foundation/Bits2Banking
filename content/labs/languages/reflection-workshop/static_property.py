# Umicom Bits2Banking
# File: content/labs/languages/reflection-workshop/static_property.py
#
# PURPOSE:
#   Inspect Python dataclass fields and a property descriptor with explicit value access.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT

from dataclasses import dataclass, fields
from inspect import getattr_static


@dataclass
class Reading:
    station: str
    degrees_c: int

    # This exercise counter belongs to the instance after the first read.
    # Leaving it unannotated keeps it outside the declared dataclass fields.
    summary_reads = 0

    @property
    def summary(self):
        self.summary_reads += 1
        return f"{self.station} at {self.degrees_c} C"


def main():
    reading = Reading("Bench A", 68)
    for item in fields(Reading):
        print(f"{item.name}: {item.type.__name__}")

    # Read the descriptor itself so that building the catalogue leaves the
    # counter alone. The next normal access deliberately invokes the getter.
    descriptor = getattr_static(reading, "summary")
    print(f"summary descriptor: {type(descriptor).__name__}")
    print(f"reads before explicit access: {reading.summary_reads}")
    print(f"summary: {reading.summary}")
    print(f"reads after explicit access: {reading.summary_reads}")


if __name__ == "__main__":
    main()
