<!--
Umicom Bits2Banking
File: content/wiki/studio-build.md

PURPOSE:
Teach contributors to distinguish Studio command usage from a project build result.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Check a Studio build command

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

Use this guide when you have already built `umicom-studio-build.exe`. You will read its instructions, reproduce a missing-argument message and inspect the chosen project. Use a practice project for the final step.

## 1. Find the executable

In File Explorer, locate `umicom-studio-build.exe` in your build output. Open PowerShell and replace the example path with your actual path.

```powershell
$StudioBuild = 'C:\path\to\umicom-studio-build.exe'
Get-Item -LiteralPath $StudioBuild
```

Expect PowerShell to show the named executable. If it says the path cannot be found, check your build output directory before going further.

## 2. Read the accepted arguments

```powershell
& $StudioBuild --help
$LASTEXITCODE
```

An *argument* is a word you supply after the program name. Here the only argument is `--help`. Studio prints the accepted forms and PowerShell shows exit status `0`. Read `$LASTEXITCODE` immediately after the executable so that it still describes this run.

## 3. Reproduce a missing argument

```powershell
& $StudioBuild --phase
$LASTEXITCODE
```

`--phase` needs a phase name, such as `build` or `test`. Expect a usage message and exit status `2`. The command refuses this request before opening workspace services. Keep the first message and the exact command together when asking a contributor for help.

## 4. Inspect a practice project

Use the same PowerShell window. Replace the example with a project folder you already use with Studio. Run the following commands one at a time.

```powershell
Set-Location -LiteralPath 'C:\path\to\practice-project'
& $StudioBuild
$LASTEXITCODE
& $StudioBuild --graph
$LASTEXITCODE
```

The summary starts with `Build profile:` when the workspace opens successfully. The graph starts with `Build graph:` and lists planned steps. If either command reports a workspace or toolchain problem, stop there and read that output. A planned step becomes evidence of a successful build only after it executes successfully.

[Practise building and testing with CMake](../simple-steps/course-guides/learning-cmake.md) · [Contributor wiki](index.md)
