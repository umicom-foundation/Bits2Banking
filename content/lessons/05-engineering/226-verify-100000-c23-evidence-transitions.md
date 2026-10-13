# Chapter 226 — Verify 100,000 C23 evidence transitions

**Bits to Banking · Testing and verification · Umicom Foundation**  
**Author:** Sammy Hegab · **Laboratory:** `labs/native/git-review-timeline`.

## Why this matters

A program can produce the expected demonstration output yet still be incorrect for malformed inputs. A Git evidence tool must not treat a missing branch as `main`, accept a shortened commit as a full identity, or overwrite the previous trusted report after rejecting an invalid call. A single happy-path test is not enough. The Update 33 suite names each invariant and exercises it independently.

## Learn to read the tests before changing code

Open `test_review.c`. Every CTest entry invokes the **same native C executable** with a different case name. This makes failures identifiable without creating multiple near-identical test source files. The tests are deterministic: no live socket, remote GitHub connection, timer wait, background task or filesystem mutation is required.

Important cases include `detached`, `behind`, `remote-not-fresh`, `unknown-ancestry`, `conflict-priority`, `dirty-child`, `stale-evidence`, `wrong-commit-evidence`, `observation-invalidates`, `rebuild-invalidates`, `invalid-atomic`, `sha256`, `nonmonotonic`, `unborn` and `mutation-100k`. The last one executes 100,000 changing observations with assertions on identity, conflict detection and invalidated evidence.

## Build with strict native diagnostics

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\git-review-timeline" -B ".\output\learning-build\git-review-timeline" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\git-review-timeline" --parallel 2
ctest --test-dir ".\output\learning-build\git-review-timeline" --output-on-failure
```

Expect **29 standalone tests**, or **30** when the existing Update 32 release-gate source is installed. A compiler warning, failed CTest case or absent optional dependency must be reported according to what actually happened on your machine. The training package does not pretend to have performed Windows UCRT64 or complete MkDocs acceptance merely because Linux tests passed.

## Failure-atomicity exercise

Read `TestInvalidAtomic`. It first creates a valid observation. It then supplies a contradiction: the number of staged files exceeds the total number of entries. The operation must return `BTB_REVIEW_INVALID`, leaving the previous observation unchanged. Next, the test attempts to evaluate a malformed commit ID into a report that already contains a sentinel value. The output must retain the sentinel. This is a general C23 API design pattern: validate locally, then publish the complete result once.

Look also at `TestRebuildInvalidatesTest`. A second build operation is recorded after tests passed. Because the executable may have changed, the test proof becomes `NOT_RUN` again. This intentionally conservative contract stops a stale green test result being attached to an unverified rebuild.

## Static reasoning and sanitizer limits

GCC and Clang warnings can reveal conversion mistakes and suspicious assumptions. AddressSanitizer and UndefinedBehaviorSanitizer help expose some invalid memory accesses and undefined operations during the executed tests. Neither tool can prove all possible inputs safe, confirm the real Git repository state, or establish a financial application's release quality. The result must be described at the scope actually exercised.

## Learner assignment

Create one additional failing test **without modifying production Framework code**. For example, supply a valid 64-digit SHA but an evidence ID from the previous observation. Predict the expected result (`STALE`) and which fields must remain unchanged. Add a test name to the laboratory CMake configuration, compile, execute and report the outcome. Keep the existing tests and comments intact.

## Review questions

What does a 100,000-transition deterministic test prove, and what does it not prove? Why are `size_t` counts checked before interpreting the status? Why must a test's return code be verified? Which parts of an Umicom OS release still require real boot or UI acceptance?

**Next:** [Chapter 227 — The complete Umicom contributor capstone](227-umicom-os-framework-git-evidence-capstone.md).
