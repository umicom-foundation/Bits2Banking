# Chapter 200 — Integrate Umicom Framework, Applications and OS in the correct order

**Bits to Banking · Multi-repository engineering · Umicom Foundation**
**Prerequisites:** Chapters 193, 194 and 199.

## One authoritative Framework, several consumers

Umicom Framework is the reusable source owner. The Applications and OS repositories consume particular Framework commits through Git submodules; Umicom Kernel remains independent of the Framework. This design prevents one new VCS utility being copied into Studio, OS and Bits2Banking. The same rule applies to C23 process execution, repository inspection, status parsing, gitlink recording, configuration and UI adapters.

For a real reusable change, the correct sequence is **Framework implementation → Framework tests → Framework commit/push → consumer checkout update → consumer tests → consumer gitlink commit/push**. A parent commit that records an unpublished child SHA cannot be reproduced reliably by another contributor.

## Work in Framework's canonical development checkout

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git status
git branch --show-current
git fetch origin main
git log --oneline origin/main..HEAD
```

Only after confirming that you are on `main`, source changes are reviewed, and the Framework build/tests have passed, stage and publish:

```powershell
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(framework): extend reviewed shared service"
git push origin main
```

This is an illustrative release command block: do not commit a placeholder message or untested code.

## Update the Applications parent

```powershell
Set-Location "C:\umicom\Umicom-Applications"
git status
git diff --submodule=log -- framework
```

Build and test the correct parent configuration. The existing Framework-owned `umicom repo verify .` is a **read-only** review command; `umicom repo lock .` is the native, C23-owned gitlink-staging operation. It does not pull child source, create a commit or push anything. Use your actual built Framework executable and inspect every lock action before committing the Applications parent. Parent `git add -A` can stage unrelated application submodule pointer changes; review those individually.

## Update the OS checkout

```powershell
Set-Location "C:\umicom\umicomOS"
git -C ".\framework" status
git -C ".\framework" log --oneline origin/main..HEAD
git submodule update --init --remote framework
git submodule status framework
git diff --submodule=log -- framework
```

Only use the `--remote` step when the child is clean, any unpublished HEAD commits are preserved and OS deliberately targets the new Framework revision. Then perform the OS headless/GTK4 CMake and CTest acceptance required for your change. The Framework-owned native `repo verify`/`repo lock` commands can inspect and stage the OS gitlink where that executable is available. Review and publish only after all intended parent changes are understood.

## Parent commit sequence

```powershell
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached --submodule=log
git commit -m "chore(os): record verified Framework integration"
git push origin main
```

This does not publish any new Framework source; the child commit must already be on the Framework remote. If the application/OS build fails, do not mark the gitlink as accepted merely because `git submodule update` succeeded.

## Exercise

Construct a dependency table for Framework, Applications, OS and Kernel. Note the authoritative source owner, build test target, Git remote, consumer pointer and order of publication. In a separate training environment, simulate a parent pointing to an unavailable child commit and explain why a fresh clone would fail to initialise that submodule.

**Next:** [GitHub reviews and maintainer responsibility](201-github-reviews-and-approvals.md).
