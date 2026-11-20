<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/multikernel-systems/05-recover-a-domain-without-losing-evidence.md

PURPOSE:
Practise draining, reconciling unknown outcomes and safely restarting a domain.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material.
-->

# Recover a domain without losing evidence

<p class="umicom-course-artwork"><span class="umicom-brand-mark"><img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom" width="180"></span> <a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="30"></a></p>

A supervisor needs to explain what happened to accepted work after the worker stops responding. A timeout means the supervisor did not receive the required response in time. The worker might have completed a storage write before the reply was lost. Record an **unknown outcome** until there is evidence of completion or refusal.

## Walk through a checkpoint write

| Event | Action | Evidence to keep |
| --- | --- | --- |
| The worker accepts write 42 | Stop admitting new jobs before a planned shutdown. | Request 42 and the current generation. |
| No result arrives before the deadline | Check the checkpoint owner’s receipt. Keep the old valid checkpoint. | Accepted work and missing response. |
| The worker reaches a safe stop | End its access and release the resources that are confirmed idle. | Stop and completion observations. |
| Resources may still be in use | Keep them reserved while the provider investigates. | Resource owner, pending access and recovery condition. |
| A replacement starts | Give it a new generation and run a probe before admission. | New peer identity and the result of reconciling request 42. |

**Draining** stops admission while accepted work progresses. **Quiescence** means the affected work and access have reached a documented safe boundary. **Quarantine** keeps uncertain resources unavailable for assignment while the supervisor checks them. For a checkpoint, keep enough information to resume from a known model state, input position and software configuration.

## Check the recovery boundary

1. Write two endings for request 42. In the first it completed before the timeout. In the second the owner can prove it never committed.
2. In the first ending, return the original outcome when the caller asks. In the second, decide whether a retry is safe under the workload contract.
3. Leave the outcome unknown for a third ending with incomplete evidence. A request identifier lets you correlate records. It does not prove that a side effect occurred only once.
4. Draw an independent recovery path for the host’s basic storage or console. Keep it usable when the normal Framework provider is unavailable.

Barrelfish/DC offers a research example of an orderly transition that retains state. Recovery after an unexpected failure needs separate evidence. [Barrelfish/DC](https://www.usenix.org/conference/osdi14/technical-sessions/presentation/zellweger) · [Umicom OS foundation](https://github.com/umicom-foundation/umicom-os/blob/main/docs/foundation/architecture.md)
