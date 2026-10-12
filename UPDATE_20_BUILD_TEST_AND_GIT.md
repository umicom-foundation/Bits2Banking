# Bits2Banking — Update 20: Build, test and publish your changes

The files in this update belong **only to `C:\umicom\Umicom-Bits2Banking`**. The Umicom Framework, Umicom Applications, Umicom Kernel and Umicom OS directories must remain unchanged. Both new laboratories are standalone C23 projects.

## 1. Extract the delivery for review

Place `Umicom-Bits2Banking-Update-20-Device-Discovery-MMIO-and-DMA.zip` in `C:\umicom`, then open PowerShell:

```powershell
Set-Location "C:\umicom"
Expand-Archive `
    -LiteralPath ".\Umicom-Bits2Banking-Update-20-Device-Discovery-MMIO-and-DMA.zip" `
    -DestinationPath ".\Bits2Banking-Update20-Review" `
    -Force
```

Compare these directories in Beyond Compare:

```text
LEFT:  C:\umicom\Bits2Banking-Update20-Review\Umicom-Bits2Banking
RIGHT: C:\umicom\Umicom-Bits2Banking
```

Review and merge the changed files individually. In particular, `mkdocs.yml` and the four updated catalogue indexes should **extend**, not replace, any unrelated local changes. The original Islam volume, older lessons and BookForge workflows remain untouched.

## 2. Confirm the working tree

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git diff --stat
```

Work on `main` according to the established maintainer workflow. If a branch or revision is not as expected, investigate before staging. You do not need to make changes in Framework.

## 3. Prepare the compiler

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
& "C:\msys64\ucrt64\bin\gcc.exe" --version
cmake --version
ninja --version
```

The laboratories need a C23-capable C compiler, CMake 3.24 or later and Ninja. They do not require Python or a running operating-system kernel.

## 4. Build the Device Tree Inspector

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

cmake -S ".\labs\native\device-tree-inspector" `
    -B ".\output\learning-build\device-tree-inspector" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON

cmake --build ".\output\learning-build\device-tree-inspector" --parallel 2

ctest --test-dir ".\output\learning-build\device-tree-inspector" `
    --output-on-failure

& ".\output\learning-build\device-tree-inspector\btb-fdt-demo.exe"
```

**Expected:** Two passing CTest cases. The demonstration reports one `virtio,mmio` candidate, address `0x10001000` and a size of 4096 bytes. This is a generated teaching fixture; no real MMIO address is accessed.

## 5. Build the Virtqueue Lifetime model

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

cmake -S ".\labs\native\virtqueue-lifetime" `
    -B ".\output\learning-build\virtqueue-lifetime" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON

cmake --build ".\output\learning-build\virtqueue-lifetime" --parallel 2

ctest --test-dir ".\output\learning-build\virtqueue-lifetime" `
    --output-on-failure

& ".\output\learning-build\virtqueue-lifetime\btb-vq-demo.exe"
```

**Expected:** Two passing CTest cases. The demonstration reports that a cancellation was requested and a simulated device completion still arrived. No real disk or device queue is touched.

## 6. Check website navigation

The new pages extend the existing MkDocs site. Its renderer still uses the project's existing Python virtual environment; **this update does not introduce any new Python application source**.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$Python = ".\.venv\Scripts\python.exe"

& $Python ".\tools\check_mkdocs_config.py" --syntax-only
& $Python ".\tools\check_mkdocs_config.py"
& $Python ".\tools\validate_learning.py"
```

If a page or original book illustration is reported missing, check whether the earlier batches were merged and whether the original site preparation step has been completed. Do not create empty placeholder lessons simply to suppress a warning.

Build the complete local website:

```powershell
& $Python -m mkdocs build --strict
Test-Path ".\site\index.html"
```

A successful site build should yield `True`. The new lessons must be visible in the software engineering and Umicom navigation, and the original *Islam: Blueprint for Life* entries must still open correctly.

## 7. Preview with the existing native Umicom Education web server

No Framework update is needed. If your existing `umicom-education.exe` is already built, start it from the separate Applications checkout:

```powershell
Set-Location "C:\umicom\Umicom-Applications"
$Education = ".\build\umicom-education\bin\umicom-education.exe"
$Books = "C:\umicom\Umicom-Bits2Banking"

& $Education serve --repo $Books --port 8765
```

Open `http://127.0.0.1:8765/` and inspect chapters 127–131 and episodes 42–43. Stop the server using Ctrl+C. This operation *uses* an already-existing Framework executable; it does not modify Framework source.

## 8. Review and commit only Bits2Banking

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

git status
git branch --show-current
git diff --check
git diff --stat

git add -A
git diff --cached --check
git diff --cached --stat

git commit -m "feat(learning): teach device discovery DMA and VirtIO ownership"
git push origin main

git status
```

Before committing, inspect `git diff --cached` and confirm it contains only the educational files you intended. `git add -A` also stages unrelated deletions or local edits if they exist, so review the staged summary and stop if the scope is incorrect. Do not create commits in Framework, Applications, OS or Kernel for this batch.

## Expected acceptance record

| Check | Expected result |
| --- | --- |
| FDT parser project | 2 CTest passes |
| Virtqueue lifetime project | 2 CTest passes |
| MkDocs YAML syntax | Valid |
| Navigation | New 127–131 and episode 42–43 links exist; earlier links retained |
| Full MkDocs build | Must pass on the actual local checkout before publication |
| Original Islam volume | All original chapter navigation remains intact |
| Repositories changed | `Umicom-Bits2Banking` only |
