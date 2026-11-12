<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/conda-miniforge-for-developers/05-install-packages-with-clear-ownership.md

PURPOSE:
Provide the editable manuscript for install packages with clear ownership.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Install packages with clear ownership

Lesson 5 of 10. Suggested study time: 35 minutes. Command exercises are unexecuted teaching examples.

[Course contents](index.md) · [Browser lesson](../../../courses/conda-miniforge-for-developers/lessons/05-install-packages-with-clear-ownership.html)

## What you will learn
Distinguish Conda channels from Python package indexes and install into the intended environment. You should already be able to identify your interpreter. This lesson adds a small package to the disposable practice environment; it does not install an AI SDK.

## Inspect the sources and installed state

~~~powershell
conda activate umicom-env-lab
conda config --show channels channel_priority
conda list --show-channel-urls
python -m pip --version
~~~

Conda solves package requirements using configured channels. Mixing channels can change which binary builds are selected. For this course, use conda-forge explicitly for Conda packages rather than adding unrelated channels to repair a solve. Review a solve before applying it. Channel priority influences the available choices. [Conda channel guidance](https://docs.conda.io/projects/conda/en/stable/user-guide/tasks/manage-channels.html).

## A small worked installation

~~~powershell
conda install --name umicom-env-lab --override-channels --channel conda-forge packaging --dry-run
conda install --name umicom-env-lab --override-channels --channel conda-forge packaging
python -c "from packaging.version import Version; print(Version('1.10') > Version('1.9'))"
~~~

The comparison is expected to print True. Version objects compare numeric release components; comparing plain strings would answer a different question. If the import fails, first check the interpreter location. Do not immediately install the same package globally.

## When a project also requires pip
Prefer installing the required Conda packages first and use pip for the remaining reviewed Python requirements. Invoke pip through the chosen interpreter with python -m pip. Do not add --user inside this practice environment. After pip has changed an environment, plan substantial Conda changes in a replacement environment rather than assuming both managers have a complete shared view. [Conda's pip guidance](https://docs.conda.io/projects/conda/en/stable/user-guide/tasks/manage-environments.html#using-pip-in-an-environment).

A requirements file is input to a package manager, not a proof of compatibility. Read it before running python -m pip install -r requirements.txt. The file may include URLs, local paths or options. Keep project credentials out of shared examples. A custom index needs an identified project requirement; do not paste an old vendor index into every environment.

## Check the installed metadata

~~~powershell
python -m pip check
python -m pip list
~~~

Pip check examines declared dependency compatibility. A clean result does not test numerical correctness, DLL loading in every code path, GPU drivers or application behaviour. [Pip check reference](https://pip.pypa.io/en/stable/cli/pip_check/).

## Exercise and answer
A package installs successfully and pip check reports no broken requirements, but the application fails while loading a native library. Has the application passed?

**Answer:** no. Installation and dependency metadata are two checkpoints; the import or launch is another. Preserve the exact first loader error and investigate the required binary architecture and runtime libraries. Do not report an installation success as an application success.


[Course contents](index.md) · [Previous lesson](04-create-and-inspect-an-environment.md) · [Next lesson](06-plan-a-python-ai-project.md)
