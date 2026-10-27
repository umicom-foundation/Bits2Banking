# Primary research and reproducibility reading list — distributed and verifiable AI

**Bits to Banking · Umicom Foundation** · **Author: Sammy Hegab** · **Research snapshot: 27 October 2026**

This annotated bibliography is learner-facing. It distinguishes peer-reviewed proceedings from unreviewed preprints, and published results from Umicom-native implementations. Paper results are the **authors’ measured configurations**, not independently replicated Umicom outcomes. The authorised dataset and checkpoint requirements apply equally to open-source and proprietary experiments.

## FedAvg — McMahan et al. (AISTATS 2017)

**Primary source:** https://proceedings.mlr.press/v54/mcmahan17a.html

Foundational sample-weighted local model averaging over decentralised data; venue AISTATS 2017. First baseline before all extra trust mechanisms.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## LoRA — Hu et al. (2021)

**Primary source:** https://arxiv.org/abs/2106.09685

Original low-rank adaptation paper. Demonstrates frozen base and B×A updates; no licence or privacy property is implied by the factorisation.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## Federated Low-Rank Adaptation Survey (IJCAI 2025)

**Primary source:** https://ijcai.org/proceedings/2025/1196

IJCAI 2025 survey of communication, aggregation discordance, data heterogeneity and LoRA rank incompatibility.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## SDFLoRA: Selective Decoupled Federated LoRA (IJCAI 2026)

**Primary source:** https://ijcai.org/proceedings/2026/533

IJCAI 2026 paper on separate shared/private low-rank components and rank heterogeneity; independent comparison required.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## DiLoCo — Douillard et al. (2023 preprint)

**Primary source:** https://arxiv.org/abs/2311.08105

Low-communication outer optimisation across accelerator islands; 2023 preprint. Carefully separate communication count from achieved held-out quality.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## OpenDiLoCo — Jaghouar et al. (2024)

**Primary source:** https://arxiv.org/abs/2407.07852

Open research implementation of DiLoCo; 2024 preprint. Useful reference for WAN worker coordination and reproducibility.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## GeoMesh: Workload-Balanced Geo-Distributed Training (Findings EMNLP 2026)

**Primary source:** https://aclanthology.org/2026.findings-emnlp.720/

Findings of EMNLP 2026 study of heterogeneous GPU scheduling and compressed low-bandwidth updates. Use only with matched evaluation controls.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## Practical Secure Aggregation — Bonawitz et al. (CCS 2017)

**Primary source:** https://research.google/pubs/practical-secure-aggregation-for-privacy-preserving-machine-learning/

CCS 2017 cryptographic protocol for secure summation under explicit dropout/threat models. Does not by itself prevent data poisoning.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## Proof of Learning (PoLe) — Lan et al. (2020)

**Primary source:** https://arxiv.org/abs/2007.15145

2020 Proof-of-Learning preprint. Example of prior art for useful-computation consensus; its assumptions differ from ordinary hash-only PoW.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## Proof-of-Learning with Incentive Security (2024 preprint)

**Primary source:** https://arxiv.org/abs/2404.09005

Incentive-security preprint. Study precisely which computation is checked and the expected challenge cost.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## SoK: Decentralized AI (DeAI) (2024 preprint)

**Primary source:** https://arxiv.org/abs/2411.17461

Decentralised-AI systematisation preprint. Provides security/governance taxonomy; not a deployable verification standard.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## INTELLECT-2 — globally distributed RL (2025 preprint)

**Primary source:** https://arxiv.org/abs/2505.07291

2025 distributed RL preprint involving heterogeneous workers; distinguish author-reported scale from independent reproduction.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## SWARM Parallelism — Ryabinin et al. (2023)

**Primary source:** https://arxiv.org/abs/2301.11913

Heterogeneous/unreliable network model parallelism research; valuable counterexample to assuming data-centre links.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## Petals — Borzunov et al. (2022/2023)

**Primary source:** https://arxiv.org/abs/2209.01188

Peer-to-peer collaborative inference and adaptation; not proof that inference traffic trains a common base model.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## QLoRA — Dettmers et al. (2023)

**Primary source:** https://arxiv.org/abs/2305.14314

Quantised frozen base with trainable LoRA adapters; distinguish weight storage from arithmetic and communication.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## FlashAttention — Dao et al. (2022)

**Primary source:** https://arxiv.org/abs/2205.14135

Exact attention accelerated through IO-aware algorithm/data movement. Separate mathematical correctness from hardware speed.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## GaLore — Zhao et al. (2024)

**Primary source:** https://arxiv.org/abs/2403.03507

Gradient low-rank projection for memory-efficient broader parameter updates; algorithm differs from LoRA adapters.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## Mamba — Gu & Dao (2023)

**Primary source:** https://arxiv.org/abs/2312.00752

Selective state-space modelling as an alternative sequence-mixer research family; do not imply native Umicom support.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## DataComp-LM — controlled data curation

**Primary source:** https://arxiv.org/abs/2406.11794

Controlled language-model data curation studies; rights, quality and held-out leakage require separate reviews.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## DeepSeek-V3 Technical Report — MoE and MLA

**Primary source:** https://arxiv.org/abs/2412.19437

Modern MoE/latent-attention architecture; sparseness and routing generate different communication constraints from FedAvg.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## Covenant-72B: Pre-Training with Trustless Peers (2026 preprint)

**Primary source:** https://arxiv.org/abs/2603.08163

2026 trustless-peer pretraining preprint; author scale and verification claims require independent scrutiny.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## Muon is Scalable for LLM Training (2025 preprint)

**Primary source:** https://arxiv.org/abs/2502.16982

2025 research preprint on matrix-aware optimiser scaling, with author-reported efficiency under declared workloads.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## SOAP: Improving and Stabilizing Shampoo using Adam (2024 preprint)

**Primary source:** https://arxiv.org/abs/2409.11321

2024 study of an optimiser combining second-moment adaptation with matrix preconditioning; preprint results need independent comparison.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## The Best Optimizer Depends on Batch Size (October 2026 preprint)

**Primary source:** https://arxiv.org/abs/2610.08975

October 2026 preprint on optimiser rankings changing with batch size; a warning against blanket optimisation claims.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## Direct Preference Optimization (2023)

**Primary source:** https://arxiv.org/abs/2305.18290

Direct preference optimisation paper; distinct from SFT and online RL.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## DeepSeekMath: GRPO and mathematical reasoning (2024)

**Primary source:** https://arxiv.org/abs/2402.03300

GRPO paper: verifiable-reward reasoning under specified training settings.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## Docling project: document extraction

**Primary source:** https://github.com/docling-project/docling

Open-source structured document extraction reference; licensing and dependencies require independent review.

**Teaching link:** The full reference is to be consulted before claiming novelty, correctness or generality beyond the published tests. No source text or model weights are reproduced here.

## Evidence vocabulary

- **[SOURCE]**: exact public page or repository checked on the recorded date; presence does not establish correctness.
- **[PAPER]**: paper-reported experiment, method or limitation; not independent replication.
- **[LESSON]**: worked toy calculation or synthetic fixture; not field deployment.
- **[PROPOSAL]**: hypothesis or prospective system boundary; not implemented by the existing service.
- **[TESTED]**: result obtained with an explicitly named test executable, compiler and environment.

Never infer from an Ed25519 signature that training gradients were honest, from a hash that a data source is licensed, or from a lower toy loss that an end-user banking application is reliable.
