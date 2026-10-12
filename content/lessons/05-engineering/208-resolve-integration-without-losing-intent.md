# Chapter 208 — Resolve integration conflicts without losing author intent

**Bits to Banking · Professional Git track · Umicom Foundation**  
**Prerequisites:** [Chapter 191](191-resolve-merge-conflicts-with-evidence.md) and [Chapter 207](207-publish-a-tested-framework-gitlink.md).

## A merge tool cannot decide application behaviour

Suppose one contributor adds a GtkSourceView diagnostic marker while another fixes the existing editor's painting behaviour. Both change `adapters/gtk4/...` in Umicom Framework. Git may show a textual conflict, but only a maintainer who understands the editor's user-facing behaviour can safely integrate both changes. Choosing the newer timestamp, accepting every “ours” hunk or replacing the entire file can remove code paths, tooltips, public headers or comments that the Framework is required to preserve.

In Git, a **merge** combines two histories; a **rebase** rewrites a series of commits atop another base; a **cherry-pick** copies one commit's patch onto a different history. Those operations solve different problems. They should never be used interchangeably as a way to “make Git stop complaining.” In Umicom's canonical repositories, publishing directly to `main` is the established maintainer policy; use a disposable practice repository to learn history rewriting.

## Read conflicts before resolving

When Git reports unresolved entries:

```powershell
git status
git diff --name-only --diff-filter=U
git ls-files -u
git diff --check
```

An unmerged index can contain stages 1 (common ancestor), 2 (ours) and 3 (theirs). Inspecting all three reveals what *both* sides changed. During rebase, “ours” and “theirs” refer to the replay context, and the familiar interpretation can be reversed; do not select a side based only on the label.

A responsible resolution for a C23 file preserves the ownership contract, public ABI, error handling and both independent features where required. Use Beyond Compare to review the complete old and new files. Compile affected targets, rerun regression tests, and only then mark the conflict resolved with `git add path/to/file`.

## Detached HEAD and conflict are not the same problem

In `umicomOS/framework`, Git can be detached at a valid pinned commit even when every file is clean. That state is not a conflict. An **unpublished detached commit** is more serious: it can be lost from ordinary branch navigation if nothing keeps a reference to it. Inspect:

```powershell
git -C ".\framework" status
git -C ".\framework" log --oneline origin/main..HEAD
git -C ".\framework" reflog -8
```

If a detached commit contains valuable work, stop and preserve its commit ID and contents before any checkout. Use a reviewed integration plan; do not force a checkout or push a stale local `main` branch. The earlier recovery chapters explain how to rescue unreachable work using reflog and review tools.

## A practical conflict classification

| Symptom | Likely scope | Engineering response |
|---|---|---|
| `both modified` in one `.c` file | Content conflict | Review base and both sides; preserve semantics; test |
| `modify/delete` | One side removed a file | Determine whether deletion was intentional and approved |
| `both added` | Two implementations compete | Compare public contracts and select or compose deliberately |
| Parent gitlink differs | Dependency conflict | Select one *published, tested* child SHA, then test parent |
| Untracked file would be overwritten | Checkout collision | Preserve or move local file first; never force |
| Push rejected | Remote ancestry issue | Fetch and inspect; do not interpret as a merge conflict automatically |

## Exercise: resolve a fictional API refactor

Take a *disposable* Notes module and imagine two versions of `NotesSave`: one adds a new validation error, the other fixes ownership after allocation failure. Write a review note specifying both obligations: invalid note length must not modify the old document, and allocation failure must leave the original document intact. A correct resolution includes both behaviours and retains explanatory comments. Use `git diff --check` and a CTest case for each condition. A one-line conflict-marker deletion is not sufficient evidence.

## Avoid history rewriting on shared main

Do not run `git push --force` to overcome a non-fast-forward rejection. Do not automatically rebase already published shared `main` commits. A cherry-pick may be appropriate for a specifically approved backport, but it creates a new commit identity and needs its own regression evidence. Use normal commits and verified fast-forwards for routine Umicom integration.

**Next:** [Chapter 209 — Diagnose a rejected push](209-troubleshoot-a-rejected-push.md).
