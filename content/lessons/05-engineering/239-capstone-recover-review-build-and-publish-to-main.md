# Chapter 239 — Capstone: recover, review, build and publish to `main`

**Bits to Banking · Professional contributor assessment · Umicom Foundation**  
**Prerequisites:** Chapters 216–238. **Laboratory:** `labs/native/git-three-way`.

## Scenario

A new contributor has edited Umicom Framework from the Umicom OS submodule checkout. Later, `git submodule update --init --remote framework` refuses to proceed because dozens of tracked and untracked files could be overwritten. They try `git push` and receive a detached HEAD error; `git push origin main` then fails with non-fast-forward. You must preserve the work, identify the intended Framework commit, separate source ownership from consumer checkout and qualify the parent gitlink. At the same time, your Bits2Banking learning change needs its own reviewed, separate commit.

![Framework source ownership and verified parent publication](../../assets/diagrams/git-framework-gitlinks-update34.svg)

## Phase 1 — establish identity and preserve edits

From `C:\umicom\umicomOS`, record parent HEAD, current gitlink and child HEAD. In the child, inspect `git status`, `git branch -vv`, `git log origin/main..HEAD`, `git stash list` and `git reflog`. Do not run any destructive or checkout command until local-only commits and untracked changes have been accounted for.

If necessary, preserve changes using an explicitly reviewed `git stash push --include-untracked -m "backup: ..."`, and **verify** stash contents; an ignored file is not automatically saved. Avoid restoring the stash blindly onto a newer source tree. A conflict can mean that your local work is already included in upstream or that both implementations need consolidation.

## Phase 2 — investigate the conflict

Check the common ancestor and ancestry counters after fetching:

```powershell
git -C ".\framework" fetch origin main
git -C ".\framework" merge-base HEAD origin/main
git -C ".\framework" rev-list --left-right --count HEAD...origin/main
git -C ".\framework" log --oneline --left-right HEAD...origin/main
```

If there is an actual merge conflict, inspect `git ls-files --unmerged` and each available stage 1/2/3 blob. Never silently choose a side for a C23 financial control. Use Beyond Compare, preserve approved existing features and document where any old implementation is retained under an explained disabled block.

## Phase 3 — test the teaching model

Build and test this batch's C23 laboratory. The laboratory teaches why two independent edits require a human decision; it **does not execute Git** or modify Umicom Framework. Record the actual CTest totals. Run the demo and explain why `BtbMergeMaterialise` refuses unresolved conflicts.

In the capstone report, separate three evidence columns: **educational model passed**, **real Framework integration passed**, and **Umicom OS system passed**. Do not convert NOT RUN into PASSED.

## Phase 4 — source authority and parent pin

If new reusable Framework functionality is genuinely needed, merge it into the canonical `C:\umicom\Umicom-Applications\framework`, build/test, review and publish it **first**. If Framework `main` already contains all desired changes, no new Framework commit is necessary.

After the clean OS consumer is aligned to the selected, published Framework revision, configure and test OS headless/GTK4 targets. Use Framework `umicom repo verify .` and then `umicom repo lock .` only after inspecting the intended child HEAD. Review the resulting gitlink before committing the OS parent.

## Phase 5 — publish this learning batch separately

After reviewing Update 34 in Beyond Compare and merging it into the Bits2Banking repository, build the native lab and check the website navigation. Then use the project owner's direct-to-`main` sequence:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): add Git merge recovery and C23 three-way lab"
git push origin main
git status
```

**Review what `git add -A` staged.** It includes deletions and unrelated changes if any exist. If you are not on `main`, or the push is rejected, stop and inspect the local/remote history instead of force-pushing. These commands do not automatically commit Framework or OS.

## Required evidence and assessment criteria

| Evidence | Required answer |
|---|---|
| Parent/child identity | Record separate actual SHAs, detached state and tracked/untracked changes. |
| Divergence | Show the common ancestor and ahead/behind result after a fetch. |
| Conflict review | Explain stage 1/2/3 and why both implementations may be needed. |
| Native C23 | Provide CMake/CTest output and explain the failure-atomic contract. |
| Framework | Identify its source owner and whether a new Framework commit was required. |
| OS | Explain pinned gitlink, tested profile and any pending QEMU/GUI gates. |
| Git publication | Show reviewed staging, commit SHA, remote push and clean status. |
| Unverified work | State remaining Windows/site/Framework acceptance explicitly. |

A professional solution is allowed to conclude **BLOCKED** when evidence is missing. Silent overwrites, fabricated test results and forced history rewrites are incorrect outcomes even if a subsequent build happens to pass.

## Reflection

Explain why our classroom record merge refuses a conflict while the real-world Umicom workflow may require a **new combined C23 implementation**. Explain how `git add -A`, `git commit` and `git push origin main` relate to three different states: index, local history and remote publication.

**Next milestone — Update 35:** actual Framework-backed VCS consumer walkthroughs and source-linked C23 build diagnostics, subject to verified API and test availability.
