<!--
Umicom Bits2Banking
File: content/lessons/learning-c/21-follow-a-rejected-call.md

PURPOSE:
  Present "Follow a rejected function call" with source-based exercises.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Follow a rejected function call

A function can refuse a request. The caller must know whether a result was produced before using it. This lab follows one small C function from input checks to output assignment, then designs checks for its boundary.

Source to open: `Umicom-Bits2Banking/labs/native/framework-activity/activity.c`.

## Setup recap

Use a text editor, this course and a checkout of the named source. A checkout is a folder containing a repository's files. This is a source-reading and reasoning lab; it needs no running service or account. Choose your own practice folder and keep the original example unchanged. The commands below display source rather than compile or execute it. Replace the example directory with your checkout location. The detailed terminal and editor guide explains how to obtain a checkout, open a terminal and prepare later executable exercises.

A terminal accepts commands. Set-Location (PowerShell) and cd (Bash) choose the folder in which subsequent commands work. Get-Content and sed display text. If a path is missing, locate the repository first instead of creating an empty replacement file.

### PowerShell

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
Get-Content -LiteralPath 'labs\native\framework-activity\activity.c'
```

### Bash

```bash
cd /path/to/umicom/Umicom-Bits2Banking
sed -n '1,200p' 'labs/native/framework-activity/activity.c'
```

## Understand the idea

BtbActivityAdvance receives current by value: changing that local parameter would not change the caller's variable. Its second parameter points to storage supplied by the caller. Writing through *next changes that storage. A status value reports success or explains why no result was produced. The number 1000 is a policy limit, not the largest value an unsigned integer can hold.

```text
input + caller's result → argument check → capacity check → write result → success
                              ↓ reject         ↓ reject
                         result unchanged  result unchanged
```

## Read the exact check

```c
CHECK(BtbActivityAdvance(1000U, &result) == UMI_STATUS_CAPACITY_EXCEEDED && result == 77U);
```

This line is already in test_activity.c; do not add a duplicate. CHECK is the example's small test macro. It reports an error and returns a failing exit status when the expression is false. == compares values; && requires both comparisons to be true and evaluates the right side only when the left side is true. &result passes the address of caller-owned storage. The U suffix makes 1000U and 77U unsigned integer constants. The case begins with result set to 77U, so an accidental write is visible. Your additional 1001U exercise checks the first invalid count as well as the existing largest-unsigned-value example.

## Work through the lab

1. Open activity.c and underline every return. Circle the only assignment through next. Read the conditions in order; the first matching return ends the call.
2. On paper, set result to 77. Trace BtbActivityAdvance(0, &result), then repeat from result = 77 with current equal to 999, 1000 and 1001.
3. For each trace, record status and result separately. Now trace a null output pointer: the first check returns before any dereference.
4. Open test_activity.c beside activity.c. Find the existing full case, which already checks both refusal and preservation. In a practice copy, extend the invalid case with current = 1001 and a fresh result = 77 before the existing UINT_MAX case. Predict both statuses before running anything.

## Expected result

The four non-null traces produce OK/1, OK/1000, CAPACITY_EXCEEDED/77 and INVALID_ARGUMENT/77. A null result pointer returns INVALID_ARGUMENT.

## If the result differs

If result changes on refusal, look for an assignment before validation. If the result is correct but the test fails, compare the status as well: a capacity limit and an invalid argument express different problems.

## Explain it yourself

Would checking only that result is nonzero detect every defect? Explain using the starting value 77.

<details>
<summary>Worked explanation</summary>

No. An unchanged 77 is nonzero even when the function refused. The test needs the status and the exact expected output. Keeping an unmistakable starting value helps reveal accidental writes.

</details>

## Use the idea in Umicom

Record inputs, expected outputs and refusal cases before extending the example. Reusable production behaviour belongs in Umicom Framework; applications translate user actions and show the service result. A traced example explains a contract. It does not establish that every application using a similar idea has been integrated or tested.

[HTML edition](../../courses/learning-c/lessons/21-follow-a-rejected-call.html)

[Terminal and editor setup guide](terminal-to-visual-studio.md)

[Previous lesson](20-allocation-outputs-and-lifetimes.md) · [Course contents](index.md)

[Continue: Open, read and close a file](22-open-read-and-close-a-file.md)
