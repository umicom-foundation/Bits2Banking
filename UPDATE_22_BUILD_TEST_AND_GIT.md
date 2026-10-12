# Update 22 — Build, test and publish

## Merge

Extract the Update 22 ZIP to a **review directory**, then compare its `Umicom-Bits2Banking` folder with `C:\umicom\Umicom-Bits2Banking` using Beyond Compare. Merge individual files. Do not replace the entire repository.

## Compile and test the C23 laboratory

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\fat16-inspector" -B ".\output\learning-build\fat16-inspector" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
if ($LASTEXITCODE -ne 0) { throw "CMake configure failed" }
cmake --build ".\output\learning-build\fat16-inspector" --parallel 2
if ($LASTEXITCODE -ne 0) { throw "C23 build failed" }
ctest --test-dir ".\output\learning-build\fat16-inspector" --output-on-failure
if ($LASTEXITCODE -ne 0) { throw "FAT16 tests failed" }
```

The test generates `fixture-fat16.img` inside its build working directory. Run the read-only executable against that fixture if you want to inspect the generated volume.

## Build the website

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
& ".\.venv\Scripts\python.exe" -m mkdocs build --strict
if ($LASTEXITCODE -ne 0) { throw "MkDocs build failed" }
Test-Path ".\site\index.html"
```

MkDocs remains an existing website dependency. No Python implementation source is added by this batch.

## Commit to main — Bits2Banking only

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
git status
git branch --show-current
git add -A
git diff --cached --check
git diff --cached --stat
git commit -m "feat(learning): teach FAT16 layout and read-only filesystem inspection"
git push origin main
```

Do not run the commit if the branch is not `main`, if tests failed or if staged files include unrelated local changes. Framework, Kernel, OS and Applications are not modified by this batch.
