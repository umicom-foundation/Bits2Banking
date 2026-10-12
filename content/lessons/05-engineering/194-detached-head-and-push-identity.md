# Chapter 194 — Detached HEAD, local `main` and what `git push` really sends

**Bits to Banking · Version control · Umicom Foundation**
**Prerequisites:** [Git submodules](193-umicom-framework-submodule-integration.md).

## Three similar-looking names, three separate meanings

Inside `C:\umicom\umicomOS\framework`, the checkout may be at a specific Framework commit, while the local `main` branch still names an older commit. If you execute `git push`, Git may refuse because there is no current branch with an upstream. If you execute `git push origin main`, Git will push the local **ref `main`**, not whichever detached commit you currently have checked out.

This is exactly why a push can be rejected as non-fast-forward even though `git log -1 HEAD` prints a commit that is newer than the local branch. The solution is not to add `--force` or indiscriminately use `HEAD:main`. First establish whether detached HEAD has **unpublished commits** and whether the working tree is clean.

## Read-only diagnosis

```powershell
Set-Location "C:\umicom\umicomOS\framework"
git status
git branch --show-current
git branch -vv
git log -1 --oneline HEAD
git log -1 --oneline main
git fetch origin main
git log -1 --oneline origin/main
git log --oneline origin/main..HEAD
git log --oneline origin/main..main
```

If `git branch --show-current` prints nothing, you are detached. That is normal for a submodule. If `origin/main..HEAD` prints commits, they may represent work not yet published on `origin/main`; **do not switch** until those commits have been reviewed and preserved. Likewise, files in `git status` may include changes not protected by commits.

## When no work is at risk

When the working tree is clean, no detached-only commits need rescue and the local `main` is simply behind its remote, you may move to local `main` and fast-forward:

```powershell
git switch main
git pull --ff-only origin main
git status
git log -1 --oneline
```

This updates a named local branch. It does **not** by itself change the OS parent repository's gitlink; the parent must separately record and test the chosen Framework SHA. Do not switch merely to suppress the detached-head message when the parent intentionally pins a historical revision.

## Publishing genuinely new Framework work

Framework implementation work should be integrated from the canonical checkout at `C:\umicom\Umicom-Applications\framework`, on `main`, after reviewing relevant changes and running tests. The expected command shape is:

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(framework): improve shared capability"
git push origin main
```

**Never run this block blindly.** It assumes the local branch is `main`, upstream history is synchronised and the staged changes match one reviewed, tested modification. The commit message must describe the real work, not an invented success. In the OS checkout, the normal goal is to consume the published Framework commit and record the parent pointer—**not** to generate duplicate Framework commits.

## Short assessment

A developer says: “`git log -1 HEAD` shows commit D, so `git push origin main` will push D.” Give a counterexample with local `main` at B, remote `origin/main` at D, and detached `HEAD` at D. Explain the failed assumption using Git refs rather than vague descriptions of branches.

**Next:** [Stash, recovery and collision-safe restoration](195-stash-and-collision-safe-recovery.md).
