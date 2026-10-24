# Umicom Native LLM and Bits2Banking — Planned Roadmap After Batch 93–94

**Owner:** Umicom Foundation · **Author:** Sammy Hegab · **Planning status:** proposed, subject to acceptance tests · **Language policy:** C23 and Assembly; other languages only with explicit approval.

## Engineering batches and planned course lessons

| Batch | Framework milestone | LLM lessons | Maths units | Video scripts | Acceptance gate |
|---|---|---|---|---|---|
| **95–96** | Run real production tape suite in Windows UCRT64 and Linux; close genuine failures without discarding old logic | 95 Production Tape Integration; 96 Repairing Failed Native Tests | 21 Numerical Precision; 22 Debugging Equations | 4 narrated labs | Real CTest logs, reproducible compiler and commit |
| **97–98** | Prototype separate fused rotary operation behind opt-in C ABI; no checkpoint changes | 97 Fused Operator Design; 98 Backward Parity | 23 Jacobians; 24 Gradient Accumulation | 4 | Numerical gradients and rollback parity |
| **99–100** | Measure allocations, correctness and performance against composed baseline | 99 Memory Profiling; 100 Honest Benchmarks | 25 Statistical Variation; 26 Timing Measurements | 4 | Paired benchmark with same model/seed/hardware |
| **101–102** | Specify separately identifiable training-capable RoPE decoder | 101 RoPE Decoder Architecture; 102 Tensor Shapes | 27 Matrix Calculus; 28 Neural Networks | 4 | Shape bounds, independent reference and explicit migration policy |
| **103–104** | Build and validate decoder forward-only reference | 103 Decoder Forward Pass; 104 Attention Parity | 29 Exponentials and Softmax; 30 Numerical Stability | 4 | Logits parity and finite input handling |
| **105–106** | Add bounded training using existing Framework optimisers | 105 Training a RoPE Decoder; 106 Gradient Checks | 31 Loss Functions; 32 Optimisation | 4 | All trainable gradients checked independently |
| **107–108** | New versioned checkpoint family, explicit incompatibility with learned-absolute models | 107 Safe Checkpoints; 108 Model Identity | 33 Data Encoding; 34 Checksums and Signatures | 4 | Round-trip, corruption rejection and provenance policy |
| **109–110** | Qualified incremental inference and bounded KV cache | 109 Token Generation; 110 Context Windows | 35 Relative Positions; 36 Sequence Limits | 4 | Prefix parity and correct eviction semantics |
| **111–112** | Multi-layer rollover verification and performance profiling | 111 Multi-Layer Attention; 112 Rollover Accuracy | 37 Composition; 38 Error Accumulation | 4 | Verify multi-layer context equivalence or document divergence |
| **113–114** | Framework/Studio educational tools and evidence browser integration | 113 Test Explorer; 114 Visualise Model Evidence | 39 Data Visualisation; 40 Reproducibility | 4 | Studio thin consumer, Framework sole owner |
| **115–116** | Native model packaging, distribution and safe offline inference | 115 Packaging Models; 116 Offline Deployment | 41 Model Size; 42 Memory/Latency Trade-offs | 4 | Relocatable Windows launcher and signed distribution gate |
| **117–118** | Comprehensive developer documentation and course navigation integration | 117 Complete Native LLM Capstone; 118 Production Readiness Checklist | 43 Review and Practice; 44 Capstone Mathematics | 4 | Real end-to-end tests and full accessible navigation |

## Core engineering rules

- Each planned batch is a proposal, **not a claim of implemented functionality**. Prioritise genuine integration failures before expanding scope.
- Framework owns reusable behaviour, models, maths, persistence and build/test services. Applications remain thin.
- Preserve superseded code and comments, public function names, headers and licences; no implicit deletion or rewrite.
- Checkpoint families must never be silently reinterpreted.
- Independent numerical oracles and real production builds precede speed claims.
- Full-file releases retain exact `Umicom-Applications/framework` and `Umicom-Bits2Banking/content` directories for Beyond Compare.

## Learning content policy

Each lesson includes (a) purpose and real-world application, (b) prerequired concepts, (c) symbol-by-symbol explanations, (d) worked arithmetic, (e) C23 implementation or test walkthrough, (f) exercises with answers, (g) companion mathematics links, and (h) matching HTML, Markdown and recorded-video-ready narration scripts. Video scripts are textual production assets; they are **not** finished recordings.

## Next immediate acceptance condition

Run `framework.ai.training.rotary_real_tape_*` with the full production library under supported Windows UCRT64 and a suitable sanitiser-capable environment. Save actual test reports. Only after pass/fail evidence is available should any fused rotary implementation be approved.
