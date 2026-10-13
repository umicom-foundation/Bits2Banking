# Episode 76 — Build a C23 Git evidence timeline

**Bits to Banking · Umicom Foundation · Author: Sammy Hegab**  
**Format:** 11–14-minute native programming walkthrough.  
**Reading:** Chapters 222–224 and `labs/native/git-review-timeline`.

## Purpose

Use an inspectable C23 state model to teach how test evidence becomes stale without recreating Git parsing, staging, branch management or remote access. Introduce bounded buffers, copied structs, generation-like observation IDs and failure-atomic APIs.

## Opening (0:00–1:30)

**Visual:** The timeline diagram shows observation 41 receiving a green build and test. Observation 42 arrives and the earlier green icons turn grey.

**Narration:** “A green test belongs to the code that was actually tested. If the observation changes, we must not silently carry yesterday's proof into today's release.”

## Read the header (1:30–4:30)

Open `review.h`, explain `BtbReviewObservation` and `BtbReviewEvidence`. Point out the 65-byte SHA capacity for a full SHA-256 ID plus terminator. Contrast caller-owned buffers with borrowed pointer lifetimes. Show the tiny four-function lifecycle: Init, Observe, RecordEvidence and Evaluate.

## Follow the C23 implementation (4:30–8:30)

Highlight validation before mutation in `BtbReviewObserve`. Show `BtbReviewRecordEvidence` refusing mismatched observation IDs and commit IDs. Highlight how recording a new build invalidates previous test proof. Use `review_demo.c` to explain why the demonstration reports checks rather than executing Git automatically.

## Build and run (8:30–11:30)

Demonstrate the exact PowerShell CMake commands from `labs/native/git-review-timeline/README.md`. Run `ctest --output-on-failure`; show case names including `stale-evidence`, `invalid-atomic` and `mutation-100k`. Explain the scope of the proof: this is a deterministic pure C23 laboratory, **not** a live Framework integration or a full OS release.

## Optional Framework boundary (11:30–14:00)

Open `framework_bridge.c`. Explain that it consumes the existing `UmiVcsWorkingTreeSummary` type. Its CMake target is opt-in and compile-only. In a future approved production migration, the Framework remains the source of truth and will own real VCS state, rather than this lesson growing into a competing repository service.

## Closing exercise

Ask learners to predict what happens when an older test receipt arrives after a fresh observation. Have them locate and run the specific CTest case proving the answer, then identify the fields that must remain unchanged after rejection.
