# First C programs: read, build and check

This lab builds seven small hosted C23 programs and two contract tests. You may read the source and predict output without executing anything. The commands below describe expected behaviour; a published source file is not evidence that these commands passed on your computer.

## What you need

- A local Bits2Banking checkout containing labs/native/first-c-programs.
- An editor that saves plain text. Keep source names ending in .c or .h, without adding .txt.
- CMake 3.24 or later, Ninja and a compiler that supports the project's C23 setting.
- For the Windows commands: the prepared MSYS2 UCRT64 toolchain under C:\msys64\ucrt64\bin. These commands do not install it.
- For Linux: a prepared shell with cmake, ninja and a suitable cc available. Use a personal checkout and an ordinary user account.

Run one command at a time and stop on an error. PowerShell does not automatically stop a pasted sequence after a failed native command. Read the [development setup](../../../content/lessons/06-umicom/24-development-setup.md) chapter for the wider environment.

## Windows: build and run only the greeting

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\first-c-programs" -B ".\build\first-c-programs" -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DBUILD_TESTING=ON
cmake --build ".\build\first-c-programs" --target btb-first-greeting
& ".\build\first-c-programs\btb-first-greeting.exe"
$LASTEXITCODE
```

The expected displayed line is Hello, learner. The immediately following completion result should be 0. $LASTEXITCODE is PowerShell’s record of the most recently completed native program; another native command replaces it.

## Linux: build and run only the greeting

Replace /path/to/your/Umicom-Bits2Banking with your actual checkout before running the first line.

```sh
cd /path/to/your/Umicom-Bits2Banking
cmake -S ./labs/native/first-c-programs -B ./build/first-c-programs -G Ninja -DCMAKE_C_COMPILER=cc -DBUILD_TESTING=ON
cmake --build ./build/first-c-programs --target btb-first-greeting
./build/first-c-programs/btb-first-greeting
echo $?
```

The expected displayed line is Hello, learner. The following echo reports the previous command’s result; 0 means success.

## Read the commands

1. Change to your checkout so relative paths have a known meaning.
2. Configure: -S selects source, -B selects a separate generated build folder and -G Ninja chooses the build tool. -D supplies CMake settings.
3. Build the named greeting target. This compiles and links it but does not run it.
4. Launch the executable. Its path is relative to the checkout used here.
5. Read the completion result immediately, before another native command changes it.

## Build and check all examples

After the single-target exercise works, build the remaining programs and run the registered checks. The expected selection contains nine tests: seven output checks, one count-contract test with thirteen input rows, and one borrowed-memory contract test.

Windows:

```powershell
cmake --build ".\build\first-c-programs" --parallel 2
ctest --test-dir ".\build\first-c-programs" --output-on-failure --no-tests=error
```

Linux:

```sh
cmake --build ./build/first-c-programs --parallel 2
ctest --test-dir ./build/first-c-programs --output-on-failure --no-tests=error
```

The expected result is nine executed passing tests with no skips. Record your actual result. The test runner does not build missing executables. --output-on-failure prints failed-test details; --no-tests=error rejects an empty selection.

## Make a small change

In a personal working copy, change only the greeting text. Save the file, rebuild btb-first-greeting and launch it. Predict the new line first. Its existing output check should fail until you deliberately update expected/greeting.txt to the intended wording. Do not change expected results just to conceal an unexplained failure.

The values, decisions, repetition and functions targets use the same btb-first- prefix. Their complete sources are paired with explanations in the [C from the Beginning course](../../../content/courses/c-from-the-beginning/index.html).

## Troubleshooting

### A command is not recognised

The shell cannot find the named tool. Check the prepared toolchain and its PATH setting; do not assume a source change can fix a missing compiler. Use the reading route while preparing tools.

### The source folder is not found

Confirm the checkout and working folder. -S points to the folder containing CMakeLists.txt, not directly to greeting.c. Change the documented path to your actual checkout.

### Configuration says C23 is unsupported

Use a compiler/CMake combination supporting the requested language standard. Keep the stated requirement visible; silently downgrading the setting would not qualify the C23 lab.

### Compilation reports an error

Read the first diagnostic and check punctuation, spelling and the preceding line. Compare the complete example, save the correction and rebuild the affected target.

### Linking reports BtbRemainingCount is undefined

Use the supplied functions target, which links the counts implementation. Including counts.h declares the function but does not compile counts.c.

### Launching cannot find the executable

Stop and check that its target built successfully. The paths here assume Ninja's single-configuration layout. A different generator can use a configuration subfolder.

### A test reports changed output

Compare the exact expected text, actual stdout, stderr and completion result. The check normalises Windows line endings only. An intentional greeting change requires an intentional reviewed expectation change.

### No tests were found

Confirm configuration enabled BUILD_TESTING and that --test-dir names this lab's build folder. An empty selection is not a successful check.

## Limits

These programs neither read arbitrary user input nor implement production financial or OS services. The small count rule is an educational contract. No privileged operation, network connection or account is required. Build output stays under build, separate from source. Compiler/test evidence and accessibility review remain separate from authoring this guide.

Sammy Hegab · Umicom Foundation · MIT. Original learning material.
