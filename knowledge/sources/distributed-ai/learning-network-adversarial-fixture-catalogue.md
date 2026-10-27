# Federated-learning adversarial fixture catalogue

**Bits to Banking · Umicom Foundation · Synthetic public fixtures only**

| Scenario | Synthetic input | Correct bounded behaviour | Evidence still missing |
| --- | --- | --- | --- |
| Shared base | A/B/C all labelled checkpoint D | Admit only reviewed identities | Was D truly used for training? |
| Wrong base | B reports checkpoint E while round expects D | Reject before aggregator | Identity origin/trusted key |
| Wrong data policy | Shard policy Q rather than P | Reject admission | Independent licence review |
| Duplicate contribution | Worker A sends the same update twice | Count once | Network-level durable idempotency |
| Non-finite value | Delta contains NaN or infinity | Reject without state change | Whether a claimed run was genuine |
| Oversized norm | Delta (3,4) under norm threshold 2.5 | Reject in reject-only policy | Directional poisoning |
| Over-reservation | Pending 50 KiB + requested 50 KiB, cap 96 KiB | Refuse request | Actual transport bytes |
| Cancellation | Ticket cancelled after assignment | Free declared outstanding bytes once | Lost-ack/restart behaviour |
| Replayed ticket | Old job slot/serial reused | Reject locally | Authenticated remote identity |
| Non-IID mixture | A:90/10, B:10/90 domain composition | Evaluate per-domain and global loss | Practical robustness on real models |

Do not embed actual customer, medical, proprietary or identifiable training records into a public fixture. For every attempted test, record whether it is isolated, full SDK, live LAN or simulation.
