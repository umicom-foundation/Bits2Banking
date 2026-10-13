# Bits2Banking — Major Update 36: Merge, Build, Test and Git

**Scope:** `C:\umicom\Umicom-Bits2Banking` only. Do not replace the whole repository or delete code; do not modify Framework, Applications, OS or Kernel to install this educational batch. C23 is the native implementation language. PowerShell below consists of **interactive operator commands**, not a new script file.

## 1. Extract for Beyond Compare review

Save `Umicom-Bits2Banking-Update-36-Change-Impact-and-C23-Build-Recovery.zip` in `C:\umicom`.

```powershell
Set-Location "C:\umicom"
Expand-Archive `
    -LiteralPath ".\Umicom-Bits2Banking-Update-36-Change-Impact-and-C23-Build-Recovery.zip" `
    -DestinationPath ".\Bits2Banking-Update36-Review" `
    -Force
```

Compare:

- **Left:** `C:\umicom\Bits2Banking-Update36-Review\Umicom-Bits2Banking`
- **Right:** `C:\umicom\Umicom-Bits2Banking`

Merge the reviewed **additions only**. Existing content, MkDocs navigation, credits, the Islam volume, media, code and scripts remain unchanged by the ZIP. Review the manifest and SHA-256 checksums before merge. If a path already exists locally with different content, inspect the difference rather than overwriting it automatically.

## 2. Configure and build the native C23 lab on Windows

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\change-impact" `
    -B ".\output\learning-build\change-impact" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\change-impact" --parallel 2
```

If configuration or compilation fails, stop and send the first diagnostic with surrounding lines. Do not delete the source or test to make the build succeed.

## 3. Run tests and demonstration

```powershell
ctest --test-dir ".\output\learning-build\change-impact" --output-on-failure
& ".\output\learning-build\change-impact\btb-change-impact-demo.exe"
```

Expected after a successful Windows build: **43 named CTest cases**. The executable demonstration prints a fictional change with an initially unexecuted OS boot gate, then a fictional complete record suitable for further human review. This does not prove that your actual OS boots.

## 4. Optional installed Framework SDK integration

Only when an installed Framework SDK with `Umicom::vcs` and `Umicom::build` targets is available:

```powershell
cmake -S ".\labs\native\change-impact" `
    -B ".\output\learning-build\change-impact-framework" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DCMAKE_PREFIX_PATH="C:\umicom\installed\framework" `
    -DBTB_WITH_UMICOM_FRAMEWORK=ON `
    -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\change-impact-framework" --parallel 2
& ".\output\learning-build\change-impact-framework\btb-framework-readonly-example.exe" `
    "C:\umicom\Umicom-Applications"
```

The prefix is illustrative. If no compatible SDK exists, record **not run**; do not copy Framework private `.c` files to compensate. The optional C23 executable uses Framework's existing **Automated Build System (`umi_build_automation_*`)**, read-only Git observation and compiler diagnostic APIs and makes **no Git modifications**.

## 5. Existing content and website regression checks

Use the existing native Framework educational publication tool if installed; this batch does not add a new validator. The current publishing system retains an existing MkDocs environment. If that environment is available, run its **existing** strict build:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
```

This invokes an **existing third-party publishing tool**. This update does not introduce Python code or a PowerShell automation script. The command needs a valid `.venv` and compatible MkDocs installation. If absent, mark the website gate **not run**. After reviewing `UPDATE_36_NAVIGATION_AND_REVIEW.md`, merge the additive MkDocs section into your existing `mkdocs.yml`, preserving all previous entries. Then rerun the strict website build and verify actual pages.

To verify previously existing native labs you have installed, rebuild and test them independently using their own `CMakeLists.txt`; do not claim the 43 focused cases cover Updates 28–35 or the full website.

## 6. Git status, add -A, commit, push

Only after reviewing the intended merged files, passing relevant Windows checks and **confirming `main`**:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

git status

git branch --show-current

git add -A

git diff --cached --check

git diff --cached --stat

git commit -m "feat(learning): add C23 change impact and native build recovery training"

git push origin main

git status
```

`git add -A` includes deletions and unrelated modifications within this repository. Inspect `git diff --cached` as necessary. Never commit or push on a detached HEAD as if it were `main`. A non-fast-forward error requires history investigation; do not force push, reset hard, or clean files.
