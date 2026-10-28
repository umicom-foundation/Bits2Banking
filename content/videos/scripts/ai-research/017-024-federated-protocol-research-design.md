# Video script — Designing falsifiable research on decentralised AI

**Bits to Banking · Sammy Hegab · Umicom Foundation**
**Companion:** AI Research Frontiers Lessons 017–024 · **Target:** 8 minutes

Opening question: When can a small group of heterogeneous devices improve
one shared model more efficiently than a central baseline? Do not answer
with architecture slogans: define worker capabilities, data distributions,
communication limits and an independent target loss.

Study 1: FedAvg versus DiLoCo. Explain local steps and the outer update. A
longer local period means fewer network transfers but may increase client
drift on non-IID data. Compare matched training-token counts and report
time-to-target loss, not just messages saved.

Study 2: LoRA factor invariance. Two workers each represent ΔW=+1 with
(A,B)=(+1,+1) and (−1,−1). Naively averaging factors creates zeros and erases
the update. The mathematically meaningful baseline aggregates the effective
weight-space deltas or an equivalent provably correct representation.

Study 3: Verifiable work. A signed receipt only establishes a key-bound
statement. Challenge replay can establish evidence about selected computation,
while hidden-set evaluation measures observed usefulness. Record false
acceptance, false rejection, audit compute and the attacker model.

Study 4: Privacy. Raw data need not leave a worker to expose information;
transmitted gradients may leak. Secure aggregation, individual verification
and Byzantine robustness have distinct objectives and tensions.

Closing worksheet: Pre-register one measurable hypothesis with a baseline,
three independent seeds, a defined network topology and the strongest
counterexample that could disprove it. A negative result is a valid research
outcome when its controls and limitations are transparent.
