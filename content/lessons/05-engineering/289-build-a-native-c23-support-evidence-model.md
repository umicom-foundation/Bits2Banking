# Chapter 289 — Build an offline C23 support-evidence model with fail-closed checks

**Bits to Banking · Advanced Engineering · Umicom Foundation**  
**Implementation language:** C23.  
**Prerequisite:** System Administration Chapters 1–36 and Engineering Chapter 287.

## Why this matters

This chapter introduces the standalone C23 model in `labs/native/sysadmin-evidence`. It does **not** inspect live Windows services, manage Linux accounts or alter a repository. Learners supply fictional observations as data. The aim is to practise exact enums, bounded records, memory ownership and explicit readiness policies.

## Build as a separate laboratory

From **PowerShell 7** in `C:\umicom\Umicom-Bits2Banking`:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\sysadmin-evidence" -B ".\output\learning-build\sysadmin-evidence" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\sysadmin-evidence" --parallel 2
ctest --test-dir ".\output\learning-build\sysadmin-evidence" --no-tests=error --output-on-failure
```

Expected result: sixteen registered CTest cases pass. If CMake reports that your GCC version does not support C23, record the actual toolchain version rather than changing the required language mode to make the error disappear.

## Understand the model before calling it

`BtbAdminObservation` stores a checked ID, capture ID, a finite state and a 64-byte label. The state is one of PASS, WARNING, FAILURE or NOT_RUN. A review stores at most 16 observations and supports check identifiers 1 to 32. A 32-bit required-check mask expresses which of those check IDs the operator requires for a decision.

```c
const uint32_t requiredMask = UINT32_C(0x3); /* IDs 1 and 2 */
BtbAdminReport report;
BtbAdminResult result = BtbAdminReviewEvaluate(
    &review, requiredMask, &report);
if (result != BTB_ADMIN_OK) {
    /* The caller's previous report remains unchanged. */
}
```

Required observations must be present, current and PASS. A stale or NOT_RUN required check results in BLOCKED. An optional warning results in REVIEW. A genuine READY is available only for the supplied fictional evidence; it is **not** a release certificate for a real Umicom product.

## Guided examination

Start with `admin_evidence.h`, then follow the implementation from `BtbAdminReviewInit` through `BtbAdminReviewAdd` to `BtbAdminReviewEvaluate`. Explain the loop that detects duplicates and the check that rejects a label with no NUL terminator. Run the named CTests `missing`, `stale`, `preserve` and `full` separately if you want to see four distinct refusal cases.

## Exercises

1. Change the fictional required backup result in the demo from PASS to NOT_RUN. Predict the outcome before compiling.
2. Add a 17th distinct check to a review and explain the FULL result without freeing or writing beyond capacity.
3. Explain how a report distinguishes a missing required check from an explicit FAILURE.

**Answers:** An unrun required check is BLOCKED; the 17th record is rejected without mutation; missing is absence while FAILURE is an observed adverse result.


## The Umicom Framework ownership rule

This chapter teaches a reproducible concept and, where applicable, uses a stand-alone learning-only model. Production tools must reuse Framework-owned VCS, build, diagnostics, process, security, storage and observability contracts before any new shared functionality is proposed. No PowerShell or Python implementation files are introduced.

## Safe completion criterion

Write one short paragraph distinguishing **observed facts**, **policy decisions** and **not-yet-verified outcomes**. Preserve the previous source and comments. If you cannot reproduce a result on your operating system, state the limitation rather than guessing.
