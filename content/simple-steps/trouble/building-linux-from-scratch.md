<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/building-linux-from-scratch.md

PURPOSE:
Give learners an additional practical case for Building Linux from Scratch Using C Code.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read the status of the command you just ran

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

An existing Linux VM runs the course's hello program and then runs ls. A learner reads $? after ls to check whether hello succeeded.

1. Run ./hello inside the practice folder and follow it immediately with printf '%s\n' "$?".
2. Match the printed status to the command immediately preceding printf. Leave other commands out between the two.

**Check your result.** A successful hello run prints “Hello from a user-space C program.” The next command reports status 0 for hello.

[Step-by-step course guide](../course-guides/building-linux-from-scratch.md) · [Full course](../../courses/building-linux-from-scratch/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/building-linux-from-scratch.md)
