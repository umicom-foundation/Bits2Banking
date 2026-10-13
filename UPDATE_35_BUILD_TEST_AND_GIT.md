# Bits2Banking — Major Update 35: Build, Test and Git

**Title:** Framework VCS Reuse, C23 Build Evidence and Advanced Diagnostics  
**Owner:** Sammy Hegab · Umicom Foundation  
**Source repository:** `C:\umicom\Umicom-Bits2Banking`  
**Development policy:** C23 and Assembly first; no new `.py`, `.ps1` or application-local Git/compiler parsers.

## 1. Examine and merge the update

Download `Umicom-Bits2Banking-Update-35-Framework-VCS-and-C23-Build-Evidence.zip` into `C:\umicom`, then in PowerShell run:

```powershell
Set-Location "C:\umicom"
Get-FileHash -Algorithm SHA256 ".\Umicom-Bits2Banking-Update-35-Framework-VCS-and-C23-Build-Evidence.zip"
Expand-Archive `
  -LiteralPath ".\Umicom-Bits2Banking-Update-35-Framework-VCS-and-C23-Build-Evidence.zip" `
  -DestinationPath ".\Bits2Banking-Update35-Review" -Force
```

Compare the following paths in **Beyond Compare**:

- **Left:** `C:\umicom\Bits2Banking-Update35-Review\Umicom-Bits2Banking`
- **Right:** `C:\umicom\Umicom-Bits2Banking`

Merge **only the reviewed additions**, never mirror/delete the destination tree. Existing manuscripts, Git history, `mkdocs.yml`, earlier chapter files and Framework repositories remain unchanged by this partial ZIP. The archive includes a file manifest with SHA-256 hashes for each delivered source file.

## 2. Configure the native C23 laboratory

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
gcc --version
cmake --version
ninja --version
cmake -S ".\labs\native\build-evidence" `
  -B ".\output\learning-build\build-evidence" `
  -G Ninja `
  -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
  -DBUILD_TESTING=ON
```

The standalone target uses no Python, PowerShell script, Framework SDK, network service or Git process. Its CMake files are declarative build metadata; all new executable learning logic is C23.

## 3. Build and run 56 named native tests

```powershell
cmake --build ".\output\learning-build\build-evidence" --parallel 2
ctest --test-dir ".\output\learning-build\build-evidence" --output-on-failure
& ".\output\learning-build\build-evidence\btb-build-evidence-demo.exe"
```

**Expected from the standalone default configuration: 56/56 passing CTest cases.** This expectation is based on GCC/Clang validation in the authoring Linux environment; it is NOT a report that your UCRT64 run has already passed. Tests cover correct and malformed SHAs, owned copied diagnostics, capacity refusal, sealed-state invariants, stale and incomplete build outcomes, tests failed/skipped/not-run, exact multiset comparisons, profile/toolchain mismatch, output atomicity and 50,000 reproducible adversarial operations.

To inspect one negative test:

```powershell
& ".\output\learning-build\build-evidence\btb-build-evidence-test.exe" assessment_dropped
& ".\output\learning-build\build-evidence\btb-build-evidence-test.exe" compare_toolchain_refused
```

Passing a negative test means the native library rejected invalid evidence as designed.

## 4. Optional SDK-linked Framework acceptance

The standalone laboratory deliberately builds without Framework. A second CMake option enables a **real imported Framework dependency** and executable using Framework's existing `Umicom::vcs` and `Umicom::build` targets. First install the same-ABI Framework SDK and identify its actual prefix. The path below is **illustrative**; update it to your real installed package location:

```powershell
cmake -S ".\labs\native\build-evidence" `
  -B ".\output\learning-build\build-evidence-sdk" `
  -G Ninja `
  -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
  -DCMAKE_PREFIX_PATH="C:\umicom\installed\framework" `
  -DBTB_ENABLE_FRAMEWORK_SDK=ON `
  -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\build-evidence-sdk" --parallel 2
ctest --test-dir ".\output\learning-build\build-evidence-sdk" --output-on-failure
```

When the SDK build succeeds, it registers **one additional named test** (56 in total) and provides `btb-build-evidence-framework-demo.exe`. The program can read a repository in **read-only mode** using Framework VCS:

```powershell
& ".\output\learning-build\build-evidence-sdk\btb-build-evidence-framework-demo.exe" `
  --repo "C:\umicom\umicomOS\framework"
```

**The SDK-linked target was not tested in the authoring environment.** Do not report it as passed unless it actually builds and runs with your Framework SDK. A missing SDK or ABI mismatch is an explicit external acceptance issue, not a reason to copy Framework source into Bits2Banking.

## 5. Documentation and regression gates

Review `UPDATE_35_NAVIGATION_AND_REVIEW.md` and merge its additive entries into your **current** `mkdocs.yml`. The previous curriculum may have local navigation entries from Updates 28–34 that were not present in the last public GitHub file; never replace the full navigation with this partial snippet. Preserve every original *Islam: Blueprint for Life* page and all historic book links.

The existing MkDocs publisher may require the current repository's pre-existing Python virtual environment. **No Python implementation files are added in this batch.** If that environment is already installed, invoke the existing tool without creating a script:

```powershell
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
```

If the virtual environment is absent, mark the documentation build **not run** rather than claiming it passed. The source files and diagrams can still be inspected directly. The complete existing repository/Framework regression suite was not run in the authoring environment, so run the relevant established suites after merging before publishing.

## 6. Standard Git Add, Commit and Push (main only)

After reviewing merged source, navigation, and actual Windows test results:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): add Framework VCS reuse and native C23 build evidence lessons"
git push origin main
git status
```

Stop if the active branch is not `main`. `git add -A` stages additions, modifications **and deletions** in the current repository. Inspect the staged changes before committing and omit unrelated work. Do not use force pushes to bypass non-fast-forward errors. This batch does **not** change Umicom Framework, Applications, Kernel or OS; there is no other repository to commit for this learning-only delivery.

## 7. Source-preservation and safety rules

- Do not delete or simplify existing source because it is unfamiliar.
- Preserve authorship, licences, public APIs, features, tests and educational comments.
- When an old implementation must be superseded, retain it for review under an explained disabled block unless its deletion has been explicitly approved.
- Keep C23/Assembly as implementation languages. Other runtime languages are only allowed when essential and approved.
- Do not introduce Python/PowerShell scripts, clone an existing Framework module into the application, or let the educational tool mutate Git repositories.
- A clean Git status is not a release approval and a green model assessment is not permission to push.
