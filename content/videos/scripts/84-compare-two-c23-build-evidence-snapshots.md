# Episode 84 — Compare Two C23 Build Evidence Snapshots

**Bits to Banking · Umicom Foundation · Sammy Hegab**  
**Companion chapters:** 244–247 · **Format:** 12–15 minutes  
**Implementation:** ISO C23, CMake and native CTest. No Python/PowerShell source files.

## Learning outcomes

Viewers learn how to bind diagnostic results to a complete source SHA, copy caller-owned data into a bounded structure, compare repeated problem occurrences and reject incomplete test evidence.

## 00:00–02:15 — Define the identity

Display `BtbEvidenceIdentity` in `evidence.h`: complete commit hash, profile, toolchain and observation sequence. Explain why seven-character display hashes and modified working trees cannot stand alone as durable release provenance.

**Visual:** `build-evidence-state-update35.svg` from Initialise to Seal. Emphasise: sealed means finished, **not passed**.

## 02:15–05:30 — Walk through C23 ownership

Open `BtbEvidenceRunInit` and `BtbEvidenceAddProblem`. Demonstrate that the consumer stores a copy of a normalized diagnostic. Show the tests `copied_problem_ownership`, `unterminated_message_atomic`, and `full_failure_atomic`.

**Narration:** “A user interface must not retain a pointer into a parser's temporary memory. And when a fixed-size record cannot fit, we reject it rather than replace the old evidence with a partial or shortened answer.”

## 05:30–09:15 — Run the executable comparison

Configure and build using the commands in the [build-evidence laboratory](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/build-evidence/README.md), then run:

```powershell
& ".\output\learning-build\build-evidence\btb-build-evidence-demo.exe"
```

The demonstration uses **fictional** Umicom finance source names. One prior error becomes resolved, and a new snapshot contains twelve passing sample tests. The executable asserts the expected values; it does not inspect actual bank source.

**Visual:** `build-comparison-update35.svg` shows exact matching and new/resolved counts. Explain why repeated occurrences are a multiset and why moving a problem to another line creates a different identity in this lesson.

## 09:15–12:40 — Fail closed

Run `assessment_stale_sha`, `assessment_missing_tests`, `assessment_not_run_tests`, `assessment_dropped` and `compare_toolchain_refused`. A test passes because it correctly refuses misleading evidence. A diagnostic count of zero cannot overrule a nonzero build exit code.

**Narration:** “Never confuse the success of the evaluation API with the success of the operation being evaluated. A blocked assessment is often the most accurate result an engineer can provide.”

## End — Challenge

Ask learners to add a new CTest case to their private practice copy testing an error whose line number changed, without altering existing files in the published library. Predict the compare result and explain why this is not a semantic source-tracking algorithm.
