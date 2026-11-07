# Video script: Read a build log and choose the next step

**Aim:** Tell configuration, compilation and test failures apart and keep evidence of the first useful diagnostic.

**Preparation:** PowerShell and the small notes-word-count project from the previous lab. The reading steps also apply to an existing Umicom build log. Use a separate practice folder and hide notifications or personal account details before recording.

[Lesson and exact commands](../lessons/12-read-a-build-log.md)

## Opening words

Next, we will take this topic one step at a time: read a build log and choose the next step. Follow one step at a time. Pause the video whenever you need a little more time.

## Scene 1

Show three blank labels: Configure, Build and Test. Explain their different jobs before displaying commands.

## Scene 2

Create the timestamped folder and run each stage separately. Pause at every exit code.

## Scene 3

Introduce one deliberate typo only in the practice copy, compare its failure with the repaired build and show the evidence note.

## Walkthrough and pauses

### Three different stages

**Say:** Configuration discovers the compiler and creates build instructions. Building compiles source files and links them into libraries or programs. Testing runs checks against the built program. A failure in one stage can leave old output from an earlier attempt. Do not treat that old program as proof that the latest source built successfully.

### 1. Give this attempt its own folder

**On screen — type one line at a time:**

```powershell
$runFolder = Join-Path $PWD ("logs-" + (Get-Date -Format "yyyyMMdd-HHmmss"))
New-Item -ItemType Directory -Path $runFolder
```

Pause. Read the result before continuing.

**Say:** Get-Date formats the current date and time. Join-Path joins a folder and a name. $runFolder keeps that path for this terminal session. Use the same folder for the three logs from this one attempt so they can be compared.

### 2. Capture configuration and check the result

**On screen — type one line at a time:**

```powershell
cmake -S . -B build -G Ninja 2>&1 | Tee-Object (Join-Path $runFolder "configure.log")
$LASTEXITCODE
```

Pause. Read the result before continuing.

**Say:** 2>&1 sends the error stream into the output stream. The pipe sends that combined output to Tee-Object, which shows it and saves a copy. Tee-Object completing does not prove CMake succeeded. Read the exit code immediately. Zero means this command reported success. Stop here if it is non-zero.

### 3. Build, then test only after a successful build

**On screen — type one line at a time:**

```powershell
cmake --build build 2>&1 | Tee-Object (Join-Path $runFolder "build.log")
$LASTEXITCODE
```

Pause. Read the result before continuing.

**Say:** If the build succeeded, run the following. A test can still fail even when compilation succeeded.

**On screen — type one line at a time:**

```powershell
ctest --test-dir build --output-on-failure --no-tests=error --output-log (Join-Path $runFolder "tests.log")
$LASTEXITCODE
```

Pause. Read the result before continuing.

### 4. Read the first useful error

**On screen — type one line at a time:**

```powershell
Get-Content (Join-Path $runFolder "build.log") -Tail 40
Select-String -Path (Join-Path $runFolder "build.log") -Pattern "error:|FAILED:|warning:"
```

Pause. Read the result before continuing.

**Say:** -Tail 40 reads the last forty lines. Select-String finds matching text. These searches are clues, not a complete diagnosis: other compilers may use different wording. Read the surrounding lines and the named source file. An error near the beginning can cause several later errors.

**Say:** A missing header usually needs a dependency or include-path investigation. An undefined reference usually comes from linking: the declaration was seen but an implementation was not linked. A test assertion means the program ran far enough to compare a result with an expectation. A crash or timeout needs its own investigation.

### 5. Record enough to repeat the problem

**Say:** Keep the command, current folder, compiler version, source revision when available, first diagnostic and exit code. Remove credentials and private paths before sharing a public report. Write what you changed and which check you reran. Keep a failure visible until the relevant check passes against the intended source.

### Your turn

**Say:** In the practice project, misspell a function name in src/main.c, build and read the error. Correct it, rebuild and test. Compare both logs. Do not make deliberate mistakes in a product checkout.

## Closing words

Before moving on, try the exercise once more in your own practice folder. If the result is different, compare the command and current location with the lesson. You can come back to this step at any time.
