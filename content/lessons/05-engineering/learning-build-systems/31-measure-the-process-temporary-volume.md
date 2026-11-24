<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/31-measure-the-process-temporary-volume.md

PURPOSE:
Measure the process temporary volume

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Measure the process temporary volume

A build can write temporary working files in one folder and keep its results in another. A **volume** is the part of the storage system that holds those folders. In this lesson, you will choose which two folders to measure and decide what to do when they share one volume. You can complete the exercises on paper using the saved practice figures.

## 1. Choose the folders the build will use

Find the configured build folder in your project’s settings. It holds files such as objects, libraries and executables. A compiler may put some working files in a temporary folder, also called a **scratch folder**, and clear them as work finishes. Ask for the build’s actual scratch location if a launcher starts the compiler with its own temporary directory.

The two forms below show the command syntax. Replace `ABSOLUTE_DIRECTORY` with the full path to the existing folder for that option.

~~~text
Usage: umicom dev storage --temp ABSOLUTE_DIRECTORY --build ABSOLUTE_DIRECTORY
       umicom dev storage --process-temp --build ABSOLUTE_DIRECTORY
Optional: --min-temp-bytes UINT64 --min-build-bytes UINT64
~~~

- Use **`--process-temp`** when the directory that Umicom resolves for the running command is the one you need. This option takes no folder argument. The command uses the running process’s temporary-directory settings. Start it in the same environment and under the same account as the build when you want that comparison.
- Use **`--temp`** with the full scratch-folder path when Studio IDE, a build launcher or a compiler configuration supplies a different location.
- Supply **`--build`** with the actual configured build folder in either form. Choose one temporary option. Giving both, repeating one, or leaving out the build folder produces a usage error.

For example, when the build folder is `build` inside the project folder, these are the PowerShell steps for a future preflight, a check you do before building. For paper practice, read the commands and continue with the saved readings below.

~~~powershell
$buildFolder = (Resolve-Path -LiteralPath '.\build' -ErrorAction Stop).ProviderPath
umicom dev storage --process-temp --build $buildFolder
$LASTEXITCODE
~~~

If your launcher supplies the scratch folder, use this second form with the build folder from the first step. Type its full path when asked. A full Windows path looks like `D:\BuildScratch`.

~~~powershell
$scratchFolder = Read-Host 'Enter the full path to the existing build scratch folder'
umicom dev storage --temp $scratchFolder --build $buildFolder
$LASTEXITCODE
~~~

## 2. Read bytes and compare with the plan

The saved demonstration used tiny made-up amounts. **Caller-available bytes** is the space the system reports as available to the current account when the tool checks. A quota, which limits what an account can store, can lower that number. Here the configured build folder had 150 bytes available and the scratch folder had 70.

~~~text
Temporary caller-available bytes: 70
Build caller-available bytes: 150
~~~

With neither minimum given, exit status 0 means the tool read both locations. To check a requirement from your build plan, add `--min-temp-bytes`, `--min-build-bytes` or both to either command form. Give plain decimal bytes, such as `4096`. A value written as `4 KB` or `4,096` will not be accepted. Leaving a minimum out keeps that location in observation mode.

The practice plan asks for 70 temporary bytes and 150 build bytes. Equality meets the minimum. The saved check returned status 0.

~~~text
Temporary caller-available bytes: 70
Temporary minimum bytes: 70 (met)
Build caller-available bytes: 150
Build minimum bytes: 150 (met)
~~~

On paper, raise the temporary requirement by one byte and leave the build minimum out. Now compare your prediction with the saved report. Both locations were readable and one was below its minimum, so the command returned status 3.

~~~text
Temporary caller-available bytes: 70
Temporary minimum bytes: 71 (insufficient)
Build caller-available bytes: 150
~~~

After either PowerShell command, `$LASTEXITCODE` shows how it finished.

| Status | Meaning |
| --- | --- |
| 0 | Both locations were measured and every supplied minimum was met. |
| 1 | The command could not read a location or could not write its report. |
| 2 | The arguments were incomplete or invalid. No measurement ran. |
| 3 | Both locations were measured and at least one was below its supplied minimum. |

Read both the diagnostic and the available rows if status is 1. The tool still tries the build volume if the temporary directory cannot be resolved. A read or reporting failure takes priority over a known shortfall in the other row. Check the folder choice and permissions, then repeat the observation before drawing a conclusion.

## 3. Work out whether the amounts share a volume

Imagine a different build with 90 bytes available on one shared volume. One row describes the scratch folder on that volume and the other row describes the build folder on the same volume. The two readings describe the same space, so count the 90 bytes once.

The plan needs 60 temporary bytes and 50 build bytes at the same time. Each separate requirement is below 90. Together they require 110 bytes, which leaves a 20-byte shortfall. If each folder instead has its own independent 90-byte volume, each fits. If the temporary files are released before the build output is written, the highest amount held at any one time is 60 bytes. That fits on the shared volume in this exercise.

Use this pseudocode with the made-up figures. A **peak** is the highest amount you expect to need at one time.

~~~text
IF the folders are known to share a volume
    SET peak TO the largest combined usage at one time
    CHECK that the shared available bytes are at least peak
ELSE IF the folders are known to be on separate volumes
    CHECK each available byte count against its own requirement
ELSE
    CHECK where the paths lead before deciding
~~~

Two equal readings can come from different volumes. Use the folder destinations from your system or build configuration to make that distinction. Keep those destinations beside the results in your Umicom Studio IDE build notes. A measurement leaves the available space unchanged. Other work can use that space between your measurement and the build.

[Course contents](index.md) · [Previous lesson · Match a dry plan to its recipe digest](30-match-a-dry-plan-to-its-recipe-digest.md) · [Related lesson · Check available storage before building](27-check-available-storage-before-building.md) · [HTML edition](../../../courses/learning-build-systems/lessons/31-measure-the-process-temporary-volume.html)

[Next lesson · Read child and fixture deadlines](32-read-child-and-fixture-deadlines.md)
