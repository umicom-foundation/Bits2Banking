# Video script — Replay protection, blockchain boundaries and a reproducible capstone

**Bits to Banking · Sammy Hegab · Umicom Foundation**
**Companion:** LLM Lessons 418–424 · **Target:** 7 minutes

Start with two incoming result messages bearing the same public correlation.
Narration: Distributed delivery can repeat a message when acknowledgements
are lost. The *transport packet identifier* might change, but the original
worker's contribution must count only once. An internal generation-stamped
job ticket closes after successful completion; a repeat must not advance the
FedAvg sum.

Visual: A counter initially `accepted=1`. Three identical arrows reach the
coordinator. Two return `already completed` while the accepted counter stays
one. Show a different arrow carrying an old checkpoint SHA and mark it stale.

Next show a ledger diagram. Narration: A blockchain is not a GPU or training
algorithm. It may help several administrators agree on an ordered set of
commitments and decisions. It must not carry private datasets, model tensors
or live gradients. A digest is not encryption; a signature is not a
proof of improved loss. Only an independent evaluator can measure usefulness.

Worked maths: For 4,096 FP32 elements, the wire payload is 16,384 bytes;
framing adds 216 bytes, giving 16,600 bytes. On a theoretical 10 Mbps link,
raw serialisation takes at least 13.28 milliseconds, not counting RTT,
cryptography, transport headers or queueing.

Capstone storyboard: Run a native C23 codec test, corrupt a frame, execute
separate coordinator/worker processes, verify synthetic +0.029, record one
rejected duplicate. End with an evidence table: structural validity passed,
local process exchange passed, remote identity untested, neural learning
not run, independent model quality not evaluated.

Conclude: Good science describes the boundary of what has been shown.
