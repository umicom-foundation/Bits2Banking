<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/conda-miniforge-for-developers/07-keep-native-builds-separate.md

PURPOSE:
Provide the editable manuscript for keep native c and assembly builds separate.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Keep native C and Assembly builds separate

Lesson 7 of 10. Suggested study time: 30 minutes. Command exercises are unexecuted teaching examples.

[Course contents](index.md) · [Browser lesson](../../../courses/conda-miniforge-for-developers/lessons/07-keep-native-builds-separate.html)

## What you will learn
Recognise when environment activation changes the tools selected by a native build. Read lesson 4 first. This lesson inspects tools; it does not ask you to configure, compile or launch a product.

## The same command name can select another file
A terminal process carries environment variables, including PATH. Programs started from it inherit that environment. An activated Python environment can change executable search order and available libraries. A command named cmake may therefore resolve differently in two terminals.

Umicom's Windows native workflow uses the repository's documented MSYS2 UCRT64 toolchain. Keep that compiler, its headers and its runtime libraries together. Conda is optional supporting infrastructure for Python experiments, not a required dependency of native Framework, Studio, OS or kernel builds.

## Make a read-only tool inventory
Open a fresh ordinary PowerShell window without an activated Conda environment. Inspect:

~~~powershell
$env:CONDA_PREFIX
Get-Command cmake,ninja,gcc,python -All -ErrorAction SilentlyContinue
where.exe cmake
where.exe gcc
~~~

A missing command is an observation, not a reason to install the first available similarly named package. Compare the returned paths with your repository's setup guide. Get-Command can reveal aliases or functions as well as executable files; where.exe focuses on executable search. [PowerShell command discovery](https://learn.microsoft.com/en-us/powershell/module/microsoft.powershell.core/get-command).

If the documented tools are installed at the following locations, explicit paths avoid ambiguity for these version checks:

~~~powershell
& 'C:\msys64\ucrt64\bin\cmake.exe' --version
& 'C:\msys64\ucrt64\bin\gcc.exe' --version
& 'C:\msys64\ucrt64\bin\ninja.exe' --version
~~~

These are examples of the usual installation location, not a claim that those files exist on every machine. A version check does not establish that all DLL dependencies or build settings are correct.

## Worked diagnosis
A project configured yesterday with UCRT64 is opened today from an AI terminal. The shell finds another CMake and Python. The existing CMake cache still records yesterday's compiler. Activating or deactivating an environment does not rewrite that cache. Inspect both the shell selection and the recorded build configuration before deciding whether a separate build directory is needed. Do not copy a cache between checkouts or delete the old directory as a first diagnostic step.

After your environment experiment, use conda deactivate and inspect CONDA_PREFIX again. If environments were stacked, one deactivation may reveal another active environment. A terminal inherited from an already activated parent can retain that environment; verify the values instead of trusting the word “new.”

## Exercise and answer
CMake's version is identical in two terminals, but its full executable path differs. Is that enough evidence to treat their results as interchangeable?

**Answer:** no. Record the actual binary, compiler, library paths and build configuration. Equal version strings do not prove equal dependencies or environment state. Preserve evidence before changing toolchain selection.

Continue with [Learning Build Systems](../../../courses/learning-build-systems/index.html) and [Learning CMake](../../../courses/learning-cmake/index.html) for compilation exercises. Keep those qualification steps separate from the environment checks in this course.


[Course contents](index.md) · [Previous lesson](06-plan-a-python-ai-project.md) · [Next lesson](08-describe-and-recreate-environments.md)
