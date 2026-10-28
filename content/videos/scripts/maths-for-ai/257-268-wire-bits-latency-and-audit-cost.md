# Video script — Mathematics of federated messages

**Bits to Banking · Sammy Hegab · Umicom Foundation**
**Companion:** Mathematics Units 257–268 · **Target:** 8 minutes

Begin by writing three numbers: `184`, `4×n`, `32`. These are the fixed header,
FP32 payload and digest lengths in bytes. For twelve parameters calculate
`184+48+32=264` bytes. The payload is only `48/264=18.18%` of the frame.
Use a table to separate *byte size*, *number of parameters* and *memory
allocation*; they describe different things.

Next illustrate integer encoding. Put `00 00 01 00` on screen and derive 256.
Then put `3f 80 00 00` and explain why it means binary32 1.0. Briefly contrast
the finite bits with `7f 80 00 00`, positive infinity, which the parser must
reject for a model update.

Move to transfer maths. A maximum 16,600-byte result contains 132,800 bits.
At 10 Mbps, ideal serialisation time is 0.01328 seconds. Add a nominal
100 ms RTT as a separate term; do not claim a measured throughput number.

Now do FedAvg: `100×0.05 + 250×(−0.01) + 150×0.08 = 14.5`. Divide by
500 distinct samples to obtain +0.029. Emphasise that an arithmetic mean
is not an independent validation result.

For sampled challenges, show `1-(1-p)^k`: p=0.1, k=5 gives 40.951%
under independent, stationary discovery probability assumptions. Explain
that adaptive adversaries may invalidate those assumptions.

Final questions: Does a 256-bit hash authenticate a sender? Does a smaller
payload imply a faster finished training run? What fraction of training
GPU-seconds can verification consume before it becomes uneconomical? Record
specific assumptions instead of supplying universal answers.
