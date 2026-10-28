# Video script — Replayed messages, private updates and optional consensus

**Bits to Banking · Sammy Hegab · Umicom Foundation**
**Companion:** Distributed Learning Lessons 031–036 · **Target:** 7 minutes

Scene one: a network transport retries a result. The coordinator already
accepted it. A safe federated job refuses a second application; idempotent
transport responses can acknowledge the duplicate without counting it again.

Scene two: a worker submits an update with a legitimate signature, valid
checksums and finite values, yet the evaluation loss becomes worse. The
lesson: cryptographic authenticity and useful learning are different claims.

Scene three: compare three privacy approaches. Local raw-data retention can
reduce direct exposure, but gradients still leak. Secure aggregation hides
individual contributions under its stated assumptions; it does not by itself
stop poisoning. A public audit ledger should store only approved commitments
and decisions, not protected gradients or financial records.

Storyboard: Two diagrams, *single-owner signed record-chain* and *multi-party
consensus*. A chain of hashes does not become independent consensus merely
because someone calls it blockchain. Learners explain when disputes between
independent administrators could justify a more expensive consensus process.

Capstone: Show three synthetic workers, a bounded result frame, checksum
rejection and a sample-weighted aggregate of +0.029. Finish with untested
boxes for actual training, TLS/network identity, convergence and security.
