# Federated-learning provenance and evidence boundaries

**Authors:** Sammy Hegab / Umicom Foundation · **Licence:** MIT

- [FedAvg](https://arxiv.org/abs/1602.05629): model aggregation is numerical optimisation and requires matching worker/base assumptions.
- [Low-Rank Adaptation](https://arxiv.org/abs/2106.09685): trainable low-rank factors reduce update size; averaging factors independently is not generally averaging their weight-space products.
- [Secure aggregation](https://arxiv.org/abs/1611.04482): a threat-modelled collective privacy service can conceal individual updates, but it does not by itself prove model quality.
- [NIST blockchain overview](https://csrc.nist.gov/pubs/ir/8202/final): a ledger can record evidence, but training quality is a separate statistical evaluation problem.

A Merkle proof demonstrates membership in a known committed set under hash assumptions. HMAC or digital signatures address authentication under separate keys. Independently held-out evaluation addresses useful learning. One passing check must not be used as a substitute for the others. Never put client, patient or licensed dataset content on a shared public ledger.
