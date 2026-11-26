<!--
Umicom Bits2Banking
File: content/simple-steps/extension/building-linux-from-scratch.md

PURPOSE:
Give learners an additional practical case for Building Linux from Scratch Using C Code.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Return a distinct status from a test program

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

In a practice Linux VM, you have the small C hello example. You want two separate executables to report different exit statuses.

1. Copy hello.c to hello-status.c. Change the last return 0 to return 7 and build it with cc hello-status.c -o hello-status.
2. Run the original and the variant separately. Immediately after each, enter printf '%s\n' "$?" to record its status.

**Check your result.** Both successful writes print “Hello from a user-space C program.” The original reports exit status 0, and the variant reports 7.

[Step-by-step course guide](../course-guides/building-linux-from-scratch.md) · [Full course](../../courses/building-linux-from-scratch/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/building-linux-from-scratch.md)
