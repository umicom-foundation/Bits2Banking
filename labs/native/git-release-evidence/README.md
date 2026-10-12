# Git release evidence — native C23 laboratory

**Owner:** Umicom Foundation · **Author:** Sammy Hegab · **Licence:** MIT

This laboratory **does not call Git, checkout a branch, stage files, commit,
push, copy source, or update a submodule**. It evaluates caller-provided,
immutable evidence. The actual source of truth for Git observation is the
Umicom Framework VCS/Repository subsystem. This teaching code is **not** a
security boundary or a substitute for Git's fast-forward checks.

## Build and test with GCC or Clang

From the root of `C:\umicom\Umicom-Bits2Banking` in PowerShell:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\git-release-evidence" -B ".\output\learning-build\git-release-evidence" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\git-release-evidence" --parallel 2
ctest --test-dir ".\output\learning-build\git-release-evidence" --output-on-failure
& ".\output\learning-build\git-release-evidence\btb-git-release-gate-demo.exe"
```

The build uses strict warnings **as errors**. CTest contains 34 independent
scenarios (33 case-driven tests and one demonstration), including 100,000
reproducible negative mutations. No Python, PowerShell script or remote
network access is required.

## Lifecycle and ownership

`BtbGateSnapshot` and `BtbGateReport` are caller-owned structures. On invalid
input the report is not modified. On a valid call, the complete report is
replaced. Strings for pin checks contain exactly 40 hexadecimal digits and one
terminating byte. Every blocked reason is retained in a bitmask; return codes
distinguish malformed evidence from legitimate failed qualifications.

- **COMMIT** requires a reviewed, non-empty staging area, main branch, known
  remote ancestry, clean unstaged/untracked state, and passing build/tests/docs.
- **PUSH** requires a clean index/worktree, at least one outgoing local commit,
  known upstream ancestry, and passing build/tests/docs.
- **PIN** requires a reviewed, sole staged Framework gitlink, a published and
  tested clean child checkout, and an exact match between requested and tested
  child commit identifiers. Pinning changes the *parent repository*, not the
  canonical Framework repository.

These gates are deliberately conservative educational policies. They cannot
prove a remote remained unchanged after observation; only Git's actual push
transaction can make that determination. They cannot turn a modelled test
result into real evidence that a test ran.

## Architecture bridge (read-only)

Read `include/umicom/vcs/working_tree.h` in Umicom Framework and inspect
`UmiVcsWorkingTreeRequest`, `UmiVcsWorkingTreeRead`,
`UmiVcsWorkingTreeDescribe` and `UmiVcsWorkingTreeSummary`.

Those Framework APIs are the authoritative way for a native consumer to obtain
working-tree and child-repository observations. The demonstration intentionally
*does not compile against Framework*: it exposes a portable policy contract
and avoids introducing a second Git status parser. Any production integration
must confirm the Framework target, runtime ABI and current snapshot lifetime.

See Chapters 213–215 and the instructor guide for mapping, evidence collection
and a realistic Umicom OS parent-pin review.
