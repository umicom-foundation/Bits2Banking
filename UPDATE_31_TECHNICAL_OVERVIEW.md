# Bits2Banking — Major Update 31 — Technical overview

**Release focus:** Git engineering, preservation-led recovery, tested release controls and native C23 commit-graph reasoning.
**Source owner:** Umicom Foundation · **Author/project lead:** Sammy Hegab.
**Publication branch:** `main` · **Scope:** `Umicom-Bits2Banking` only.
**Repository reference reviewed:** `umicom-foundation/Bits2Banking`, `main` at `88efcf4a50c65c8a9a85744ee58c78bf37a8dfc2` (13 October 2026).
**Framework reference reviewed:** `umicom-foundation/umicom-framework`, `main` at `0d40b2d9222d0a0a0eaf912b8594e0e29fbb2796`.

## 1. Purpose and continuity

This batch builds on the 14-chapter Update 30 curriculum (177–190) and its native C23 `work-dispatch` laboratory, including the preceding Update 29 work-handoff and Update 28 networking lessons. It introduces **13 new chapters, 191–203**, prioritising Git behaviour that new Umicom contributors actually need: working-tree and index review, non-fast-forward rejection, Framework gitlinks, detached HEAD, recovery, testing and release evidence. It also adds **four video scripts, Episodes 66–69**, **five SVG diagrams**, a quick-reference command guide and a tested **native C23** commit ancestry laboratory.

The `git-history` laboratory is intentionally separate from live repository tools: it demonstrates the DAG and fast-forward concept using integer labels and caller-owned structures. It **does not** parse real Git object files, invoke Git, update repositories, or replace Framework's existing repository tooling. Production use must reuse Framework VCS APIs.

## 2. Reuse and architecture decision

The current Framework already defines:

- `include/umicom/vcs/working_tree.h`: bounded read-only status observation, including staging, child repositories and divergence.
- `include/umicom/vcs/git_cli.h`: the Git CLI VCS provider.
- `include/umicom/repository/gitlink.h`: parser/validator for mode-160000 submodule gitlinks.
- `include/umicom/repository/submodule_lock.h`: native Framework-owned gitlink staging, with explicit dry-run; it does not commit or push.
- `docs/SHARED_FRAMEWORK_SUBMODULE_UPDATE_POLICY.md`: canonical repository update ordering and rules.

No new Framework function is invented or modified in Update 31. It would be poor architecture to implement a second application-local Git process runner or PowerShell-based version-lock script when those capabilities exist in Framework. The demonstration library is **mathematical teaching code**, reusable only as a concept—not proposed as an additional production VCS abstraction.

## 3. Native C23 public contract

`graph.h` exposes `BtbGitGraphInit`, `BtbGitGraphAdd`, `BtbGitGraphInvariants`, `BtbGitGraphClassify` and `BtbGitGraphAssess`. All APIs use caller-owned memory. A graph has a fixed capacity of 64 nodes. Each newly added node may name up to two parents already in the graph, ensuring no cycles can be introduced through supported operations. Graph validity checks protect subsequent traversals even when a caller directly corrupts visible storage.

Given local and remote branch tips, the classifier returns one of four relations:

| Relation | Graph meaning | Consequence to teach |
|---|---|---|
| Equal | Both tips are the same commit. | No graph-level sync needed. |
| Local behind | Local tip is an ancestor of remote tip. | Local branch is a possible fast-forward recipient. |
| Local ahead | Remote tip is an ancestor of local tip. | Local branch is a graph-level fast-forward push candidate. |
| Diverged | Neither tip is an ancestor of the other. | A human must review reconciliation; force push is not the default. |

The snapshot assessor keeps `checkedOut` (HEAD), `localMain` and `remoteMain` separate; detached HEAD does not itself imply an error. Dirty and detached-unpublished flags trigger review, but these do not analyse actual filesystem collisions or know the remote server's branch policies. Tests reject malformed data without mutating caller outputs or graph storage.

## 4. Design constraints and limits

- **C23/Assembly first:** All newly delivered executable source is ISO C23. No `.py` or `.ps1` files are created. CMake is only the build declaration; Markdown, YAML snippets and SVG are educational/presentation data.
- **No source deletion:** Existing Framework, OS, Kernel, Applications and Bits2Banking code is not replaced or deleted. The ZIP contains only new files.
- **No hidden automation:** No executable stages or commits Git repositories. All Git examples are human-reviewed interactive PowerShell commands.
- **Educational scope:** The graph supports ordinary no-parent, single-parent and two-parent commits. Real Git may have octopus merges, SHA hashes, shallow clones, replace refs, protected branches, hooks, authentication and file-level conflicts; this bounded lab models none of those fully.
- **Platform boundary:** Linux GCC/Clang validation is documented. Windows UCRT64 and full MkDocs publication remain acceptance gates for the local host.

## 5. Installation and publication

Unzip into a review directory and compare the single `Umicom-Bits2Banking/` folder with the existing repository in Beyond Compare. Merge the approved **additions**. Update `mkdocs.yml` only by inserting the additive chapter/video entries in `UPDATE_31_NAVIGATION_AND_REVIEW.md`, retaining all existing navigation and book content. For the final local review, run CMake, CTest and the existing MkDocs strict builder, then commit to `main` with the explicit commands in `UPDATE_31_BUILD_TEST_AND_GIT.md`.

## 6. Next milestone

**Major Update 32:** Git merge/rebase case studies using disposable repositories, Framework-owned VCS inspection as a practical consumer, native C23 repository diagnostics without duplicate process handling, release qualification and regression coverage. Extend the curriculum from Chapter 204 and Episode 70, while respecting the source-preservation and first-party Framework rules.
