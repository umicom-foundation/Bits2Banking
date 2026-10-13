# Episode 79 — Build a safe C23 three-way review model

**Bits to Banking · Umicom Foundation · Sammy Hegab**  
**Target duration:** 11 minutes · **Companion:** Chapters 232–234.  
**Lab:** `labs/native/git-three-way` · **Language:** ISO C23.

## 00:00–01:15 — Define the boundary

**Narration:** "The example we are building is not Git. Git already exists and Umicom Framework already exposes Git providers. We are learning one safe decision model: compare a common ancestor with two independent versions, refuse disagreement and preserve the old output after a failure."

**Screen:** Show `merge.h` and highlight `BTB_MERGE_MAX_RECORDS`, `BtbMergeSnapshot`, `BtbMergePlan` and `BtbMergeMaterialise`. Point out bounded lengths and caller-owned memory.

## 01:15–03:10 — Why presence matters

Use the `git-conflict-cases-update34.svg` decision matrix. Compare `v1 / v1 / v1`, `v1 / v2 / v1`, `v1 / v2 / v2`, `v1 / v2 / v3`, and base-present/ours-deleted/theirs-edited. Explain that a missing record is **different from an empty string**. In Umicom Bank this could represent an intentionally removed field, not a harmless blank value.

## 03:10–05:45 — Follow source in C23

Open `merge.c` and explain:

- `BoundedString`: use `memchr` rather than an unbounded `strlen` on input.
- `AppendNames`: create a deterministic union of symbolic keys with a fixed capacity.
- `CopyVersion`: own the selected bytes; no caller buffer is retained.
- `Classify`: identify no-op, one-sided, identical, and conflicting edits.
- `BtbMergeMaterialise`: return `BTB_MERGE_CONFLICT_PENDING` without modifying an existing result.

**Narration:** "A fail-atomic API is easier to reason about than one that partly writes a report and later discovers that a conflict remains."

## 05:45–07:30 — Configure and run

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\git-three-way" -B ".\output\learning-build\git-three-way" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\git-three-way" --parallel 2
ctest --test-dir ".\output\learning-build\git-three-way" --output-on-failure
```

Show the actual Windows output; **do not** replace the displayed result with the Linux results from the authoring environment. If tests fail, demonstrate capturing the failing CTest name, compiler version and build command.

## 07:30–09:25 — Stop at unresolved conflict

Run the demo and show the classifying output. Set a breakpoint on `BtbMergeMaterialise`, inspect `unresolvedCount`, and show the caller-owned output unchanged. Explain the difference between **an explicit classroom choice** (`BTB_CHOOSE_BASE`) and a *real source merge* that may need both independent features combined.

## 09:25–11:00 — Test discipline and real-world boundary

Highlight `TestPendingOutputAtomic`, `TestPlanOverflowAtomic` and `TestMutation50000`. State that 50,000 seeded mutations are reproducible but not a proof of all possible inputs. The lab has no file access, Git process, network client, threads, database connection or Framework modification.

**Viewer assessment:** Explain what changes if the record array grows beyond 16 keys. Explain why production source must still use Git and the Framework VCS contracts.
