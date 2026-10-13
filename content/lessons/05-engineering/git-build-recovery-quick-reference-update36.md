# Git, build failure and submodule recovery — professional quick reference

**Bits to Banking · Major Update 36 · Umicom Foundation**

This reference is for **interactive PowerShell commands only**. It does not instruct contributors to create `.ps1` or `.py` scripts. Run commands from the correct repository and stop on unexpected output. Before `git add -A`, review all changes and make sure you are on the intended `main` branch.

## Observe without mutation

| Question | Command | Caution |
|---|---|---|
| Where am I? | `git rev-parse --show-toplevel` | A submodule is a separate repository. |
| What changed? | `git status` / `git diff` | Check tracked and untracked work. |
| What is staged? | `git diff --cached --stat` | `git add -A` includes deletions. |
| What HEAD? | `git rev-parse HEAD` | A detached HEAD has no current branch. |
| What local branch? | `git branch -vv` | Local `main` can be behind remote `main`. |
| Which upstream commit? | `git log -1 --oneline origin/main` | Requires a recent fetch for current knowledge. |
| Which local-only commits? | `git log --oneline origin/main..HEAD` | Preserve these before switching. |
| Parent gitlink? | `git ls-files --stage -- framework` | Mode 160000 is a submodule reference. |
| Child checkout SHA? | `git -C ".\framework" rev-parse HEAD` | May differ from parent index. |
| Submodule state? | `git submodule status framework` | Leading marker can indicate revision mismatch. |
| Stash inventory? | `git stash list` | Local to the current repository. |

## Safe Framework and OS synchronisation checklist

1. Inspect the authoritative Framework working tree and unpublished commits. If changes exist, preserve them without resetting, cleaning, or forcing a checkout.
2. Review and commit **Framework** changes from its canonical checkout under `Umicom-Applications\framework`, directly to `main` only when all required tests pass.
3. In Applications, run required integration checks and stage/test the revised gitlink. The native Framework CLI's `repo verify .` is a read-only preview; `repo lock .` stages checked-out submodule heads but does not pull, commit or push.
4. In OS, preserve local child changes, compare child SHA and remote history, then synchronise a *clean, reviewed* child to the intended Framework commit. Build and test OS **before** recording its parent pointer.
5. Inspect `git diff --cached --submodule=log` before committing a parent gitlink.

## Recover safely

For a child with reviewed tracked and ordinary untracked changes:

```powershell
Set-Location "C:\umicom\umicomOS"
git -C ".\framework" status
git -C ".\framework" log --oneline origin/main..HEAD
git -C ".\framework" stash push --include-untracked `
    -m "backup: preserve Framework work before synchronisation"
git -C ".\framework" stash list
git -C ".\framework" status --short
```

Do **not** switch to another revision if there are unpublished detached commits you have not preserved by a reviewed method. A stash does not by itself save such commits. Do not run this block mechanically if the backup and status checks are unexpected. Later, inspect a specific stash by message and identity. `stash@{0}` can change position as other stashes are added.

## Build and test the native C23 exercise

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\change-impact" `
  -B ".\output\learning-build\change-impact" -G Ninja `
  -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\change-impact" --parallel 2
ctest --test-dir ".\output\learning-build\change-impact" --output-on-failure
```

**Expect 43/43 named CTest cases.** This proves only the educational model's tested contracts in that configuration. It does not test the real Framework, Studio application, Windows installer, OS kernel or QEMU boot.

## Investigate failures by stage

**Configure:** CMake cache, selected compiler, missing dependency. **Compile:** earliest diagnostic, include path, source line. **Link:** symbol/export/ABI, static/shared library order. **CTest:** test executable present, failed vs not run, exit status, runtime. **GUI launch:** DLLs, working directory, assets, GTK schemas. **OS image:** actual boot mode and QEMU evidence. Record each stage's exact revision and configuration; do not substitute an unrelated green result.

## Commit Bits2Banking directly to main

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): add C23 change impact and native build recovery training"
git push origin main
git status
```

A non-fast-forward rejection is a request to inspect history, **not** permission to force push. `git pull --ff-only origin main` is appropriate only after checking that the checkout is clean and the histories permit a fast-forward. Use a per-repository sequence; do not use loops or wrapper scripts that obscure which repository receives a commit.
