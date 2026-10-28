# Video script — Typed messages, real processes, synthetic contributions

**Bits to Banking · Sammy Hegab · Umicom Foundation**
**Companion:** LLM Lessons 413–417 · **Target:** 6 minutes

## Scene 1 — A shared Framework boundary

Narration: Umicom Framework already defines `UmiMessageEnvelope`,
`UmiAiTrainingFederatedJob` and `UmiAiTrainingFederatedRound`. We should
compose them. One component encodes a bounded learning message; another owns
job tickets and numerical aggregation; the message bus owns routing and
storage. An application should be a thin consumer of these contracts.

Visual: Three labelled boxes: *Framework codec*, *Framework messaging*,
*Framework federated job*. An Umicom LLM window appears above as a read-only
client, not a duplicate parser.

## Scene 2 — Failure atomicity

Narration: A robust decoder must reject a truncated frame before accessing
nonexistent bytes. It must refuse NaN and infinity, unsupported versions and
bad digests. More importantly, it must not change a previously valid caller
output merely because some early fields happened to parse successfully.

Visual: Show a numeric output initially `-99`. Flip one byte in the frame.
A red *REJECT* appears while the output remains `-99`.

## Scene 3 — Three distinct operating-system processes

Narration: A coordinator writes three assignment files. Each worker runs as a
separate native process and returns a checksum-protected **synthetic** scalar:
+0.05, −0.01 and +0.08. The coordinator checks the round, public sequence,
worker, base checkpoint, dataset commitment and policy, then delegates
aggregation to the existing Framework service.

Display: `100×0.05 + 250×(−0.01) + 150×0.08 = 14.5`, divided by 500 gives
`+0.029`.

## Scene 4 — What it does not prove

Narration: These worker processes did not actually learn; they generated
fixed example values. The exchange was through local files, not an
authenticated WAN. A valid result is not permission to release a checkpoint.

Final challenge: What independent quality experiment would be needed after
replacing synthetic values with actual local training updates?
