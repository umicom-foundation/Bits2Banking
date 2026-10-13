# Chapter 283 — Capstone: review, test and publish a learning change

**Bits to Banking · Optional Advanced Unit · Versioned delivery**  
**Time:** 45–90 minutes · **Prerequisite:** completion of Chapters 264–279 and authorisation to push to your intended repository.

## Goal

Combine the habits from the course into a safe end-to-end delivery. Your change could be a corrected explanation in a Markdown lesson or a reviewed improvement to the C23 Notes demonstration. It must be small enough that another contributor can understand what changed and why. The aim is not to make a large number of commits; it is to produce one reproducible, reviewable update.

## Step 1 — Identify the owner and repository

Use your **practice repository** for this capstone unless an Umicom maintainer has explicitly authorised an official Bits2Banking change. Check the current folder and branch:

```powershell
Get-Location
git status
git branch --show-current
git remote -v
```

Confirm which repository you intend to modify. If you are in a parent repository with submodules, examine their status separately rather than assuming `git status` covers all child edits.

## Step 2 — Describe the change in one sentence

For example: “Clarify the difference between Windows Terminal and PowerShell 7”, or “Improve the Notes demonstration's displayed instruction”. Decide which user will benefit and how you will verify the behaviour. Use an editor to make a targeted change; preserve headers, authorship, comments, existing features and educational context.

## Step 3 — Build/test the relevant source

For a Markdown-only change, inspect the links, heading, commands and rendered preview in the existing approved publishing system. For a C23 Notes change, run the Chapter 277 configure, build and CTest commands, and record the actual number of passing tests. If a larger Framework-owned component is affected, follow its own build and testing requirements; do not substitute the Notes lab for Framework acceptance.

## Step 4 — Review staging before commit

```powershell
git status
git diff
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached
```

**Pause:** If any unrelated path, unreviewed deletion or suspicious secret appears, do not commit. Stage only the intended changes after correcting the problem. `git add -A` is broad and therefore requires careful review.

## Step 5 — Commit and push (authorised `main` only)

```powershell
git commit -m "docs(learning): clarify the first contributor workflow"
git push origin main
git status
```

These commands follow the Umicom owner-maintained direct-to-`main` policy. External contributors who cannot push to the organisation repository should submit a fork-based pull request instead. A remote push may be rejected if the remote advanced independently; do not force push. Fetch and compare histories first.

## Step 6 — Confirm publication separately

A successful `git push` establishes only that GitHub accepted the commits. It does **not** establish that the learning site deployed successfully or that a final executable works on Windows and Linux. Publication must be checked independently using the repository's approved CI and site build process. If you cannot observe the final site, report publication as *not verified*.

## End-of-course evidence package

Retain the change description, reviewed diff, Git commit ID, tool versions, build/test results, relevant screenshots or logs and remaining open checks. For a practical Umicom contribution, clearly distinguish: *source is committed*, *tests passed locally*, *CI passed*, and *site or binary deployed*. These are separate milestones.

**Final reflection:** What would go wrong if a developer assumed `git push` also compiled and tested code? Which fact changes when an OS parent gitlink is updated? Why is preserving old functionality especially important when the project is used to teach new contributors?

**Continue learning:** Revisit the professional Git recovery chapters and the Umicom Framework architecture course. You now have the essential vocabulary to ask specific questions about shell commands, Git state, native builds and shared Framework services.
