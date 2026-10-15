# Native C23 build-evidence laboratory — Major Update 35

**Owner:** Umicom Foundation · **Author:** Sammy Hegab  
**Licence:** MIT · **Primary implementation:** ISO C23

## Purpose

Explore copied compiler-diagnostic evidence, revision-bound build identity, immutable snapshot lifecycles and exact diagnostic comparisons. The standalone lab does **not** parse Git, execute Git, parse raw compiler output, run builds, modify files or confer release approval. Those production capabilities belong to **Umicom Framework**, with existing public contracts:

- `umicom/vcs/working_tree.h` — `UmiVcsWorkingTreeRead`, `Describe`, `Destroy`.
- `umicom/build/parser.h` — shared GCC/Clang/MSVC/CMake parser output.
- `umicom/build/diagnostic.h` — normalized owned diagnostic list and dropped count.
- `umicom/repository/submodule_lock.h` — parent gitlink staging, not pulling/pushing.

## File map

| File | Responsibility |
|---|---|
| `evidence.h` | Public bounded C23 teaching data model and ownership contracts |
| `evidence.c` | Snapshot lifecycle, test status, diagnostic assessment and exact multiset comparison |
| `evidence_demo.c` | Fully fictional old/new Umicom finance diagnostic demonstration |
| `test_evidence.c` | Named positive/negative/atomicity tests and 50,000 deterministic mutations |
| `framework_bridge.h` / `.c` | Optional conversion from **real public Framework types**, no duplicate parser |
| `framework_demo.c` | Optional Framework-linked read-only Git and parser example |
| `CMakeLists.txt` | Native targets, strict compiler warnings, CTest and optional SDK exports |

## Source contract

A snapshot owns its complete copied data. `BtbEvidenceRunInit` only publishes valid identities. `BtbEvidenceAddProblem` validates strings without assuming a NUL terminator exists, copies data, and refuses a 25th record. `BtbEvidenceRecordBuild` fixes the process exit and dropped-diagnostic count; problem additions are prohibited afterwards. Tests are recorded separately. `BtbEvidenceSeal` freezes the snapshot without claiming that it passed.

`BtbEvidenceAssess` returns `OK` when evaluation succeeds, but reports **nonzero review flags** for stale revision, wrong profile, failed build, parsed errors, missing/dropped diagnostics and tests that failed, were skipped or did not run. The resulting `readyForHumanReview` signal is not permission to commit or push.

`BtbEvidenceCompare` preserves repeated diagnostic occurrences, matches each previous occurrence at most once, and refuses comparisons across different profiles/toolchains. The model uses exact locations and messages, so a line-number change is intentionally reported as a resolved plus introduced record.

## Standalone build (Windows PowerShell commands, NOT a script)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\build-evidence" -B ".\output\learning-build\build-evidence" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\build-evidence" --parallel 2
ctest --test-dir ".\output\learning-build\build-evidence" --output-on-failure
& ".\output\learning-build\build-evidence\btb-build-evidence-demo.exe"
```

The standalone suite registers **56 CTest cases**, including the demo. No Python, PowerShell script or Framework SDK is needed for this target.

## Optional installed Framework SDK integration

Only enable this target when the compatible Framework CMake package exports `Umicom::vcs` and `Umicom::build`:

```powershell
cmake -S ".\labs\native\build-evidence" -B ".\output\learning-build\build-evidence-sdk" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DCMAKE_PREFIX_PATH="C:\umicom\installed\framework" -DBTB_ENABLE_FRAMEWORK_SDK=ON -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\build-evidence-sdk" --parallel 2
ctest --test-dir ".\output\learning-build\build-evidence-sdk" --output-on-failure
```

The prefix is an example. No installed Framework SDK was available to validate this optional target in the authoring environment; **do not claim it has passed until you run it against your own installed SDK**. If this target is enabled it adds one further CTest case, for **57 total registered cases**.

The optional executable's `--repo` mode calls the **real Framework** `UmiVcsWorkingTreeRead` and performs read-only inspection; it never runs commit, push, switch, update, reset, clean or stash.

## Deliberate limitations

- Only 24 diagnostic records, 255-byte paths and 255-byte messages in the teaching snapshot; long records are refused, never cropped.
- No diagnostic suppression database, AST identity, Git-history parser, filesystem watcher, concurrent queue, remote authentication or build invocation.
- The educational observation sequence is caller-owned and is not a cryptographic timestamp.
- A SHA cannot describe a dirty working tree without additional provenance.
- Different toolchains/profiles produce `INCOMPARABLE`, not a fabricated trend.
- The SDK-linked example needs an ABI-compatible Framework SDK, build-and-launch validation and separate product release controls.

See Chapters 240–251 and the [build-evidence teaching guide](../../../content/teaching/build-evidence.md) for guided source walkthroughs.
