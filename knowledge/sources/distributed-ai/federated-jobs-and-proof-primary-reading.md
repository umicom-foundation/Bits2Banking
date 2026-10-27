# Primary reading — federated job admission and verifiable AI

**Bits to Banking · Umicom Foundation · Authors: Sammy Hegab**

These are independently authored teaching summaries of primary work; research citations identify external publications, not permission to copy their training data or code into Umicom. Research approaches are distinct from capabilities already implemented in native Framework.

| Theme | Primary source | Learning implication |
| --- | --- | --- |
| Sample-weighted model aggregation | [FedAvg, McMahan et al.](https://proceedings.mlr.press/v54/mcmahan17a.html) | Worker datasets must share a model ancestry and a declared weighting objective. |
| Communication-efficient learning | [DiLoCo](https://arxiv.org/abs/2311.08105) | Compare local-step cadence under equal tokens and independent quality criteria. |
| Efficient adapters | [LoRA](https://arxiv.org/abs/2106.09685) | Weight-space products, not arbitrary factor coordinates, are comparable. |
| Federated LoRA | [IJCAI 2025 survey](https://ijcai.org/proceedings/2025/1196) | Prior art must be considered before a new aggregation claim. |
| Variable-rank federation | [SDFLoRA (IJCAI 2026)](https://ijcai.org/proceedings/2026/533) | Heterogeneous client rank is not solved by naive A/B averaging. |
| Heterogeneous WAN | [GeoMesh (Findings EMNLP 2026)](https://aclanthology.org/2026.findings-emnlp.720/) | Bandwidth and speed-aware scheduling require strong baselines. |
| Protected updates | [Bonawitz et al. secure aggregation](https://arxiv.org/abs/1611.04482) | Hidden individual updates conflict with naive per-client inspection. |
| Computational verification | [Proof of Learning](https://arxiv.org/abs/2007.15145) | Hash identity and useful training verification are different claims. |
| Critical blockchain review | [Can Blockchains Reliably Train ML Models?](https://arxiv.org/abs/2307.07066) | Consensus adds security assumptions and overhead; compare append-only logs. |
| Public replay/audit | [Gensyn OPEN-1B](https://open1b.gensyn.ai/) | Define what computation replay actually proves. |

## Methods to reproduce, not assertions to repeat

Start with one synthetic three-worker round and one shared initial parameter vector. Test exact arithmetic, identity and failure-atomic rejection. Next repeat with a held-out dataset and genuinely trained local models before studying signed transport, WAN conditions or blockchain. Distinguish simulated from observed and never treat a user-provided digest as a proof of computation.
