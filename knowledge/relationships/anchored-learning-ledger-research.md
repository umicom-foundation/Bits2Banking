# Relations: anchored federated learning evidence and distributed ledger foundations

The following cross-topic relationships help learners follow prerequisites without confusing different guarantees.

| First concept | Related concept | Technical distinction |
|---|---|---|
| Canonical SHA-256 and binary fields | Merkle leaf and batch root | Domain separation and count binding make precise byte commitments, not signatures. |
| Merkle inclusion | Record-chain checkpoint | Inclusion covers one leaf; predecessor links and an independently trusted tip cover the ordered history. |
| HMAC and signed receipts | Identity and authorisation | Key possession alone is not legal permission to use a private dataset. |
| Local FedAvg delta | Held-out evaluation | A weighted mean of valid numbers is not a promise of model improvement. |
| Permissioned replicated log | Crash-fault consensus | Log copies do not select a unique leader or safe commit rule by themselves. |
| Crash-fault majority | Byzantine quorum | Vote counts and overlapping sets must be interpreted under different fault models. |
| Ledger consensus | Financial settlement and AI deployment | An ordered final statement does not establish that a payment settled or that a model is suitable to deploy. |
| Model source metadata | Distributed learning | Federated privacy limits raw data movement but does not ensure gradients are private. |

**Primary source catalogue:** `knowledge/sources/blockchain-ledgers/` and `knowledge/sources/distributed-learning/`. The corresponding public lessons provide worked numerical examples and negative tests. This map describes educational relationships, not completed production integration.
