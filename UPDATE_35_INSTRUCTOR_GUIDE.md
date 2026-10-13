# Major Update 35 — Instructor guide and answer key

**Bits to Banking · Umicom Foundation · Sammy Hegab**  
**Audience:** new Umicom contributors progressing into professional C23 development and build engineering.  
**Prerequisites:** Git basics, C23 structures, CMake/CTest and ownership concepts in Chapters 1–239.

## Instructor strategy

Teach the difference between **observation**, **interpretation** and **authorised action**. Learners often say “Git is clean, therefore the release is ready” or “CTest says 56/56, therefore the OS works”. Both are logical errors. Build evidence applies to a specific source revision, toolchain, configuration and test population. The Framework owns real repository and compiler observations; Bits2Banking illustrates how to copy and interpret them without changing source.

Use the authentic Umicom paths to demonstrate scale, but do not encourage learners to introduce defects in production checkouts. Use the new standalone C23 program, disposable clones or synthetic records for hands-on mistakes.

## Suggested three-session delivery

| Session | Duration | Chapters and activities | Evidence learners produce |
|---|---:|---|---|
| 1. Source and build ownership | 90 min | 240–244, Episodes 82–83; inspect `HEAD`, `main`, `origin/main`, Framework gitlink, existing Framework diagnostic headers | Table of repository refs plus correctly classified compile/link/test failure |
| 2. C23 evidence models | 120 min | 245–247, Episode 84; build library, inspect owned records, run named negative tests, predict compare counts | Passing CTest transcript and explanation of failure atomicity and multiset matching |
| 3. Professional integration review | 120 min | 248–251, Episode 85; complete capstone, optionally link SDK, document not-run gates | Source-preserving review note and exact publication sequence |

## Core concept checks

**1. A clean working tree proves that remote `main` was fetched.** False. Git status is local. A remote-tracking branch may be stale and a build may have targeted an older SHA.

**2. A detached HEAD in an OS Framework submodule is necessarily a fault.** False. Submodules routinely pin exact child revisions without following a branch. The error occurs when attempting to commit/push as though that checkout were already on the intended branch.

**3. A parent repo includes Framework files as normal tracked files.** False. The parent records mode-160000 gitlink entry. Framework commits are made in the Framework repository. The parent integration pin is a separate commit.

**4. A compiler log line containing “error” must be parsed locally by Studio.** False. Framework's existing compiler grammar is the authority; ordinary output can contain that word without being a diagnostic.

**5. No parsed errors plus process exit 1 means success.** False. Tool crashes and unsupported output formats produce nonzero exits without recognised messages.

**6. A `Not Run` test may be counted as passed if all executed tests passed.** False. Not-run and skipped tests must remain visible and require an explicit policy decision.

**7. Copying a pointer to a parser-owned diagnostic ensures memory safety.** False. The parser can release/reuse its storage. The C23 teaching model copies normalized fields into its own arrays.

**8. Two identical diagnostics in the prior snapshot should be collapsed before comparison.** False. The model compares occurrences as a multiset. One identical occurrence in the new run leaves one persisting and one resolved.

**9. An error moving to another source line can appear introduced.** True. Exact line/column identity is an explicitly documented limitation, not semantic AST matching.

**10. Passing an educational C23 release assessment authorises Git push.** False. It is a review aid, not a production permission mechanism. Product-specific tests, approvals and staging review remain independent.

## Debugging workshops

**Workshop A — malformed SHA.** Run `sha_short_rejected` and `sha_unterminated_rejected`. The output snapshot must remain untouched on `INVALID`. Inspect why the code accepts exactly 40 or 64 hexadecimal digits and never seven-character display IDs.

**Workshop B — copied ownership.** Run `copied_problem_ownership` and then `full_failure_atomic`. The input record is changed after submission, but the snapshot retains the original. The full queue refuses one more addition without changing its recorded state.

**Workshop C — incomplete build evidence.** Compare `assessment_build_failed`, `assessment_dropped`, `assessment_missing_tests`, `assessment_skipped_tests` and `assessment_not_run_tests`. The first four arise from different causes and must produce distinct review flags.

**Workshop D — comparability.** Run `compare_line_shift`, `compare_duplicate_multiset`, `compare_profile_refused` and `compare_toolchain_refused`. Ask learners to predict counts or refusal before looking at the assertions.

**Workshop E — real-world review.** Use the guided Umicom OS scenario in Chapter 251. Learners inspect **read-only** repository state. If an actual checkout is dirty, they must document a safe preservation action rather than reset it.

## Grading rubric (100 points)

| Criterion | Points | Evidence |
|---|---:|---|
| Source and gitlink identity | 15 | Distinguishes child/parent SHAs and detached HEAD correctly |
| Framework reuse | 15 | Names the real Framework VCS and compiler parser APIs, no duplicate implementation |
| Native C23 correctness | 20 | Explains bounds, ownership, sealed state and failure-atomic outputs |
| Diagnostic comparison | 15 | Predicts introduced/persisting/resolved occurrences including duplicates |
| Build/test attribution | 15 | Records exit, profile, compiler, stale and missing/skipped/not-run evidence |
| Cross-platform honesty | 10 | Separates Linux/GCC, Windows/UCRT64 and optional SDK qualification |
| Safe Git publication | 10 | Inspects staged files and preserves source; correct `git add -A`/commit/push sequence |

A learner may receive full credit for concluding that a release **must not be published** when required evidence is missing. The decisive criterion is correctness of the reasoning, not a green status.

## Source and policy notes

The standalone laboratory is an educational projection with a maximum of 24 diagnostic records. It has no parser for real Git data and cannot modify repositories. The optional Framework demo depends on a compatible installed Framework SDK. Instructors must not represent SDK linkage or Windows acceptance as completed unless they have actually been run.

Do not ask learners to remove old features, delete historical source, bypass failing tests or add Python/PowerShell helpers. The source-preservation rule and native-first policy apply throughout the course.
