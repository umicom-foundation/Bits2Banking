# Teaching dependency changes and qualification

**Course:** Professional native engineering and source-preserving Umicom development  
**Chapters:** 252–263 · **Video episodes:** 86–89 · **Lab:** `labs/native/change-impact`

## Teaching sequence

| Session | Chapters | Observable student capability | Practical evidence |
|---|---|---|---|
| 1. Shared impact | 252–254 | Trace Framework dependants, distinguish gitlink and ABI | Annotated dependency diagram |
| 2. Native policy | 255–257 | Read bounded C23 contracts, map gates to a full revision | Compiled demo and gate table |
| 3. Failure engineering | 258–259 | Separate configure/compile/link/test/launch failures | Stage-specific triage note |
| 4. Preservation and SDK | 260–261 | Distinguish HEAD/main/origin and reuse Framework read APIs | Read-only repository evidence |
| 5. Verification and capstone | 262–263 | Reproduce negative cases, document missing OS/GUI evidence | 43-case CTest result and review memo |

The classroom references Umicom Framework, Studio, Bank and OS because that is where these concepts become operationally important. Do not run destructive Git operations in student working trees. Use disposable repositories if practising a merge or stash interactively; avoid changing the user's production code as part of teaching.

## Answer key and design reasoning

**Chapter 252:** A dependency arrow points from *consumer* to *required provider*, while impact flows from a changed provider toward consumers. For actual Umicom product planning use Framework's existing `UmiBuildAutomation`, not the classroom graph. Git status alone does not establish a successful build. A parent gitlink stores a specific child commit; a child directory can be checked out at another commit until the parent is committed.

**Chapter 253:** `UmiVcsWorkingTreeRead` owns an opaque result; borrowed entries are invalid after `UmiVcsWorkingTreeDestroy`. `divergence_known == 0` means no authoritative ahead/behind assessment was available, not that there is no divergence. Pushing `origin main` from detached HEAD pushes local `main`, not automatically the detached commit.

**Chapter 254:** ABI changes can break existing consumers despite library compilation. Public struct layout, exported symbols, enum stability, callbacks and ownership rules require separate consideration. Runtime assets and GTK4 DLLs add non-compile gates. The teaching graph refuses cycles because its dependency contract is acyclic.

**Chapter 255:** The twelve-module limit keeps all shifts defined in a 64-bit mask after checking indices. Module identifiers are logical names, copied into graph-owned storage. Rejected writes must preserve both graph and caller output. The grammar deliberately rejects spaces, path separators and colons.

**Chapter 256:** A *required gate* is not a result. FAILED indicates a check executed and failed; NOT RUN explicitly indicates it did not execute; MISSING means no trustworthy observation was supplied. A passing C23 lab says nothing about a real Windows GUI or QEMU OS boot.

**Chapter 257:** A syntactically valid but mismatched SHA is blocking stale evidence; a malformed SHA is invalid input. Dropped diagnostics prevent claiming complete error evidence. A full SHA is necessary for unambiguous identity but not sufficient to attest to build provenance.

**Chapter 258:** The first observed compiler/link/test failure guides diagnosis, but the root cause can be earlier. Framework's existing compiler parser must be reused rather than writing a new application-local parser that mishandles Windows drive letters or multiline CMake diagnostics.

**Chapter 259:** CTest *Not Run* is not passed, and often requires checking the earlier build stage for a missing executable. Exit `0xC0000409` or SIGSEGV is a symptom, not a diagnosis. Use separate sanitizer builds and a debugger, retain complete source and regression evidence.

**Chapter 260:** A stash saves uncommitted tracked and ordinary untracked work with `--include-untracked`, **not** detached commits without a preserved reference. A parent must record a tested child SHA in its gitlink. `umicom repo lock .` stages checked-out heads; it does not perform a remote Git push.

**Chapter 261:** `Umicom::vcs` and `Umicom::build` are Framework libraries. The SDK consumer must link them instead of vendoring private `.c` files. A missing installed SDK is an honest *not-run* result; it is not permission to bypass architectural boundaries.

**Chapter 262:** Each negative test exits zero when the API correctly refuses an unsafe operation. 43 tests include a 50,000-iteration deterministic sequence; these are finite tested paths, not proof of absent defects across all OS/toolchain configurations.

**Chapter 263:** A complete capstone distinguishes the Framework source SHA, Applications parent SHA, OS parent SHA, gitlink reference, toolchain/profile and test coverage. It records all outstanding gates and requires explicit reviewer acceptance before a real publication. A blocked recommendation can be correct and professionally complete.

## Named test matrix

- Graph and input bounds: `graph_empty`, `graph_null`, `duplicate_modules`, `name_empty`, `name_space`, `name_overflow`, `invalid_gates`, `capacity`, `module_atomic`.
- Dependencies and cycles: `edge_added`, `edge_duplicate`, `cycle_self`, `cycle_indirect`, `edge_atomic`, `corrupted_graph`.
- Source identity and change planning: `sha1_valid`, `sha256_valid`, `revision_short`, `revision_bad_hex`, `revision_too_long`, `plan_empty_changes`, `plan_unknown_index`, `plan_transitive`, `plan_targeted`, `plan_ui_change`, `plan_atomic`.
- Review-gate outcomes: `assess_ready`, `assess_stale`, `assess_missing`, `assess_failed`, `assess_not_run`, `assess_dropped`, `assess_incomplete_log`, `assess_unreviewed`, `assess_overlap`, `assess_badmask`, `assess_badboolean`, `assess_atomic`, `assess_extra_pass`, `assess_multiple`, `assess_sha256`.
- Deterministic stress and demonstration: `deterministic_mutations` (50,000 iterations), `demo`.

The baseline contains **42 named functional cases plus the demo**, registered by the native `CMakeLists.txt`. Failures must be investigated, not removed or silenced.

## Review rubric (100 points)

| Criterion | Points |
|---|---:|
| Correct Framework / parent / gitlink identity and no destructive Git changes | 20 |
| Dependency direction, transitive impact and ABI reasoning | 15 |
| Named verification categories with passed/failed/not-run/missing distinctions | 20 |
| Correct C23 ownership, bounds and failure-atomic reasoning | 15 |
| Reproducible build/test results and failure diagnosis | 15 |
| Honest evidence boundaries, not-run gates and publication sequence | 15 |

Grant no release-authorisation credit if the learner claims that a passing isolated lab automatically qualifies an OS image, Studio installer or production banking feature. Encourage clear recorded uncertainty rather than fabricated positive evidence.
