# Native federated-job laboratory — three synthetic workers

**Bits to Banking · Umicom Foundation · Sammy Hegab · MIT**

This C23 classroom program calls the real Umicom Framework admission service and the real previously implemented FedAvg arithmetic owner. It implements **no** model-training algorithm, numerical aggregation copy, network communication, signatures or blockchain. All digest bytes are synthetic labels for testing interface behaviour, not actual validated content hashes.

## Learning objectives

Learn to account for a bounded round, make sure each admitted assignment is completed exactly once, observe that capacity is a *concurrent reservation* and calculate a sample-weighted update.

## Build from the existing Framework checkout

The variable `UMICOM_FRAMEWORK_SOURCE` must identify your existing local Framework root, not a second copy inside this educational lab:

```text
cmake -S . -B build -G Ninja -DBUILD_TESTING=ON -DUMICOM_FRAMEWORK_SOURCE=<existing Framework source root>
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
```

The expected synthetic mean is **+0.029000**, computed from 100×0.05, 250×−0.01 and 150×0.08 over 500 samples. In the demo, the incoming values are **precomputed illustrative updates**; they were not obtained by training a neural network.

## Independent exercises

1. Change the second worker's sample count, and predict the exact candidate delta before compiling.
2. Make the third worker’s checkpoint-label byte differ, and observe rejection before the numeric round changes.
3. Add an outstanding 20-byte assignment when 16 bytes are already reserved under a 32-byte cap; explain why the second is refused.
4. Compare a cancelled assignment with a completed worker whose delta happens to be zero.

## Security and research limitations

Workers are not authenticated here; matching 32-byte labels do not verify dataset rights, honest execution or model quality. The API is caller-serialised and its local tickets do not serve as distributed credentials. Production deployment would need reviewed transport, identity, data governance, replay/attestation where appropriate, independent held-out evaluation and an explicit release approval.
