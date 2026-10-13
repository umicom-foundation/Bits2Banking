# Chapter 217 — Structured Git status without duplicate parsers

**Bits to Banking · Native tooling · Umicom Foundation**  
**Author:** Sammy Hegab · **Prerequisites:** Chapter 216 and C23 strings/arrays.

## Why this matters

A human reads `git status` as a list of sentences. Software cannot safely assume those sentences will remain stable, be in English or contain simple filenames. Git filenames can contain spaces, tabs, newlines and unusual byte sequences. Rename reports can represent two different paths. Submodules also have their own state. A parser that splits every line at the first space can silently misidentify files and lose evidence.

Git provides machine-oriented status formats, including `--porcelain=v2` and NUL-delimited output. Umicom Framework already has a bounded native implementation of this responsibility. Our training goal is to **read the contract, not write another parser**.

## Learning objectives

Identify the index column versus the worktree column, understand why NUL delimiters matter, distinguish a rename from a one-path modification, and find the existing `UmiVcsWorkingTree` public interface in Framework.

## Observe in PowerShell

```powershell
git -C "C:\umicom\Umicom-Applications\framework" status --short
git -C "C:\umicom\Umicom-Applications\framework" status --porcelain=v2 --branch
git -C "C:\umicom\Umicom-Applications\framework" diff --cached --stat
git -C "C:\umicom\Umicom-Applications\framework" diff --stat
```

The short form is useful for a person. The long porcelain form shows structured header and entry records. The true machine-safe form uses `-z`, for example:

```powershell
git -C "C:\umicom\Umicom-Applications\framework" status --porcelain=v2 --branch -z
```

Because the output contains NUL bytes, a terminal may not display it intelligibly. **Do not pipe it through a text line splitter and claim to have parsed it.** Native Framework uses a bounded byte parser and keeps rename-path ownership explicit. The CLI invocation above is for diagnosis, not a new production parser.

## Read the C23 API

Find these types and operations in `include/umicom/vcs/working_tree.h`:

```c
UmiStatus UmiVcsWorkingTreeRead(
    const UmiVcsWorkingTreeRequest *request,
    UmiVcsWorkingTree **out_tree);

UmiStatus UmiVcsWorkingTreeDescribe(
    const UmiVcsWorkingTree *tree,
    UmiVcsWorkingTreeSummary *out_summary);
```

The request identifies a repository root and an optional Git programme. The returned observation is owned and must be destroyed when finished. `UmiVcsWorkingTreeEntry` preserves independent index and worktree status codes, unmerged state and submodule-specific markers. `UmiVcsWorkingTreeSummary` contains counts useful to Studio's Source Control view and Umicom OS's release review.

The exact API comes from the Framework revision on your machine; check its header before building production integration. This chapter uses the public contract for explanation, not a promise about a particular binary version.

## Worked example — a file changed in three different ways

Assume the learner has a modified `src/platform/recent_items.c`, a newly created `tests/vcs/test_revision.c`, and an updated Framework submodule commit in the OS parent. The files are not interchangeable. The modified C file may be unstaged, the new test may be untracked, and the submodule update appears as a changed gitlink in the parent. `git diff` without `--cached` and `git diff --cached` deliberately inspect different snapshots.

A safe review starts with `git status --short`, then looks at specific paths. Only after identifying the source changes and running tests do you decide what should enter the index. `git add -A` is appropriate **after** review when every working-tree change is intended; it is not a substitute for review.

## Why the Update 33 adapter is deliberately small

`framework_bridge.c` translates an existing `UmiVcsWorkingTreeSummary` to an educational observation. It does not launch `git`, interpret NUL records or infer that a remote fetch occurred. It copies the current commit identity and counts. The adapter is optional because the standalone C23 test suite should also be usable by a learner who has not built the full Framework.

## Failure and assessment

An incorrectly decoded rename can make an audit say a file was deleted rather than moved. A truncated NUL stream must fail instead of reporting partial success. A missing Framework observation is not an empty status. Explain why each of these decisions is important for release governance. Locate `UmiVcsWorkingTreeParse` and describe which component must reject malformed raw Git output.

**Next:** [Chapter 218 — Detached HEAD and reference identity](218-detached-head-and-local-main-identity.md).
