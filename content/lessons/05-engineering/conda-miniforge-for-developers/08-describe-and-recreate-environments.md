<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/conda-miniforge-for-developers/08-describe-and-recreate-environments.md

PURPOSE:
Provide the editable manuscript for describe and recreate an environment.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Describe and recreate an environment

Lesson 8 of 10. Suggested study time: 40 minutes. Command exercises are unexecuted teaching examples.

[Course contents](index.md) · [Browser lesson](../../../courses/conda-miniforge-for-developers/lessons/08-describe-and-recreate-environments.html)

## What you will learn
Distinguish a readable environment specification from a record of resolved packages. You need a working named environment and a practice folder. Choose new output filenames so you do not overwrite a specification you still need.

## Intent and observation are different records
An environment specification says what you ask a package manager to install. An inventory says what was installed on one machine. A successful recreation needs both a usable specification and appropriate checks; a list of package names is not a test result.

The supplied [practice environment file](../../../courses/conda-miniforge-for-developers/practice/environment.yml) requests Python 3.12, pip and packaging from conda-forge. It excludes default channels for this solve. The version constraints are intentionally simple, so it is a teaching specification rather than an exact deployment lock.

Save that file as environment.yml in your practice folder. Inspect it before use:

~~~powershell
Get-Content -LiteralPath .\environment.yml
conda env create --name umicom-env-recreated --file .\environment.yml
conda run --name umicom-env-recreated python -c "from packaging.version import Version; print(Version('1.10') > Version('1.9'))"
~~~

Use a different environment name if this one already exists. The expected comparison result is True, but record the actual result. Environment creation may choose newer compatible package builds than an earlier run.

## Export with a stated purpose
Current Conda supports structured and explicit export formats. Run the following from your practice folder after checking that the output files do not already contain work to preserve:

~~~powershell
conda export --name umicom-env-lab --from-history --format=environment-yaml --file=environment-intent.yml
conda export --name umicom-env-lab --format=explicit --file=conda-resolved.txt
~~~

The history-based export records explicit Conda requests and avoids capturing every platform-specific transitive choice. Explicit output identifies resolved Conda package artifacts for compatible platforms. It is not a portable all-platform guarantee or a complete pip lock. [Conda export reference](https://docs.conda.io/projects/conda/en/stable/commands/export.html).

For an older Conda release without that export interface, consult its help and use the established YAML export alternative:

~~~powershell
conda env export --name umicom-env-lab --from-history --file=environment-intent-legacy.yml
~~~

[Conda env export reference](https://docs.conda.io/projects/conda/en/stable/commands/env/export.html).

## Preserve pip requirements separately when needed
A history export is not a reliable inventory of all pip-installed dependencies. In a mixed environment, keep the reviewed pip requirements and an observed pip inventory as separate records:

~~~powershell
conda run --name umicom-env-lab python -m pip freeze | Set-Content -LiteralPath .\pip-observed.txt -Encoding utf8
~~~

Do not blindly reinstall this inventory over a Conda environment: it can include distributions Conda already owns. Review package ownership and use the project's chosen dependency workflow. Before sharing exports, inspect local paths, private repository URLs and credentials. Keep secrets outside public course material.

## Exercise and answer
Two machines recreate a history-based specification and receive different patch versions. Does that prove Conda ignored the file?

**Answer:** no. A broad version request allows multiple solutions. Decide whether you need portable intent or exact artifact selection, then use a suitable record and repeat the relevant checks. Even identical package artifacts do not establish identical GPU drivers, OS state or application input.


[Course contents](index.md) · [Previous lesson](07-keep-native-builds-separate.md) · [Next lesson](09-troubleshoot-one-layer-at-a-time.md)
