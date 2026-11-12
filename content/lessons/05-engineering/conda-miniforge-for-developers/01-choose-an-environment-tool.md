<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/conda-miniforge-for-developers/01-choose-an-environment-tool.md

PURPOSE:
Provide the editable manuscript for choose an environment tool for the job.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Choose an environment tool for the job

Lesson 1 of 10. Suggested study time: 25 minutes. Command exercises are unexecuted teaching examples.

[Course contents](index.md) · [Browser lesson](../../../courses/conda-miniforge-for-developers/lessons/01-choose-an-environment-tool.html)

## What you will learn
Choose between a native toolchain, Python's venv and Conda. You need to know how to open a terminal and find a saved file; no Python programming is required. If folders and commands are unfamiliar, begin with [Introduction to Computers](../../../courses/learning-computer-architecture/index.html).

## Three different jobs
A compiler turns source code into an executable. A package manager installs software and its dependencies. An environment is a named collection of tools and packages that a process can use. These jobs overlap, but they are not interchangeable. Installing Conda does not compile Umicom Framework or supply a bootable kernel.

Conda manages environments and packages. Miniforge supplies Conda and Mamba with conda-forge as its default package channel. A channel is a package source. Mamba is an alternative command-line client; the exercises use Conda consistently. [Miniforge documentation](https://github.com/conda-forge/miniforge).

Python's venv creates an isolated package environment using an interpreter you already installed. It is often enough for a small Python utility. It does not independently select and download a different Python version. [Python venv documentation](https://docs.python.org/3/library/venv.html).

| Work you want to do | Starting choice | Reason |
| --- | --- | --- |
| Build a C23 Framework application on Windows | The project's MSYS2 UCRT64, CMake and Ninja workflow | Keep the compiler and libraries compatible with its supported preset. |
| Study kernel entry code | The kernel's documented cross compiler and emulator | A Python environment cannot replace the target architecture's toolchain. |
| Run a small Python script with a few packages | An existing Python installation plus venv | There may be no need for another package manager. |
| Compare Python AI tools requiring different interpreter versions | Separate Conda environments | Each experiment can have its own dependency set. |

## Worked decision
Maya has a native C editor and a separate Python document-analysis experiment. The editor already builds with UCRT64. The experiment requests Python 3.12. She leaves the editor's build instructions alone and creates one Python environment for the experiment. She does not install a second GCC into that environment merely because GCC is available as a package.

Umicom keeps reusable product behaviour in native Framework services. The Python commands in this course inspect Python itself and exercise an external environment manager. They do not replace native product services or establish that a Python AI package is Umicom's own model.

## Exercise and explained answer
A colleague proposes putting every project's packages into Conda's base environment. What goes wrong when one experiment needs a dependency version that another rejects?

**Answer:** both experiments would share one changing dependency set. Separate named environments make the conflict visible and avoid changing an unrelated experiment. Keep base primarily for managing environments. Isolation improves dependency control; it is not a security sandbox and does not restrict a program's file or network access.

## Your decision record
Write three sentences: the project you are studying, the toolchain it already supports, and why an extra environment is or is not needed. A defensible answer can be “keep the existing native workflow.” Continue to installation only if Conda serves your chosen exercise.


[Course contents](index.md) · [Next lesson](02-install-miniforge-and-verify.md)
