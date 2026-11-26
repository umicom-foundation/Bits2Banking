# Umicom Bits2Banking
# File: content/labs/languages/reflection-workshop/practice/signature_dry_check.py
#
# PURPOSE:
#   Use Python signature metadata to admit one proposed call shape and refuse another.
#
# AUTHOR AND ORGANISATION:
# Sammy Hegab
# Umicom Foundation
#
# LICENCE:
# MIT

from inspect import signature


def format_reading(*, station: str, degrees_c: int) -> str:
    # A successful observation must not enter the body of this function.
    raise AssertionError("the formatter ran during metadata inspection")


def main():
    format_signature = signature(format_reading)

    # Binding checks the argument shape. Printing the keys leaves the values
    # available for separate application validation.
    proposed = format_signature.bind(station="Bench A", degrees_c=68)
    print("complete call: " + ", ".join(proposed.arguments))

    try:
        format_signature.bind(station="Bench A")
    except TypeError:
        print("missing measurement: refused")
    else:
        raise AssertionError("a required keyword was absent")


if __name__ == "__main__":
    main()
