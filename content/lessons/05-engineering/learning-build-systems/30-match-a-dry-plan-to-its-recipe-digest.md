<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/30-match-a-dry-plan-to-its-recipe-digest.md

PURPOSE:
Match a dry plan to its recipe digest

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Match a dry plan to its recipe digest

A **recipe** is a JSON file that describes sources, tools and stages. A **dry plan** lists the stages the planner would select and puts their prerequisites first. A **digest** is a short, fixed-length value calculated from the exact file bytes. Keep the digest with a saved plan so you can check which recipe produced it.

In this exercise you will preview a label-making project, compare the plan's digest with an independent hash, and see how an extra space changes the digest while the stage order stays the same.

## 1. Save a small recipe

Open PowerShell in a folder for this exercise. Save the following text as `labels-recipe.json` using UTF-8 without a byte-order mark (BOM). You need a current `umicom` command that lists `--recipe-digest` in `umicom recipe --help`.

~~~json
{
  "schema": 1,
  "id": "labels-plan",
  "build": "x86_64-w64-mingw32",
  "host": "x86_64-w64-mingw32",
  "target": "x86_64-w64-mingw32",
  "toolchain": {
    "id": "lesson-c",
    "compiler": "tools/bin/lesson-cc",
    "manifest": "tools/toolchain.json",
    "sha256": "0000000000000000000000000000000000000000000000000000000000000000"
  },
  "inputs": [
    {
      "id": "label-source",
      "path": "src/labels.c",
      "sha256": "0000000000000000000000000000000000000000000000000000000000000000",
      "bytes": 0
    }
  ],
  "stages": [
    {
      "id": "pack-labels",
      "label": "Pack labels",
      "phase": "package",
      "dependencies": ["check-labels"],
      "inputs": [],
      "outputs": ["out/labels.zip"]
    },
    {
      "id": "check-labels",
      "label": "Check labels",
      "phase": "test",
      "dependencies": ["make-labels"],
      "inputs": [],
      "outputs": ["out/labels-check.txt"]
    },
    {
      "id": "make-labels",
      "label": "Make labels",
      "phase": "build",
      "dependencies": [],
      "inputs": ["label-source"],
      "outputs": ["out/labels.o"]
    }
  ]
}
~~~

The all-zero hashes are placeholders for the source file and toolchain manifest. This plan only reads the JSON recipe. You can leave the declared sources, tools and output files absent for this exercise.

## 2. Preview one stage

Resolve the recipe to its full path. Ask for `check-labels` and keep `--recipe-digest` at the end. Stop and check the message if the plan command returns a nonzero exit status.

~~~powershell
$recipe = (Resolve-Path -LiteralPath './labels-recipe.json').Path
umicom recipe plan --file $recipe --target check-labels --recipe-digest
$LASTEXITCODE
~~~

Expect exit 0. Find `Recipe ID: labels-plan`, a 64-digit hexadecimal value after `Recipe SHA-256:`, and `Plan scope: check-labels`. The stage list should read as follows.

~~~text
Plan: 2 stages
1. make-labels
2. check-labels
~~~

The recipe lists the packaging stage first. The planner follows dependencies and puts `make-labels` before its check. Selecting the check leaves packaging outside this plan. The final CLI line says the plan executed no stages and source and toolchain claims remain unverified.

## 3. Check the digest independently

Measure the saved file with PowerShell. Compare the printed value with the line labelled `Recipe SHA-256` in the plan. Hexadecimal letters may appear in either case.

~~~powershell
(Get-FileHash -LiteralPath $recipe -Algorithm SHA256).Hash.ToLowerInvariant()
~~~

Compare results from the same saved file version. A different digest means the bytes differ. Confirm the file path and check whether your editor changed its encoding, spaces or line endings.

## 4. Change only the file bytes

Make a copy in your practice folder. Append one UTF-8 space to the end. JSON allows whitespace after the final brace.

~~~powershell
$copy = Join-Path (Get-Location).Path 'labels-recipe-spaced.json'
if (Test-Path -LiteralPath $copy) { throw 'Choose a fresh name for the spaced copy.' }
Copy-Item -LiteralPath $recipe -Destination $copy
[System.IO.File]::AppendAllText($copy, ' ', [System.Text.UTF8Encoding]::new($false))
umicom recipe plan --file $copy --target check-labels --recipe-digest
if ($LASTEXITCODE -ne 0) { throw 'Review the plan refusal before comparing hashes.' }
(Get-FileHash -LiteralPath $copy -Algorithm SHA256).Hash.ToLowerInvariant()
~~~

The copy should produce the same recipe ID and stage order. Its digest should differ from the original and match the independent hash of the copy.

## Questions and answer key

1. **What happens if you omit `--target check-labels`?** The scope becomes `all stages`. The order is `make-labels`, `check-labels` and `pack-labels`.
2. **Why do the original and spaced copy have different digests?** The digest covers the full byte sequence. The extra space changes those bytes while leaving the recipe's instructions and dependency order the same.
3. **What happens if you ask for a stage called `ship-labels`?** The planner reports an unknown target and returns exit 1. It prints no plan or recipe digest because the requested scope could not be planned.
4. **What evidence would support a claim that the source file matches its recipe entry?** Use a separate `umicom recipe verify` check with the actual source and toolchain directories. Retain the verified results with the recipe. The dry plan records the recipe's byte identity and proposed stage order.

Save the plan text, recipe ID, scope and digest together. That gives another learner enough information to check the same preview against a copy of the recipe.

[Course contents](index.md) · [Previous lesson · See which library Ninja will link](29-see-which-library-ninja-will-link.md) · [Related lesson · Recognize stale tests after a failed build](26-recognize-stale-tests-after-a-failed-build.md) · [HTML edition](../../../courses/learning-build-systems/lessons/30-match-a-dry-plan-to-its-recipe-digest.html)

[Next lesson · Measure the process temporary volume](31-measure-the-process-temporary-volume.md)
