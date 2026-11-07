<!--
Umicom Bits2Banking
File: content/lessons/07-practical-domains/financial-instruments-pricing/04-follow-a-discount-factor-and-its-failures.md

PURPOSE:
  Present "Follow a discount factor and its failure paths" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow a discount factor and its failure paths

A pricing function needs a clearly stated model as well as correct arithmetic. This lab reads Framework's small discount calculation, checks a result we can predict exactly and follows its handling of invalid or non-finite values.

Source to open: `Umicom-Applications/framework/src/finance/quant/discount_curve.c`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath '..\Umicom-Applications\framework\src\finance\quant\discount_curve.c'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' '../Umicom-Applications/framework/src/finance/quant/discount_curve.c'
```

## Understand the idea

A future amount is money associated with a later time. In the model used by this function, the discount factor is exp(-r × d / 365), where r is a continuously compounded annual rate written as a decimal and d is a number of days. exp is the exponential function. Present value is future amount multiplied by the factor. These assumptions are part of the calculation: another day-count convention or compounding rule changes the model. This exercise teaches the inspected function, not instrument-specific market quotation rules.

```text
rate and days -> checked exponent -> finite factor -> amount × factor
                                                           |
                                                finite result -> output
Model: factor = exp(-rate × days / 365)
```

## Work through the lab

1. Locate the argument checks and the expression that computes the exponent. Write units next to each input: decimal annual rate, days and amount. A rate of 0.05 means five percent; 5 would mean a very different rate.
2. Choose an amount of 100, rate zero and 365 days. The exponent is zero, exp(0) is one, and the expected present value is 100. Repeat with zero days and a finite rate; explain the same factor.
3. Trace a negative days argument to its rejection path. Then find the finite-value checks after the exponent, exponential and amount multiplication. Identify where the final output is written and whether each failure occurs before that point.
4. Create a case table with ordinary success, zero time, negative days, non-finite input and an extreme finite calculation that cannot be represented. Use an unchanged output sentinel for rejected cases. Do not assume one exact floating-point status without reading the relevant branch.

## Expected result

The exact zero-rate and zero-time examples give a factor of one. Rejected inputs or non-finite results should follow the documented status path without publishing an invalid value. The inspected finite check does not by itself reject every underflow to zero, so representational limits remain part of the model review.

## If the result differs

If results differ by a large factor, check rate units and day-count assumptions first. For small differences, inspect precision and the chosen tolerance. Do not adjust an expected number until a failing test passes without explaining the model and numeric error.

## Explain it yourself

Why is a zero-rate case useful before trying a realistic-looking market example?

<details>
<summary>Worked explanation</summary>

It gives a simple independently predictable result. If a zero-rate factor is not one, the problem is not hidden in a difficult market convention. More complex examples can then test the stated assumptions and numerical behaviour.

</details>

## Use the idea in Umicom

Record inputs, expected outputs and refusal cases before extending the example. Reusable production behaviour belongs in Umicom Framework; applications translate user actions and show the service result. A traced example explains a contract. It does not establish that every application using a similar idea has been integrated or tested.

[HTML edition](../../../courses/financial-instruments-pricing/lessons/04-follow-a-discount-factor-and-its-failures.html)

[Terminal and editor setup guide](../../learning-c/terminal-to-visual-studio.md)

[Previous lesson](03-framework-pricing-and-evidence.md) · [Course contents](index.md)
