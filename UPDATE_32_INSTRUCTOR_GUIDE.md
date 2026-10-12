# Major Update 32 — Instructor guide and practical assessment

**Target:** New and intermediate Umicom contributors who understand simple C23, Git basics and CMake.  
**Duration:** Four workshops of 90 minutes plus a release qualification capstone.  
**Style:** Professional plain UK English, realistic Umicom examples, explicit evidence and limitations.

## Teaching sequence

| Workshop | Chapters | Live practical exercise | Review evidence |
|---|---|---|---|
| 1 — Git state and review | 204–206 | Separate HEAD/index/worktree; check FF ancestry | Status, two diff ranges, reviewed index |
| 2 — Framework publishing | 207–209 | Explain detached HEAD; draft published-child/parent-pin sequence | Child SHA, parent gitlink, collision recovery plan |
| 3 — Quality qualification | 210–212 | Classify failing CI, retained source and ABI changes | Exact first diagnostic, tests, compatibility checklist |
| 4 — Native policy decisions | 213–214 | Build C23 gate; run positive, blocked and invalid paths | 34 named CTest results and explanation of limitations |
| Capstone | 215 | Plan a simulated Framework/OS/Bits2Banking release | Evidence register, test results, staged diff review |

Do not conduct live force-reset, clean or force-push demonstrations on an active Umicom checkout. Use disposable local repositories to illustrate conflicts. The reusable Framework VCS contract is taught directly from its existing public header rather than implementing a second parser.

## Sample oral assessment and model reasoning

**Q: Why does `git push origin main` not necessarily publish detached HEAD?** Because the refspec names the local branch `main`; detached HEAD is an independent current commit reference. Compare the three SHAs before choosing an operation.

**Q: Why is a green Framework build insufficient to qualify a new OS gitlink?** The OS must compile and pass its own tests against the selected child revision; packaging, boot and GUI checks are separate where relevant.

**Q: Which data is owned by the native C23 release gate?** The caller owns both the snapshot and report; the gate retains no pointers and never touches a Git repository. It only computes an in-memory decision.

**Q: Why distinguish `INVALID` from `BLOCKED`?** INVALID input is structurally unusable and must not replace a valid previous report. BLOCKED input is well-formed evidence that fails one or more release requirements; a full reason bitmask is returned.

**Q: Can the lab prevent a remote race during `git push`?** No. A remote can advance after the evidence was collected. Git's push transaction remains authoritative.

## Practical marking rubric (100 marks)

- **20 — Git identity:** demonstrates understanding of HEAD, main, origin/main, current repo and submodule HEAD.
- **20 — Preservation and staging:** inspects entire staged content; does not remove features/comments or silently discard local files.
- **20 — Framework/OS dependency correctness:** uses one Framework source, published child SHA, tested parent pin, distinct commits.
- **20 — Native C23 verification:** can run 34 CTests and explain input ownership, failure atomicity and multi-issue reporting.
- **20 — Release evidence honesty:** documents compiler, tests, docs, not-run checks, residual risks and human authorisation.

Award no credit for fabricated test results, unsafe forced history updates, silent source deletion, new Python/PowerShell implementation scripts or a claimed Framework production integration that has not been built and tested.

## Learner capstone deliverables

Submit a Markdown note with: scenario, touched repositories, staged paths, SHAs, build commands, actual result excerpts, failures, actions taken, and remaining verification. Add a short explanation of how a stale remote observation changes the decision. Do not include passwords, access tokens or private records.
