<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/developing-with-umicom-c/index.md

PURPOSE:
Introduce the Umicom C brew-time developer workshop.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Develop with Umicom C

![Umicom Foundation](../../../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../../../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }
<a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="28"></a>

Use one practice recipe to learn how to check source, run it, save a compiled program and test its behaviour. The recipe starts with four minutes of brewing and adds 15 seconds for pouring. A simple check gives 255 seconds.

## Set up once

1. Work through [the Windows C setup steps](../../../simple-steps/toolchain.md). You will use PowerShell, CMake, Ninja and a C23-capable compiler such as the MSYS2 UCRT64 GCC used there.
2. In PowerShell, point the folder variables at your local checkouts. Run the configure and build separately. Stop if a command reports an error.

   ~~~powershell
   $UcSource = 'C:\umicom\umicom-c'
   $Bits = 'C:\umicom\Umicom-Bits2Banking'
   $env:Path = "C:\msys64\ucrt64\bin;$env:Path"
   $UcBuild = Join-Path $UcSource 'build\windows-ucrt64-debug'
   cmake -S $UcSource -B $UcBuild -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe
   cmake --build $UcBuild --target umicom-c --parallel 2
   ~~~

3. Run these lines in the same window. They identify the tool, its linked capabilities and the folder that holds the exercises. Each new practice folder keeps earlier output available for comparison.

   ~~~powershell
   $Uc = Join-Path $UcBuild 'bin\umicom-c.exe'
   $Lab = Join-Path $Bits 'content\labs\native\umicom-c-brew-time'
   $Practice = Join-Path $env:TEMP ('uc-brew-' + [guid]::NewGuid().ToString('N'))
   New-Item -ItemType Directory -Path $Practice
   & $Uc --version
   & $Uc profile
   Test-Path (Join-Path $Lab 'brew-time.uc')
   ~~~

4. Check for a version, a profile report and a final True. If you get False, check the Bits2Banking path or download the linked exercise files and point the lab variable at their folder. If you reopen PowerShell, reset the folder variables before continuing.

## Follow the steps

1. [Check and run the recipe](01-check-and-run.md)
2. [Save and compare bytecode](02-save-and-compare.md)
3. [Bind one input and plan the budget](03-bind-one-input.md)
4. [Trace, pause and diagnose](04-trace-and-diagnose.md)
5. [Try an edit before accepting it](05-preview-and-commit.md)
6. [Classify two language regions](06-classify-source.md)
7. [Inspect and link native x64 output](07-link-a-constant.md)
8. [Call the compiler and runtime from C23](08-embed-and-test.md)
9. [Display a number and a Boolean](09-print-and-return.md)
10. [Inspect objects before collecting them](10-inspect-objects.md)

The workshop uses the bounded Umicom C profiles in the linked tool. Continue into the [checked integer keyword reference](../umicom-c-keyword-reference/index.md) for language details or [the compiler construction course](../../05-engineering/building-a-compiler-in-c/index.md) to read the implementation.
