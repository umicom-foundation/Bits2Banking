# Reject overflow before multiplying

For a decimal parser, the next value would be `value * 10 + digit`. If multiplication wraps first, checking the wrapped result is too late. The Kernel tests the equivalent bound before the arithmetic: `value > (maximum - digit) / 10`.

## Trace two values

1. Read `UmicomKernelShellUnsignedSpan` in `kernel/console_line.c`.
2. Trace the last digit of `18446744073709551615`, the maximum unsigned 64-bit value.
3. Trace the last digit of `18446744073709551616`. Identify the guard that refuses it.
4. Inspect the `boundary` and `legacy` cases in `tests/console_numbers/test_numbers.c`.

## Ownership matters too

The span contract requires a trusted, readable buffer of the supplied length. It does not validate an arbitrary user-space pointer. Kernel entry points still need their established checked copy/ownership boundary before calling a parser.

The parser also cannot decide whether a caller selected the complete field. Parsing the first two bytes of `42suffix` accepts 42; parsing all eight bytes rejects it. Framing belongs to the caller, digit validation belongs to the parser.

## Exercise

Initialize the output to 73, try a field with a trailing question mark, and assert that 73 remains unchanged. Explain why a temporary local accumulator is simpler to reason about than publishing each partial digit.

## Need an earlier explanation?

[Review the foundation concepts](../../00-getting-started/04-memory-storage-and-information.md), then use the [connected learning map](../../../courses/learning-paths.html#kernel) for the longer written chapters. For C syntax or compiler commands, use the map's first-programming route before running this lab.

---

[Read this lesson in HTML](../../../courses/umicom-kernel-from-scratch/lessons/03-overflow-and-ownership.html) · [Learning sequence](../../../start/learning-sequence.md)

[Previous: A byte span is not a string](02-bounded-input.md)

[Next: Never execute a damaged prefix](04-damaged-console-lines.md)
