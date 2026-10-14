# Native C23 read-only text inspection — Chapter 22

This is a **teaching-only** C23 laboratory. Reusable production filesystem tools must be supplied through Umicom Framework. It accepts an explicit local path and a limit; it never creates, edits, deletes, renames or executes files.

**Output contract:** the caller owns `BtbTextSummary` and receives a new result only on success. Binary content (NUL), an over-limit file, missing paths and invalid inputs yield explicit errors. The function counts LF endings, treats CRLF as one newline and counts a non-empty final fragment as a line. It does **not** attempt UTF-8 validation or claim to be a security-hardened untrusted-path sandbox.

## Windows UCRT64 (PowerShell 7 commands, not a script)

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\sysadmin-readonly-text" -B ".\output\learning-build\sysadmin-readonly-text" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\sysadmin-readonly-text" --parallel 2
ctest --test-dir ".\output\learning-build\sysadmin-readonly-text" --no-tests=error --output-on-failure
& ".\output\learning-build\sysadmin-readonly-text\btb-sysadmin-text.exe" ".\labs\native\sysadmin-readonly-text\fixtures\sample.md"
```

## Linux (Bash commands)

```bash
cmake -S labs/native/sysadmin-readonly-text -B output/learning-build/sysadmin-readonly-text -G Ninja -DBUILD_TESTING=ON
cmake --build output/learning-build/sysadmin-readonly-text --parallel 2
ctest --test-dir output/learning-build/sysadmin-readonly-text --no-tests=error --output-on-failure
./output/learning-build/sysadmin-readonly-text/btb-sysadmin-text labs/native/sysadmin-readonly-text/fixtures/sample.md
```

**Expected:** 10 CTest cases. Run the actual commands before reporting that the Windows checks passed. The lab's exact fixture bytes are documented in the test source. Do not inspect private files as part of these exercises.
