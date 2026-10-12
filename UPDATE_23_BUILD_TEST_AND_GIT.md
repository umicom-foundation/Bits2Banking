# Bits2Banking — Update 23: Build, Test and Git

## 1. Review and merge the files

Place `Umicom-Bits2Banking-Update-23-VFS-Descriptors-and-Providers.zip` in
`C:\umicom`, then extract into a separate review directory:

```powershell
Set-Location "C:\umicom"
Expand-Archive `
    -LiteralPath ".\Umicom-Bits2Banking-Update-23-VFS-Descriptors-and-Providers.zip" `
    -DestinationPath ".\Bits2Banking-Update23-Review" `
    -Force
```

Compare in Beyond Compare:

```text
Left:  C:\umicom\Bits2Banking-Update23-Review\Umicom-Bits2Banking
Right: C:\umicom\Umicom-Bits2Banking
```

Merge only the reviewed files. Do not replace the whole repository. The archive
has no `Umicom-Applications`, Framework, Kernel or OS folders.

## 2. Check your local working copy

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git diff --stat
```

Stop if the checkout is on a detached HEAD, if unrelated work was changed by
the merge or if `mkdocs.yml` contains unresolved conflict markers.

## 3. Build the VFS descriptors and Notes laboratory

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"

cmake -S ".\labs\native\vfs-descriptors" `
    -B ".\output\learning-build\vfs-descriptors" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON

cmake --build ".\output\learning-build\vfs-descriptors" --parallel 2
ctest --test-dir ".\output\learning-build\vfs-descriptors" --output-on-failure
```

Expected: **3/3 tests passed**. Run the demo:

```powershell
& ".\output\learning-build\vfs-descriptors\btb-vfs-demo.exe"
```

Expected text: `Mounted /notes: Umicom Studio (13 bytes)`.

## 4. Build the read-only provider composition laboratory

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

cmake -S ".\labs\native\vfs-provider-composition" `
    -B ".\output\learning-build\vfs-provider-composition" `
    -G Ninja `
    -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" `
    -DBUILD_TESTING=ON

cmake --build ".\output\learning-build\vfs-provider-composition" --parallel 2
ctest --test-dir ".\output\learning-build\vfs-provider-composition" --output-on-failure
```

Expected: **2/2 tests passed**. Run the demo:

```powershell
& ".\output\learning-build\vfs-provider-composition\btb-vfs-provider-demo.exe"
```

Expected: `Library: Computing, C23, Assembly, Umicom Kernel.`

## 5. Check and build the educational website

The existing website renderer requires MkDocs. No new Python implementation
files were added by Update 23; the existing dependency remains necessary to
render the Markdown pages and Material theme.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

& ".\.venv\Scripts\python.exe" ".\tools\check_mkdocs_config.py"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
```

If your checkout does not contain the earlier `check_mkdocs_config.py`, omit
only the first command. Do not omit the strict MkDocs build.

Confirm the generated homepage:

```powershell
Test-Path ".\site\index.html"
```

Expected: `True`. If MkDocs fails, retain the complete output and do not
publish a partial website.

## 6. Review and publish Bits2Banking only

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"

git status
git branch --show-current

git add -A
git diff --cached --check
git diff --cached --stat

git commit -m "feat(learning): add C23 VFS descriptors and filesystem providers"
git push origin main
```

Inspect all staged files before committing. In particular, ensure that
`output/learning-build/`, `site/`, temporary fixtures and the `.venv/`
Python environment are not staged. If they are, stop and correct the staging
rather than commit generated or private files.

No Framework submodule update, Umicom Applications parent commit or Kernel/OS
commit is required for this batch.
