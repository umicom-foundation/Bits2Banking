# Native federated-learning wire protocol — concepts, formats and threats

**Umicom Foundation · Research learning source · 2026**

The educational schema-one wire format is a concrete case study of portable
native messaging, not a standardised public banking or Internet protocol. Its
invariants are specified in the Framework-owned document
`learning/native-ai-federated-wire/WIRE_FORMAT.md`.

## Layers and the security property each can demonstrate

| Layer | Observable result | Not established |
| --- | --- | --- |
| Canonical byte layout | Same semantic fields represented without native padding/pointers | Peer authorisation |
| SHA-256 trailer | Accidental change is detectable when the expected digest is known | Malicious forgery resistance or a trusted signer |
| Typed Framework message envelope | Existing routing/ownership metadata is available | Transport encryption or durable delivery by itself |
| FederatedJob admission | Approved-by-caller worker ID and round metadata are matched | That the caller's authorisation was correct |
| Numeric FederatedRound | Finite weight-space delta with correct limits enters weighted average | That any model improved |
| Held-out evaluator (future integration) | Empirical quality on a locked benchmark | Proof that every training step was honestly computed |
| Independent ledger consensus (optional) | Multi-party agreement under a stated threat model | That off-chain tensor computation was truthful |

## Adversarial fixtures to reproduce

1. Truncated frame: reject before reading offset outside the source.
2. Wrong version or kind: reject rather than applying a guessed interpretation.
3. Checksum mismatch: preserve the destination and numeric round state.
4. Recomputed checksum on malicious content: demonstrate why identity signing
   must be a separately verified policy.
5. Incorrect checkpoint/shard/round/sequence: reject the stale contribution.
6. NaN, infinity and excessive vector length: reject before using arithmetic.
7. Duplicate result: maintain one accepted contributor even after retries.
8. A harmful but bounded signed update: admit that cryptography alone cannot
   demonstrate usefulness.

## Reading

- McMahan et al., *Communication-Efficient Learning of Deep Networks from Decentralized Data*, AISTATS 2017: https://proceedings.mlr.press/v54/mcmahan17a.html
- Bonawitz et al., *Practical Secure Aggregation for Privacy-Preserving Machine Learning*, CCS 2017: https://research.google/pubs/practical-secure-aggregation-for-privacy-preserving-machine-learning/
- PoLe, *Proof of Learning*: https://arxiv.org/abs/2007.15145

Always separate a proposed security improvement from an experimentally verified
one. A local-file process experiment is not a secure WAN connection.
