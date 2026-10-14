# Major Update 41 — Technical Overview and Architecture Boundaries

**Product:** Bits to Banking · System Administration From Zero · Umicom Foundation  
**Primary language:** ISO C23, Assembly where required; no new Python or PowerShell implementations  
**Change scope:** additive learning content and isolated native laboratory inside `Umicom-Bits2Banking` only.

## 1. Existing sources reviewed

The package continues Update 40's `labs/native/service-readiness` and Update 39's `labs/native/sysadmin-evidence`. Their public contracts are not renamed, duplicated, replaced or deleted. The existing Foundation educational site and original application-creation guide remain unchanged. PowerShell and Bash appear only as **interactive commands in educational prose**; CMake remains declarative build metadata.

## 2. Reuse graph

```text
Update 39:  BtbAdminReview -> BtbAdminReport
                         |
                         v
Update 40:  BtbServiceGraph -> BtbServiceSummary
                         |
                         v
Update 41:  BtbMaintenanceReview -> change-window transition
```

`BtbMaintenanceReview` stores caller-owned, copied `BtbServiceSummary` snapshots. It accepts a READY baseline, a bounded change ID, a 40- or 64-character hexadecimal sample source revision and a fictional operator label. Before the simulation begins, `BtbMaintenanceApprove` requires distinct operator/reviewer labels, a claim that a recoverable backup was verified and a documented rollback plan. These are **teaching flags**, not proof of authentication, real backup integrity or any granted permission.

After the planned change, `BtbMaintenanceObserveAfter` requires valid, consistent service counts, the same service-ID population and a different nonzero capture ID. An all-READY observation becomes VERIFIED and may be completed. An observation with blocked or review outcomes enters ROLLBACK_REQUIRED. A later independent, all-READY capture becomes RESTORED. It is never relabelled COMPLETE, because an upgrade that failed should remain distinguishable from a successful upgrade.

## 3. C23 public API and lifetime

The new header declares eight states and six result codes. No global mutable state, dynamic allocation, sockets or platform APIs are used. The caller owns all input and output structures. Baseline, post-change and restoration summaries are copied by value and may be retained after the original service graph is destroyed. Where operations can be rejected, validation precedes assignment to the caller's record. `BtbMaintenanceExplain` uses a fixed-size local candidate buffer and writes the caller's buffer only when the complete explanation fits.

Source revisions are **syntax checked**, not fetched or cryptographically bound to a real compiled artefact. Capture IDs are distinct labels, not timestamps, signatures or authorisation credentials. The teaching implementation does not prove concurrency safety; shared mutable objects require caller-owned synchronisation. The C23 model does not implement host operating-system changes.

## 4. Core test contract

The new named scenarios exercise a malformed baseline, invalid revision and identifiers, missing backup/rollback preconditions, same-person labels, premature execution, cancellation restrictions, post-change READY/WARNING/FAILURE outcomes, service-ID mismatch, reused capture ID, corrupt aggregate counters, late completion, recovery with failed or reused evidence, explanatory buffer capacity, full-record preservation and a deterministic 30,000-iteration mutation sequence. A separate demonstration shows an expected simulated failure and a distinct restoration capture.

CTest also discovers the Update 39 and Update 40 cases because those libraries are compiled by their original CMake targets. Expected total when prerequisites are present: **57 tests**. Strict compiler flags include `-Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror` on new targets. Sanitizer builds additionally use `-fsanitize=address,undefined` where supported.

## 5. Publishing and course structure

The new 12 chapters live under `content/lessons/08-system-administration`; the existing engineering track gains Chapters 296–299 under `content/lessons/05-engineering`. Episodes 111–115 use the established `content/videos/scripts` directory. SVG sources are original, accessible diagrams under `content/assets/diagrams` and are also embedded in the complete **60-chapter** offline HTML edition. Previous 48 chapters remain textually unchanged in the combined edition, and earlier website book navigation must be preserved during review.

`UPDATE_41_MKDOCS_NAV_SNIPPET.yml` is a **snippet only**. It must be merged into the current MkDocs configuration by review. Replacing `mkdocs.yml` with the snippet would destroy existing navigation and is prohibited.

## 6. Future reuse and migration boundary

Real application lifecycle, authentication, VCS observation, native build automation, signed releases, Data Server recovery and observability continue to belong to Umicom Framework. Production migrations must inspect their existing C23 contracts first. No Framework, Studio, Trader, Bank, OS or Kernel source is changed in this package.
