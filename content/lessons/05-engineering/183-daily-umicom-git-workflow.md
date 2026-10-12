# Chapter 183 — The daily Umicom Git workflow: inspect, stage, commit, push

**Bits to Banking · Version-control track · Umicom Foundation**  
**Tools:** Git and interactive PowerShell commands.  
**Prerequisite:** Chapter 182.

## Work deliberately on `main`

The current internal Umicom development policy is to commit to `main` directly **after local review and tests**. This chapter follows that instruction for maintainers with write access. External contributors can still use a fork and pull request as explained in [Chapter 17](17-first-pull-request.md); that is a different collaboration path, not permission to push to Umicom's protected source.

Before any change, identify the repository. `C:\umicom\Umicom-Applications`, its Framework submodule, `C:\umicom\umicomOS` and the Bits2Banking repository can each have **separate histories**. A commit in one does not automatically commit changes in another.

## First: observe without modifying

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git rev-parse --show-toplevel
git branch --show-current
git status --short --branch
git remote -v
git log -1 --oneline
```

Read the output. Confirm you are inside the intended repository and on `main`. If the branch name is blank, you may be in **detached HEAD**; follow [Chapter 185](185-umicom-git-submodules-and-detached-head.md) before committing.

`git status --short` uses two columns for tracked files: the first represents the index, the second the working tree. `??` means untracked. A clean tree is not proof that the remote has the same commit. It proves only that this local checkout has no visible staged or unstaged changes.

## Second: fetch and fast-forward safely

```powershell
git fetch origin main
git status --short --branch
git log --oneline --left-right HEAD...origin/main
git pull --ff-only origin main
```

`fetch` updates remote-tracking knowledge without changing your work tree. `pull --ff-only` refuses unexpected divergent history. If the command refuses, do not force the update; examine the graph and protect any unpublished commits first.

## Third: build and test *before* committing

For the Update 30 C23 learning lab:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\work-dispatch" -B ".\output\learning-build\work-dispatch" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\work-dispatch" --parallel 2
ctest --test-dir ".\output\learning-build\work-dispatch" --output-on-failure
```

If tests fail, keep your changes local until the error is understood. Do not make CI someone else's first opportunity to detect a regression. Additional website-build gates are documented in the update's build reference.

## Fourth: inspect what will become history

```powershell
git status
git diff --check
git diff --stat
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached
```

`git add -A` is appropriate only after reviewing the working-tree inventory; it can stage newly created files and deletions too. If there are unrelated changes, prefer explicitly staging the intended files. `git diff --cached --check` checks whitespace, but **does not** detect accidentally removed features, changed permissions or wrong logic. Read the actual patch.

## Fifth: commit and push

```powershell
git commit -m "feat(learning): add C23 completion delivery and Git workshops"
git push origin main
git status
```

The commit message should describe the actual work you staged. If `git push` is rejected, do not repeat it with `--force`. Chapter 184 explains remote divergence. For submodules, use the repository-specific order in Chapter 190.

## What a good review looks like

A high-quality change makes it possible to answer: Which source files changed? Why are they necessary? Which existing interfaces are preserved? Which tests were executed? Did the work introduce a new dependency? Were prior authors, licence notices and educational commentary retained? Was an earlier implementation disabled for review rather than silently erased?

For an Umicom update, the review should also check that C23 and Assembly remain the preferred executable languages, reusable behaviour stays in Framework, and no new Python or PowerShell **script files** were created. Interactive PowerShell Git commands are allowed; project functionality should not depend on scripts.

## Practical exercise

Using the practice repository from Chapter 182, add one line clarifying which bank team owns a reconciliation exception. Show the unstaged diff, stage just that file, inspect the staged diff, commit, and show the two latest commits. Write one sentence explaining why pushing cannot succeed until a remote is configured.

**Next:** [Remotes, fast-forward updates and non-fast-forward rejections](184-git-remotes-fetch-pull-and-non-fast-forward.md).
