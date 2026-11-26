<!--
Umicom Bits2Banking
File: content/simple-steps/extension/introduction-to-version-control.md

PURPOSE:
Give learners an additional practical case for Introduction to Version Control.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read the revision a parent repository records

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

An existing local submodule exercise has a working child checkout at a new commit. The parent HEAD still records the previous child commit.

1. From the practice parent, run git ls-tree HEAD -- child and note the child object name.
2. Run git -C child rev-parse HEAD and compare the two names without changing either history.

**Check your result.** The parent output shows a gitlink with the earlier child object name. The child command prints its newer object name.

[Step-by-step course guide](../course-guides/introduction-to-version-control.md) · [Full course](../../courses/introduction-to-version-control/index.html) · [Extend a skill by course](index.md) · [First practice case](../practice/introduction-to-version-control.md)
