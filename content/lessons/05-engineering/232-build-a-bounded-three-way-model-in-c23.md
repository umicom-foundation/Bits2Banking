# Chapter 232 — Build a bounded three-way reconciliation model in C23

**Bits to Banking · Native C23 laboratory · Umicom Foundation**  
**Prerequisite:** Chapter 231; understanding `struct`, arrays, pointers and `size_t`.  
**Source:** `labs/native/git-three-way/merge.h` and `merge.c`.

## What we are building — and what we are not

Git's actual merge algorithms understand trees, rename detection, line-based changes, attributes and conflict mechanics. We must **not** implement a second production Git engine inside Bits2Banking. The Framework already has Git providers and working-tree contracts. Instead, this laboratory models the *decision* that a three-way merge must make for a **bounded set of named records**, without opening a file or running Git.

A snapshot can contain up to 16 unique named records. A key such as `bank/ledger.c` is **a symbolic label**, not a source file to merge. The value is a small NUL-terminated teaching payload representing the version. This limitation makes memory lifetime, conflict classification and failure behaviour visible in the debugger.

![Three-way merge model](../../assets/diagrams/git-three-way-versions-update34.svg)

## Understand the three inputs

`base` is the common ancestor, `ours` is one descendant and `theirs` is the other. For each key, compare both the **presence** of the record and its value. A deleted record is *absent*. It is **not** the same thing as a present record whose value is an empty string.

Look at the public C API:

```c
BtbMergeStatus BtbMergePlanBuild(
    const BtbMergeSnapshot *base,
    const BtbMergeSnapshot *ours,
    const BtbMergeSnapshot *theirs,
    BtbMergePlan *outPlan);
```

The three inputs are caller-owned and never modified. `outPlan` is replaced only on success. The plan owns copies of all three versions rather than borrowed pointers. Open `merge.c` and follow `AppendNames`, `CopyVersion` and `Classify` in order.

## Classification rules

| Base | Ours | Theirs | Result |
|---|---|---|---|
| `v1` | `v1` | `v1` | Unchanged |
| `v1` | `v2` | `v1` | Ours-only change |
| `v1` | `v1` | `v3` | Theirs-only change |
| `v1` | `v2` | `v2` | Both changed identically |
| `v1` | `v2` | `v3` | Conflict: review required |
| absent | `v2` | `v3` | Conflicting additions |
| `v1` | absent | `v3` | Delete-versus-edit conflict |

The implementation first checks whether our version is unchanged from base, then whether theirs is unchanged, and whether both descendants agree. A disagreement between two independently changed versions is left unresolved; **no global preference for ours/theirs** exists.

## Configure, compile and run on Windows

These are **interactive PowerShell commands**, not a script file:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\git-three-way" -B ".\output\learning-build\git-three-way" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\git-three-way" --parallel 2
ctest --test-dir ".\output\learning-build\git-three-way" --output-on-failure
& ".\output\learning-build\git-three-way\btb-git-three-way-demo.exe"
```

On a working Windows UCRT64 environment, you should observe the conflict report followed by an explicitly resolved demonstration and passing tests. If CMake cannot find your compiler or Ninja, fix the environment before changing source.

## Debugging experiment

Set a breakpoint in `Classify`. Observe `basePresent`, `oursPresent`, `theirsPresent`, the two values and the selected decision. In a conflicting edit, verify `resolved == 0` and `choice == BTB_CHOOSE_NONE`. Then step into `BtbMergeMaterialise` and confirm the caller's output is *not changed* when the result is `BTB_MERGE_CONFLICT_PENDING`.

## Questions

Why use `memchr` with a fixed capacity rather than `strlen` on untrusted input? Because `strlen` has no built-in bound and can read beyond the provided buffer. Why retain the three values in the plan? So the reviewer can examine original evidence without depending on the lifetime of the caller's input buffers. Why not use these records to merge actual C source? Because lines, syntax, rename, source comments, licensing and business semantics require the real Git integration and human/code review.

**Next:** test the difficult add/delete cases and explicitly resolve disagreements.
