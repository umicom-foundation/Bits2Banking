<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/conda-miniforge-for-developers/02-install-miniforge-and-verify.md

PURPOSE:
Provide the editable manuscript for install miniforge and verify completion.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Install Miniforge and verify completion

Lesson 2 of 10. Suggested study time: 30 minutes. Command exercises are unexecuted teaching examples.

[Course contents](index.md) · [Browser lesson](../../../courses/conda-miniforge-for-developers/lessons/02-install-miniforge-and-verify.html)

## What you will learn
Distinguish a downloaded installer from a completed installation. This optional practical lesson requires a supported Windows computer, internet access and permission to install software. If Miniforge already works, inspect it and skip installation.

## Inspect before changing anything
Run these commands separately in PowerShell:

~~~powershell
Get-Command conda -All -ErrorAction SilentlyContinue
winget list --id CondaForge.Miniforge3 --exact
~~~

No Get-Command result means this shell cannot resolve Conda. It does not prove that no installation exists anywhere. Likewise, a missing folder at one guessed location proves only that location is absent. Search Start for Miniforge Prompt and check your installation record before installing another copy.

## Install one distribution
If you have decided to install, inspect the package and then request that exact package:

~~~powershell
winget show --id CondaForge.Miniforge3 --exact
winget install --id CondaForge.Miniforge3 --exact
~~~

Review the displayed publisher, installer and prompts. Wait for the command to finish. Stop on an error; a PowerShell terminal does not automatically prevent you from running the next pasted line after a native program fails. The exact package ID avoids selecting another similarly named distribution. [Microsoft's Winget install reference](https://learn.microsoft.com/en-us/windows/package-manager/winget/install).

If Winget is unavailable or has no matching package, use the Windows installer linked by the [official Miniforge project](https://github.com/conda-forge/miniforge#install). Choose the architecture matching your machine. Record the installation directory and retain the Start menu shortcut. Do not add every Miniforge subdirectory to the global PATH to make a missing command disappear.

## Verify in the supplied prompt
After installation succeeds, open a **new Miniforge Prompt** from Start:

~~~text
conda --version
conda info --base
conda env list
~~~

The first command should report a version; the second identifies the actual installation prefix. The environment list should include base. These checks establish that the command runs in that prompt. They do not yet establish PowerShell activation, package compatibility or GPU support. The Miniforge prompt is the documented Windows starting point; ordinary terminals can require initialization.

## Worked evidence trace
A terminal shows a 151 MB download with 39 MB received. There is no success message. The correct conclusion is “download in progress.” Later, an installer success message appears and a new Miniforge Prompt reports a Conda version. Now you have stronger evidence: installation finished and the command is usable there. Keep those observations separate.

## Exercise and explained answer
The package appears in Winget's list, but an old PowerShell window still says the command is unknown. Should you reinstall immediately?

**Answer:** no. Open the supplied prompt first. If Conda works there, investigate shell initialization in the next lesson. If the supplied prompt also fails, preserve the installer error and actual installation path before deciding whether repair is needed.

## Record the result
Write down the distribution, installed version, installation prefix, shell used and actual command result. Do not copy somebody else's expected output into your record. Reading this page does not perform an installation.


[Course contents](index.md) · [Previous lesson](01-choose-an-environment-tool.md) · [Next lesson](03-connect-conda-to-powershell.md)
