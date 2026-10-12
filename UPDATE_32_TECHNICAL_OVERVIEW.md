# Major Update 32 — Technical Overview

## Architecture and source ownership

The Umicom ecosystem has one reusable C23 Framework. The Framework owns repository observation, process execution, Git provider contracts and submodule locking. Bits2Banking owns learner-facing lessons, source examples and video scripts. This update **does not** add a second Git parser or a command wrapper. The native lab evaluates already-collected release evidence and is deliberately unable to alter a real repository.

The Framework interfaces reviewed while preparing this batch are:

| Existing source | Responsibility |
|---|---|
| `include/umicom/vcs/working_tree.h` | Native read-only working-tree and child-submodule observation; explicit lifetime |
| `include/umicom/vcs/git_cli.h` | Framework Git provider behind the stable VCS contract |
| `include/umicom/repository/gitlink.h` | Validate Git index gitlink records |
| `include/umicom/repository/submodule_lock.h` | Stage parent gitlinks through the native Framework service |
| `docs/SHARED_FRAMEWORK_SUBMODULE_UPDATE_POLICY.md` | Canonical order for Framework, Applications and OS |

These contracts are existing Framework functionality, not additions made in this ZIP. Call sites and build targets must always be checked against the Framework revision actually present in the consumer checkout.

## Native release evidence evaluator

`labs/native/git-release-evidence/` contains `gate.h`, `gate.c`, `gate_demo.c`, `test_gate.c`, a CMake target and its README. All C sources are ISO C23. No dynamic allocation, global mutable state, background thread, socket, filesystem mutation or subprocess launch is involved.

The evaluator has three actions with different evidence requirements:

| Action | Required local evidence | Extra evidence |
|---|---|---|
| COMMIT | Main branch, known ancestry, reviewed non-empty index, no conflicting/unstaged/untracked changes, passing build/tests/docs | Human authorisation to commit |
| PUSH | Main branch, known remote ancestry, no behind commits, at least one outgoing local commit, clean index/worktree, passing build/tests/docs | Git remote actually accepts the push |
| PIN | Parent main, reviewed **sole staged gitlink**, clean source files, passing parent build/tests/docs | Child working tree clean, child commit published and tested, exact tested SHA |

A C23 function cannot establish that a user really ran a build: trusted evidence collection must supply that fact. The `observationId`/`expectedObservationId` fields detect a caller *knowingly* presenting mismatched snapshots; they are not a cryptographic freshness mechanism.

## Safety and failure contracts

- **INVALID:** structurally malformed evidence, such as an unsupported action, impossible Boolean, invalid proof enum or non-hex child SHA. The caller-owned report stays unchanged.
- **BLOCKED:** structurally valid input lacking sufficient evidence. The report contains all recognised issue bits, a count and an explanatory issue-name mapping.
- **READY:** all modelled gates pass. A human reviewer must still verify context and authorise real Git changes. The state can become stale before the next push.

The demonstration intentionally changes remote ancestry and observation identity between two simulated evaluations, showing a previously ready push become blocked.

## Where Framework reuse begins

A future Umicom Studio implementation should use `UmiVcsWorkingTreeRead` from a worker, obtain a copied `UmiVcsWorkingTreeSummary`, and expose an application-owned view model. Remote tracking and CTest results would be assembled by existing Framework services. The live action must remain behind reviewed Framework repository-control interfaces, never behind a new Bits2Banking ad hoc script. The laboratory makes no claim to implement this production integration yet.

## Known educational limits

The pin SHA validator accepts 40 hexadecimal characters and a terminator because the currently supplied Framework examples use SHA-1-size commit IDs; this is **not** a general Git hash-algorithm negotiation layer. The course explicitly labels this constraint. The strict COMMIT gate chooses to block unrelated unstaged and untracked files even though Git permits partial commits. That is an intentionally conservative batch-publication rule, not a claim about Git capability.

All project content is UK English and uses realistic Umicom Framework, OS, Studio, Trader, Bank and Bits2Banking examples. The build tool is CMake/Ninja; no new Python or PowerShell implementation is introduced.
