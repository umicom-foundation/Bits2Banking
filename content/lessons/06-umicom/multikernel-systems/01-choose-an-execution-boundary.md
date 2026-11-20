<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/multikernel-systems/01-choose-an-execution-boundary.md

PURPOSE:
Choose an execution boundary based on workload requirements and the failures it can contain.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original learning material.
-->

# Choose an execution boundary

<p class="umicom-course-artwork"><span class="umicom-brand-mark"><img src="../../../assets/branding/umicom-wordmark.svg" alt="Umicom" width="180"></span> <a href="../../../assets/branding/umicom.ico"><img src="../../../assets/branding/umicom-icon.svg" alt="Umicom icon" width="30"></a></p>

An execution domain is an environment with a stated responsibility for running work and using resources. Start by asking what can fail, who can stop it, and which other workloads must keep running. These questions help choose a process, a virtual machine or a native research instance.

## Recognise the boundaries

| Choice | Who owns protection | What you can observe |
| --- | --- | --- |
| Supervised Linux process | The host kernel owns process memory, scheduling and device access. | The supervisor can observe the child’s exit. A host kernel or shared device failure can affect other children. |
| Virtual machine | A hypervisor runs a guest that has its own kernel and claims a defined set of virtual resources. | A guest failure can have a smaller scope than a host failure. Shared devices, the host and the supervisor still matter. |
| Native research kernel instance | Boot, memory and device ownership depend on the platform and any enforcing monitor. | A second CPU starts independently only if the bootstrap, memory and interrupt ownership have been established. |

A **multikernel** coordinates operating-system work across kernel instances. Barrelfish is an example that makes cross-core communication explicit. Running an emulated guest alongside Linux introduces a second kernel and gives a controlled place to practise service requests. An AI compute kernel is a routine such as matrix multiplication. Keep that use of the word separate when discussing architecture.

## Practise with a workload

1. Write down three jobs. Use an editor, an image-generation worker and a short integer transform.
2. For each job, state one failure and one requirement. An editor should keep responding when an image job fails. A native research endpoint should preserve the identity of each completed request after restart.
3. Choose the simplest environment that can meet each requirement. Give the editor and image generator independently supervised processes first. Use one emulated guest to study the native endpoint.
4. Record what would change your choice. A requirement to verify a guest memory boundary calls for hypervisor evidence. A shared driver reset can still stop otherwise independent workers.

The Umicom OS decision register records the GNU Linux-libre production direction. The diskless foundation documents a Linux build recipe that can be checked independently. Record the actual recipe, firmware and provider before claiming a free-system profile. [Umicom Kernel decision register](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/DECISION_REGISTER.md) · [Umicom OS architecture](https://github.com/umicom-foundation/umicom-os/blob/main/docs/foundation/architecture.md) · [The Multikernel paper](https://people.inf.ethz.ch/troscoe/pubs/sosp09-barrelfish.pdf)
