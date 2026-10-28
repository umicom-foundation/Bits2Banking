# Cryptographic membership, distributed consensus and useful learning

**Sammy Hegab / Umicom Foundation · Public educational knowledge relationship map · MIT**

| Concept | Required input | What can be concluded | What does not follow |
|---|---|---|---|
| SHA-256 digest | Defined canonical bytes | Byte commitment under hash assumptions | Authorisation or confidentiality |
| HMAC-SHA-256 | Shared secret and exact message | Message authentication to a secret holder | Publicly transferable signer identity |
| Digital signature | Verified signing key and signature | Signature was made by holder of private key | Permission to use dataset or honest training |
| Record chain | Records, predecessors and independent tip | Ordered history matches the trusted tip | Agreement between autonomous administrators |
| Merkle membership | Leaf, path, count and trusted root | Leaf digest is in a committed batch | Full append-only consistency or finality |
| Raft | Membership, protocol terms, authenticated voters | Crash-fault consensus under stated assumptions | Byzantine security |
| Byzantine consensus | Authenticated committee, message protocol, limits | Ordered agreement/finality within its model | Truth of external market or model-quality claim |
| Federated aggregation | Compatible weight-space deltas | Arithmetic weighted aggregate | Beneficial validation result |
| Held-out evaluation | Frozen trusted test corpus, agreed metrics | Observed result on tested distribution | Universal correctness or fairness |

## Relationship to existing Umicom source

The `umicom/record_chain/chain.h` ordered commitment and `umicom/base/sha256.h` digest implement the shared underlying data integrity. The optional `umicom/record_chain/merkle.h` supplies a count-bound membership proof over previously hashed records. No new digest algorithm, token chain, or financial application-local ledger is introduced. Use distinct Framework security, messaging, and AI training contracts for identity, authorisation, source admission and numerical evaluation.
