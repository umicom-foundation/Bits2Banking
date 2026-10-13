# Chapter 219 — Review Umicom Framework gitlinks across repositories

**Bits to Banking · Multi-repository engineering · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Chapters 193, 200 and 218.

## Why this matters

Umicom Applications and Umicom OS consume the **same canonical Umicom Framework repository** at potentially different pinned revisions. A successful `git pull` in Umicom OS does not automatically mean its Framework child is current. Conversely, checking out the newest Framework commit inside OS does not publish a new OS gitlink. The parent and child are independent repositories with independent commit histories.

The canonical repository map is documented in Framework's `docs/SHARED_FRAMEWORK_SUBMODULE_UPDATE_POLICY.md`. That document is the starting point for real operations; this chapter is a worked explanation of its constraints.

![Canonical Framework source and separately pinned parent gitlinks](../../assets/diagrams/git-parent-child-evidence-update33.svg)

## Evidence to collect

In PowerShell, begin at the OS parent:

```powershell
Set-Location "C:\umicom\umicomOS"
git status
git ls-files --stage framework
git submodule status framework
git -C ".\framework" rev-parse HEAD
git -C ".\framework" status --short
```

Then inspect the Applications Framework checkout independently:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
git submodule status framework
git -C ".\framework" rev-parse HEAD
git -C ".\framework" branch --show-current
```

These are observations. The two child checkouts may be at different revisions without violating Git rules; the question is whether those revisions are deliberately selected and tested.

## Correct publication order

The controlled order is **Framework source → Framework tests → Framework commit/push → consumer checkout update → consumer tests → parent gitlink commit/push**. A Framework change is authored once in `Umicom-Applications\framework`. The OS child consumes its published revision; it should not become a second place where the same source patch is manually copied. `umicom-kernel` remains an independent project and must not gain a Framework submodule merely for symmetry.

The native Framework CLI offers read-only `umicom repo verify .` and a staging operation `umicom repo lock .`. The latter resolves initialised child HEADs and stages gitlinks; it does **not** fetch, build, commit or push. You still review the staged pointer and run tests yourself.

```powershell
Set-Location "C:\umicom\umicomOS"
git diff --submodule=log -- framework
git diff --cached --submodule=log -- framework
```

The first command describes unstaged parent changes; the second describes the index. Neither checks whether the child commit is published remotely. That requirement needs its own evidence.

## What not to do

Do not solve a dirty child checkout with `git submodule update --force`. Do not use `git clean -fd` to remove untracked C23 source. Do not replace the entire `framework/` folder with an extracted ZIP. Do not commit a new OS gitlink before the child tests have passed against the exact checked-out Framework revision. A visually clean Studio application is not enough evidence for OS service or boot functionality.

## Assessment

For a change from child SHA A to child SHA B, identify (a) the source repository that publishes B, (b) the parent commit that records B, (c) the exact tests required at each layer and (d) what a clean `git status` does **not** prove. Then draw both commit graphs separately. Why is the parent's `160000` gitlink not a directory tree of C source?

**Next:** [Chapter 220 — Local changes and stash recovery](220-preserve-work-before-git-synchronisation.md).
