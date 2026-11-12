<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/conda-miniforge-for-developers/03-connect-conda-to-powershell.md

PURPOSE:
Provide the editable manuscript for connect conda to powershell.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Connect Conda to PowerShell

Lesson 3 of 10. Suggested study time: 35 minutes. Command exercises are unexecuted teaching examples.

[Course contents](index.md) · [Browser lesson](../../../courses/conda-miniforge-for-developers/lessons/03-connect-conda-to-powershell.html)

## What you will learn
Explain command discovery and initialize the shell that you actually use. Complete the installation checks first: Conda must already run in Miniforge Prompt.

## Why an executable is not the whole story
PowerShell resolves a command name against commands it knows and executable search locations. Get-Command can show whether the name is a function, script or application. Activation must change the current shell's environment, so finding an executable alone is not equivalent to installing Conda's shell integration. [Get-Command reference](https://learn.microsoft.com/en-us/powershell/module/microsoft.powershell.core/get-command), [Conda init reference](https://docs.conda.io/projects/conda/en/stable/commands/init.html).

## Preview, initialize and reopen
Run these commands in **Miniforge Prompt**, where Conda already works:

~~~text
conda init --dry-run powershell
conda init powershell
conda config --set auto_activate false
~~~

Review the preview before the real initialization. The configuration command keeps base from automatically becoming your active working environment. It does not uninstall Conda. Current Miniforge guidance uses the auto_activate setting; if an older release rejects it, consult that installed release's help rather than repeatedly editing PATH. [Miniforge activation guidance](https://github.com/conda-forge/miniforge#automatic-activation-of-environments).

Close the existing PowerShell terminal and open a fresh one. Then inspect:

~~~powershell
$PSVersionTable.PSVersion
$PROFILE
Get-Command conda -All
conda --version
~~~

Initialization changes startup integration. An already-running shell may not have read that integration. A version result in the new shell is the first checkpoint; successful activation in lesson 4 is the next.

## If the prompt still cannot find Conda
Windows PowerShell, PowerShell 7 and an editor's integrated terminal can use different profile locations or startup options. A profile is a script loaded when a shell starts. Inspect the exact profile path and any startup error in the failing host. A terminal launched with NoProfile deliberately skips profile initialization. [PowerShell profiles](https://learn.microsoft.com/en-us/powershell/module/microsoft.powershell.core/about/about_profiles).

If script policy blocks the profile, inspect the policy before changing anything:

~~~powershell
Get-ExecutionPolicy -List
~~~

Follow your organisation's approved policy. Do not set a machine-wide unrestricted policy as a generic Conda repair. The working Miniforge Prompt remains an alternative while the profile problem is resolved. A permission failure is a different problem from an absent executable.

## Exercise and explained answer
Conda works in Miniforge Prompt but fails in a PowerShell window started with NoProfile. Is the installation necessarily broken?

**Answer:** no. That startup deliberately bypasses the initialization profile. Test a normal newly opened PowerShell window, then compare host, profile path and startup diagnostics. A visible environment name is helpful, but later checks should inspect the interpreter path too.

## Completion check
You can explain which shell was initialized, find its profile, and run Conda from a fresh terminal. Preserve custom profile contents; do not replace an entire profile with a copied initialization block from another computer.


[Course contents](index.md) · [Previous lesson](02-install-miniforge-and-verify.md) · [Next lesson](04-create-and-inspect-an-environment.md)
