# Lesson 39 — Identify the Actual Training Bytes with SHA-256

**Course:** Build an LLM from Scratch  
**Level:** Developing  
**Focus:** Immutable training datasets, cryptographic digests, byte ownership and reproducible identity

## Why a training run needs a source-byte identity

A language model can only be reproduced when its inputs are known. A checkpoint records the model's parameters. The training configuration records settings such as the optimiser and random seeds. Neither alone tells us which exact source-file bytes were used to calculate the gradients.

In the previous lesson, we introduced a run lock based on the dataset's ordered document catalogue. That catalogue includes file names, training/evaluation splits, lengths and FNV-1a64 fingerprints. FNV is fast and useful for detecting accidental changes. **It is not collision-resistant:** different byte sequences can deliberately be constructed with the same short fingerprint. Applying SHA-256 to an FNV number does not recover the information the fingerprint discarded.

To strengthen the identity, we hash the **original imported bytes**, using the immutable in-memory corpus maintained by Umicom Framework. We do not create a second dataset loader or reopen the source files.

![How the immutable corpus feeds SHA-256 source identity](../../assets/diagrams/source-snapshot-hashing.svg)

## What exactly do we hash?

Umicom's source manifest lists documents in an order. A document has a partition (`train` or `eval`), a relative path, a byte count and an immutable byte corpus. A reproducible identity must bind all of them.

For each document, the Framework calculates SHA-256 over its raw byte corpus. It then constructs a second SHA-256 digest over the ordered document catalogue, recording the source-byte digest alongside each document's partition, path and length.

The digest input begins with a fixed domain string:

```text
UMICOM-AI-DATASET-SOURCE-SNAPSHOT-1
```

It is followed by the number of documents and, for each one, the numeric partition, relative-path length, path bytes, source-byte length and 32-byte SHA-256. Numeric fields are written in defined little-endian byte order; the representation never depends on how a particular compiler pads a C structure.

Consequently, changing `train/a.c` to contain different bytes, moving a document from `train` to `eval`, or rearranging the manifest order changes the snapshot identity.

## Use the Framework's existing corpus owner

The public interface for the source-byte digest is:

```c
UmiStatus UmiAiCorpusSha256(
    const UmiAiCorpus *corpus,
    unsigned char outDigest[32]);
```

The corpus already owns a copy of the source bytes. The implementation passes those bytes to the Framework's existing incremental SHA-256 service. There is no second file reader, script or mathematical implementation.

You can calculate a dataset identity from an approved manifest:

```c
#include "umicom/ai/training/dataset_manifest.h"
#include "umicom/base/sha256.h"
#include <stdio.h>

int main(void)
{
    UmiAiTrainingDataset *dataset = NULL;
    unsigned char identity[32];
    char hexadecimal[65];

    UmiStatus status = UmiAiTrainingDatasetLoadManifest(
        "framework/learning/native-llm/fixtures/manifest.txt", &dataset);
    if (status != UMI_STATUS_OK) return 1;

    status = UmiAiTrainingDatasetSourceSha256(dataset, identity);
    if (status == UMI_STATUS_OK) {
        UmiSha256Hex(identity, hexadecimal);
        printf("Reviewed source snapshot: %s\n", hexadecimal);
    }

    UmiAiTrainingDatasetDestroy(dataset);
    return status == UMI_STATUS_OK ? 0 : 1;
}
```

This example assumes the process starts in the Umicom Applications directory. The `manifest.txt` path is an educational fixture, not a production data-source recommendation.

## A small numerical fact worth remembering

SHA-256 produces **256 bits**, or **32 bytes**, of digest. Writing each byte as two hexadecimal characters produces exactly **64 hexadecimal characters**; a C string requires a 65th byte for its terminator. The output array sizes in the example follow directly from that representation.

A matching digest gives strong evidence that the hashed bytes have not changed, subject to SHA-256's cryptographic assumptions. It does **not** prove that the files were safe, that their author was authorised, or that the model learned correctly.

## Practical exercises

1. Load the same approved dataset twice. Verify that both 32-byte source identities match.
2. Create a separate working copy of a small manifest and its source files. Change one source byte, reload the dataset and show that its source digest changes.
3. Restore the original bytes but reverse the order of two `train` entries. Confirm that the dataset digest changes even though the set of source files is unchanged.
4. Explain why an immutable in-memory snapshot is preferable to reopening disk paths while recording training evidence.

## Check your understanding

**Question:** Why not simply calculate `SHA256(FNV64(document))` for each source file?  
**Answer:** Because a collision in the FNV64 fingerprint would still give identical input to SHA-256. We instead calculate SHA-256 directly from the original source bytes.

**Question:** Does a source SHA-256 identity authenticate the person who approved the corpus?  
**Answer:** No. Authentication requires a separately trusted signing or authorisation process.

**Next:** Bind the source-byte digest to a checkpoint and verify all required evidence before AdamW training resumes.
