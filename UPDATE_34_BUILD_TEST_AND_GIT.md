# Major Update 34 — Merge, C23 build, tests, documentation and Git

**Scope:** `C:\umicom\Umicom-Bits2Banking` only. **No scripts added.** Commands below are interactive PowerShell commands. CMake is declarative build metadata, not a PowerShell script.

## 1. Extract for review

Download `Umicom-Bits2Banking-Update-34-Git-Three-Way-Recovery-and-C23-Conflict-Lab.zip` into `C:\umicom`.

```powershell
Set-Location "C:\umicom"
Expand-Archive -LiteralPath ".\Umicom-Bits2Banking-Update-34-Git-Three-Way-Recovery-and-C23-Conflict-Lab.zip" -DestinationPath ".\Bits2Banking-Update34-Review" -Force
```

Compare in Beyond Compare:

- Left: `C:\umicom\Bits2Banking-Update34-Review\Umicom-Bits2Banking`
- Right: `C:\umicom\Umicom-Bits2Banking`

Merge the reviewed additions. Do **not** mirror/delete or replace the complete repository. Confirm the files under `content/lessons/05-engineering`, `content/videos/scripts`, `content/assets/diagrams`, `labs/native/git-three-way` and the Update 34 root documentation. The package is intended to contain no existing-file replacements.

## 2. Configure the native C23 lab on Windows UCRT64

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --version
gcc --version
ninja --version
cmake -S ".\labs\native\git-three-way" -B ".\output\learning-build\git-three-way" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
```

### Build

```powershell
cmake --build ".\output\learning-build\git-three-way" --parallel 2
```

### Test

```powershell
ctest --test-dir ".\output\learning-build\git-three-way" --output-on-failure
```

**Expected after a successful Windows build: 36/36 tests passing** (35 named test cases plus the executable demo). This is an expectation, not a claim that Windows acceptance has already run.

### Demonstrate and inspect a specific failure case

```powershell
& ".\output\learning-build\git-three-way\btb-git-three-way-demo.exe"
ctest --test-dir ".\output\learning-build\git-three-way" -R "(different_edits|delete_edit|plan_overflow_atomic|mutation_50000)" --output-on-failure
```

## 3. Linux native verification (optional contributor host)

```bash
cmake -S ./labs/native/git-three-way -B ./output/learning-build/git-three-way -G Ninja -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTING=ON
cmake --build ./output/learning-build/git-three-way --parallel 2
ctest --test-dir ./output/learning-build/git-three-way --output-on-failure
```

Compiler versions and test totals must be recorded from the host where the contributor actually runs the command.

## 4. MkDocs navigation and website acceptance

Read `UPDATE_34_NAVIGATION_AND_REVIEW.md` and insert the **new entries exactly once** into your *current* `mkdocs.yml`, preserving all previous groups. Prior Updates 28–33 may have been merged locally without appearing in the same remote navigation snapshot. Do not overwrite the entire configuration.

If the existing MkDocs virtual environment is installed, the existing site can be built with the installed interpreter (this batch adds no Python files):

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
```

If that environment is missing, report **NOT RUN**, do not invent a Python replacement or report the website as qualified. The live Git practice in Chapter 230 is optional and must take place only inside disposable `$HOME\UmicomLearning` directories.

## 5. Review source and publish the Bits2Banking repository on main

This update contains **no changes** to Framework, Applications, Kernel or OS; do not create commits in those repositories because you are installing this learning batch.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached --name-status
git commit -m "feat(learning): add Git merge recovery and C23 three-way lab"
git push origin main
git status
```

**Mandatory pause before commit:** `git add -A` stages all additions, modifications and deletions in the current repository. Inspect `git diff --cached --name-status`, confirm that any MkDocs edit was intentional and that no unrelated source or manuscript has been removed. Confirm the current branch is `main`. If the push rejects as non-fast-forward, fetch and inspect ancestry; do not use force push.

## 6. Honest acceptance matrix

| Gate | How to verify | Status supplied with this ZIP |
|---|---|---|
| GCC C23 lab | `cmake`, `ctest` on authoring Linux | PASSED (36/36) |
| Clang sanitizer lab | Clang ASan/UBSan CTest | PASSED (36/36) |
| Windows UCRT64 | Commands above on your computer | NOT RUN |
| Strict MkDocs | Existing installed MkDocs after navigation merge | NOT RUN |
| Actual Framework/OS integration | Separate native Framework + OS build/test | NOT RUN (unchanged repositories) |
| Live repository recovery | User-authorised disposable exercise | NOT RUN |

The existing Update 33 code and documentation remain unmodified. Running this lab does not automatically execute the previous C23 laboratories; run those separately if a full learning-suite regression is required.
