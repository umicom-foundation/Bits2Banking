# Verifiable learning versus a blockchain — annotated primary reading

**Umicom Foundation · Public research study notes · 2026**

A learning network is not automatically more secure, private or useful because
its receipts are hash-linked. Read these approaches with a precise claim model:

1. **FedAvg** — McMahan et al., AISTATS 2017. Establishes local training and
   weighted aggregation over heterogeneous data. https://proceedings.mlr.press/v54/mcmahan17a.html
2. **DiLoCo** — Douillard et al., 2023/2024. Studies less frequent communication
   between learning islands. https://arxiv.org/abs/2311.08105
3. **LoRA** — Hu et al., 2021. Model adaptation through low-rank factors; this
   does not justify averaging factor matrices independently.
   https://arxiv.org/abs/2106.09685
4. **Secure aggregation** — Bonawitz et al., 2017. A protocol for aggregating
   inputs while limiting visibility of individuals under explicit threat and
   dropout assumptions. https://research.google/pubs/practical-secure-aggregation-for-privacy-preserving-machine-learning/
5. **Proof of Learning** — 2020 research. Explores linking computation and
   verification but not a universal, cheap proof of improved gradients.
   https://arxiv.org/abs/2007.15145
6. **Systematisation of blockchain-based decentralised AI** — architecture
   and verification limitations. https://arxiv.org/abs/2411.17461
7. **GeoMesh** — Findings EMNLP 2026. Strong comparator for heterogeneous
   geographical communication/scheduling. https://aclanthology.org/2026.findings-emnlp.720/

## Distinguish four statements

- “The bytes match a SHA-256 commitment”: a content-integrity statement.
- “A trusted key signed the receipt”: a key-bound authenticity statement.
- “A challenge replicated part of training”: evidence about that challenged
  computation under the replay protocol's assumptions.
- “The checkpoint is better”: an independent statistical/evaluation claim.

No one statement implies the others. A public chain may be useful for multiple
administrators that cannot trust one keeper of records, but it is not the
training engine and does not eliminate adversarial data quality problems.
