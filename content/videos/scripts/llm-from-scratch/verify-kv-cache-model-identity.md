# Video lesson — Bind a Transformer Cache to Its Model Identity

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab

## Scene 1 — Same dimensions, different weights

**Visual:** Two models, both labelled `3 layers × 4 channels`, with differing synthetic parameter tables and different SHA-256 fingerprints.

**Narration:** "Two models can have the same network shape and still produce completely different keys, values and logits. A cache built from one model must never be used as if it came from the other. Even a fine-tuning step can change the numerical projections while leaving the number of layers unchanged."

## Scene 2 — The digest label

**Visual:** A 32-byte digest icon and an ordinary unsigned model-checkpoint file. Connect a matching digest to a cache state.

**Narration:** "Umicom Framework can capture an SHA-256 digest of a canonical stacked model checkpoint. The K/V store retains a copy of an approved digest label, then refuses requests that explicitly present a different label. The application must independently verify the current model identity before producing or consuming those rows. The store itself is not a signature verifier."

**Important distinction:** SHA-256 is a content fingerprint. Authentication of the publisher and authorisation of the source are separate questions.

## Scene 3 — A stale-model example

**Visual:** Model A is fine-tuned to model B. The old K/V state is marked stale. A new blank store appears beside the new checkpoint.

**Narration:** "Suppose a cache was created from checkpoint A. Training resumes and produces checkpoint B. The correct action is not to keep the old K/V projections because their array sizes fit. Reject the stale cache, create a new store bound to B and prefill it using B's actual projections. This protects the meaning of the generated output."

## Scene 4 — An engineering exercise

**On-screen question:** "Can you authenticate a downloaded model merely by hashing it yourself?"

**Worked answer:** "No. You can learn the downloaded bytes' digest, but you still need a trustworthy source or independently verified signed release approval. A malicious supplier can also calculate a digest."

## Continue

[Read LLM Lesson 192](../../../lessons/10-native-ai/192-pin-a-cache-to-a-checkpoint-identity.md) and [Mathematics Unit 97](../../../lessons/11-maths-for-ai/97-separate-sha-256-content-identity-from-trust.md). In a sensitive application, generated model output must not independently authorise financial operations.

*Service to Many Leads to Greatness.*
