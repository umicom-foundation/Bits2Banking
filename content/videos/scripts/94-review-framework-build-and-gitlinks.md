# Episode 94 — Review Framework build impact and Git submodules safely

**Bits to Banking · Umicom Foundation · Advanced companion video**  
**Companion lessons:** Chapters 280–283 · **Suggested duration:** 11–15 minutes. This is *not* required for first-day learners.

## The shared-source problem (0:00–3:00)

**On screen:** Show the diagram `umicom-framework-ownership-update37.svg` and identify Applications, OS and the same canonical Framework remote. Explain why a submodule gitlink is a commit reference, not a copied source directory.

## Read-only observations (3:00–6:00)

In the authorised Applications checkout:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
git status
git submodule status framework
git -C ".\framework" status --short
git ls-files --stage framework
```

**Narration:** “Submodules often use a detached HEAD. Before trying to push or switch branches, first preserve local changes and check whether any unpublished commits exist. Never force the checkout to a different revision simply to suppress a warning.”

## Framework-native verification (6:00–9:00)

Check a reviewed, previously built Framework `umicom.exe` path, then run its **read-only** `repo verify .`. Explain that `repo lock .` has a different effect: it stages a parent gitlink and requires a review before any commit. Neither operation pushes to GitHub.

## Automated planning using real Framework (9:00–12:00)

Open `labs/native/contributor-notes/framework_planner_example.c`, pointing to calls to `umi_build_automation_*`. The example is an optional *consumer* of a compatible installed SDK. It does not copy Framework source or implement a new planner. Explain the difference between an affected-test plan and the results of actually running those tests.

## Wrap-up (12:00–15:00)

Ask what should happen if the Framework is dirty, if Windows CTest shows `Not Run`, or if the OS root has not yet been rebuilt. **Correct answer:** stop publication, preserve evidence, repair the real problem, rerun acceptance and review the parent gitlink. A green teaching lab is not a production release gate.
