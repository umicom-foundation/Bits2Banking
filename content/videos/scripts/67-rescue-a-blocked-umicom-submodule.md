# Episode 67 — Rescue a blocked Umicom Framework submodule

**Bits to Banking · Umicom Foundation**
**Related chapters:** [193 — Submodules](../../lessons/05-engineering/193-umicom-framework-submodule-integration.md), [195 — Stash and recovery](../../lessons/05-engineering/195-stash-and-collision-safe-recovery.md)
**Suggested length:** 10–12 minutes.

## Purpose

Demonstrate a responsible recovery process when `git submodule update --init --remote framework` refuses to overwrite modified and untracked files. All screen commands operate on a **disposable repository prepared by the instructor**. The real Umicom repository is used as a path diagram, not modified during recording.

## 00:00–02:00 — Establish the source owner

**Show:** `git-framework-gitlinks.svg`. The Framework remote is the single source owner. `Umicom-Applications` and `umicomOS` each have a gitlink that records an exact Framework commit. `umicom-kernel` is not a Framework submodule.

**Narration:** “A submodule is not just an ordinary folder copied into another repository. The parent's tracked record contains a commit ID. Changing files inside the child and committing the parent without first publishing the child cannot provide collaborators with those new source files.”

## 02:00–04:00 — Reproduce the failure

Create a harmless untracked `.c` file and a tracked documentation edit inside the **practice submodule**. Display `git status --short`, then show a checkout/update that would collide and Git's refusal. Do not use any forced operation.

**Narration:** “Git is protecting two categories of work. One is a tracked file whose contents changed. The other is an untracked file that would be overwritten by the incoming revision. A tracked-only stash does not solve the second problem.”

## 04:00–06:30 — Preserve work

```powershell
git status --short
git fetch origin main
git log --oneline origin/main..HEAD
git stash push --include-untracked -m "backup: before safe review"
git status --short
git stash list
git stash show --include-untracked --stat 'stash@{0}'
```

**Narration:** “We inspect detached-only commits before switching because a stash saves file changes, not arbitrary unpublished commits. We use include-untracked because the error explicitly listed new files. We confirm that the stash succeeded. Ignored files require a separate decision.”

## 06:30–09:00 — Synchronise and compare

Demonstrate the difference between pinned update and `--remote` in the practice parent. Choose only one based on the planned integration. Inspect new child HEAD and compare it with stash content through staged/working diffs or Beyond Compare. Explain why similar filenames are not proof of identical implementation.

## 09:00–11:30 — Parent publication

Show the Framework's native C23 `repo verify` and `repo lock` responsibilities as a conceptual flow—only run commands if the matching built tool is available. Stage and review a **parent** gitlink with `git diff --cached --submodule=log`, then explain that tests must pass and the child commit must be published before parent commit and push.

**End question:** “Why do we commit the Framework source first and the OS gitlink second?” The answer should include reproducibility and remote object availability.
