<!--
Umicom Bits2Banking
File: content/simple-steps/trouble/introduction-to-version-control.md

PURPOSE:
Give learners an additional practical case for Introduction to Version Control.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check why a tracked edit is missing from the proposed snapshot

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

In a practice repository, edit a tracked notes.txt that was clean at the start. The staging area is empty.

1. Run git status --short and git diff --cached on the practice copy.
2. Run git add notes.txt and repeat both checks.

**Check your result.** The first status places M in the unstaged column and the staged diff is empty. After staging, M is in the staged column and the diff shows the edit.

[Step-by-step course guide](../course-guides/introduction-to-version-control.md) · [Full course](../../courses/introduction-to-version-control/index.html) · [Troubleshoot by course](index.md) · [First practice case](../practice/introduction-to-version-control.md)
