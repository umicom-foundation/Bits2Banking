# Lesson 22 — Separate Training Evidence from Evaluation Evidence

**Level:** beginner • **Estimated time:** 15 minutes • **Domain:** C23 source-code learning

## The question a training score cannot answer

A model may learn to predict bytes from the files it has just studied. A low training loss tells us that it predicts those **training examples** well. It does not tell us whether the model can respond to unfamiliar code, find mistakes or solve a new problem.

That is why we keep a **held-out evaluation partition**: source material never used to update the model's parameters during that experiment.

## A practical banking example

Imagine reviewing these fictional modules:

| Source file | Purpose | Partition |
|---|---|---|
| `train/account.c` | Account checks | Training |
| `train/notes.c` | Native notes storage | Training |
| `eval/payment.c` | Payment validations | Held-out evaluation |

The training process samples input–target windows only from the first two files. The evaluator samples from the third file. It calculates next-token cross-entropy **without changing model weights**.

A file-level split is stronger than taking random windows from one file: neighbouring windows can share most of the same bytes. The same file in both partitions would make the apparent test far too easy.

## The reviewed manifest format

Umicom Framework accepts a bounded, reviewed text file such as:

```text
UMICOM-AI-DATASET-1
# Independent, permitted C23 teaching files
train train/account.c
train train/notes.c
eval eval/payment.c
```

The parser requires both partitions and disallows duplicate paths and obvious byte-identical duplicates. However, **a renamed or lightly edited near-duplicate can still leak information**. Reviewers must recognise overlapping functions, generated boilerplate and copied tests.

A dataset manifest is a list of authorised local inputs, **not a security sandbox**. Symlinks and concurrent filesystem changes require separate trust controls. Never include API keys, personal bank records, confidential customer data or third-party source whose licence does not permit use.

## Provenance matters

For each source file the Framework records relative path, byte count, assigned partition and an FNV-1a64 fingerprint. That value can identify an accidental file change but is not a digital signature and is not proof that a file came from a trustworthy author.

A trustworthy experiment also records the exact training plan, model checkpoint and code revision. Otherwise, comparing two evaluation scores may compare different datasets rather than different models.

## Step-by-step source review

1. Open the teaching manifest and confirm that all paths are expected.
2. Open each referenced C23 file and check its licence and intended scope.
3. Look for duplicate or near-duplicate functions across train and evaluation files.
4. Confirm that no file contains credentials or confidential records.
5. Run a dataset audit through the existing Umicom Framework owner.

PowerShell can inspect the existing manifest **without executing source code**:

```powershell
Set-Location 'C:\umicom\Umicom-Applications'
Get-Content '.\framework\learning\native-llm\fixtures\manifest.txt'
Get-FileHash '.\framework\learning\native-llm\fixtures\train\account.c' -Algorithm SHA256
```

The SHA-256 file hash above is a separate inspection checksum. It is not the FNV fingerprint displayed by the teaching dataset API.

## Knowledge check

A training file called `transfer.c` contains almost the same function as a held-out file called `transfer_copy.c`. Would the filenames being different make the evaluation independent?

<details><summary>Reveal the answer</summary><p>No. The inputs are near-duplicates. The model could reproduce familiar source structure and appear to generalise. Review and replace the held-out example with genuinely independent permitted material.</p></details>

**Next:** construct a reproducible, reviewed training plan.
