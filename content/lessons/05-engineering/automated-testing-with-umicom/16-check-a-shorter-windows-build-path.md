<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/automated-testing-with-umicom/16-check-a-shorter-windows-build-path.md

PURPOSE:
Check a shorter Windows build path

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Check a shorter Windows build path

[Previous lesson](15-group-console-checks-by-what-they-submit.md) · [Course index](index.md) · [Next lesson · Check available build and temporary space](17-check-available-build-and-temporary-space.md) · [HTML edition](../../../courses/automated-testing-with-umicom/lessons/16-check-a-shorter-windows-build-path.html)

A C compiler produces an **object file** from a piece of source code. The linker combines such files into a library or program. CMake chooses the directories for these files when it generates the build plan. A long build directory leaves fewer characters for the rest of a generated object path.

## Work it out on paper

1. Imagine the directory prefix takes 180 characters and the remaining part of the object path takes 80. The result is 260 characters.
2. The toolchain in this exercise reports an object-path budget of 250 characters. Replace the prefix with a 40-character build directory. The same object path now takes 120 characters.
3. Write down which setting you changed. Keeping the source revision and toolchain fixed makes the two logs easier to compare.

## Read the actual warning

In a recorded Umicom Framework configuration, a deep directory produced 295 messages mentioning `CMAKE_OBJECT_PATH_MAX`. Every message showed an object file directory and the applicable budget. A later configuration using a short path reported zero of those messages and listed both Web Workbench test names. The later checkout included other reviewed changes, so the records describe two observed runs. For a controlled experiment, configure the same revision twice.

## Configure in a short directory

1. Start PowerShell on a Windows machine that already has the Framework checkout and UCRT64 tools. Use an existing parent directory where you can create a fresh folder. Replace the two example paths for your machine.

   ```powershell
   $Framework = 'C:/umicom/Umicom-Applications/framework'
   $Build = 'C:/umicom/_local/fw-path-check'
   $Log = "$Build-configure.log"
   if ((Test-Path -LiteralPath $Build) -or (Test-Path -LiteralPath $Log)) { throw 'Choose a fresh build folder and log name.' }
   cmake --preset windows-ucrt64-debug -S $Framework -B $Build -DUMICOM_BUILD_GTK4_ADAPTER=OFF *> $Log
   $ConfigureExit = $LASTEXITCODE
   if ($ConfigureExit -ne 0) { throw "Read the configure log at $Log." }
   Select-String -LiteralPath $Log -Pattern 'CMAKE_OBJECT_PATH_MAX'
   ```

2. Expect the log to report both configuration and generation. Each selected warning line will appear under the final command. If the command prints nothing, read the saved log and confirm it contains the successful generation message.

3. List the selected tests. The small example below asks CTest to show the registered cases without executing them.

   ```powershell
   ctest --test-dir $Build -N -R '^framework\.web_api_workbench\.(response|stream)$'
   if ($LASTEXITCODE -ne 0) { throw 'Read the test listing and verify the build path.' }
   ```

   Write down the names you see. A listing describes the planned checks. A test outcome comes from a separate execution and result report.

## If the warning is still present

Read the full path in the warning and compare it to your new directory. Check that CMake used the directory passed to `-B`. Preserve both logs. Compare other messages separately so you can tell whether an optional dependency or a different setting also needs attention.
