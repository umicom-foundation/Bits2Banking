# Major Update 44 — Build, Test and Git (PowerShell commands only)

**Umicom Foundation · Bits2Banking · 15 October 2026**

This package contains **only new files** for `C:\umicom\Umicom-Bits2Banking`. It does not replace or delete earlier source files. Its native C23 lab requires the original learning labs from Updates 39–43. Real Umicom Framework, Applications, Kernel and OS repositories are not changed by this batch.

## 1. Inspect and merge rather than overwrite

Download the ZIP to `C:\umicom` and run these interactive PowerShell commands:

```powershell
Set-Location 'C:\umicom'
Expand-Archive -LiteralPath '.\Umicom-Bits2Banking-Update-44-Security-Operations-and-C23-Review.zip' -DestinationPath '.\Bits2Banking-Update44-Review' -Force
```

Use Beyond Compare to compare:

- Left: `C:\umicom\Bits2Banking-Update44-Review\Umicom-Bits2Banking`
- Right: `C:\umicom\Umicom-Bits2Banking`

Merge **only the reviewed new files**, preserving existing features, comments, educational chapters, navigation and the Umicom New Project Beginner Guide from earlier updates. The ZIP is not a whole-repository replacement.

## 2. Configure the native C23 project

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S '.\labs\native\security-operations-review' -B '.\output\learning-build\security-operations-review' -G Ninja -DCMAKE_C_COMPILER='C:\msys64\ucrt64\bin\gcc.exe' -DBUILD_TESTING=ON
```

**Expected:** CMake finds the earlier `remote-access-review`, `deployment-rehearsal`, `maintenance-review`, `service-readiness` and `sysadmin-evidence` libraries. If it reports a missing previous lab, stop, merge the correct earlier update and configure again. Do **not** replace previous code with a shortened example.

## 3. Build, run regression tests and demonstrate

```powershell
cmake --build '.\output\learning-build\security-operations-review' --parallel 2
ctest --test-dir '.\output\learning-build\security-operations-review' --no-tests=error --output-on-failure
& '.\output\learning-build\security-operations-review\btb-security-operations-demo.exe'
```

**Expected after merging Updates 39–44:** 131 CTest registrations: 101 prior tests plus 30 new tests. The demo prints a fictional `REVIEWABLE` outcome, then `BLOCKED` after independent restore-test evidence is withheld. These are teaching states, not production authentication or authorisation.

For focused tests:

```powershell
ctest --test-dir '.\output\learning-build\security-operations-review' -R 'bits2banking.security-operations' --no-tests=error --output-on-failure
```

Expected focused result: **30/30 passing**. Capture the actual result on your machine; Linux test evidence from the package does not prove Windows acceptance.

## 4. Integrate website navigation and review offline HTML

Open `UPDATE_44_MKDOCS_NAV_SNIPPET.yml` alongside the **current** `mkdocs.yml` in Beyond Compare. Append the 12 Stage 7 chapters, five references, four C23 chapters and five video scripts without replacing prior entries or creating another `nav:` root key. The existing *Islam: Blueprint for Life* chapters must remain accessible.

The offline course is `UPDATE_44_SYSTEM_ADMINISTRATION_COMPLETE_COURSE.html`; it contains **96 chapters** and preserves the previous **84 chapter bodies**. An external standalone copy of the same HTML is also supplied.

If MkDocs is already installed in the repository's existing `.venv`, build the site:

```powershell
& '.\.venv\Scripts\python.exe' -m mkdocs build --strict
```

This command invokes an existing publishing tool; **no Python or PowerShell project implementation script has been added**. If the environment is unavailable, record this publishing gate as *Not Run*. Do not claim a passing website build from a YAML syntax check.

## 5. Verify the Git working tree and publish only Bits2Banking

Complete builds, tests and the reviewed navigation merge first. Check that the current branch is `main`. `git add -A` stages all additions, modifications and deletions in the current repository, including unrelated work, so carefully review the staged changes.

```powershell
Set-Location 'C:\umicom\Umicom-Bits2Banking'
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git diff --cached
git commit -m "feat(learning): add security operations course and C23 evidence review"
git push origin main
git status
```

If `git push` is rejected, inspect remote divergence; never force-push or hard-reset to hide problems. This batch does not update any Framework or OS gitlink.
