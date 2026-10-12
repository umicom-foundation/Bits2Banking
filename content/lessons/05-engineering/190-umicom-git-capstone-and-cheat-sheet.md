# Chapter 190 — Git capstone: reproduce and publish a verified Umicom update

**Bits to Banking · Version-control track · Umicom Foundation**  
**Tools:** Git, CMake, Ninja and PowerShell commands (no script files).  
**Prerequisites:** Chapters 182–189 and a working C23 toolchain.

## Scenario: Framework, OS and learning source all have separate owners

Assume a contributor has three pieces of work: an approved reusable Framework fix, an Umicom OS update that consumes it and a Bits2Banking lesson explaining the change. These must not become one undifferentiated Git commit. The Framework repository owns the shared implementation; Umicom OS owns the pinned submodule reference and its OS-only code; Bits2Banking owns authored lessons and native teaching exercises.

**Your task:** publish each reviewed change in dependency order, preserving the current working trees and leaving an auditable trail of source revision and test evidence.

## Checkpoint A — Inspect every repository

Do not use loops that hide which repository failed. Inspect each explicitly:

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git status --short --branch
git log -1 --oneline

Set-Location "C:\umicom\umicomOS"
git status --short --branch
git submodule status framework

Set-Location "C:\umicom\Umicom-Bits2Banking"
git status --short --branch
git log -1 --oneline
```

These are **read-only** checks. Do not proceed to commits if a working tree contains unknown changes or a submodule reports unpublished commits. Distinguish a changed gitlink (parent) from changed implementation files (nested repository).

## Checkpoint B — Finish Framework first, if it actually changed

Inside the authoritative Framework checkout, inspect, build and test according to that repository's current validated presets. Then:

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached
git commit -m "feat(framework): describe approved shared service update"
git push origin main
```

**Only perform this commit if you have actual approved Framework changes.** Do not commit merely to update a version number, and do not push a detached HEAD blindly. This teaching batch itself does **not** modify Framework and therefore does not require a Framework commit.

## Checkpoint C — Upgrade and verify the OS submodule deliberately

If the OS must use the new Framework commit, preserve local submodule work first (Chapter 186), then update the child to the approved revision. Run OS build/test acceptance on the resulting dependency set. Finally:

```powershell
Set-Location "C:\umicom\umicomOS"
git status
git diff --submodule=log -- framework
git add framework
git diff --cached --submodule=log
git diff --cached --check
git commit -m "chore(os): update reviewed Framework revision"
git push origin main
```

Only run this stage if the OS gitlink genuinely needs upgrading and the new Framework commit already exists on its published remote. Do not set OS to whichever revision happens to be newest without compatibility tests.

## Checkpoint D — Build and commit the learning repository

Use the native laboratory and website checks from `UPDATE_30_BUILD_TEST_AND_GIT.md`. Inspect the staged paths before creating the learning commit:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached
git commit -m "feat(learning): add C23 dispatch and advanced Git workshops"
git push origin main
git status
```

The learning documentation must link to sources that actually exist at the revision being taught. Retain older lessons even when a new lesson corrects or expands the explanation. A companion reference is available in [Git command quick reference](git-safe-commands-quick-reference.md).

## Acceptance worksheet

Before claiming completion, record the **repository name**, the **full commit hash**, the **compiler and version**, each **CTest suite and result**, any **MkDocs publication check**, the **submodule gitlink**, and **outstanding platform-specific verification**. Keep separate evidence for Windows and Linux. State explicitly when no Windows compilation was performed.

| Gate | Accepted only when |
|---|---|
| Repository identity | `git rev-parse --show-toplevel` points to the intended project. |
| Preservation | No unapproved source removals or overwritten local changes. |
| Native source policy | No new Python/PowerShell application or test scripts; C23/Assembly preferred. |
| Functionality | All named deterministic tests pass on the tested platform. |
| Dependency alignment | Parent gitlink references an available, tested Framework commit. |
| Publication | Content is navigable and strict MkDocs build passes where run. |
| Git push | Reviewed commits successfully reach the intended `origin/main`. |

## Final exercise: explain the failure rather than memorising commands

A contributor runs `git push` inside `umicomOS\framework` and receives “not currently on a branch”. Then `git push origin main` is rejected as non-fast-forward. Explain (1) which pointer the first command consults, (2) which pointer the second command tries to publish, (3) what checks protect unpublished local work and (4) why the OS parent needs a **separate** gitlink commit after a Framework upgrade. Verify your reasoning using Chapters 184–186 before running a modifying command.

**Continue studying:** [Git command quick reference](git-safe-commands-quick-reference.md) and the [official Git documentation](https://git-scm.com/docs).
