# Relationship map — authenticated distributed training

## Concept → lesson → Framework component

| Concept | Canonical lesson | Reused Framework component | Claim boundary |
|---|---|---|---|
| HMAC | 426 | `security/hmac_sha256` + `base/sha256` | Keyed integrity, not encryption |
| Portable frames | 429 | `ai/training/federated_wire` | Parsing, not worker authority |
| Authenticated wrapper | 430 | `ai/training/federated_authenticated_frame` | Message tag, not legal data rights |
| Message ownership | 432 | `messaging/message.h` | Safe lifetime, not delivery assurance |
| Assignment completion | 434 | `ai/training/federated_job` | Process-local ticket replay, not durable replay |
| Aggregation | 437 | `ai/training/federated_round` | Weighted numerical mean, not generalisation |
| Ledger and proof | 438 | record-chain and trust components for research | Not a deployed consensus protocol |

All research examples use synthetic contributor and dataset identities.
