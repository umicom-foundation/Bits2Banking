# Chapter 220 — Preserve local work before Git synchronisation

**Bits to Banking · Source-preservation workshop · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Chapters 186, 195 and 219.

## Scenario

You attempt `git submodule update --init --remote framework`. Git refuses because tracked modifications would be overwritten, and also lists untracked files that would collide with the target revision. This safeguard protects potentially unpublished work. A sensible recovery begins by inspecting **what exists**, not by deleting it.

The difference between a tracked modification, an untracked file, an ignored file and a local commit matters. Each requires a different form of preservation. A stash protects some of them; it is not a universal backup of everything inside a repository.

## Step 1 — inspect and preserve evidence

```powershell
Set-Location "C:\umicom\umicomOS\framework"
git status --short
git status --ignored --short
git branch -vv
git log --oneline origin/main..HEAD
git stash list
```

Do not stage unknown credentials or generated binaries merely to make them visible. If the repository contains important ignored source or sensitive local configuration, protect it separately outside the project before attempting cleanup. In Umicom, `secrets.env` and credentials must never be committed.

## Step 2 — optionally use a reviewed stash

After confirming which untracked files belong to the change, you can store tracked and untracked work:

```powershell
git stash push --include-untracked -m "backup: before Framework synchronisation"
git stash list
git stash show --include-untracked --stat 'stash@{0}'
git status --short
```

`--include-untracked` does **not** include ignored paths. The stash does not automatically publish or preserve local commits. If the stash fails or status remains unexpectedly dirty, stop. Avoid force-updating the child because you cannot yet account for the outstanding files.

A stash is not proof that work has been merged into `main`. Later, compare its tracked content with the updated checkout and inspect any separately stored untracked entries. Retain the stash until the full source has been reconciled and tests pass. `git stash pop` may produce conflicts; do not run it blindly just because an update succeeded.

## Step 3 — protect commit history

To inspect potentially unpublished commits, use:

```powershell
git log --oneline origin/main..HEAD
git reflog --date=iso -12
git show --stat HEAD
```

The reflog records local movements of references and HEAD. It is useful for locating a commit whose branch pointer changed. It is **not** an off-machine backup and its records can expire. If you find a valuable commit, record its full object ID and inspect its contents before deciding how to reintegrate it. Do not force-push a reconstructed history over colleagues' work.

## Recovery decision table

| Evidence | Safe immediate action | Do not assume |
|---|---|---|
| Modified tracked files | Inspect and preserve diff or reviewed stash | Remote contains them |
| Untracked C23 source | Back up or include in reviewed stash | `git stash` default saves it |
| Ignored files | Identify and preserve important items separately | `--include-untracked` saves ignored paths |
| Local-only commit | Record SHA and inspect history | Switching branches will keep it visible |
| Child HEAD newer than parent gitlink | Review published SHA and integration tests | Parent already records the update |

## Connection to C23

The Update 33 observation model contains `untracked`, `entries` and `dirtyChildren`, because “dirty” without context is too ambiguous for a recovery plan. It cannot preserve local files, by design. Real working-tree state belongs to Framework VCS; the actual safeguard remains explicit human review before mutating Git commands.

## Questions

What is the difference between `git stash push` and `git stash push --include-untracked`? Why can `git status --short` display no output after a stash while important ignored files still exist? Why does `git reset --hard` fail the Umicom source-preservation policy when used as a generic repair?

**Next:** [Chapter 221 — Diagnosing remote divergence safely](221-inspect-divergence-before-git-push.md).
