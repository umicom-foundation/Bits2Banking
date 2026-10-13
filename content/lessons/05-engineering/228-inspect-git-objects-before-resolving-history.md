# Chapter 228 — Inspect Git objects before resolving history

**Bits to Banking · Professional Git engineering · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisite:** Chapters 191–227 · **Duration:** 45–60 minutes.

## The engineering problem

A contributor says, "Git lost my Framework changes." Before making a recovery decision, establish what Git actually recorded. Git is not a folder of copied source-code versions. It stores objects: file content as **blobs**, directory mappings as **trees**, and changeset metadata and parent relationships as **commits**. Names such as `main`, `origin/main` and tags point at commits. The contents of a commit are recoverable as long as the object remains available; whether a name still points to it is a separate question.

![Commit data and references](../../assets/diagrams/git-three-way-versions-update34.svg)

In Umicom, one published Framework commit may be referenced by several *different* parent gitlinks. That is why a clean `umicomOS` working tree does not mean the OS is pinned to the newest Framework revision.

## Prerequisite check

Confirm that Git is installed, and use read-only commands first. These commands are safe to try in a working Umicom checkout because they do not stage or edit files:

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git --version
git status --short
git rev-parse --show-toplevel
git rev-parse HEAD
git rev-parse refs/heads/main
git rev-parse refs/remotes/origin/main
```

`HEAD` means the checked-out commit. `refs/heads/main` means your **local** branch tip. `origin/main` is a local record of what you last fetched, not a live remote query. These three identifiers can be different without any Git database corruption.

## Inspect a real commit, tree and file

```powershell
git cat-file -t HEAD
git cat-file -p HEAD
git ls-tree HEAD
git show --stat --oneline HEAD
git log --oneline --decorate -8
```

The output of `git cat-file -p HEAD` contains the commit's `tree`, `parent`, `author`, `committer` and message fields. Find the tree identifier and use `git ls-tree` to inspect the files it contains. `git show` is better for a human-friendly summary; `git cat-file` exposes the underlying format.

Next inspect one tracked file without modifying it:

```powershell
git ls-tree HEAD -- CMakeLists.txt
git show HEAD:CMakeLists.txt
```

The first command shows the tree entry, including file mode and object identifier. The second retrieves that file's committed content. It is **not** the current working-tree file if you have uncommitted edits.

## SHA-1 and SHA-256 are not interchangeable

Git repositories can use different object formats. Check yours rather than assuming every object identifier is 40 characters:

```powershell
git rev-parse --show-object-format
git rev-parse --verify HEAD
```

Classic Git uses 40 hexadecimal characters for SHA-1 object names. SHA-256 repositories use 64. The identity is content-addressed, but verifying a Git SHA alone does not certify software quality, code authorship or release readiness. A release also needs reviewed source, provenance, tests and a recorded dependency revision.

## Practical interpretation

Imagine Framework commit `F2` implements ledger validation, and Umicom OS still records Framework gitlink `F1`. `git log` in the OS parent shows its own history; it does not automatically show every Framework source commit. Open `framework` as a separate repository to inspect its objects. The parent records a *reference*, not a copy of each child source file.

## Guided exercise

1. Record the three identifiers for HEAD, local main and origin/main in the Framework directory.
2. Inspect the most recent commit's parent and tree with `git cat-file`.
3. Inspect one committed header using `git show HEAD:<path>` and compare it with the working file via `git diff -- <path>`.
4. Explain which observation could establish that a change is **committed**, which establishes that it is **published**, and which would establish that an OS parent **uses it**.

## Review questions and answers

**Question:** Does `git push origin main` publish a detached `HEAD`? **Answer:** No. It pushes the local `main` ref, which may not point at the checked-out commit. **Question:** Is `origin/main` necessarily current? **Answer:** No; it must be refreshed using `git fetch` and checked. **Question:** Does a valid commit SHA prove a passing build? **Answer:** No; build and test evidence must be associated with that exact source and dependency state.

**Next:** identify the merge base and understand why Git sometimes refuses a push.
