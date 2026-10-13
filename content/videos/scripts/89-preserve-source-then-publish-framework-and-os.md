# Episode 89 — Preserve source, then publish Framework and OS in order

**Bits to Banking · Umicom Foundation · Presenter script**  
**Companion lessons:** Chapters 260–263 · **Estimated running time:** 14–17 minutes.

## Opening scenario (0:00–3:00)

**On screen:** Display `framework-to-os-preservation-update36.svg` and a **fictional** transcript of `git submodule update --init --remote framework` refusing to overwrite local modifications. Do not use a live dirty checkout for destructive demonstrations.

**Narration:** “Git is preventing data loss. The correct solution starts with understanding what is local, what is published, and what each parent records. A detached HEAD is normal for submodules. Pushing `origin main` from a detached checkout attempts to push the local `main` branch, not the detached commit.”

## Inspect and preserve (3:00–8:00)

```powershell
Set-Location "C:\umicom\umicomOS"
git status
git -C ".\framework" status
git -C ".\framework" branch -vv
git -C ".\framework" rev-parse HEAD
git -C ".\framework" log --oneline origin/main..HEAD
git -C ".\framework" stash list
```

Explain the three risks: uncommitted tracked modifications, untracked files and unpublished detached commits. Describe `stash push --include-untracked` as one preservation mechanism for uncommitted work, but **not** a substitute for preserving detached commits. Do not execute a stash in a viewer's real directory; use a disposable example repository if demonstrating mutation.

## Framework first, parent later (8:00–13:00)

**On screen:** Compare the authoritative `Umicom-Applications\framework` checkout with `umicomOS\framework`. Explain that both are working trees of the same remote source. The Framework implementation is committed once from the authoritative checkout on `main`. The OS parent then records the tested Framework commit as a gitlink.

**Narration:** “Framework's existing Automated Build System plans affected targets; the native `umicom repo verify .` previews a parent update; `umicom repo lock .` stages checked-out submodule heads. Neither pushes upstream commits. The parent must still build and test, and the maintainer must inspect the staged pointer before committing.”

Show the standard direct-to-main commands for a reviewed educational batch:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): document safe Framework and OS integration"
git push origin main
```

Explain that `git add -A` stages deletions too, and that the example commit should only be executed when those are the changes the owner intends. If a push rejects, stop and inspect remote divergence; do not force it.

## Final review (13:00–17:00)

Display the capstone rubric: full SHAs, local changes preserved, tests bound to the current revision, GTK4 and QEMU gates reported honestly, stage reviewed, correct repository commit order. The acceptance criterion is **traceable evidence**, not just a successful Git command.

**Audience task:** Produce a fictional three-repository commit plan (Framework, Applications, OS), with a test gate and a commit command at each step. Explain what changes if the OS Framework checkout contains unpublished commits.

**Production boundary:** No Python or PowerShell implementation scripts; all executable lab logic is C23 and no real repository modifications are performed by the lab.
