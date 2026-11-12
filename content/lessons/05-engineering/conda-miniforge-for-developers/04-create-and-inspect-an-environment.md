<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/conda-miniforge-for-developers/04-create-and-inspect-an-environment.md

PURPOSE:
Provide the editable manuscript for create an environment and identify its interpreter.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Create an environment and identify its interpreter

Lesson 4 of 10. Suggested study time: 30 minutes. Command exercises are unexecuted teaching examples.

[Course contents](index.md) · [Browser lesson](../../../courses/conda-miniforge-for-developers/lessons/04-create-and-inspect-an-environment.html)

## What you will learn
Create a named environment and prove which Python interpreter runs. Complete lesson 3 first. Run each command separately and stop on errors. The name umicom-env-lab is reserved for this practice; choose another name if it already contains work you need.

## A name is not your source folder
Your source files stay in the project directory. Conda stores the interpreter and packages in its environment directory. Changing directory with Set-Location does not select a Python environment, and activating an environment does not move your source files.

Inspect existing environments, preview a creation plan, then create and activate the practice environment:

~~~powershell
conda env list
conda create --name umicom-env-lab --override-channels --channel conda-forge python=3.12 pip --dry-run
conda create --name umicom-env-lab --override-channels --channel conda-forge python=3.12 pip
conda activate umicom-env-lab
~~~

Python 3.12 is the teaching baseline for this exercise, not a promise that every AI SDK supports it. The channel options make the source explicit for this solve. The preview performs dependency resolution without installing its plan; it may still require network metadata. [Conda create reference](https://docs.conda.io/projects/conda/en/stable/commands/create.html).

## Inspect the running process

~~~powershell
$env:CONDA_DEFAULT_ENV
$env:CONDA_PREFIX
Get-Command python -All
python --version
python -c "import sys; print(sys.executable); print(sys.prefix)"
python -m pip --version
~~~

The two printed paths should identify the selected environment. Pip's location should agree. A different Python path is a reason to stop before installing anything. An alias, shell function, editor interpreter selection or earlier PATH entry can explain a mismatch. Activation is useful, but the interpreter's own report is stronger evidence than a prompt label.

The small Python command is a diagnostic expression: import sys loads Python's runtime information, then print displays the executable and environment prefix. It performs no model inference and opens no project data.

## Compare explicit execution

~~~powershell
conda deactivate
conda run --name umicom-env-lab python -c "import sys; print(sys.executable)"
~~~

Conda run selects an environment for that child command without requiring it to remain your interactive shell's active environment. It does not guarantee that every descendant program or external dependency is correctly configured. [Conda run reference](https://docs.conda.io/projects/conda/en/stable/commands/run.html).

## Worked example and exercise
A prompt says umicom-env-lab but python reports a global installation. Which result should guide the next step?

**Answer:** the executable path. Do not install packages until command resolution is understood. Compare Get-Command output and the explicit Conda run command. If the explicit command points to the intended environment, the environment exists; the interactive shell's resolution needs attention.

## Checkpoint
Record the environment name, prefix, Python version and pip path. Your evidence should let another reader distinguish a shell integration problem from a package problem. An environment successfully starting Python is not proof that an application can run.


[Course contents](index.md) · [Previous lesson](03-connect-conda-to-powershell.md) · [Next lesson](05-install-packages-with-clear-ownership.md)
