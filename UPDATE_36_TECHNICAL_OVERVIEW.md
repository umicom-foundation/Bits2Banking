# Major Update 36 — Technical overview

## Purpose and placement

This batch advances Bits2Banking's native engineering curriculum to **Chapters 252–263** and videos **86–89**. It teaches the distinction between a changed source revision, a reviewed module dependency map, downstream consumers and the build/test evidence required before a candidate release can be submitted for human review. It builds directly on Update 35's Framework VCS and diagnostic material.

Umicom Framework already supplies a real **Automated Build System planner** through `include/umicom/build/automation.h` (`UmiBuildAutomation`), as well as Git inspection and compiler diagnostics. **Do not implement an application-local production change-impact planner.** The educational `labs/native/change-impact` directory implements a small, bounded **from-first-principles classroom model** so students can understand the reasoning behind the existing Framework service. It neither duplicates Git subprocess handling nor compiler text parsing. It has no application-local network server, database, worker pool or long-running daemon.

## Architecture

1. `BtbImpactGraph` is caller-owned and has up to 12 modules. Each module's unique ASCII identifier, dependency mask and gate mask are validated.
2. `BtbImpactAddDependency` refuses duplicate edges, unregistered indices and cycles; rejected operations preserve the graph.
3. `BtbImpactPlanBuild` consumes the reviewed changed-module bitset and a syntactically complete 40-/64-hex revision; it computes **reverse-dependency closure** and the union of required gates.
4. `BtbImpactAssess` consumes caller-provided gate outcomes, a copied full source revision, dropped-record count and completeness/review flags. It identifies **stale**, **failed**, **not run**, **missing**, **dropped**, **incomplete log** and **unreviewed source** conditions. Contradictory masks are refused. Invalid input never partly updates the output assessment.
5. `framework_example.c` is **optional**. It links against the installed SDK and calls `UmiVcsWorkingTreeRead`, `UmiVcsWorkingTreeDescribe`, `UmiVcsWorkingTreeDestroy`, `umi_build_parse_diagnostic_line`, and the actual `umi_build_automation_*` scope/plan API. It is not part of the standalone tests and does not execute Git itself.

## Explicit boundaries

A plan containing all required gates and no blocking reasons is **suitable for human review only**. It does not authenticate the supplied evidence, prove that a Git object exists, declare a production release qualified, stage code, perform an automated merge, deploy a service, place financial orders, release payments, or update an OS image. No live Framework service is extended: Framework **already has** `UmiBuildAutomation` for real change-impact and target/test selection. Any genuinely missing capability requires an approved extension to that existing C23 service, not a duplicate implementation.

The `BTB_GATE_*` flags represent **classes** of checks, not test identifiers or recorded executions. An automatic generator of a production graph would need the real target catalogue, generated sources, public ABI dependencies, runtime resources, security responsibilities, installation and deployment profiles. The current reviewed input model deliberately does not claim those capabilities.

## Failure and ownership contracts

- Input strings must be NUL-terminated within documented capacities. Module identifiers accept ASCII letters/digits and `._-` only, with length 1–47 bytes.
- The graph rejects module overflow, malformed gate masks, duplicates, invalid indices and dependency cycles.
- Plans require a nonzero subset of registered modules, not an arbitrary raw file path.
- Revision identifiers must be full 40-/64-character hex values. Accepted syntax alone is **not cryptographic verification**.
- Unrecognised evidence bits, overlapping pass/fail/not-run masks and invalid Boolean values return invalid input without modifying output.
- A valid but stale source revision is a **blocking assessment outcome**, not an invalid representation.
- The C23 model uses caller-owned fixed storage; it allocates no heap, retains no input pointers and provides no thread safety. If reused in a concurrent host, the host owns synchronisation and snapshot stability.

## Testing

CMake registers **43** named CTest cases: 42 focused cases plus one executable demonstration. The focused cases exercise both ordinary behaviour and intentional rejections; one case performs 50,000 deterministic state-evaluation iterations. Tests on GCC 14.2.0 and Clang 17 + AddressSanitizer/UndefinedBehaviorSanitizer passed in the provided Linux container. Windows UCRT64, website generation and optional installed Framework SDK acceptance remain host gates, not represented as completed.

## Files and migration

All archive payload files are **new additions** under the established `Umicom-Bits2Banking/` top-level prefix. Existing repository implementations, `mkdocs.yml`, original manuscripts, historical code and comments remain untouched. `UPDATE_36_NAVIGATION_AND_REVIEW.md` supplies an additive top-level nav section to be merged manually after reviewing the current site configuration. This follows the existing source-preservation practice while avoiding an unsafe overwrite of locally updated navigation.
