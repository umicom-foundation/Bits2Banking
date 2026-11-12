<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/conda-miniforge-for-developers/command-reference.md

PURPOSE:
Provide the written command reference for the environment course.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Conda command reference and glossary

[Course contents](index.md)

## Use this reference after the lessons
These are individual interactive commands, not an automation script. Select the operation you intend, review its effect, then run it. Stop after an error. Names beginning umicom-env are disposable examples; inspect existing environments before reusing a name.

| Purpose | Command | What it establishes |
| --- | --- | --- |
| Find the shell command | Get-Command conda -All | How the current PowerShell session resolves Conda. |
| Identify the installation | conda info --base | The installation prefix used by this Conda. |
| List environments | conda env list | Known names and prefixes, not their application health. |
| Preview shell integration | conda init --dry-run powershell | Proposed startup integration changes. |
| Initialize PowerShell | conda init powershell | Requests shell integration; reopen the terminal afterwards. |
| Keep base inactive at startup | conda config --set auto_activate false | Changes Conda's automatic activation preference. |
| Activate the practice environment | conda activate umicom-env-lab | Selects its environment in the current shell. |
| Leave the active environment | conda deactivate | Returns to the previous activation level. |
| Identify running Python | python -c "import sys; print(sys.executable)" | The actual interpreter running that expression. |
| Identify pip | python -m pip --version | Pip resolved through that interpreter. |
| Inspect packages and sources | conda list --show-channel-urls | Conda's installed package inventory. |
| Check Python dependency metadata | python -m pip check | Compatibility of declared Python requirements. |
| Run in a selected environment | conda run --name umicom-env-lab python --version | Starts that child command with the selected environment. |

## Commands that create or install
Read the plan and expected effects before using these examples. The first command is a preview; the second applies a creation request. Package versions and download sizes depend on the solve.

~~~powershell
conda create --name umicom-env-lab --override-channels --channel conda-forge python=3.12 pip --dry-run
conda create --name umicom-env-lab --override-channels --channel conda-forge python=3.12 pip
~~~

Environment files are explained in [lesson 8](../../../courses/conda-miniforge-for-developers/lessons/08-describe-and-recreate-environments.html). Do not replace a project's dependency file with a broad environment export without reviewing package ownership and reproducibility needs.

## Small glossary
- **Base:** the environment containing the Conda management installation.
- **Environment prefix:** the filesystem directory containing an environment's interpreter and packages.
- **Activation:** shell state changes that select an environment's commands and related settings.
- **PATH:** search locations used to find executable commands; shell functions and aliases can also affect resolution.
- **Channel:** a Conda package source. A pip index is a separate Python packaging source.
- **Solver:** the component that chooses package versions and builds satisfying the request.
- **Dependency:** software another package requires.
- **Binary compatibility:** agreement about platform, architecture and runtime contracts needed by compiled code.
- **Specification:** a description of requested dependencies; broad constraints may allow several solutions.
- **Resolved inventory:** a record of selected packages from a particular environment.
- **Qualification:** executing a stated check against an identified source and environment, then examining the result.

## What to do when a command fails
Use [lesson 9's decision table](../../../courses/conda-miniforge-for-developers/lessons/09-troubleshoot-one-layer-at-a-time.html). Record the first failure and the selected interpreter before changing versions. The final [capstone](../../../courses/conda-miniforge-for-developers/lessons/10-capstone-and-knowledge-check.html) demonstrates how to keep an honest result record.

## Official references
- [Miniforge installation and activation](https://github.com/conda-forge/miniforge)
- [Conda initialization](https://docs.conda.io/projects/conda/en/stable/commands/init.html)
- [Conda environment creation](https://docs.conda.io/projects/conda/en/stable/commands/create.html)
- [Conda explicit execution](https://docs.conda.io/projects/conda/en/stable/commands/run.html)
- [Conda exports](https://docs.conda.io/projects/conda/en/stable/commands/export.html)
- [Python venv](https://docs.python.org/3/library/venv.html)
- [Pip dependency check](https://pip.pypa.io/en/stable/cli/pip_check/)

These references document the external tools. None establishes that a particular Umicom product, vendor model SDK or GPU backend has passed its own checks.

