# Supplement 16A — Training Manifests, Corpus Provenance and Leakage

**Bits to Banking · Umicom Foundation · Sammy Hegab**  
**Companion:** [Lesson 16 — Train an Umicom Decoder on C23 Source Code](16-source-code-training-with-file-level-evaluation.md)

## A manifest is a contract, not a folder of random files

The file `framework/learning/native-llm/fixtures/manifest.txt` tells the training program which reviewed source files are allowed into the training and evaluation partitions. The format is intentionally small:

```text
UMICOM-AI-DATASET-1
# Place these reviewed files into the training partition.
train train/account.c
train train/notes.c
# Never train on this held-out evaluation file.
eval eval/payment.c
```

Each entry is resolved relative to the *manifest file's directory*. The trainer does not depend on the terminal's working directory when locating a named file within that manifest. This matters when Umicom Studio launches a process from a different workspace.

The parser rejects unexpected fields, empty or oversized manifest files, more than 16 documents, paths with backslashes, absolute paths, obvious `..` traversal, and duplicate paths. Files are read as exact binary bytes using the existing Framework Corpus Loader. Each individual file is limited to 1 MiB for this first laboratory.

**Limits:** These lexical checks do not stop a trusted local path from resolving through a symbolic link, junction or race to an unexpected file. A production untrusted-data importer requires stronger filesystem containment. The current lesson requires the operator to review both manifest and files first.

## Provenance that we can actually verify

The Framework records the source path, partition, byte length and 64-bit FNV-1a fingerprint computed from the immutable in-memory corpus snapshot. A fingerprint is not a secret-key signature; deliberately crafted files may collide. We reject simple duplicates by matching lengths and fingerprints to avoid an obvious train/evaluation overlap, but this does not catch copy-pasted functions or near-duplicate documents.

A meaningful experiment record should also contain the Framework Git commit, model configuration, initialisation seed, dataset manifest version, training-batch seed, optimiser settings, checkpoint digest and compiler/test results. Not all of those are captured automatically by Batch 06; retain this information in your experiment notes until a full native experiment registry is implemented.

## Why a good held-out number is not enough

Imagine that `train/account.c` contains a function used verbatim in `eval/payment.c`. The model might predict it because it memorised repeated bytes, not because it understands accounting or financial controls. Whole-file splitting improves separation but does not guarantee independence. For larger repositories we may need partitioning by *project or time period*, duplicate analysis, explicit licences and a genuine programming benchmark.

A practical C23 rule remains simple: **treat the model's output as an unverified proposal**. The compiler, unit tests, runtime checks and human review establish whether proposed changes are useful.

## Try it yourself

Run the dataset inspection example. Confirm that three files appear, with two in `train` and one in `eval`. Then deliberately create a separate manifest that lists the same relative filename twice. Observe the nonzero failure result. Restore the original manifest; the learning fixtures should remain unmodified.

Next, read the public contract at `framework/include/umicom/ai/training/dataset_manifest.h`. Identify who owns the returned dataset, what capacities mean, when output buffers remain untouched and how the train/evaluation partition is selected.
