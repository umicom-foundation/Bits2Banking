# Mathematics for AI — Lesson 299: Distinguish collision probability from random-guess success

**Bits to Banking · Umicom Foundation**  
**Author:** Sammy Hegab · **Language:** UK English · **Licence:** MIT  
**Study level:** Intermediate; review earlier foundational course units as needed.

## Learning outcome

Explain **distinguish collision probability from random-guess success** and defend the stated trust model, numerical assumptions and implementation boundary.

## The idea, in detail

A 256-bit ideal hash has 2^256 possible outputs. For q independent random inputs, the birthday approximation for at least one collision is roughly q(q−1)/(2×2^256) when q is much smaller than 2^128. This is distinct from preimage search against one target, where random success per trial is 2^−256. Cryptographic hash designs must also resist more structured attacks.

## Step-by-step worked example

For q=2^32 random inputs, approximate collision probability=2^64/(2×2^256)≈2^−193, an extremely small idealised number.

## Practical task

Explain why SHA-256 root identity should not be described as absolute impossibility of collision.

### Worked answer and reasoning

Security rests on computational assumptions; the probability model is an idealisation and does not prove an implementation has no bugs.

## Threat model and qualification limits

Input privacy, membership and signer identity are separate from collision resistance. For an independently verifiable experiment, specify the input source, exact protocol encoding, model/dataset provenance when applicable, expected root or checkpoint, authorised participant set and tests for altered data. Mark unexecuted network or training tests explicitly.

## Connection to the native Umicom platform

The reusable C23 implementation is owned by Umicom Framework. Its existing SHA-256 and ordered record-chain modules remain canonical; the optional `umicom_record_chain_merkle_*` member-proof service produces bounded local inclusion evidence. No script or second tensor engine is introduced. UI applications consume Framework capabilities instead of implementing their own hashes or consensus algorithms. This is not a deployed distributed ledger.

## Further reading

- [NIST Blockchain Technology Overview](https://csrc.nist.gov/pubs/ir/8202/final)

## Continue learning

- [Browser lesson](../../courses/maths-for-ai/lessons/299-estimate-random-hash-collision-probability.html)
- [Course study route](../../courses/maths-for-ai/merkle-and-consensus-mathematics.html)
- [Previous lesson](298-compare-full-digest-lists-and-membership-paths.md)
- [Next lesson](300-calculate-validator-majority-in-raft.md)

*Service to Many Leads to Greatness.*
