<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/conda-miniforge-for-developers/10-capstone-and-knowledge-check.md

PURPOSE:
Provide the editable manuscript for capstone: prove isolation and document a recreation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Capstone: prove isolation and document a recreation

Lesson 10 of 10. Suggested study time: 50 minutes. Command exercises are unexecuted teaching examples.

[Course contents](index.md) · [Browser lesson](../../../courses/conda-miniforge-for-developers/lessons/10-capstone-and-knowledge-check.html)

## Your objective
Create two disposable environments, compare their interpreters, recreate one from a supplied specification and return to an unactivated native-development shell. This is a hands-on assessment, not evidence that Umicom applications or an AI SDK passed qualification. Read the earlier lessons before executing these steps.

## Preparation
Use a writable practice folder outside a product checkout. Save the supplied [environment.yml](../../../courses/conda-miniforge-for-developers/practice/environment.yml) and [evidence worksheet](../../../courses/conda-miniforge-for-developers/practice/evidence-worksheet.md) there. Inspect existing environments first; the names below must not already contain work you need.

~~~powershell
conda env list
conda env create --name umicom-env-capstone --file .\environment.yml
conda create --name umicom-env-alternate --override-channels --channel conda-forge python=3.11 pip
~~~

The first environment requests Python 3.12; the second requests 3.11. Stop after a failed command. These commands download packages, but they do not require a model, GPU or account with an AI provider.

## Observe without guessing

~~~powershell
conda run --name umicom-env-capstone python -c "import sys; print(sys.version_info[:2]); print(sys.executable)"
conda run --name umicom-env-alternate python -c "import sys; print(sys.version_info[:2]); print(sys.executable)"
conda run --name umicom-env-capstone python -c "from packaging.version import Version; print(Version('1.10') > Version('1.9'))"
conda run --name umicom-env-capstone python -m pip check
~~~

Expected observations are (3, 12), (3, 11), different interpreter paths and True for the version comparison. Pip check should either report compatible metadata or explain a dependency problem. Record what you actually see. Do not treat these expectations as a prefilled pass report.

## Recreate under another name

~~~powershell
conda env create --name umicom-env-capstone-copy --file .\environment.yml
conda run --name umicom-env-capstone-copy python -c "from packaging.version import Version; print(Version('1.10') > Version('1.9'))"
conda list --name umicom-env-capstone
conda list --name umicom-env-capstone-copy
~~~

Compare requested versions and resolved package versions. Explain differences instead of hiding them. The two prefixes should differ because these are separate environments. The same functional example can pass even when unpinned compatible package builds differ.

## Return to native work
If you activated an environment interactively, deactivate it and inspect CONDA_PREFIX. Open an ordinary PowerShell session and perform the read-only tool inventory from lesson 7. Verify the supported native compiler paths before following your native project's build guide. This assessment does not run a Framework configure, build or test.

## Knowledge check with answers
1. **Does changing directory activate an environment?** No. Directory selection and interpreter selection are independent.
2. **Does a missing guessed install folder prove Conda is absent?** No. Find the actual installation and test its supplied prompt.
3. **Why use python -m pip?** It selects pip through the interpreter you are inspecting, reducing ambiguity about which Python receives the operation.
4. **Does pip check validate a GPU backend?** No. It checks declared dependency relationships, not every import or runtime path.
5. **Is a history export an exact all-platform lock?** No. It records requests that can resolve differently.
6. **Should an external AI experiment replace Umicom's native toolchain?** No. Keep its environment boundary explicit and qualify the native product separately.

## Completion criteria
Your worksheet identifies the shell, installation, three environment prefixes, expected and actual outputs, any failures, and the native tool paths selected afterwards. Another learner should be able to follow your reasoning without needing access to your private files. Do not claim a successful capstone until you have executed and inspected each required step. Keep practice environments until you have reviewed the evidence; environment removal is not required to complete the course.


[Course contents](index.md) · [Previous lesson](09-troubleshoot-one-layer-at-a-time.md)
