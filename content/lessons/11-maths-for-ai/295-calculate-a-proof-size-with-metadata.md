# Mathematics for AI — Lesson 295: Calculate Merkle proof storage including metadata

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **calculate merkle proof storage including metadata** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

An inclusion proof contains sibling hashes plus an index and count. The current native C structure reserves ten 32-byte sibling slots even if fewer are used. Its in-memory size may include size_t fields and padding; do not claim a portable network size by applying sizeof to a C struct. A portable transport must specify field widths explicitly.

## Step-by-step worked example

For five records: sibling hashes=3×32=96 bytes. With a designed frame of BE64 index and BE64 count, the compact metadata adds 16 bytes, producing 112 bytes before signature, root or length headers.

## Practical task

If a proposed signed frame adds a 64-byte signature, calculate the result.

### Worked answer and reasoning

The frame reaches 176 bytes, but excludes any other headers or independent root dissemination.

## Threat model and qualification limits

The demonstration has no signed Merkle wire protocol; these sizes describe a proposed serialisation. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Browser lesson](../../courses/maths-for-ai/lessons/295-calculate-a-proof-size-with-metadata.html)
- [Course study route](../../courses/maths-for-ai/merkle-and-consensus-mathematics.html)
- [Previous lesson](294-count-hash-operations-for-a-merkle-batch.md)
- [Next lesson](296-derive-odd-leaf-duplication.md)

*Service to Many Leads to Greatness.*
