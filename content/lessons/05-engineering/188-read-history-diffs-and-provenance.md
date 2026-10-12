# Chapter 188 — Read Git history, compare versions and investigate regressions

**Bits to Banking · Version-control track · Umicom Foundation**  
**Tools:** Git and PowerShell commands · **Prerequisite:** Chapter 187.

## A bug report needs a source revision

Someone reports that an Umicom Studio panel stopped displaying a saved document after a build. “I have the latest code” is not enough to reproduce the defect. The investigator needs the exact repository, commit ID, build preset, compiler and steps required to cause the problem. Git provides the source revision and change history; CTest and build logs provide separate execution evidence.

## Find out what is checked out

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git rev-parse --show-toplevel
git rev-parse HEAD
git log -1 --format="%H%n%an%n%ad%n%s" --date=iso-strict
git status --short --branch
```

The 40-character (or algorithm-dependent) commit ID identifies the object you built. Store it in your test report. Do not assume that a file name or ZIP date uniquely identifies a Git version.

## Read a small history graph

```powershell
git log --oneline --decorate --graph -15
git show --stat --oneline HEAD
git show --format=fuller --no-patch HEAD
```

The graph displays ancestry; decoration shows branch and tag names. `git show --stat` reveals the files touched by a commit. `--no-patch` shows the metadata without the full source diff. Author and committer dates may differ, and neither establishes that all tests were run.

## Investigate one real file without changing it

Suppose the training lesson `content/lessons/05-engineering/16-git.md` became unclear after an edit:

```powershell
git log --oneline -- "content/lessons/05-engineering/16-git.md"
git blame -- "content/lessons/05-engineering/16-git.md"
git log -p -2 -- "content/lessons/05-engineering/16-git.md"
```

`git blame` associates each currently displayed line with a historical commit. It is a **starting point for investigation**, not proof of who caused a defect. The author may have preserved older code or moved logic from another file. Read the surrounding history and engineering rationale before judging a change.

## Compare commits precisely

```powershell
git diff HEAD~1 HEAD --stat
git diff HEAD~1 HEAD -- "content/lessons/05-engineering/16-git.md"
git show HEAD:"content/lessons/05-engineering/16-git.md"
```

`HEAD~1` means the first parent of `HEAD`; it is unavailable in a repository with only a root commit. The first two commands compare an older version and the current commit. `git show HEAD:path` reads the committed file at that revision; it does not overwrite the working tree. Contrast this with `git restore --source`, which can modify local files and therefore requires review.

To compare specific known commits, use their verified hashes. In a submodule, remember that a parent repository's diff usually shows a **gitlink change**, not the nested source patch. Inspect the nested repository separately using `git -C framework show ...`.

## Preserve historical implementation comments

When a refactor supersedes an earlier method, Umicom's source-preservation policy requires retaining the previous implementation for review unless the project owner approves deletion. Before accepting a replacement, check `git diff --cached` for deleted code, documentation, licence headers, callbacks, tests and comments. If the old executable path cannot remain active, document why, retain an explicit disabled implementation where suitable and add a regression test for the intended behaviour.

Git history makes restoration possible, but it is **not** a justification for silently deleting authorial work from a review package. A project must still make migration decisions understandable to its maintainers.

## Exercises

1. Pick a single changed Markdown file in a practice repository. Find the last three commits affecting it and name one nontrivial change in the patch.
2. Record the exact commit that produced a passing CTest log and explain why a passing build on another commit is not identical evidence.
3. Investigate a hypothetical changed Framework header. Which commands show the public API diff and which show the history of its implementation?
4. Why might `git blame` point to a formatting commit rather than the author who originally designed a function?

**Next:** [Review, recover and revert without losing work](189-review-recover-and-revert-safely.md).
