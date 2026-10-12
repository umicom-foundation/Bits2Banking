# Native C23 Git ancestry teaching laboratory

**Author:** Sammy Hegab · **Organisation:** Umicom Foundation · **Licence:** MIT

This is a **read-only, deterministic educational model**, not a Git replacement or a repository management tool. It does not call Git, read `.git`, execute a subprocess, authenticate, stage changes, modify commits, push, pull or perform network I/O. For real Umicom applications, use the existing Framework C VCS and repository contracts.

## Learning outcomes

- Show why the parent links in a commit DAG—not dates or filenames—determine fast-forward eligibility.
- Identify equal, local-ahead, local-behind and diverged branch tips.
- Understand why a detached HEAD may differ from the local `main` branch being pushed.
- Model dirty tracked and untracked work as an explicit review condition.
- Recognise a detached commit reachable from neither local nor remote main as needing provenance review.
- Test rejected arguments and full-capacity operations for failure atomicity.

## Source files

| File | Purpose |
|---|---|
| `graph.h` | Public C23 contract and caller-owned records. |
| `graph.c` | Bounded commit DAG, invariant checks, traversal and classification. |
| `graph_demo.c` | Explains the detached HEAD vs local-main case. |
| `test_graph.c` | Ten deterministic classifier tests. |
| `CMakeLists.txt` | C23 build, strict warnings and 11 CTest entries. |

The graph has 64 slots, supports at most two parents and uses integer classroom labels instead of real Git hashes. Commit additions require parents to exist first; this prevents cycles by construction. Each observation uses a bounded `seen` array. `BtbGitGraphAssess` never grants permission to run a Git command; ancestry-compatible operations can still fail because of filesystem collisions, protected branches, transport errors or insufficient permissions.

## Windows UCRT64 — build, test, inspect

These are **interactive PowerShell commands**, not a script.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\git-history" -B ".\output\learning-build\git-history" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\git-history" --parallel 2
ctest --test-dir ".\output\learning-build\git-history" --output-on-failure
& ".\output\learning-build\git-history\btb-git-history-demo.exe"
```

Expected: **11/11** CTest cases and a short explanation showing checked-out HEAD 4, local main 2 and remote main 4. Windows results must be verified on the learner's machine.

## Linux / Clang sanitizers

```text
cmake -S labs/native/git-history -B output/learning-build/git-history-asan -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_C_FLAGS="-fsanitize=address,undefined -fno-omit-frame-pointer -g" -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=address,undefined"
cmake --build output/learning-build/git-history-asan --parallel 2
ctest --test-dir output/learning-build/git-history-asan --output-on-failure
```

An ASan/UBSan pass checks observed runtime violations for the exercised paths; it is not a mathematical proof of memory safety or a cross-platform certification. The CMake project requires GCC/Clang support for `-std=c23` and targets the installed compiler; all warnings are promoted to errors.

## Failure and recovery exercises

Call `BtbGitGraphAdd` with an unknown parent and verify that `graph.count` does not change. Compare two diverged tips and explain why neither a fast-forward pull nor a normal push of the old branch is justified. Mark the simulated worktree dirty and explain why preflight review is still required when the graph relation says “behind”. Finally examine the source of a real Framework working-tree observation API, but **do not copy that implementation into this lab**.

## Validated environment

- GCC 14.2.0, C23, `-Wall -Wextra -Wpedantic -Wconversion -Wshadow -Werror`: 11/11 passed (Linux).
- Clang 17.0.0, C23 with ASan/UBSan: 11/11 passed (Linux).
- 20,000 reproducible graph-classification iterations: passed.
- Windows UCRT64, full MkDocs site and real Umicom Framework integration: not run in this environment.
