# Open research questions and reproducible baselines

**Umicom Foundation · Sammy Hegab**

## Focused research directions

1. **Low-rank aggregation correctness:** Does rank-aware compression preserve held-out quality better than naive factor averaging at matched communication budgets? Baselines: FedAvg over actual weight deltas, IJCAI FedLoRA, SDFLoRA.
2. **Heterogeneous scheduling:** Under which RTT, bandwidth and client-speed regimes does adaptive job scheduling improve time-to-target loss versus constant schedules, DiLoCo and GeoMesh?
3. **Useful-work verification:** Can a reproducible challenge scheme lower accepted-malicious-update rate at a fixed verification-cost budget versus random sampling and full replay?
4. **Provenance governance:** Which threat model actually requires multi-administrator consensus rather than an append-only signed Framework receipt log?
5. **Data rights and privacy:** Which legally admitted synthetic and authorised datasets support measurable gains without leaking sensitive worker data through gradients?
6. **C23 / RISC-V optimisation:** Can optional SIMD micro-kernels outperform a portable C23 reference under strict numeric parity, total-energy and end-to-end timing constraints?

## Universal acceptance and falsification requirements

Each claim must identify the pinned checkpoint, tokenizer, dataset split, optimiser, worker count, hardware, seed, numeric precision, training-token budget, network topology, RTT, bytes transmitted, source revision and independent evaluation. Report negative or failed experiments. Do not publish a blockchain token, reward mechanism or claims of permissionless model training based on the in-process job-admission demo.
