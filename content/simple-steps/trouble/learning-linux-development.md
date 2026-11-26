<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/learning-linux-development.md

PURPOSE:
Give learners an additional practical case for Learning Linux Development.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read the exit immediately after the program

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A practice program returns 2. An intervening successful printf command runs before the shell status is read.

1. Place the program, printf and the status read from the process lesson on three lines. Mark which program owns the last status.
2. In Bash capture the process result in a variable immediately after it exits. Print the saved value on a separate line.

**Check your result.** The saved process status is 2. Reading the shell’s latest status after the successful printf gives 0.

[Step-by-step course guide](../course-guides/learning-linux-development.md) · [Full course](../../courses/learning-linux-development/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/learning-linux-development.md)
