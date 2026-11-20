<!--
Umicom Bits2Banking
File: content/lessons/05-ai/preparing-llm-training-data/34-identify-the-bytes-a-dataset-loaded.md

PURPOSE:
Show how the native dataset inspector identifies each immutable source document and the ordered dataset.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Identify the bytes a dataset loaded

[Course contents](index.md)

## Read a document identity and a dataset identity

A SHA-256 digest is a fingerprint represented here by 64 hexadecimal characters. If you change a byte in a file, its digest should change. The digest belongs to the bytes read, so differences in line endings count even when a text editor displays the same words.

The Umicom inspector can report two related identities. A document digest covers one file's original bytes. The dataset digest also covers the document order, relative names and train or evaluation partition. A copy with the same bytes under a new name keeps its document digest and changes the dataset digest when you update the manifest.

The importer creates an immutable snapshot. An object that is still open keeps its own bytes when someone edits the file. Loading the manifest again creates another snapshot. A SHA-256 value can help you identify and compare those snapshots. It does not show who supplied the material, whether it is licensed for training, or whether the model learned anything useful.

## Build the native inspector on Windows

1. Open PowerShell in the Framework checkout. Use a terminal with your C23 compiler, CMake and Ninja on `PATH`. The course uses the three short, included training and evaluation examples.
2. Configure and build the focused learning target. Stop at the first error and keep that message.

~~~powershell
cmake -S learning/native-llm -B build/lesson-dataset-identity -G Ninja -DBUILD_TESTING=ON
cmake --build build/lesson-dataset-identity --target umicom-native-llm-dataset umicom-ai-training-dataset-source-sha256-test --parallel 2
ctest --test-dir build/lesson-dataset-identity -R '^framework[.]ai[.]training[.](dataset_inspector|dataset_source_sha256)$' --output-on-failure
~~~

3. Run the inspector with the explicit `--document-sha256` option. Keep the relative names in the report so each digest can be matched to its source entry.

~~~powershell
$lab = 'build/lesson-dataset-identity'
$source = 'learning/native-llm/datasets/first-documents'
& "$lab/umicom-native-llm-dataset.exe" --document-sha256 "$source/dataset.txt"
(Get-FileHash -Algorithm SHA256 "$source/training/project.txt").Hash.ToLowerInvariant()
~~~

The report should show three documents, with two for training and one for evaluation. It should add three `Document SHA-256` lines. The digest beside `training/project.txt` should match the final PowerShell value exactly. The independent hash reads the current file, so complete this comparison before editing it.

Use the same configure, build and test commands on Linux with CMake and Ninja available. Run `build/lesson-dataset-identity/umicom-native-llm-dataset` without the `.exe` suffix and use `sha256sum` for the independent file comparison.

## Change a working copy and predict what will move

1. Save the first report. Pick a new path inside the build folder and copy the fixture into it. Keep the checked-out examples as the baseline.

~~~powershell
$copy = "$lab/review-copy"
Copy-Item -LiteralPath $source -Destination $copy -Recurse
& "$lab/umicom-native-llm-dataset.exe" --document-sha256 "$copy/dataset.txt"
~~~

2. Confirm the copied manifest gives the same dataset digest. It names the same files in the same order, and those files contain the same bytes.
3. Edit `training/project.txt` in the copy and save. Run the command again. The changed document and dataset digests should differ from the first report. The evaluation document and the other training document should retain their digests.
4. Try moving an entry in the copy's manifest while keeping it in the same partition. Its document digest should stay the same, and the ordered dataset digest should change. A reproducible sampler can use source order, so record the full dataset digest when describing an experiment.
5. If the inspector cannot find the document, open `dataset.txt` and compare each relative path with the copy on disk. If the SHA-256 values differ after a copy, compare the original and copied bytes before looking at token IDs. Editors may change line endings or add a final line break.

## Read the native interface

The public header is `umicom/ai/training/dataset_manifest.h`. `UmiAiTrainingDatasetDocument` gives you the name and partition for a zero-based index. `UmiAiTrainingDatasetDocumentSha256` gives you the digest for the same index. Use the output only after `UMI_STATUS_OK` and keep the dataset alive while reading it. An invalid index leaves the output unchanged, so an old buffer must never be reported as a fresh result after a failed call.

This exercise reads explicitly selected local files. It does not publish data, train a model or grant permission to use someone else's source. For a real experiment, keep rights review and independent evaluation evidence alongside the dataset identity.

[Previous: Aggregate evaluation with checked summaries](33-aggregate-evaluation-with-checked-summaries.md)
