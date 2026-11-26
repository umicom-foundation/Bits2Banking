<!--
Umicom Bits2Banking
File: content/simple-steps/compare/introduction-to-version-control.md

PURPOSE:
Give learners an additional practical case for Introduction to Version Control.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Compare a saved file with the commit's change description

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

In a disposable course repository, the latest commit changes notes.txt from a single line Draft to a single line Ready.

1. Run git show HEAD:notes.txt to read the committed file contents.
2. Run git show --format= -- notes.txt and find the removed and added lines.

**Check your result.** The committed file reads Ready. The change removes Draft and adds Ready.

[Step-by-step course guide](../course-guides/introduction-to-version-control.md) · [Full course](../../courses/introduction-to-version-control/index.html) · [Compare two approaches by course](index.md) · [First practice case](../practice/introduction-to-version-control.md)
