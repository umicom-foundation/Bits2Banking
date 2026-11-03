# Remotes and safe updates

A remote is another repository you can communicate with. Updating a remote and changing your local working files are separate operations.

## Understand four names

`main` is a local branch. `origin` is a configured remote name, not a guarantee about who owns a server. `origin/main` is your locally stored observation of the remote branch after a fetch. The actual remote may have changed since that observation.

 <svg viewbox="0 0 700 110" role="img" aria-label="Fetching records remote information. A checked fast-forward then advances a compatible local branch." style="width:100%;max-width:700px"><title>Fetching records remote information. A checked fast-forward then advances a compatible local branch.</title><rect x="10" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="115" y="53" text-anchor="middle" fill="white" font-size="17">Fetch remote history</text><path d="M220 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="240" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="345" y="53" text-anchor="middle" fill="white" font-size="17">Review difference</text><path d="M450 47h18l-7 -6m7 6l-7 6" fill="none" stroke="#287b78" stroke-width="3"></path><rect x="470" y="15" width="210" height="65" rx="8" fill="#203247"></rect><text x="575" y="53" text-anchor="middle" fill="white" font-size="17">Fast-forward if safe</text></svg>

Fetching records remote information. A checked fast-forward then advances a compatible local branch.

```text
git remote -v
git status --short --branch
git fetch --no-recurse-submodules origin
git log --oneline --left-right main...origin/main
```

These commands assume the repository has the named remote and branches. If not, inspect its configuration; do not rename branches as a shortcut. A left marker in the last command indicates a commit unique to local main; a right marker indicates one unique to origin/main.

## Update a clean main checkout

When you have confirmed you are on main, have no local changes to preserve and want the incoming commits, use:

```text
git pull --ff-only --no-recurse-submodules origin main
```

A **fast-forward** moves a branch forward along history it already belongs to. If each side has unique commits, this command refuses. That refusal preserves a decision for review; it is not an instruction to reset or force anything. A pull is a fetch followed by integration. It is not a universal conflict repair.

## Publish a reviewed local commit

```text
git push origin main
git status --short --branch
```

A push transfers commits. It does not upload unstaged edits. A rejected push usually needs fresh inspection of the remote and local histories; do not retry with force. A successful push says nothing about independently edited copies elsewhere on the computer.

## Read the state before acting

| Observed state | Next decision |
| --- | --- |
| Clean main, only remote commits ahead | Review and fast-forward. |
| Uncommitted files | Review and preserve that work before integration. |
| Commits unique to both sides | Compare both histories; resolve as a separate task. |
| Detached HEAD | Inspect unpublished commits before any branch transition. |

Detached HEAD means your current position names a commit directly rather than a branch. It is common in submodule checkouts. A clean working tree does not prove that its commits have been published.

## Exercise

Two developers begin at commit A. One records B and publishes it. The other records C locally from A. Can the second checkout fast-forward to B without a decision about C?

<details>

<summary>Answer</summary>

No. B and C are different continuations. The safe routine refuses. Preserve C and inspect both changes; a single push or pull command cannot decide their intended combined meaning.

</details>

---

[Read this lesson in HTML](../../../courses/introduction-to-version-control/lessons/03-remotes-and-safe-updates.html) · [Learning sequence](../../../start/learning-sequence.md)
