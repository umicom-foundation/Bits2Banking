<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/building-a-compiler-in-c/122-store-a-true-or-false-value-in-a-local.md

PURPOSE:
Store a true-or-false value in a local

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Store a true-or-false value in a local

Imagine a door sensor that reports `0` when a door is closed and a nonzero number when it is open. The original number serves the sensor. The rest of the program can keep just the answer to “Is the door open?” A local variable belongs to the part of the program where you declare it. When you declare that local as `bool` in checked Umicom C, each successful store leaves it with either `0` (false) or `1` (true).

## Trace a declaration from left to right

This program comes from the compiler's Boolean-local regression. The test compiled it and checked that execution returned `42`.

```c
int main(void) {
    bool off=0,on=-2,later=on+6;
    const bool left=3;
    bool const right=false;
    return 39+off+on+later+left+right;
}
```

1. `off` starts from `0` and stores `0`.
2. `on` starts from `-2`. Since `-2` is nonzero, `on` stores `1`.
3. The next initializer reads that stored `1`. It adds `6` to get `7`, and `later` stores `1`.
4. `left` stores `1` from `3`. `right` stores `0` from `false`. `const bool` and `bool const` both make the local read-only after initialization.
5. The returned number is `39 + 0 + 1 + 1 + 1 + 0 = 42`.

Write those five stored numbers on paper. If you have the current Umicom C tool, save the same source as `bool-locals.uc`. Check the source before trying to run it.

```text
umicom-c check bool-locals.uc
umicom-c run bool-locals.uc
```

Expect the run to report `Result: 42`. If `check` rejects `bool`, verify which Umicom C build the command starts.

## Do the arithmetic before updating the flag

Try tracing `bool n=1; n/=2;` on paper. The abbreviated `/=` operator divides the stored value and writes the answer back. The arithmetic uses whole numbers, so `1 / 2` gives `0`. The successful store keeps `0`. This is the order the checked execution follows.

```text
FUNCTION store_bool(value)
    IF value equals zero
        RETURN 0
    RETURN 1

n ← store_bool(1)
answer ← checked integer division of n by 2
IF division fails
    REPORT the arithmetic error and stop
n ← store_bool(answer)
```

Change the divisor on paper to `0`. Division fails before any new value can be written. The Umicom C regression checks for an arithmetic error at `/=` and checks that the failed program leaves the caller's prior result record untouched. If you declare `n` with `const`, a later update is a source error discovered during `check`.

## Measure the type separately from its value

`sizeof(n)` asks how many bytes the source type of `n` uses. It gives `1` in the checked Umicom C profile, even when `n` holds `0`. `sizeof` on this local needs its declared type. It does not run an arithmetic operation or fetch the stored value. The virtual machine still carries the value in its existing integer slot.

For an integer converted to `bool`, C23 defines the same zero-versus-nonzero rule. A one-byte `bool` is Umicom C's choice for this profile. The profile shown here requires initialization and covers scalar locals in complete C source. The separate `script` and pseudocode modes retain their integer declarations. [WG14 N3220, sections 6.3.1.2 and 6.5.4.4](https://www9.open-std.org/JTC1/SC22/WG14/www/docs/n3220.pdf)

[Course contents](index.md) · [Previous lesson · Keep the last accepted script value](121-keep-the-last-accepted-script-value.md) · [Lower Boolean words without changing the VM](93-lower-boolean-words-without-changing-the-vm.md) · [Count bytes from an admitted type](99-count-bytes-from-an-admitted-type.md) · [HTML edition](../../../courses/building-a-compiler-in-c/lessons/122-store-a-true-or-false-value-in-a-local.html)

[Next lesson · Measure a Boolean literal without reading its value](123-measure-a-boolean-literal-without-reading-its-value.md)
