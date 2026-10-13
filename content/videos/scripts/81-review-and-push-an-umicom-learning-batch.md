# Episode 81 — Review, commit and push an Umicom learning batch

**Bits to Banking · Umicom Foundation · Sammy Hegab**  
**Target duration:** 8 minutes · **Companion:** Chapter 239 and Update 34 build guide.

## 00:00–01:15 — Identify the correct repository

**Narration:** "Bits2Banking education content has its own Git repository. Publishing these lessons does not require new Framework, OS or Applications commits. We commit to the repository whose content we actually changed."

Display the extracted Update 34 package beside the checkout in Beyond Compare. Show that there is one top-level `Umicom-Bits2Banking` directory and no delete/mirror operation. Check the new C23 lab, diagrams, lesson files and videos.

## 01:15–03:10 — Prove the C23 baseline

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\git-three-way" -B ".\output\learning-build\git-three-way" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\git-three-way" --parallel 2
ctest --test-dir ".\output\learning-build\git-three-way" --output-on-failure
```

State that CTest proves the *teaching model* only. Separately inspect the MkDocs navigation additions in `UPDATE_34_NAVIGATION_AND_REVIEW.md`; preserve previous entries and the original Islam volume. The website build is a different gate and may require the already-installed MkDocs interpreter.

## 03:10–05:40 — The requested main-only Git sequence

```powershell
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): add Git merge recovery and C23 three-way lab"
git push origin main
git status
```

**Narration:** "`git add -A` stages the current repository's additions, modifications and deletions. `git commit` records the staged snapshot locally. `git push origin main` asks GitHub to advance the remote `main` ref. It does not perform a review or run tests automatically."

Pause at `git diff --cached --stat`. If unrelated changes or deletions appear, stop and review; do not casually publish them.

## 05:40–07:00 — Handle a rejected push correctly

Show a **fictional** non-fast-forward message and use:

```powershell
git fetch origin main
git rev-list --left-right --count HEAD...origin/main
git log --oneline --left-right HEAD...origin/main
```

Never force-push over another contributor's history as a generic fix. If a repository is behind and no unpublished work exists, a clean fast-forward may be appropriate. If histories diverged, review the specific commits and resolve conflict safely.

## 07:00–08:00 — Final quality check

Confirm correct repository, intended branch, clean working tree, exact commit SHA and verified remote state; note whether Windows CTest and MkDocs build succeeded. Explicitly mark any unperformed test as **NOT RUN**.

**Question for viewers:** What changes after `git add -A`, after `git commit`, and after `git push origin main`? **Answer:** the index; local repository history; and the remote branch, respectively.
