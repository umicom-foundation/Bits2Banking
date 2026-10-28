# Native C23 laboratory: anchored federated learning evidence

This practical laboratory consumes the existing Umicom Framework SHA-256, record-chain and Merkle APIs together with `UmiAiTrainingFederatedEvidenceAnchorCommit`, `Prove` and `Verify`. It demonstrates a **synthetic** training round with four submitted but three accepted receipt commitments. It is deliberately not a new consensus network, signer, optimiser, identity service or standalone hashing engine.

The record contains a fixed 160-byte canonical summary (round ID, submitted/accepted counts, base model commitment, data-policy commitment, held-out evaluation commitment and Merkle root). The independently retained prior checkpoint and expected tip are the verifier's trust boundary. The test alters one included digest and confirms rejection. Run the source using an installed or existing Framework checkout containing the new API; the CMake project compiles the same Framework source, without copying implementations into the educational repository.

## Exercises

1. Change the selected receipt index to zero and recompute the proof. Observe that the leaf's commitment changes while the batch root does not.
2. Alter an accepted digest after anchoring. Explain why generating a new root would not validate against the independently held expected checkpoint.
3. Distinguish why `submittedCount=4` and `acceptedCount=3` does not independently prove that all four participants trained or were legally authorised.
4. Explain what a consortium would need to add before the phrase *permissioned blockchain finality* becomes accurate.

**Author:** Sammy Hegab · **Organisation:** Umicom Foundation · **Licence:** MIT
