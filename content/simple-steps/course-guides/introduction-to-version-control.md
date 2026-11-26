<!--
Umicom Bits2Banking
File: content/simple-steps/course-guides/introduction-to-version-control.md

PURPOSE:
Provide practical first steps and a result to check for Introduction to Version Control.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Introduction to Version Control

![Umicom Foundation](../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

1. Create an empty practice folder and run `git init -b main` inside it. Save a short note as `README.md`. [Files, snapshots and history](../../lessons/05-engineering/introduction-to-version-control/01-files-snapshots-and-history.md)
2. Run `git status --short`, then `git add README.md`. Read what will be recorded with `git diff --cached`. [Review and record a change](../../lessons/05-engineering/introduction-to-version-control/02-review-and-record-a-change.md)
3. When the staged text matches your note, run `git commit -m "Add practice note"`. Check the result with `git log -1 --oneline`. [Review and record a change](../../lessons/05-engineering/introduction-to-version-control/02-review-and-record-a-change.md)

**Check your result.** The latest commit is `Add practice note`, and `git status --short` is empty when the folder has no further changes.

[Continue in the full course](../../courses/introduction-to-version-control/index.html) · [All course guides](index.md)
