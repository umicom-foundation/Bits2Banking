# Update 10 — Merge, build, test and commit

This update adds native C23 static-archive inspection to Umicom Framework and lessons on linking, object files, cross-compilation and staged installation to Bits2Banking. No existing source files are deleted. Review complete replacements before merging.

## 1. Extract for comparison

Save `Umicom-Bits2Banking-Update-10-Native-Ar-Archives-Cross-Compilation-and-Linker-Engineering-Verified.zip` to `C:\umicom`.

```powershell
Set-Location "C:\umicom"
Expand-Archive `
    -LiteralPath ".\Umicom-Bits2Banking-Update-10-Native-Ar-Archives-Cross-Compilation-and-Linker-Engineering-Verified.zip" `
    -DestinationPath ".\Bits2Banking-Update10-Review" `
    -Force
```

Compare and selectively merge in Beyond Compare:

| Supplied folder | Existing checkout |
| --- | --- |
| `C:\umicom\Bits2Banking-Update10-Review\Umicom-Applications\framework` | `C:\umicom\Umicom-Applications\framework` |
| `C:\umicom\Bits2Banking-Update10-Review\Umicom-Bits2Banking` | `C:\umicom\Umicom-Bits2Banking` |

**Review these complete replacement files carefully:** `framework/tools/umicom-education/main.c`, `framework/tools/umicom-education/CMakeLists.txt`, `mkdocs.yml`, lesson/video/lab indexes and `ROADMAP_MAJOR_UPDATES.md`. The batch is based on the previous Update 09 delivery. Preserve any later local implementation or annotations that are not part of the supplied baseline.

## 2. Framework — configure, build and test

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\tools\umicom-education" `
    -B ".\build\umicom-education" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON

cmake --build ".\build\umicom-education" --parallel 2

ctest --test-dir ".\build\umicom-education" --output-on-failure
```

Expected after successfully merging all Framework files: **12 passing education tests**. The two new cases are `framework.education.archive_inspect` and `framework.education.archive.cli`. The existing renderer, website preview, publication, navigation and ELF/PE/COFF tests remain registered.

To focus on the new tests:

```powershell
ctest --test-dir ".\build\umicom-education" `
    -R "^framework\.education\.archive" `
    --output-on-failure -V
```

To inspect the real static-library fixture built during CMake:

```powershell
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Fixture = (Get-ChildItem ".\build\umicom-education" -Recurse -File `
    -Include "*archive-fixture*.a", "*archive-fixture*.lib" | Select-Object -First 1).FullName
& $Education archive --file $Fixture
```

The parser reports `Format: ar` and one ordinary object. It should not attempt to launch an executable or open a terminal for each member.

## 3. Bits2Banking — static library and linker map

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\static-library-map" `
    -B ".\output\learning-build\static-library-map" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON

cmake --build ".\output\learning-build\static-library-map" --parallel 2
ctest --test-dir ".\output\learning-build\static-library-map" --output-on-failure
& ".\output\learning-build\static-library-map\btb-ledger-demo.exe"
```

Expected: **2 passing tests** and `Learning fund total (fictional): GBP 504.00`.

Read the native archive with the existing Education tool:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
& $Education archive --file `
    "C:\umicom\Umicom-Bits2Banking\output\learning-build\static-library-map\libbtb_ledger.a"
```

Inspect `output/learning-build/static-library-map/btb-ledger-demo.map` in the Bits2Banking checkout. On UCRT64 GCC, the map should identify the selected archive object and the function reference that required it.

## 4. Bits2Banking — cross-target objects

Start with a host-only build, which does not need Clang:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
cmake -S ".\labs\native\cross-target-object" `
    -B ".\output\learning-build\cross-target-host" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\cross-target-host" --parallel 2
```

For an **optional** cross-compilation, first run `clang --version`. Only proceed if Clang has a RISC-V64 backend:

```powershell
$Toolchain = (Resolve-Path `
    ".\labs\native\cross-target-object\toolchains\riscv64-clang.cmake").Path
cmake -S ".\labs\native\cross-target-object" `
    -B ".\output\learning-build\cross-target-riscv64" `
    -G Ninja `
    "-DCMAKE_TOOLCHAIN_FILE=$Toolchain"
cmake --build ".\output\learning-build\cross-target-riscv64" --parallel 2
```

The cross build produces **relocatable RISC-V ELF objects only**. It does not link a kernel or execute privileged Assembly. Run `umicom-education binary --file` on a reported object path, not on a guessed executable path.

## 5. Validate site navigation and preview

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Books = "C:\umicom\Umicom-Bits2Banking"
& $Education audit --repo $Books
```

This native C23 audit should report zero missing, duplicate, unsafe or structurally incorrect MkDocs navigation entries after all historical chapters have been prepared. The original ten *Islam: Blueprint for Life* chapters must remain visible.

MkDocs is still the website renderer. The new update does not replace it or introduce another script implementation:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
Test-Path ".\site\index.html"
```

Only when the website build succeeds and the file exists should the native preview start:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
& $Education serve --repo $Books --port 8765
```

Open `http://127.0.0.1:8765/` and review Chapters 77–81, Videos 22–23, the diagrams and the preserved Islam volume. Stop the preview with Ctrl+C.

## 6. Commit — Framework first

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(education): inspect native ar archives in C23"
git push origin main
```

Use `main` for maintainer commits. If the Framework submodule is detached or contains unrelated changes, stop and inspect before committing.

## 7. Commit — Bits2Banking second

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): teach archive linking and RISC-V cross-compilation"
git push origin main
```

## 8. Commit — Umicom Applications parent last

```powershell
Set-Location "C:\umicom\Umicom-Applications"
git status
git branch --show-current
git add framework
git diff --cached --check
git diff --cached --stat
git commit -m "chore(framework): record education archive inspector"
git push origin main
```

Stage only `framework` in the parent unless you have separately reviewed other changes. If Git reports nothing to commit, do not create an empty commit. Do not use `git reset --hard`, force-push or delete legacy implementations as routine merge steps.
