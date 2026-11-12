<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/106-require-a-complete-guest-test-transcript.md

PURPOSE:
Require a complete guest test transcript

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Require a complete guest test transcript

## Preparation and outcome

Run the packet guest test from the previous lesson, then open packet-admission-guest.log in its build directory. Read the corresponding check_guest.cmake wrapper. You will distinguish an early success marker from complete, current execution evidence.

## Why one marker is insufficient

A guest can print a readiness line and fail later. A previous executable can also print a familiar marker even when the edited source has never been compiled. The packet wrapper therefore combines several observations: a current-image build fixture, source/image identity checking, a successful QEMU exit, absence of failure markers and ordered completion records.

The required records begin with Kernel boot readiness. The wrapper then expects packet admission to begin, each of the seven named groups, the group count, packet readiness and the final Kernel end marker. A missing or out-of-order record causes failure. This is stronger than searching for one word such as ready anywhere in the output.

## Inspect the host-side contract

The wrapper launches the known QEMU executable with the established RISC-V machine arguments and an explicit -nic none option. It captures standard output and standard error, writes them to the configured transcript and waits at most 30 seconds. CTest supplies a larger outer timeout. A timeout is a failure, not a successful partial run.

The wrapper checks the child exit result before reading acceptance markers. Output text alone cannot prove normal completion. Conversely, exit zero does not prove that every intended case ran, which is why the ordered records are also required.

## Test definitions are inputs too

CMake generates CTest's test definitions during configuration. CTest reads those definitions when a run starts. If a fixture rebuild regenerates the files, an already running CTest process can still hold its earlier command in memory. Build or reconfigure first when changing a test command, then start a fresh CTest run.

A literal placeholder such as an unexpanded architecture-specific variable can configure successfully but still point to no executable. Inspect the generated command and verify that it contains the actual QEMU path and image path. Configuration success does not validate every later command-line argument.

## Worked review

1. Find the earliest boot marker and the later packet begin marker.
2. List the seven case names in order and explain what each proves.
3. Confirm that packet readiness appears before the final Kernel end marker.
4. Read the captured exit status in the CTest result and check for skipped or failed entries.
5. Keep the source/image identity record with this transcript, including the toolchain and virtual machine profile.

If only a prefix exists, investigate the last completed group rather than calling the whole reader verified. If the source identity is stale, rebuild before rerunning. If QEMU is missing, fix tool discovery; a host-only test is useful but cannot substitute for the missing guest observation.

## Exercise

On a copy of the transcript, remove the final marker and show why a single-marker search would still be misleading. Then reorder two case records and compare that with the wrapper's increasing-position requirement. Do not alter the original execution log. Explain why these synthetic packet records still make no claim about a live network, a hardware NIC or a complete transport protocol.

[Course contents](index.md) · [Previous lesson](105-move-a-packet-check-from-host-to-guest.md) · [Next lesson](107-separate-a-guest-runtime-from-source-grammar.md)
