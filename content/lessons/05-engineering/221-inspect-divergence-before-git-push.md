# Chapter 221 — Diagnose remote divergence before Git push

**Bits to Banking · Git operations · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Chapters 192, 209 and 220.

## Why this matters

A failed `git push origin main` is usually a refusal to overwrite remote history, not a request to add `--force`. Suppose a colleague has published new Framework C23 tests while your local `main` still points to an older commit. Git will normally reject your non-fast-forward push. Your next task is to learn how the two histories differ and integrate them without discarding either line of development.

The words *ahead* and *behind* refer to commit graph reachability. They are not timestamps. The local branch may be behind even if a working file has a newer modification time; likewise, a fresh fetch does not by itself combine the remote changes with your local branch.

## Observe without changing source files

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git status
git branch -vv
git fetch origin main
git log --oneline --left-right HEAD...origin/main
git rev-list --left-right --count HEAD...origin/main
git log --oneline origin/main..HEAD
git log --oneline HEAD..origin/main
```

In `HEAD...origin/main`, the left side contains commits reachable only from `HEAD`; the right side contains commits reachable only from `origin/main`. The two counts allow you to distinguish a simple fast-forward from a genuinely divergent pair of histories. They do not tell you whether the modifications are semantically compatible or whether tests will pass after integration.

`git fetch` updates local knowledge about remote refs; it does not rewrite your current working files. Even so, the observation may become stale immediately when someone else pushes. A live production release pipeline needs a fresh remote check close to publication and must handle a race if another commit arrives.

## When a fast-forward is possible

If your local `main` is strictly behind `origin/main` and has no local-only commits, a clean checkout can be advanced with:

```powershell
git pull --ff-only origin main
```

This refuses to invent a merge commit if histories diverge. **Do not run it when uncommitted or unpublished work needs protection.** First complete the Chapter 220 preservation checklist. If local commits exist on both sides, inspect patches and dependencies before deciding between a reviewed merge or rebase. The right integration method depends on repository policy and whether a commit has already been shared. For Umicom internal development, avoid adding branches as an automatic repair technique; follow the established direct-to-main workflow with a reviewed integration.

## Distinguish three Git commands

`git push` with no upstream on a detached child may fail because no current branch exists. `git push origin main` refers to local `main`, which may still be behind. `git push origin HEAD:main` would attempt to update remote `main` from the current checkout, but it is not a safe shortcut around missing ancestry checks and must not be used as an automatic fix for this situation. Understand each reference before publishing.

## Native evidence connection

The Framework `UmiVcsWorkingTreeSummary` distinguishes `ahead`, `behind`, `detached` and whether divergence was successfully observed. The Update 33 C23 teaching model adds an explicit caller-provided `remoteFresh` value. A positive value means only that the caller **claims** to have recently refreshed remote state. The model itself performs no fetch and makes no promise about races after observation.

## Exercise

Draw two graphs. In the first, `main` has no local-only commits and is two behind; demonstrate why a fast-forward is possible. In the second, local and remote each have one unique commit; demonstrate why `--ff-only` refuses. For both, list read-only commands to inspect the difference, and identify why force-push would be inappropriate.

**Next:** [Chapter 222 — Temporal evidence in C23](222-design-a-c23-observation-timeline.md).
