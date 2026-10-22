# Lesson 24 — Understand Checkpoints, Recovery and Evidence

**Level:** intermediate • **Estimated time:** 18 minutes • **Theme:** preserving evidence in a native training workflow

## A checkpoint is more than a file with a `.umi` extension

A training checkpoint is a saved snapshot of a model at a known point in the experiment. It lets us inspect the model later or continue training without restarting from newly initialised parameters. The snapshot is useful only if we can explain **what it contains**, **what it omits** and **which source/plan produced it**.

## Understand two kinds of state

The teaching Framework supports an existing decoder checkpoint and a separate combined AdamW checkpoint. These are not interchangeable.

| Snapshot | Contents relevant to continuation | Important limitation |
|---|---|---|
| Decoder checkpoint | Decoder architecture, learned parameters, completed optimiser steps | Does not store AdamW's first/second moments |
| Combined AdamW checkpoint | Decoder parameters, AdamW moments, configuration and step count | Does not independently authenticate the training corpus or plan |

SGD without moment history and AdamW with moment history have different continuation requirements. Restoring only AdamW's model weights but resetting its moment estimates **changes the next optimisation update**.

## Failure-atomic operations

When a Framework loader rejects truncated or inconsistent data, it must not publish a partially reconstructed decoder. A safe save operation should not silently overwrite a previously approved checkpoint. These contracts are part of the native persistence tests.

An FNV checksum detects many accidental modifications, but it is **not a cryptographic authenticity check**. A reviewer still needs an independently trusted file source and a recorded SHA-256 or signed release manifest if authenticity matters.

## Review the evidence, not only the loss

An experiment report should identify the model checkpoint, source dataset, selected plan, optimiser-step count and held-out measurements. Umicom's read-only audit command reports sampled next-token cross-entropy, perplexity, top-1 accuracy and top-5 accuracy for an approved decoder checkpoint.

The audit CLI uses the syntax:

```text
umicom-native-llm-audit <approved-plan> <trusted-decoder-checkpoint> [expected-16-digit-hex-fingerprint]
```

This command expects a **decoder checkpoint**, not a combined AdamW checkpoint. The combined optimiser checkpoint must be inspected through its corresponding native checkpoint owner.

### Practical review without executing a quarantined binary

```powershell
Set-Location 'C:\umicom\Umicom-Applications'
Get-Content '.\framework\include\umicom\ai\training\checkpoint.h' -TotalCount 90
Get-Content '.\framework\include\umicom\ai\training\optimizer_checkpoint.h' -TotalCount 90
```

Compare the public contracts. Identify the ownership of the returned model, the declared file format, the supported limits and the rules for rejected data.

## Recovery exercise

An eight-step AdamW experiment saves a combined snapshot after step 3, then continues to step 8. Answer these questions:

1. What state must be restored before applying the update for step 4?
2. Which schedule step should be selected next?
3. If the source manifest changed, can the result be described as an exact continuation of the original experiment?

<details><summary>Reveal the reasoning</summary><p>Restore model parameters, AdamW first and second moments, optimiser configuration and completed step count. The next update uses absolute step 4. A changed source manifest invalidates a claim of identical continuation even if the binary checkpoint itself decodes successfully.</p></details>

**Next:** build an honest benchmark for a future specialised C23 assistant.
