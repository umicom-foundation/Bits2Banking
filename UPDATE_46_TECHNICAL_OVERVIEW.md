# Major Update 46 — Engineering and curriculum overview

**Author/project lead:** Sammy Hegab · **Organisation:** Umicom Foundation · **Languages:** C23/Assembly first; Markdown and SVG for learning content; CMake for build definitions.

## Delivered educational scope

Stage 9 of *System Administration From Zero* adds Chapters **109–120**, taking the cumulative standalone HTML course to **120 chapters**. It moves from inspecting one workstation to coordinating evidence for a fictional gateway-and-storage service. Learners practise safe Windows PowerShell 7 and Linux terminal commands, package provenance, filesystem read-only states, trustworthy time correlation, local backup restoration, release identity and controlled canary decisions.

The existing C23 engineering track continues with Chapters **316–319**, five video scripts **136–140**, eight original SVG diagrams, an instructor guide, glossary, workbook, command reference and incident report template. None of these materials claims permission to administer a real machine.

## C23 architecture and Framework reuse

The new `labs/native/fleet-readiness` project is a **bounded single-owner educational aggregation**. It imports the original Update 45 operational-evidence service library (`btb-operations-lib`) and calls `BtbOpsEvaluate` for each copied host record. Update 45 already uses earlier C23 security, remote-access, deployment, maintenance, service-readiness and evidence libraries. This version preserves that entire chain and its registered tests. It does not fork, rename or replace those implementations.

**Umicom Framework is the production authority** for repository state, build/test diagnostics, platform process access, security, application lifecycle, durable persistence and service observability. This lab is not a replacement for Framework VCS, Build Automation or OS inspection services. A production multi-host reviewer would first assess existing Framework APIs and their permissions and extend them natively only with explicit project-owner approval.

The classroom API has these independent layers:

| Layer | Contract | Authority |
|---|---|---|
| Fleet policy | Required host IDs, expected source commit, package digest, review age | Local fictional value, not production approval |
| Host evidence | Copied host claim, timestamp, local checks and `BtbOpsReview` | External fictional fixture |
| Service evaluation | `BtbOpsEvaluate` | Reused original Update 45 educational implementation |
| Fleet evaluation | `BtbFleetEvaluate` | Combines flags; does not perform I/O |
| Real deployment | Not implemented here | Authorised Umicom Framework/OS services and real product owner |

## C23 engineering guarantees

- No Python/PowerShell executable implementations, shells, network connections, live credential access, service administration, file writes or background threads.
- Bounded four-host input; exactly 40/64 lower-case hex source revisions; 64-digit expected SHA-256 package checksum.
- Validates host names and duplicate registered identities; refuses unknown or malformed records.
- Host observations are copied to caller-owned review state; no dangling caller-owned pointers retained.
- Validates boolean fields, source and artifact identities, and timestamp monotonicity; never subtracts an unsigned future time to compute age.
- Decisions return **PENDING, BLOCKED, REVIEWABLE or RESTORED_ONLY**; failed upgrades never become success because the previous version was recovered.
- Invalid calls preserve caller outputs and review state; CTest includes explicitly named failure-atomic tests and deterministic mutations.
- No standalone release approval is granted by an educational CTest pass.

## Known limits

Only the local Linux GCC/Clang source reconstruction has been tested in this environment. Windows UCRT64, real platform-specific tests, installed Framework SDK integration, full MkDocs website build and public Pages publishing need separate host acceptance. The offline course is a cumulative HTML reading edition with the previous 108 lesson bodies preserved; navigation still needs reviewed integration in each local `mkdocs.yml`.
