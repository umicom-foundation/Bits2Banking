# Update 12 — Windows Build, Tests, Website Preview and Git

This update applies to two repositories: Umicom Framework (as the `framework` submodule of Umicom Applications) and the separate Bits2Banking educational repository. The ZIP contains full files rooted at `Umicom-Applications/framework/` and `Umicom-Bits2Banking/` so they can be reviewed with Beyond Compare before merging. It does not contain a kernel source change or generated binaries.

## 1. Review and merge the batch

Download the ZIP into `C:\umicom`. In PowerShell:

```powershell
Set-Location "C:\umicom"
Expand-Archive `
    -LiteralPath ".\Umicom-Bits2Banking-Update-12-ELF-Load-Plans-Physical-Memory-and-Sv39.zip" `
    -DestinationPath ".\Bits2Banking-Update12-Review" `
    -Force
```

Compare and merge **complete individual files**, not whole-directory replacements:

| Review side | Existing checkout |
| --- | --- |
| `C:\umicom\Bits2Banking-Update12-Review\Umicom-Applications\framework` | `C:\umicom\Umicom-Applications\framework` |
| `C:\umicom\Bits2Banking-Update12-Review\Umicom-Bits2Banking` | `C:\umicom\Umicom-Bits2Banking` |

The full-file replacements extend the previous main CLI, education CMake graph, learning indexes, roadmap and MkDocs navigation. They do not delete earlier functions or lesson links. Do not copy generated binaries, build logs or test fixtures into Git.

## 2. Configure and build Umicom Education (Windows UCRT64)

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\framework\tools\umicom-education" `
    -B ".\build\umicom-education" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON
if ($LASTEXITCODE -ne 0) { throw "Education configure failed" }

cmake --build ".\build\umicom-education" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Education build failed" }

ctest --test-dir ".\build\umicom-education" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Education regression tests failed" }
```

**Expected:** 16/16 cases. Update 11 had 14; Update 12 adds `framework.education.elf_load_plan` and `framework.education.load_plan.cli`. Do not claim this result until the tests actually run on Windows.

For detailed diagnostics:

```powershell
ctest --test-dir ".\build\umicom-education" `
    -R "^framework\.education\.(elf_load_plan|load_plan\.cli)$" -V
```

## 3. Inspect the ELF load plan

The test creates a **synthetic** RISC-V64 ELF fixture at a path containing spaces. It is not an executable Umicom Kernel image.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"

& $Education load-plan --file `
    ".\build\umicom-education\education-load-plan-test\fixture with spaces\umicom kernel.elf"
```

Expected summary:

```text
ELF load plan: ELF64 (little-endian)
Machine: 243 | ELF type: 2
Entry address: 0x80200010 | Inside executable segment: yes
Loadable segments: 2 | File-backed bytes: 160 | Zero-fill bytes: 608
Virtual memory extent: [0x80200000, 0x80202100)
```

Try a real Linux ELF image or an Umicom Kernel ELF using its actual path. This command only reads metadata: it does not boot, load, map or execute the file.

## 4. Build the physical-frame laboratory

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\physical-frame-pool" `
    -B ".\output\learning-build\physical-frame-pool" `
    -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
if ($LASTEXITCODE -ne 0) { throw "Frame-pool configure failed" }

cmake --build ".\output\learning-build\physical-frame-pool" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Frame-pool build failed" }

ctest --test-dir ".\output\learning-build\physical-frame-pool" `
    --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Frame-pool tests failed" }
```

Expected: 2/2 tests.

## 5. Build the Sv39 page-table laboratory

```powershell
cmake -S ".\labs\native\sv39-address-translation" `
    -B ".\output\learning-build\sv39-address-translation" `
    -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
if ($LASTEXITCODE -ne 0) { throw "Sv39 configure failed" }

cmake --build ".\output\learning-build\sv39-address-translation" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "Sv39 build failed" }

ctest --test-dir ".\output\learning-build\sv39-address-translation" `
    --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "Sv39 tests failed" }
```

Expected: 2/2 tests. The demo prints `Virtual address: 0x40201120` and `Physical address: 0x9120`.

## 6. Check and build the educational website

The existing MkDocs website renderer requires the repository's Python virtual environment. No Python source is introduced by this batch; this is the unchanged website rendering dependency. Run:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$Books = "C:\umicom\Umicom-Bits2Banking"
$Python = "$Books\.venv\Scripts\python.exe"

& $Python ".\tools\check_mkdocs_config.py"
if ($LASTEXITCODE -ne 0) { throw "Website configuration check failed" }

& $Python -m mkdocs build --strict
if ($LASTEXITCODE -ne 0) { throw "MkDocs strict build failed" }

if (!(Test-Path ".\site\index.html")) { throw "Website homepage was not generated" }
```

Preview in a separate PowerShell terminal:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"
& $Education serve --repo $Books --port 8765
```

Open `http://127.0.0.1:8765/`. Check Lessons 87–91, Video Scripts 26–27, diagrams and the original *Islam: Blueprint for Life* volume. Stop the server using Ctrl+C. The server is a loopback development preview, not a public website host.

## 7. Git — Framework first

Do not commit from a detached submodule checkout; verify you are on `main`. `git add -A` also stages unrelated work, so inspect the staged changes before committing.

```powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
git status
git branch --show-current

git add -A
git diff --cached --check
git diff --cached --stat

git commit -m "feat(education): inspect ELF load plans without executing files"
git push origin main
```

## 8. Git — Bits2Banking second

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current

git add -A
git diff --cached --check
git diff --cached --stat

git commit -m "feat(learning): teach physical memory and Sv39 virtual addresses"
git push origin main
```

## 9. Git — parent Applications last

After the Framework commit has been published, the parent repository must record the new Framework submodule revision. Stage only `framework`; other application modules remain untouched.

```powershell
Set-Location "C:\umicom\Umicom-Applications"
git status
git branch --show-current

git add framework
git diff --cached --check
git diff --cached --stat

git commit -m "chore(framework): record ELF loading education revision"
git push origin main
```

Stop if any command fails, if a repository is detached, or if the staged changes include files you did not intend to publish.

## 10. Optional Umicom Kernel qualification

Do not copy the teaching allocator or Sv39 model into the kernel. Build and test the actual source in its own repository and compare behaviour against the real Kernel documentation:

```powershell
Set-Location "C:\umicom\umicom-kernel"
cmake --preset riscv64-clang-debug
cmake --build --preset riscv64-clang-debug --parallel 2
ctest --preset riscv64-clang-debug --output-on-failure
```

Read `docs/BUILD_AND_TEST.md` in that repository for the appropriate QEMU launch command. The Kernel itself is unchanged by this education batch.
