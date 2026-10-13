# Bits2Banking — Major Update 34: technical overview

**Title:** Git Three-Way Merge, Safe Repository Recovery and Native C23 Record Reconciliation  
**Author:** Sammy Hegab · **Organisation:** Umicom Foundation  
**Target working directory:** `C:\umicom\Umicom-Bits2Banking`  
**GitHub repository:** `umicom-foundation/Bits2Banking`  
**Native language:** ISO C23 · **Licensing:** MIT for new C23 educational source.

## What actually changes

This batch adds the professional Git curriculum Chapters **228–239**, Episodes **78–81**, five source-editable SVG diagrams, a complete independent C23 laboratory (`labs/native/git-three-way`), a safety quick reference and a sequential guided learning path. No prior source file, implementation, build script, manuscript, site navigation or Framework code is replaced or deleted.

Update 33 introduced an evidence timeline: a remote-freshness assertion does not prove a repository was fetched, and tests from one source revision do not certify a later revision. This update teaches a related but distinct engineering problem: **what a reviewer must preserve when two descendants of a common ancestor disagree**. It adds practical Git index-stage exercises, a bounded record-reconciliation implementation and explicit tests for conflicting deletions and concurrent additions. The native model is read-only with respect to actual repositories.

## Repository ownership and source preservation

- Real Git providers, working-tree status, gitlink parsing, repository locking, process launch and security belong to the canonical **Umicom Framework** repository.
- Umicom Applications, Umicom OS and individual products consume Framework contracts; they do not carry duplicated copies of Framework source inside product code.
- `Umicom-Bits2Banking` owns educational Markdown, diagrams, videos and **isolated pedagogical** C23 models. It does not stage, commit, push or modify a real Git repository at runtime.
- Previous implementations, licences, author headers, comments, public ABI names and working product logic must not be silently deleted during merges. A superseded implementation remains reviewable under an explained disabled block when required; physical deletion requires project-owner review.
- No `.py`, `.ps1`, C++, JavaScript or other executable implementation files are created.

## C23 contract and algorithm

The teaching API is in `labs/native/git-three-way/merge.h`:

| Function | Responsibility | Failure policy |
|---|---|---|
| `BtbMergeSnapshotInit` | Reset caller-owned bounded snapshot. | Null is rejected. |
| `BtbMergeSnapshotAdd` | Copy a validated key/value into a unique record slot. | Duplicate/overflow/invalid inputs leave snapshot intact. |
| `BtbMergeSnapshotValid` | Validate count, keys, bounded values and uniqueness. | No mutation. |
| `BtbMergePlanBuild` | Copy base/ours/theirs into one deterministic union of keys. | Invalid/overflow preserve previous output plan. |
| `BtbMergeDecisionAt` | Borrow a validated decision while plan lives. | Invalid/out of range returns null. |
| `BtbMergeResolve` | Require explicit first-time choice on a genuine conflict. | Invalid/locked/unknown decisions preserve plan. |
| `BtbMergeMaterialise` | Publish a fully owned output snapshot. | Unresolved conflicts return `CONFLICT_PENDING` with no output modification. |
| `BtbMergePlanValid` | Validate structure and recompute expected automatic classification. | Read-only internal consistency check, not source authentication. |

### Classification logic

For each symbolic key, record values may be **present** or **absent**. Equality compares both flags and, when present, bytes. The decision order is: unchanged on both → identical descendants → only theirs changed → only ours changed → conflict. Deleting a record is not the same as retaining an empty string. Both deleted is an identical change; add/add with different values and delete/edit are conflicts. The materialised snapshot contains only selected present records, in deterministic key order: base, then new ours, then new theirs.

`BtbMergePlan` is an educational C structure, **not** a production-proof provenance record. The program does not parse real Git objects or source files, authenticate upstream SHAs, verify merges with a compiler, or claim its record-level decisions are suitable to merge banking source. Real-world code may require manually combining both implementations.

### Limits and ownership

- Maximum 16 distinct keys across three snapshots.
- Key storage 48 bytes including terminating NUL; value storage 128 bytes including NUL.
- Caller owns input arrays; plan owns complete copied records; output snapshot is independently owned.
- No heap allocations, network calls, filesystem I/O, subprocesses, mutexes or threads.
- The implementation is single-owner and deterministic; callers must provide external synchronisation if they share it (not part of this lesson).

## Genuine Umicom Framework contracts, not copied into this package

Framework public interfaces verified during this batch's development:

- `include/umicom/vcs/working_tree.h`: `UmiVcsWorkingTreeRead`, `UmiVcsWorkingTreeDescribe`, `UmiVcsWorkingTreeDestroy`.
- `include/umicom/vcs/git_cli.h`: `umi_vcs_git_cli_provider`.
- `include/umicom/repository/gitlink.h`: `umi_repository_gitlink_parse`.
- `include/umicom/repository/submodule_lock.h`: `umi_repository_submodule_lock`.
- `docs/SHARED_FRAMEWORK_SUBMODULE_UPDATE_POLICY.md`: Framework source owner, consumer checkout rules and parent gitlink publication.

The C23 lab **does not link these interfaces** because its learning goal is record-merge classification. Chapter 235 gives an illustrative read-only API use case and explicitly states that it is not a linked/validated Framework integration.

## Testing and quality gates

`CMakeLists.txt` registers **35 named C23 tests + 1 executable demo**. Cases include all classifications, explicit/duplicate resolutions, invariant tampering, zero/deleted-versus-empty interpretation, capacity, invalid key, unterminated text, lossless deep copies, failure-atomic output and **50,000 deterministic property mutations**. The CTest command provides the authoritative result; do not infer acceptance from the table alone.

Validation in the authoring environment: GCC 14.2.0 36/36 passed; Clang 17 with ASan+UBSan 36/36 passed; five SVGs parsed and rendered. Windows UCRT64, the full MkDocs website, live Git merge practice, real Framework linked integration and Umicom OS are **NOT RUN** in this batch. The exact results and limitations appear in `UPDATE_34_VALIDATION_REPORT.md`.

## Publication strategy

The archive contains one directory named `Umicom-Bits2Banking`, containing only **new files**. Use Beyond Compare to merge additions, not a folder mirror. `UPDATE_34_NAVIGATION_AND_REVIEW.md` holds additive MkDocs entries but no replacement `mkdocs.yml`, because prior local Updates 28–33 may differ from the remote site configuration. Preserve the original Islam volume, navigation and published manuscripts. Run existing strict MkDocs after manual review where its environment is installed.

**Next technical milestone:** a qualified Framework-backed Studio/OS Git-observation consumer, using Framework VCS APIs without a second Git parser, plus platform-specific regression evidence before enabling production repository changes.
