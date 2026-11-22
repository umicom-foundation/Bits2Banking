<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/native-statement-calculations/02-keep-the-last-valid-total-in-c23.md

PURPOSE:
Teach Keep the last valid total in C23 through original worked exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material. Linked references retain their own terms.
-->

<picture>
  <source srcset="../../../assets/branding/umicom-wordmark-on-dark.svg" media="(prefers-color-scheme: dark)">
  <img src="../../../assets/branding/umicom-wordmark.svg" width="220" alt="Umicom">
</picture>

# Keep the last valid total in C23

[Course contents](index.md) · [Previous: Calculate posted cents in Umicom C](01-calculate-posted-cents-in-umicom-c.md)

## What you will learn

Check the range before adding to a total, and prove that failure preserves the previous value.

## Set an arithmetic contract

A signed 64-bit integer represents a fixed range of whole numbers. The add_cents function takes the address of a caller-owned total. It returns true and updates that total when addition fits. It returns false before making any write when the addition would exceed the range.

## Build a small positive and negative check

Save the following as checked_total.c. Use a C23 toolchain with the standard fixed-width integer types. The program exits with failure if either the posted value or the refusal behaviour is wrong.

```c
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

static bool add_cents(int64_t *total, int64_t amount)
{
    /* Reject before changing the caller's last accepted total. */
    if ((amount > 0 && *total > INT64_MAX - amount) ||
        (amount < 0 && *total < INT64_MIN - amount)) {
        return false;
    }
    *total += amount;
    return true;
}

int main(void)
{
    int64_t reserve = 0;
    if (!add_cents(&reserve, 2600) ||
        !add_cents(&reserve, -850) || reserve != 1750) {
        return 1;
    }

    int64_t boundary = INT64_MAX;
    if (add_cents(&boundary, 1) || boundary != INT64_MAX) {
        return 1;
    }

    puts("posted reserve 1750; overflow refused; last value retained");
    return 0;
}
```

```text
gcc -std=c23 -Wall -Wextra -Wpedantic checked_total.c -o checked_total
./checked_total
```

In PowerShell use checked_total.exe as the output name and run .\checked_total.exe. Expect the line shown by puts and a successful exit. On the boundary test, check the arithmetic on paper. INT64_MAX is greater than INT64_MAX minus 1, so the function returns before reaching the addition.

## Practice and check your answer

Add another failure case at the smallest possible total. What value should remain after trying to subtract one cent?

**Worked answer**

Start a fresh total at INT64_MIN. Call add_cents with -1 and confirm that it returns false. The stored total should remain equal to INT64_MIN. Check both the returned status and the stored value.

## Continue to verification

The next practice course groups the training ledger by account using SQL. Use the same definition of posted movement in both tools so the results are comparable.

[SQL Statement Reconciliation](../../../courses/sql-statement-reconciliation/index.html)

[Read this lesson as HTML](../../../courses/native-statement-calculations/lessons/02-keep-the-last-valid-total-in-c23.html)

## Continue learning

- [Learning C](../../../courses/learning-c/index.html)
- [Building a Compiler in C](../../../courses/building-a-compiler-in-c/index.html)

## Further reading

- [Tech Sustainify course catalogue](https://techsustainify.com/)
- [W3Schools C tutorial](https://www.w3schools.com/c/index.php)


[Course contents](index.md) · [Previous: Calculate posted cents in Umicom C](01-calculate-posted-cents-in-umicom-c.md)
