# Research-learning relationships and evidence boundaries

**Bits to Banking · Umicom Foundation** · **Author: Sammy Hegab**

| Concept | LLM lesson | Maths unit | Introductory distributed lesson | Framework/lab boundary |
|---|---|---|---|---|
| Federated versus inference | 377 | 233 | 01 | Existing inference scheduler ≠ trainer |
| Sample-weighted FedAvg | 378 | 233–234 | 03 | `UmiAiTrainingFederatedRound` arithmetic |
| Checkpoint identity | 379 | 233 | 02, 07 | Existing model identity / SHA-256 APIs |
| Client distribution drift | 380 | 238 | 04 | Held-out evaluation needed |
| Low-communication local steps | 381 | 239 | 06 | Transport not implemented in toy aggregate |
| Heterogeneous hardware | 382 | 244 | 11 | Scheduling is independent of gradient calculation |
| LoRA factor ambiguity | 383 | 235–237 | 05 | Source worker supplies weight-space delta |
| Malicious/stale submissions | 384 | 240 | 08 | Bounds/duplicates not Byzantine resilience |
| Secure sum and privacy | 385 | 242 | 08 | Cryptographic protocol not implemented |
| Proof of training claims | 386 | 241 | 10 | Receipt ≠ execution/quality proof |
| Record chain vs consensus | 387 | 243 | 09 | Existing record chain ≠ public blockchain |
| Incentives and rewards | 388 | 241, 244 | 10 | Unimplemented economics research |
| Source rights and data quality | 389 | 238 | 07 | Native source admission / independent review |
| SIMD, RISC-V, IO-aware kernels | 390 | 237 | 01 | Existing native tape and optimisers |
| Scientific methodology | 391 | 244 | 11 | Compare actual quality/time/energy |
| Three-worker research capstone | 392 | 233, 235 | 12 | `labs/native/distributed-learning/fedavg-round` |

The relationship map indexes concepts and sources for **public education**, not maintainer check-in instructions or an internal engineering roadmap.
