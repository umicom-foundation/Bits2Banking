# Chapter 224 — Compile an optional adapter against Umicom Framework VCS

**Bits to Banking · C23 integration · Umicom Foundation**  
**Author:** Sammy Hegab · **Laboratory:** `labs/native/git-review-timeline`.

## Why this matters

It would be easy to read a few lines of `git status` into a new application-specific parser. It would also be wrong for the Umicom ecosystem. The Framework already owns a native C interface for working-tree observation, so a learner should understand how to consume that interface through a narrow adapter without copying its implementation into an educational repository.

The optional `framework_bridge.c` includes `umicom/vcs/working_tree.h` from a local Framework checkout. It accepts `UmiVcsWorkingTreeSummary`, translates its existing fields to a teaching `BtbReviewObservation`, validates the result and returns a copied value. It does not call Git, assume that a remote fetch took place, or introduce a new permanent Framework service.

## Compile the independent lab first

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\git-review-timeline" -B ".\output\learning-build\git-review-timeline" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\git-review-timeline" --parallel 2
ctest --test-dir ".\output\learning-build\git-review-timeline" --output-on-failure
```

This build needs only a C23 compiler, CMake and Ninja. It is deterministic and does not communicate with GitHub. The real update-32 release gate source is reused for an additional composition test **if present**; it is not copied into the Update 33 ZIP.

## Opt into the Framework header contract

If you have the existing Framework checkout in `C:\umicom\Umicom-Applications\framework`, configure a separate build directory:

```powershell
cmake -S ".\labs\native\git-review-timeline" -B ".\output\learning-build\git-review-framework" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON -DBTB_FRAMEWORK_SOURCE_ROOT="C:\umicom\Umicom-Applications\framework"
cmake --build ".\output\learning-build\git-review-framework" --parallel 2
```

This compiles an **object target** against the current Framework public header. It does **not** link to a Framework binary or demonstrate a live repository scan. Those tasks are separate production integration work with their own ABI, CMake target and lifetime rules.

## Follow the ownership contracts

The actual Framework flow is: `UmiVcsWorkingTreeRead` creates an owned observation, `UmiVcsWorkingTreeDescribe` copies its summary, the optional adapter copies the fields relevant to the teaching model, and `UmiVcsWorkingTreeDestroy` frees the original Framework observation. The adapter never stores a pointer into Framework-owned memory after returning.

The summary exposes `branch_known`, `commit_known`, `unborn`, `detached`, `divergence_known`, `ahead`, `behind`, `staged`, `untracked`, `conflicts`, `child_commits` and `dirty_children`. Its `commit_id` is copied with explicit capacity checks. The adapter refuses malformed values rather than silently resetting them to a reassuring default.

## Important limits

A `UmiVcsWorkingTreeSummary` describes local observation state. It cannot demonstrate that `origin/main` was fetched recently, prove that a child SHA exists on GitHub, or certify that a test suite ran against the currently staged source. The adapter requires the caller to supply `remoteFresh` separately and does not attempt to derive it from the mere existence of `origin/main`.

If the real Framework public contract changes, modify the teaching adapter after reviewing the new header. Do not rename Framework API functions to suit the lab, duplicate Framework implementation or alter the production ABI without an approved change.

## Questions

Which public Framework function creates the observation? Who owns the returned object? Why is `framework_bridge.c` optional in CMake? Why would successfully compiling the adapter be weaker evidence than executing an end-to-end repository observation using a linked Framework binary?

**Next:** [Chapter 225 — Composing existing release policies](225-reuse-the-existing-c23-release-gate.md).
