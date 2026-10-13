# Major Update 33 — Technical overview

**Title:** Framework Git Evidence, Temporal Source Verification and Professional Repository Recovery  
**Repository:** `C:\umicom\Umicom-Bits2Banking` (`umicom-foundation/Bits2Banking` on GitHub)  
**Author:** Sammy Hegab · **Organisation:** Umicom Foundation  
**Development policy:** C23 native examples, Assembly only when relevant; no Python or PowerShell scripts.

## Design intent

Earlier updates teach deterministic request ownership, native Git ancestry (31) and action-specific release evidence (32). This batch turns the last topic into an auditable **sequence of observations**, because a valid test against one Git checkout should not be inherited after a later observation. It adds 12 professional lessons (216–227), four video scripts (74–77), five editable SVG illustrations and a standalone C23 teaching laboratory.

The repository's `NATIVE_SOURCE_POLICY.md` is binding. All shared real-world Git commands and parsers belong to **Umicom Framework**. The lab is not a duplicate Git implementation: it receives a caller-supplied immutable snapshot and does not execute Git, access `.git`, authenticate, perform network requests or modify a repository. A compile-only adapter consumes Framework's real public `UmiVcsWorkingTreeSummary` contract when the source checkout is supplied explicitly.

## Contracts and ownership

| Component | Responsibility | Important non-goal |
|---|---|---|
| `review.h` | Public C23 observation/evidence contract | Not a public Framework API |
| `review.c` | Validate evidence sequence, SHA lengths, counters and advisory flags | Does not fetch or parse Git |
| `framework_bridge.c` | Translate Framework summary when explicitly enabled | No runtime read, no network, no new Git provider |
| `review_demo.c` | Fictional disconnected submodule evidence case | Never changes a checkout |
| `test_review.c` | 28 named deterministic cases including 100,000 observations | No live repository integration |
| `test_gate_composition.c` | Reuse *unchanged* Update 32 gate source | Does not replace Update 32 policy |

`BtbReviewObservation` accepts full SHA-1 (40 hexadecimal characters) and SHA-256 (64), allows an explicitly unborn checkout with no SHA, keeps remote freshness separate, and retains the index/worktree/submodule distinctions supplied by Framework. A new observation invalidates previous tests and builds. Recording a new build invalidates a previously stored test result. Malformed inputs leave existing timeline and reports unchanged. Commands shown by the programme are read-only suggestions, not automatic repair actions.

## Framework API grounded in source

The following source files were inspected in the canonical Framework repository:

- `include/umicom/vcs/working_tree.h` — `UmiVcsWorkingTreeRead`, `UmiVcsWorkingTreeDescribe`, `UmiVcsWorkingTreeDestroy`, summary semantics and ownership.
- `include/umicom/vcs/git_cli.h` — existing Git provider boundary.
- `include/umicom/repository/gitlink.h` — native parent index gitlink parsing.
- `include/umicom/repository/submodule_lock.h` — native parent gitlink staging contract.
- `docs/SHARED_FRAMEWORK_SUBMODULE_UPDATE_POLICY.md` — canonical source ownership and direct-to-main integration order.

The Update 33 C23 header is a **teaching input contract** distinct from these Framework headers. No Framework source is copied into this ZIP. A future production enhancement must first examine the existing Framework facilities, then be developed and committed in the Framework repository under its own review and tests.

## Validation boundaries

The native lab validates **internal consistency of supplied data**, not the truth of a remote Git claim. The `remoteFresh` field is asserted by the caller: it cannot itself prove the remote was fetched. Full hexadecimal SHA syntax is checked, but no Git object database is read. Optional Framework header compilation is separate from a linked runtime integration and is not claimed as executed unless verified against a local Framework tree. Update 32 gate composition demonstrates code reuse only when the previous lab is installed.

Missing Windows UCRT64, end-to-end Framework linked integration, GitHub CI runs, MkDocs website build and OS GUI/QEMU evidence must remain explicitly NOT RUN until genuinely executed.

**Next engineering subject:** controlled end-to-end Framework integration and multi-repository incident rehearsals, with platform tests before production enablement.
