# Read a build log and choose the next step

Tell configuration, compilation and test failures apart and keep evidence of the first useful diagnostic.

**Before you start:** PowerShell and the small notes-word-count project from the previous lab. The reading steps also apply to an existing Umicom build log.

[Community learning route](../index.md) · [Printable HTML](../handouts/12-read-a-build-log.html)

## Three different stages

Configuration discovers the compiler and creates build instructions. Building compiles source files and links them into libraries or programs. Testing runs checks against the built program. A failure in one stage can leave old output from an earlier attempt. Do not treat that old program as proof that the latest source built successfully.

## 1. Give this attempt its own folder

```powershell
$runFolder = Join-Path $PWD ("logs-" + (Get-Date -Format "yyyyMMdd-HHmmss"))
New-Item -ItemType Directory -Path $runFolder
```

Get-Date formats the current date and time. Join-Path joins a folder and a name. $runFolder keeps that path for this terminal session. Use the same folder for the three logs from this one attempt so they can be compared.

## 2. Capture configuration and check the result

```powershell
cmake -S . -B build -G Ninja 2>&1 | Tee-Object (Join-Path $runFolder "configure.log")
$LASTEXITCODE
```

2>&1 sends the error stream into the output stream. The pipe sends that combined output to Tee-Object, which shows it and saves a copy. Tee-Object completing does not prove CMake succeeded. Read the exit code immediately. Zero means this command reported success. Stop here if it is non-zero.

## 3. Build, then test only after a successful build

```powershell
cmake --build build 2>&1 | Tee-Object (Join-Path $runFolder "build.log")
$LASTEXITCODE
```

If the build succeeded, run the following. A test can still fail even when compilation succeeded.

```powershell
ctest --test-dir build --output-on-failure --no-tests=error --output-log (Join-Path $runFolder "tests.log")
$LASTEXITCODE
```

## 4. Read the first useful error

```powershell
Get-Content (Join-Path $runFolder "build.log") -Tail 40
Select-String -Path (Join-Path $runFolder "build.log") -Pattern "error:|FAILED:|warning:"
```

-Tail 40 reads the last forty lines. Select-String finds matching text. These searches are clues, not a complete diagnosis: other compilers may use different wording. Read the surrounding lines and the named source file. An error near the beginning can cause several later errors.

A missing header usually needs a dependency or include-path investigation. An undefined reference usually comes from linking: the declaration was seen but an implementation was not linked. A test assertion means the program ran far enough to compare a result with an expectation. A crash or timeout needs its own investigation.

## 5. Record enough to repeat the problem

Keep the command, current folder, compiler version, source revision when available, first diagnostic and exit code. Remove credentials and private paths before sharing a public report. Write what you changed and which check you reran. Keep a failure visible until the relevant check passes against the intended source.

## Your turn

In the practice project, misspell a function name in src/main.c, build and read the error. Correct it, rebuild and test. Compare both logs. Do not make deliberate mistakes in a product checkout.

## Continue when you are ready

[Previous: Follow a button into Umicom Framework](11-follow-a-framework-button.md)

[Explore the related course](../../courses/learning-cmake/index.html). You can finish this exercise without leaving this page.

[Video teaching script](../video-scripts/12-read-a-build-log.md) · [Short community message](../messages/12-read-a-build-log.md)
