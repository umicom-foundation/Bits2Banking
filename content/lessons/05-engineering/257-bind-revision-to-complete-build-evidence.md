# Chapter 257 — Bind tests and diagnostics to the source actually reviewed

**Bits to Banking · Engineering track · Umicom Foundation**  
**Lab:** `labs/native/change-impact` · **Related:** Chapters 244–247.

## Revision drift: the subtle failure

A developer runs CTest against commit A, updates Framework to commit B and then publishes a screenshot of the green test result as if it covered B. The tests may genuinely have passed, but the evidence no longer establishes anything about the checked-out source. A similar mistake occurs when Studio is built against one Framework gitlink while Umicom OS records another. This is **revision drift**.

An engineering record must identify the source commit, exact build profile and toolchain, linked dependencies, observed test outcomes and any dropped or truncated diagnostic records. A full 40-character SHA-1 or 64-character SHA-256 identifier is used for unambiguous teaching input. The lab does not claim the hash belongs to a real Git repository: it validates the representation only. A production evidence system must additionally verify the object and artefact provenance.

## Follow the C23 evidence boundary

```c
typedef struct BtbImpactEvidence {
    char sourceRevision[BTB_IMPACT_REVISION_CAPACITY];
    uint32_t passedGates;
    uint32_t failedGates;
    uint32_t notRunGates;
    size_t droppedDiagnostics;
    int logComplete;
    int sourceReviewed;
} BtbImpactEvidence;
```

This teaching record is intentionally small. It stores *category outcomes*, not complete CTest XML, log bytes, toolchain fingerprints or signatures. Its two Boolean fields must contain exactly 0 or 1. It refuses contradictory states such as a BUILD gate being both passed and failed.

The assessment compares `evidence.sourceRevision` with the exact revision stored in the impact plan. A mismatch yields `BTB_REASON_STALE_REVISION`. This is a **blocking result** rather than a malformed-input error: the evidence can be perfectly valid for another source revision, but it does not qualify the current plan.

## Dropped diagnostics are not optional

Umicom Framework's existing compiler grammar recognises common GCC, Clang, MSVC and CMake diagnostic formats and reports capacity errors rather than pretending a cropped path is navigable. Its build-diagnostic list tracks dropped records. In the lab, `droppedDiagnostics != 0` blocks an assessment even if other gate bits are marked green.

Why? A truncated log might omit the first error or a failed test. If the captured evidence is incomplete, “no errors seen” does not mean “no errors occurred.” The correct operational response is to retain the original build output, increase an approved capture bound if appropriate and rerun at the same revision.

## Practical commands: record actual identity

```powershell
Set-Location "C:\umicom\Umicom-Applications"
git rev-parse HEAD
git -C ".\framework" rev-parse HEAD
git status
git -C ".\framework" status
cmake --list-presets
```

Choose a real configured preset only after viewing its definition. When you run the build, capture which preset, compiler executable, build type and target list were used. Never record “all tests passed” without the observed total and any failed, skipped or not-run categories. Do not reuse evidence from a stale build directory simply because the executable exists.

## Guided experiment

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\output\learning-build\change-impact\btb-change-impact-test.exe" assess_stale
& ".\output\learning-build\change-impact\btb-change-impact-test.exe" assess_dropped
& ".\output\learning-build\change-impact\btb-change-impact-test.exe" assess_incomplete_log
```

Inspect each test. `assess_stale` supplies a different valid full revision. `assess_dropped` supplies a positive number of lost diagnostic records. `assess_incomplete_log` explicitly clears the log-complete flag. In all three situations the evaluator returns a meaningful blocking reason, and the negative test passes because the unsafe conclusion was refused.

## Limitations and exercises

A malicious or mistaken caller can mark a gate passed without running it. This sample cannot attest to authenticity. In real engineering, the build service should produce the status after execution, and evidence should include command identity, toolchain/environment, provenance and immutable artefact hashes. The Framework Data Server and approved audit service, not the learning code, would own retained production evidence.

Write a one-page incident note where tests were executed on the wrong Framework SHA. Record what can be reused, what must be rerun and how to compare parent gitlinks without destroying code. Explain why merely comparing identical filenames or timestamps is insufficient.

**Review questions:** What distinguishes malformed input from stale evidence? Why does `droppedDiagnostics` block review? What else is required to authenticate a test result? How does a Framework SHA differ from a parent repository SHA?

**Next:** diagnose the earliest observable build-stage failure without automatically declaring it the root cause.
