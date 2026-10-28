# LLM from Scratch — Lesson 459: Use domain separation between leaves, nodes and roots

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **use domain separation between leaves, nodes and roots** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

A Merkle structure uses SHA-256 for different logical operations. Without clear domain tags, ambiguous encodings can blur the difference between the contents of a leaf and the concatenation of two internal hashes. Prefixes for leaves, parent nodes and the final count-bound root make the commitment grammar inspectable and prevent cross-type substitutions under normal cryptographic assumptions.

## Step-by-step worked example

The native module hashes each original digest as L=H(leafDomain||digest), an internal pair as P=H(nodeDomain||left||right), and the finished tree as R=H(rootDomain||BE64(count)||top). Three domain strings are distinct byte sequences.

## Practical task

Write down the exact byte-concatenation sequence for two leaf digests. Show where the count is committed and why the domain prefix is outside the model tensor data.

### Worked answer and reasoning

Two leaf hashes, one parent hash and one count-bound root hash are performed. All use the canonical Framework SHA implementation.

## Threat model and qualification limits

Domain separation is a protocol-design defence, not a substitute for safe key management or cryptographic analysis. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [Umicom native Framework SHA-256](https://github.com/umicom-foundation/umicom-framework)

## Continue learning

- [Browser lesson](../../courses/llm-from-scratch/lessons/459-use-domain-separation-in-merkle-hash-operations.html)
- [Course study route](../../courses/llm-from-scratch/merkle-proofs-and-ledger-boundaries.html)
- [Previous lesson](458-map-federated-audit-records-to-merkle-leaves.md)
- [Next lesson](460-construct-merkle-trees-with-odd-batch-sizes.md)

*Service to Many Leads to Greatness.*
