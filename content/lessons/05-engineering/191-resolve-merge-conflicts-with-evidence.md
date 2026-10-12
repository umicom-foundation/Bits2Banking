# Chapter 191 — Resolve Git merge conflicts without losing source

**Bits to Banking · Software engineering · Umicom Foundation**
**Prerequisites:** [Git states and history](182-git-working-tree-index-and-history.md), [safe staging](189-review-recover-and-revert-safely.md).
**Repository policy:** Umicom maintainers commit to `main`; this exercise uses a disposable practice repository, not production source.

## The problem we are solving

A developer changes a GTK4 menu in Umicom Studio while another contributor changes the same lines. Git can combine independent edits automatically, but it cannot decide which competing implementation is correct. A **merge conflict** is a request for a human engineering decision, not evidence of a damaged repository. A successful merge must preserve intended behaviour, headers, test coverage and explanatory comments.

Git stores three useful versions during a normal content conflict: **base**, **ours** and **theirs**. In a merge, ours is the checked-out side and theirs is the commit being merged. During a rebase the labels can surprise you because Git is replaying commits onto another base. Never resolve a conflict simply by choosing every occurrence of “ours” or “theirs”.

## Observe first

In a repository already reporting conflicts, use these **read-only** commands:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
git status
git diff --name-only --diff-filter=U
git ls-files -u
git diff --check
```

`git ls-files -u` shows the index's unmerged stages. Stage 1 is the common ancestor, stage 2 is ours, and stage 3 is theirs (when those stages are present). These are **not** the same as the usual index/worktree status letters. An unresolved file may contain markers such as `<<<<<<<`, `=======` and `>>>>>>>`, but binary conflicts and modify/delete conflicts will not necessarily present ordinary text markers.

If the conflict is in `CMakeLists.txt`, check which source files each side registers, which `target_link_libraries` relationships they require and whether a test target was removed. A clean-looking file that silently omits a target is not a successful resolution.

## A safe resolution procedure

1. Before editing, identify the base change and both intended features. Record the relevant commit IDs from `git log --oneline --max-count=10`.
2. Compare complete implementations using your editor or Beyond Compare. Preserve source headers, licences, comments, public interfaces and test registrations.
3. Edit the conflicted file to its intended combined version. Remove conflict markers only **after** both behaviours are accounted for.
4. Inspect the actual working tree with `git diff -- <path>` and your project's compiler/test output.
5. Stage only the resolved file, then verify that `git ls-files -u` has no remaining entries.
6. Use `git diff --cached --check` and `git diff --cached` to review what will actually be committed.

Example staging for a reviewed conflict:

```powershell
git add CMakeLists.txt
git ls-files -u
git diff --cached --check
git diff --cached -- CMakeLists.txt
```

Do **not** run `git commit` while unrelated unresolved files or tests remain. A merge being completed may create a merge commit; a rebase-in-progress requires its own continuation command. Determine which operation Git reports in `git status` rather than guessing. Avoid force operations and hard resets when preservation matters.

## Practical exercise

Create two conflicting variants of a file in a disposable test repository using an editor and normal Git commits. Observe the conflict and resolve it with both comments retained. In the final file, use an Umicom banking example: one change validates the account currency; the other checks the authorised user. The resolved logic must perform **both checks**, not simply retain whichever version appears first. Run the existing tests for that exercise.

## Think and verify

- Why does a zero-line output from `git ls-files -u` not guarantee correct behaviour?
- What is the difference between `git diff` and `git diff --cached` during resolution?
- Why must we not use `--ours` blindly during a rebase?
- Which file header and licence details must survive a conflict in Umicom Framework?

**Next:** [Classify local and remote history before pulling or pushing](192-fetch-and-divergent-history.md).
