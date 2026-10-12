# Chapter 205 — Review the Git index and working-tree evidence

**Bits to Banking · Professional Git track · Umicom Foundation**  
**Prerequisites:** [Chapter 204](204-observe-git-through-umicom-framework.md).  
**Practice location:** a disposable training repository; never practise destructive recovery on active Umicom sources.

## Why the staging area is an engineering control

The Git index is not simply a queue of filenames. It describes the exact content snapshot that the next commit will record. `git add -A` updates the index with all detectable additions, modifications and deletions beneath the current repository. That scope can include files outside the feature a developer intended to publish. In Umicom, a mistaken deletion of a learning chapter, licence header or GTK4 implementation is not an acceptable side effect of tidying the index.

A safe maintainer workflow therefore has a **review gate** between staging and committing. The gate asks: *What will this commit change? Does each change belong to the intended batch? Have existing functionality, comments and authorship been preserved?*

![A staged snapshot is not automatically the whole working tree.](../../assets/diagrams/git-index-review-update32.svg)


## Compare three independent states

| State | What it represents | Read-only command |
|---|---|---|
| HEAD | Most recent commit in the checkout | `git show --stat --oneline HEAD` |
| Index | Content staged for the next commit | `git diff --cached` |
| Working tree | Files currently on disk, including unstaged edits | `git diff` |

Git also tracks untracked files separately. `git diff` does not show their contents because they are not yet present in the index. Always pair diffs with `git status --short`, and inspect new files before adding them.

On the Bits2Banking checkout:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status --short
git diff --stat
git diff --cached --stat
git diff --check
git diff --cached --check
```

These inspection commands are safe. `--check` detects whitespace errors but does **not** establish that the C23 code compiles, that a removed function was unnecessary, or that MkDocs navigation is complete. A clean diff check is one condition, not a release certificate.

## Build a reversible local exercise

Inside a disposable practice repository created in the earlier Git lessons, create `README.md` and `examples/ledger.txt`. Modify the first file and create a second training file. Observe `git status --short`, then stage only `README.md`:

```powershell
git add README.md
git diff --cached --stat
git diff --stat
git status --short
```

The first diff now shows the staged README change, whereas the new `ledger.txt` remains untracked. Stage all changes using the requested maintainer command:

```powershell
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached
```

**Stop before committing** if any unexpected file appears. To remove a mistaken file *from the staging area without deleting it on disk*, use `git restore --staged -- path/to/file` for that file. This is not the same as `git restore -- path/to/file`, which can replace a working file with index content and lose edits. Keep these commands distinct.

## What a submodule looks like in the index

Git does not store all Framework files inside Umicom OS. The parent stores a gitlink entry (mode `160000`) whose value is a commit identifier. A staged Framework update in OS is therefore normally one path named `framework`, not hundreds of individual Framework C files. Inspect it using:

```powershell
Set-Location "C:\umicom\umicomOS"
git diff --cached --submodule=log
git ls-files --stage framework
git -C ".\framework" status --short
```

Reviewing only `git diff --cached --stat` is insufficient. The gitlink might advance to a commit that is still only local; the OS remote would then reference a commit other contributors cannot fetch. Later chapters show how to prove publication of the child commit before updating the parent.

## Preserving implementation during review

For a C23 refactor, compare complete original and replacement files in Beyond Compare. A removed function may look unused while still providing a public ABI or educational example. Preserve superseded implementations under an explicitly commented disabled block when required by Umicom policy; seek approval before physical deletion. In GUI work, also verify menus, keyboard shortcuts, tooltips and child widget creation paths, not merely successful compilation.

## Practical assessment

A staged diff contains a new `tests/vcs/...` file and a deletion of an existing `docs/learning/...` document. The test is intended, the deletion is not. Identify the evidence command, unstage only the deletion, and explain why no cleanup tool should remove the old document. A correct answer inspects `git diff --cached --name-status` and uses `git restore --staged -- docs/learning/...` **with a real existing path**, then rechecks the staged diff.

**Next:** [Chapter 206 — Verify a fast-forward before pulling](206-fast-forward-without-rewriting-history.md).
