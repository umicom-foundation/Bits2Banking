<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/conda-miniforge-for-developers/09-troubleshoot-one-layer-at-a-time.md

PURPOSE:
Provide the editable manuscript for troubleshoot one layer at a time.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Troubleshoot one layer at a time

Lesson 9 of 10. Suggested study time: 35 minutes. Command exercises are unexecuted teaching examples.

[Course contents](index.md) · [Browser lesson](../../../courses/conda-miniforge-for-developers/lessons/09-troubleshoot-one-layer-at-a-time.html)

## What you will learn
Find the first failing layer and preserve enough evidence to make a useful repair. Work from installation through the shell, interpreter, packages and application in that order. Do not start by reinstalling every tool.

## A practical decision table
| Observation | Next observation | Avoid assuming |
| --- | --- | --- |
| Conda name is unknown | Try the installed Miniforge Prompt and inspect Get-Command in the failing shell. | That every possible install directory is absent. |
| Conda runs but activation requests initialization | Check the shell host, profile and init preview. | That another package install will fix shell integration. |
| Environment name cannot be found | Run conda env list and conda info --base. | That two installations share the same environment registry. |
| Python path is unexpected | Inspect Get-Command python -All and sys.executable. | That the prompt label is proof. |
| Dependency solve is unsatisfiable | Preserve requested versions, channels and the conflicting constraints. | That removing all pins is a correct repair. |
| Import fails after installation | Confirm the selected interpreter, package version and exact first error. | That pip metadata checks exercised the import. |
| Native library fails to load | Record architecture, backend and the named library or symbol. | That Python version alone explains every loader error. |
| Download or certificate validation fails | Check connectivity, proxy and trusted certificate configuration with the responsible administrator. | That disabling TLS verification is a sound fix. |

## Collect a small record
Use these observations in the failing shell. Some may themselves fail; retain that fact and stop dependent actions.

~~~powershell
$PSVersionTable.PSVersion
$PROFILE
Get-Command conda,python -All -ErrorAction SilentlyContinue
conda info
conda env list
python -c "import sys; print(sys.executable); print(sys.version)"
python -m pip check
~~~

Keep the exact command, first diagnostic and exit result together. Package-manager output may include personal paths or repository addresses; remove sensitive information before sharing it publicly. Keep a private original when appropriate.

## Worked failure trace
Ravi installs a Python package in environment A. In a new terminal, an application fails with ModuleNotFoundError. He proposes reinstalling Miniforge. Instead, he checks sys.executable: the application was launched with environment B's Python. The next experiment is to run the documented application entry point with environment A explicitly selected. That tests a focused cause without disturbing B.

If the import still fails under A, the original hypothesis was incomplete. Continue with the package's installed version and API documentation. A diagnostic observation is not itself a repair.

## Exercise and explained answer
A dependency solver reports incompatible constraints. Your first change is to remove every pinned version, and installation succeeds. Can you conclude the original application is fixed?

**Answer:** no. You changed the dependency contract. Preserve the original specification, identify which constraint conflicts and check whether an intentional version change is supported by the application. Demonstrate the relevant behaviour in a separate candidate environment before replacing a working setup.

## Recovery boundary
Use a newly named practice environment to isolate an experiment. Do not delete base, remove production environments, overwrite shell profiles or clear unrelated build caches as generic troubleshooting. Return to [the PowerShell lesson](../../../courses/conda-miniforge-for-developers/lessons/03-connect-conda-to-powershell.html) for initialization and [the native toolchain lesson](../../../courses/conda-miniforge-for-developers/lessons/07-keep-native-builds-separate.html) for mixed tool paths.


[Course contents](index.md) · [Previous lesson](08-describe-and-recreate-environments.md) · [Next lesson](10-capstone-and-knowledge-check.md)
