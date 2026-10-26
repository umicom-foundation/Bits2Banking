# Encode a separate stacked-model checkpoint

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Licence:** MIT  
**Level:** Progressive native C23 / AI engineering

## Why this model needs a distinct file identity

An existing single-block decoder checkpoint represents one fixed parameter family. A multi-layer model contains more independently ordered weight tensors. Reinterpreting an old checkpoint as a stacked model would silently change the mathematics. The new Framework `UmiAiTrainingStackedCheckpointExport` creates a **separately identified binary record** with magic `UMISTK01`.

The format records the model dimensions, seed, completed SGD steps, the number and shapes of parameter tensors and every finite FP32 parameter value. Integers are explicitly little-endian; FP32 bits are copied without depending on a compiler's native C struct packing. A trailing SHA-256 digest covers the encoded bytes before the digest.

## Export without partial publication

Call `UmiAiTrainingStackedCheckpointSize` to obtain the required byte capacity. Allocate the caller-owned buffer. The export creates a private staging record, validates all tensor values, computes the digest and copies the complete bytes only on success. A short destination retains its previous bytes and write count.

The checkpoint is **not signed**. A content digest detects damage, but someone able to replace the record can calculate a new digest. A trusted publisher and model admission policy are separate Framework security concerns.

## What is and is not resumable

The current stacked trainer uses ordinary stateless SGD. Restoring its weights and completed-step count is enough to resume the same deterministic sequence of SGD operations *provided the data, order and learning rate are also unchanged*. AdamW additionally needs moment state. The snapshot does not carry experiment dataset approvals or the current position within an epoch.

## Practice

A record has the correct layer count but one weight byte is changed. What does its SHA-256 check tell you? Can it authenticate the person who supplied the record?

<details><summary>Worked answer</summary>

The check should reject the damaged record because the digest no longer matches the content. Even an unmodified matching digest does not authenticate a publisher or prove the checkpoint was trained with authorised data.

</details>

---

[Native stacked Transformer reading path](stacked-transformer-learning-path.md) · [Mathematics for AI](../11-maths-for-ai/stacked-transformer-mathematics.md)
