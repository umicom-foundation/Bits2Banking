# Supplement 18A — Repeatable Checkpoint Comparisons and Evidence Boundaries

**Bits to Banking · Native AI course · Sammy Hegab · Umicom Foundation**

## The problem of comparing different experiments

Suppose we train a small Umicom decoder twice. The first model is trained for
32 optimiser steps and the second for 64. We observe that the second model has
lower held-out cross-entropy. Is it automatically better? Not necessarily.
The source dataset, evaluation windows, model architecture, initialisation
seed, learning rate and checkpoint must also be accounted for.

A meaningful comparison needs a controlled experiment. Ideally the two models
use **exactly the same evaluation dataset, sampling plan and vocabulary**, and
they differ in only one deliberate training dimension.

The new Framework `UmiAiTrainingModelAudit` report permits reproducible
identification of each source of evidence. A changed parameter tensor changes
the model fingerprint. Swapping a source file between train and eval changes
the dataset fingerprint. Changing `learning_rate`, `train_seed`, `eval_seed`,
`steps` or the architecture changes the plan fingerprint.

## Exact identity is not performance

Two models may have different checkpoint fingerprints but identical Top-1
accuracy on a small evaluation sample. Conversely, two runs with identical
model weights might produce different evaluation metrics if the plan selects
different held-out windows. Model identity and model quality are separate
properties; both must be reported.

Top-1 accuracy is the fraction of target next tokens ranked first. The
Top-5 metric is more forgiving, but still does not measure compilation or
correct program behaviour. Perplexity is exponentiated mean cross-entropy.
Compare it only under the same tokenisation and evaluation protocol.

**Example:** a tiny decoder with a 260-ID vocabulary can assign high
probability to newlines and spaces while remaining unable to describe
Umicom's Data Server or implement safe transaction rollback. This is why our
planned expert evaluations must eventually include source-aware tasks,
compilation, unit tests and review against current Framework contracts.

## Follow the C23 provenance workflow

Read `framework/src/ai/training/model_audit.c`. The implementation uses the
existing canonical checkpoint encoder to identify the exact model bytes,
then visits the dataset manifest's immutable source document descriptions.
It hashes *declared source membership* rather than trying to infer what
training files were used from generated prose. Finally it measures the actual
held-out predictions using the Framework's decoder.

The contract deliberately does not change the binary checkpoint format.
A checkpoint alone still does **not** contain the source dataset and
training-configuration fingerprint. To reproduce an experiment, retain the
reviewed plan, source manifest, approved original source bytes, checkpoint
and reported fingerprints as a linked set of artifacts. Store these under
an appropriate controlled area, not in application source code.

For terminal-based development, `umicom-native-llm-audit` prints a deterministic
combined fingerprint. Retain it in a trusted experiment record. Re-run the
audit against the current plan, source snapshot and model, passing the
reviewed fingerprint as the optional final argument. An unexpected mismatch
is a reason to stop and investigate.

The fingerprints use **FNV-1a64**, which is not collision-resistant; it is
useful for accidental mismatch detection and educational audit trails, not
malicious tamper detection. The model itself is not signed. A proper future
release process will need cryptographically verified and authorised assets.

## Verification with changed evidence

The focused `framework.ai.training.audit_changes` regression test exercises
three distinct situations: reloading an identical checkpoint, changing
experiment parameters without changing model weights, and updating model
weights while retaining the original plan. It also loads an alternative
reviewed manifest with a different train/evaluation assignment. Matching
identities are accepted only when every recorded source of evidence matches.

The report is also **failure-atomic**: invalid inputs and a mismatched
architecture cannot overwrite a previously populated result. Verify this
behaviour by running `framework.ai.training.audit_rejections`.

## Questions for a code reviewer

- Could the claimed held-out samples have been included in training through near-duplicates or copied boilerplate?
- Can a reader reconstruct the same model configuration and seed values?
- Are all measured targets treated consistently, including whitespace and bytes outside printable ASCII?
- Are identical evaluation windows used across candidates, with enough examples to report uncertainty?
- Is the recorded fingerprint being misrepresented as a cryptographic certificate?
- Does the implementation leave model weights and optimiser steps unchanged during inspection?

This evidence foundation makes future expert-model comparisons more rigorous,
but it cannot by itself establish reliable C23, Calypso or Umicom Framework
expertise. Those claims will require representative benchmark tasks and
independent execution results.
