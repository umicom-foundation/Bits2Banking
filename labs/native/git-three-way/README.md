# Native C23 three-way merge review laboratory

**Bits2Banking · Umicom Foundation · Sammy Hegab · MIT**

This is **not** a Git client, a diff3 implementation, a source-code conflict
resolver or a substitute for Umicom Framework. It is a bounded educational
model of one idea behind a three-way merge: when a common ancestor (`base`)
changes in two independent versions (`ours` and `theirs`), a safe decision
must consider **all three versions** and must preserve disagreements.

Each snapshot consists of at most 16 unique *symbolic record keys* and one
NUL-terminated value of at most 127 bytes per key. `bank/ledger.c` in the demo
is a **record name**, not a file to open or modify. Do not pass actual source
files to this model: source files have line-level structure and need Git's
real merge machinery plus careful human review.

## Design contracts

- The caller owns all snapshot/plan structures; `BtbMergePlanBuild` copies
  content and never retains an input pointer.
- A record's **absence** is distinct from an empty string value.
- A unilateral change can be selected safely; matching two-sided changes are
  accepted once; a divergent two-sided change stays unresolved.
- Deletion-versus-edit and inconsistent concurrent addition are conflicts.
- **No output snapshot** is published while a conflict remains unresolved.
- A reviewer chooses base/ours/theirs/delete explicitly, once per conflict.
- Bounded input strings and duplicate record keys are validated before any
  caller-owned output changes. Stale/uninitialised plans are rejected.
- The code is serial, deterministic, not thread-safe and not security-grade.
- Actual Git history, stashes, ref identity, conflict markers, upstream state,
  submodule gitlinks and repository operations remain Git / Umicom Framework
  responsibilities. No product should reuse this teaching model as a VCS.

## Windows UCRT64 PowerShell build commands (interactive, not a script)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\git-three-way" -B ".\output\learning-build\git-three-way" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\git-three-way" --parallel 2
ctest --test-dir ".\output\learning-build\git-three-way" --output-on-failure
& ".\output\learning-build\git-three-way\btb-git-three-way-demo.exe"
```

The full test set includes clean convergence, add/delete cases, unresolved
conflicts, explicit resolutions, input immutability, bounded strings, capacity,
50,000 seeded deterministic mutation cases and a console demonstration. A
pass establishes this **model's** behaviour, not the correctness of Git's
real merges or the safety of publishing a live Framework change.

## Production boundary

The canonical Framework source provides, among others,
`include/umicom/vcs/working_tree.h`, `include/umicom/vcs/git_cli.h`,
`include/umicom/repository/gitlink.h` and
`include/umicom/repository/submodule_lock.h`. Refer to those actual public
contracts when integrating Git and repository inspection in Umicom Studio.
No new Framework repository source files are included in this package.
