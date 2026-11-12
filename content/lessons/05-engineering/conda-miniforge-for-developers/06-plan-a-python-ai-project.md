<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/conda-miniforge-for-developers/06-plan-a-python-ai-project.md

PURPOSE:
Provide the editable manuscript for plan an environment for a python ai project.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Plan an environment for a Python AI project

Lesson 6 of 10. Suggested study time: 35 minutes. Command exercises are unexecuted teaching examples.

[Course contents](index.md) · [Browser lesson](../../../courses/conda-miniforge-for-developers/lessons/06-plan-a-python-ai-project.html)

## What you will learn
Turn a project's setup instructions into a compatibility checklist before installing an SDK. You need the project's README, dependency file and version-control revision. Model downloads and GPU configuration are outside this course's practice lab.

## Start from the application's contract
Consider an illustrative model-router project whose README requests Python 3.12, a native inference SDK and a browser interface. Its requirements file lists an SDK package without a version. That is insufficient evidence that the newest package still exposes the API the source imports.

Before running an installation command, record:

1. The application revision and the SDK imports used by that revision.
2. The Python versions supported by the matching SDK release.
3. Windows architecture and the selected CPU or GPU backend.
4. The package source, package version and any required runtime libraries.
5. A small, documented import check and an application-specific smoke check.

This is an engineering compatibility decision. Conda can isolate the chosen interpreter, but it cannot make removed SDK functions reappear. A Mac Metal installation command cannot be treated as a Windows CUDA command.

## Review a checkout without launching it
In your chosen project directory, inspect:

~~~powershell
git rev-parse HEAD
Get-Content -LiteralPath .\README.md
Get-Content -LiteralPath .\requirements.txt
Get-ChildItem -LiteralPath . -File
~~~

These commands are observations. A missing requirements file may mean the project uses another dependency format; inspect the actual tree. Do not manufacture a file just to make a copied command work.

Use a separate environment name, such as umicom-ai-study, when you have selected a documented Python version. If the reviewed version is 3.12, the environment creation example is:

~~~powershell
conda create --name umicom-ai-study --override-channels --channel conda-forge python=3.12 pip
conda activate umicom-ai-study
python -c "import sys; print(sys.executable)"
~~~

Only then follow the matching SDK's installation guide. This course deliberately does not supply an unversioned universal Nexa, CUDA or other vendor installation command. An actual SDK recipe needs release-specific evidence.

## Separate the checkpoints
Use a record with separate rows for environment creation, dependency installation, import, model loading and one application request. Mark a row not run until you execute it. A model file also has an identity: name, version, checksum where supplied, and licence. A working Python import says nothing about which model weights were loaded.

A localhost browser address means the interface is local. It does not prove that model retrieval, telemetry or a configured provider stays offline. Check the application's own network settings and documentation before using sensitive input.

## Exercise and explained answer
A README is two years old and requests an unpinned SDK package. The current package installs but lacks an imported class. Is changing Python versions at random a good first fix?

**Answer:** no. Match application revision to the SDK API and supported interpreter range first. Preserve the exact missing import. Either select an evidenced compatible dependency release or review a deliberate source migration. A new environment makes that experiment repeatable; it does not choose the correct migration for you.

## Continue learning
For native model implementation rather than external SDK setup, follow [Building an LLM from Scratch](../../../courses/llm-from-scratch/index.html). Keep experiments and native Umicom model development distinct in your results.


[Course contents](index.md) · [Previous lesson](05-install-packages-with-clear-ownership.md) · [Next lesson](07-keep-native-builds-separate.md)
