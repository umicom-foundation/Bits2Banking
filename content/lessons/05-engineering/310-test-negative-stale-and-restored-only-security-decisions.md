# Chapter 310 — Test negative, stale and restored-only security decisions

**Bits to Banking · Native C23 engineering · Umicom Foundation**  
**Prerequisite:** Chapters 308–309.  
**Laboratory:** `labs/native/security-operations-review`.

## Why successful examples are not enough

A program may pass its happy-path demonstration while accepting a malformed identifier, misreporting an unknown observation or overwriting a previous valid result after failure. In system administration and financial software, these errors can conceal real operational risk. Tests must therefore include **negative cases**, **stale evidence**, **identity mismatches**, **repeated operations** and **failure atomicity**.

A **failure-atomic operation** leaves the caller's previously valid state untouched when it refuses a request. A **stale observation** belongs to an earlier state or capture and must not be substituted for newer evidence. A **restored-only outcome** means the old state was successfully recovered after a failed change; it is not the same as successful promotion of the new release.

## Run the positive and negative tests on Windows

After merging Updates 39–44, open PowerShell 7 in the repository root:

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S '.\labs\native\security-operations-review' -B '.\output\learning-build\security-operations-review' -G Ninja -DCMAKE_C_COMPILER='C:\msys64\ucrt64\bin\gcc.exe' -DBUILD_TESTING=ON
cmake --build '.\output\learning-build\security-operations-review' --parallel 2
ctest --test-dir '.\output\learning-build\security-operations-review' -R 'bits2banking.security-operations' --no-tests=error --output-on-failure
```

The `-R` expression selects only the new named tests, making the first review easier. Remove `-R` for the entire suite including earlier regressions. Every test may run on Windows only after a successful local build; previous Linux evidence is not a substitute.

## Compare four useful results

- `reviewable`: all fictional required flags are present and current; the status is **REVIEWABLE**, not production-approved.
- `restore`: the independent restore check is withheld; the status becomes **BLOCKED**.
- `stale`: the security evidence capture is no newer than the upstream remote observation; the status becomes **BLOCKED** with a stale-capture reason.
- `upstream-restored`: an earlier release was restored after a failed change; the status becomes **RESTORED_ONLY**, not REVIEWABLE.

The test runner registers separate test names for invalid labels, mismatched revision/configuration/policy, unauthorised same-person approval, repeated attachment, and a denied operation that must preserve its output. The `mutations` test changes one of fifteen evidence conditions across 25,000 deterministic iterations. A deficient result must never be presented as ready.

## Read the exact result before drawing a conclusion

A zero CTest failure count means those tests ran and passed under the selected build. It does not prove that a real operating-system account or network policy was checked. Conversely, a missing CTest binary, an inaccessible toolchain or a test marked *Not Run* is not a passing result; investigate and record why the test was skipped.

For a missing source library, the CMake configuration prints a prerequisite error rather than silently inserting substitute files. Return to the earlier update packages and restore the intended baseline, then rebuild.

## Exercise: derive the invariant from the code

Read `BtbSecurityEvaluate`. Write the invariant: **If any required evidence flag is false, or the upstream decision is unqualified, the result must not be REVIEWABLE.** Now locate the test for each individual bit. Identify the path that verifies the source, configuration and policy identity match before output is committed.

**Question:** Why can't we combine `BLOCKED` and `RESTORED_ONLY` into one success value? **Answer:** Because those states communicate different histories and recovery obligations.

**Question:** Does one static-analysis run prove the binary is safe? **Answer:** No. It is one bounded verification technique; code review, runtime tests and platform checks remain necessary.

**Next:** Chapter 311 — complete Framework-first security review capstone.
