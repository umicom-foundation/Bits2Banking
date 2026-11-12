<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/conda-miniforge-for-developers/index.md

PURPOSE:
Provide the written contents and study route for Conda and Miniforge.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Conda and Miniforge for Umicom Developers

## A practical introduction
Learn to install Miniforge, use Conda from PowerShell, inspect interpreter identity, manage packages and reproduce a small environment. Keep optional Python and AI experiments separate from Umicom's native C23 and Assembly toolchains.

## Before you begin
You should be able to find a folder, save a text file and open a terminal. Start with [Introduction to Computers](../../../courses/learning-computer-architecture/index.html) if those tasks are new. You do not need to understand model training or write Python programs. Allow about six hours for reading and exercises, plus downloads.

Reading is available without an account or installation. Hands-on work requires a supported Windows installation, PowerShell, internet access and permission to install software. Use disposable named environments and a practice directory. The examples use Python 3.12, with 3.11 only for the capstone comparison. These versions are teaching choices, not compatibility claims for a vendor SDK.

## How to study
Read each explanation, predict the result, run one command at a time when ready, and record the actual result. Stop on errors. Expected output in a lesson is not executed evidence. Do not paste an entire lesson into a terminal: some sections are alternatives, previews or diagnostics.

## Lessons
1. [Choose an environment tool for the job](01-choose-an-environment-tool.md) — about 25 minutes.
2. [Install Miniforge and verify completion](02-install-miniforge-and-verify.md) — about 30 minutes.
3. [Connect Conda to PowerShell](03-connect-conda-to-powershell.md) — about 35 minutes.
4. [Create an environment and identify its interpreter](04-create-and-inspect-an-environment.md) — about 30 minutes.
5. [Install packages with clear ownership](05-install-packages-with-clear-ownership.md) — about 35 minutes.
6. [Plan an environment for a Python AI project](06-plan-a-python-ai-project.md) — about 35 minutes.
7. [Keep native C and Assembly builds separate](07-keep-native-builds-separate.md) — about 30 minutes.
8. [Describe and recreate an environment](08-describe-and-recreate-environments.md) — about 40 minutes.
9. [Troubleshoot one layer at a time](09-troubleshoot-one-layer-at-a-time.md) — about 35 minutes.
10. [Capstone: prove isolation and document a recreation](10-capstone-and-knowledge-check.md) — about 50 minutes.

## Practice resources
- [Command reference and glossary](../../../courses/conda-miniforge-for-developers/command-reference.html): choose commands by purpose and understand what each result proves.
- [Environment specification](../../../courses/conda-miniforge-for-developers/practice/environment.yml): a small Python and packaging environment, with no AI SDK or model download.
- [Evidence worksheet](../../../courses/conda-miniforge-for-developers/practice/evidence-worksheet.md): record interpreter paths, package versions and actual observations.

## What completion means
You can explain environment boundaries, diagnose a missing command, prove interpreter selection, recreate the practice environment and return to the supported native toolchain. The ten lessons form this introductory course. Installation, browser rendering and the practical exercises still require qualification on the learner's computer. This course does not certify a model SDK, GPU stack or production application, and is not a native Studio content-pack release.

## Continue
Study [Learning Build Systems](../../../courses/learning-build-systems/index.html) for native build evidence, [Learning CMake](../../../courses/learning-cmake/index.html) for target configuration, or [Building an LLM from Scratch](../../../courses/llm-from-scratch/index.html) for native model implementation. Optional Python tooling does not replace those routes.

## Sources
Command descriptions link to official Conda, Miniforge, Python, pip and Microsoft documentation in the relevant lessons. Consult the help for your installed release when an option differs. The explanations, scenarios, exercises and answers are original Umicom learning material.

