# Chapter 235 — Use Umicom Framework VCS instead of creating a second Git client

**Bits to Banking · Umicom architecture · Umicom Foundation**  
**Prerequisite:** Chapters 228–234 · **Duration:** 45 minutes.

## Why Framework ownership matters

Umicom Studio IDE, Umicom OS Control Centre and developer utilities all need trustworthy repository observations. Duplicating `git status` parsing or process execution in every application would create inconsistent error handling, unsafe subprocess use and different interpretations of submodule state. The reusable functionality belongs in **Umicom Framework**; Bits2Banking contributes **educational models and lessons**, not another production VCS subsystem.

This batch does not edit the Framework. The native `git-three-way` teaching lab also does not invoke Git. Real implementation should use the existing canonical Framework source.

## Public Framework contracts inspected for this curriculum

| Existing contract | Responsibilities |
|---|---|
| `include/umicom/vcs/working_tree.h` | Read a repository without staging/fetching; describe branch, commit, staged, conflict and submodule counters. |
| `include/umicom/vcs/git_cli.h` | Obtain the existing command-line VCS provider behind a stable Framework contract. |
| `include/umicom/repository/gitlink.h` | Parse an actual Git mode-160000 parent gitlink record. |
| `include/umicom/repository/submodule_lock.h` | Check, then stage current submodule HEAD references in a parent repository. |
| `docs/SHARED_FRAMEWORK_SUBMODULE_UPDATE_POLICY.md` | Canonical source owner and Framework-first publication order. |

These names and capabilities are grounded in the current shared Framework architecture. A consumer must still link the relevant Framework target and build against its **actual checked-out** release; do not assume that matching header names prove binary compatibility.

## Read-only observation contract

```c
UmiVcsWorkingTreeRequest request = {
    .repository_root = "C:/umicom/Umicom-Applications/framework",
    .git_program = NULL,
    .timeout_ms = 30000U,
    .cancellation = NULL
};
UmiVcsWorkingTree *tree = NULL;
UmiVcsWorkingTreeSummary summary = {0};

/* Illustrative integration: link with the existing Framework VCS target. */
UmiStatus status = UmiVcsWorkingTreeRead(&request, &tree);
if (status == UMI_STATUS_OK && tree != NULL) {
    status = UmiVcsWorkingTreeDescribe(tree, &summary);
}
UmiVcsWorkingTreeDestroy(tree);
```

The snippet demonstrates the **public API shape**; it is not part of the standalone teaching executable, and this batch does not claim that a linked Framework integration was run. The caller owns `tree` after a successful read and must destroy it. A GTK4 view should call the blocking observation from a supervised worker rather than freezing the UI thread.

## Observe rather than mutate

`UmiVcsWorkingTreeSummary` contains independent observations: whether HEAD is detached, whether branch/upstream are known, behind/ahead when divergence is known, staged counts, untracked entries and child-repository dirtiness. A caller must distinguish **unknown** from **zero**. Zero behind with `divergence_known == 0` is not proof of being current with GitHub.

The `UmiRepositorySubmoduleLockRequest` API supports a dry-run. The CLI pattern is to run `umicom repo verify .` before `umicom repo lock .`. Neither operation fetches a new Framework revision, builds the code, commits or pushes it. An application must not call `lock` as a shortcut for review.

## Practical source walkthrough

1. Open `working_tree.h` and find `UmiVcsWorkingTreeRead` and `UmiVcsWorkingTreeDescribe`.
2. Identify `UmiVcsWorkingTreeRequest.repository_root` and the cancellation/timeout contract.
3. Identify what counts as a **dirty submodule** separately from a changed child HEAD.
4. Open `submodule_lock.h` and find its dry-run field and output report.
5. Sketch a Studio view: Read-only status → review conflict → separately approved Git command → rerun read-only status.

## Architectural assessment

A Studio module suggests a standalone C subprocess that runs `git status --porcelain` and splits the result on newline characters. Explain why this is a poor production design: Git paths can contain embedded newlines; Framework already owns NUL-delimited parsing, process execution and memory bounds; duplication introduces divergence and defects. Recommend consuming Framework `UmiVcsWorkingTreeRead` instead.

**Next:** apply these contracts to the Framework checkout shared by Applications and OS.
