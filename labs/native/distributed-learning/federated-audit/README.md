# Native federated-audit laboratory

**Sammy Hegab · Umicom Foundation · MIT**

This course laboratory consumes the Framework C23 `UmiAiTrainingFederatedAudit*` API and its existing record-chain and SHA-256 implementation. It deliberately implements no new hash, consensus, transaction engine or model trainer.

Use CMake with `UMICOM_FRAMEWORK_SOURCE` pointing at the Framework checkout. Build, run CTest, then inspect the original source and verify that payload changes or missing records fail when checking against the independently pinned checkpoint.

The example's identities and digests are synthetic, so it does not claim a genuine signed contribution, trusted network or model-quality improvement. See the Blockchain Technology course and NISTIR 8202 for the conceptual boundaries.
