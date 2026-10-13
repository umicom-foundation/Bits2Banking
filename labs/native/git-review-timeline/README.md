# Native C23 Git Observation Timeline — Major Update 33

**Author:** Sammy Hegab · **Organisation:** Umicom Foundation · **Licence:** MIT

This laboratory **does not implement Git**. The production source of truth is the existing Umicom Framework VCS and repository-control API. These tiny types only teach evidence provenance, failure-atomic input rejection, stale-snapshot detection and diagnostic ordering. The timeline retains copies of observations, not pointers; it never opens a repository, executes Git, changes files or performs network calls.

The exercise is cumulative. When Update 32's `git-release-evidence/gate.c` is installed, the new CMake target reuses that exact file rather than copying or replacing the earlier policy. The optional `framework_bridge.c` compiles against the real `UmiVcsWorkingTreeSummary` definition when a Framework checkout is supplied. It translates supplied facts; it does not itself fetch or observe a repository.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\git-review-timeline" -B ".\output\learning-build\git-review-timeline" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\git-review-timeline" --parallel 2
ctest --test-dir ".\output\learning-build\git-review-timeline" --output-on-failure
& ".\output\learning-build\git-review-timeline\btb-git-review-demo.exe"
```

**Optional compile-only Framework contract check** (not an end-to-end runtime integration):

```powershell
cmake -S ".\labs\native\git-review-timeline" -B ".\output\learning-build\git-review-framework" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON -DBTB_FRAMEWORK_SOURCE_ROOT="C:\umicom\Umicom-Applications\framework"
cmake --build ".\output\learning-build\git-review-framework" --parallel 2
ctest --test-dir ".\output\learning-build\git-review-framework" --output-on-failure
```

Tests include 28 named C23 cases, one demonstration case, and **one more** cross-batch composition case when Update 32 is present: **29 standalone / 30 with Update 32**. Source users should verify actual counts with `ctest -N` because optional cases depend on installed prior labs.

## Provenance and non-goals

The demonstration uses a **fictional snapshot** and deliberately references a real-looking commit solely to make the example realistic. It does **not** verify whether that commit is present, pushed, signed, tested or currently checked out. The caller-provided `remoteFresh` bit cannot be independently substantiated by a pure model. An observation ID is caller-assigned, not a cryptographic fingerprint. `BtbReviewEvaluate` reports which aspects need inspection; it never authorises `git push` or `git reset`.

The old implementation lives in the previous labs and is not altered. Production VCS work belongs in `Umicom Framework`, with the stable C ABI and Master/Slave Controller boundaries retained. Do not introduce a second production repository-observation provider in Bits2Banking.
