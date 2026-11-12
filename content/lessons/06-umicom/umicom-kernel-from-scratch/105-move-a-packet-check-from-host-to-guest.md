<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/105-move-a-packet-check-from-host-to-guest.md

PURPOSE:
Move a packet check from host to guest

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Move a packet check from host to guest

## Preparation and outcome

Complete the packet-admission lessons and build the hosted network_packet tests. Prepare the documented RISC-V Clang and QEMU toolchain for Umicom Kernel. You will now run the same production reader inside the diagnostic Kernel rather than a hosted C executable. Keep these evidence types distinct.

## Three complementary observations

A hosted test provides convenient arrays, assertions and diagnostics. A freestanding link check proves that the chosen object files resolve without a hosted runtime. A guest test actually executes the linked code under the Kernel's architecture and startup environment. Passing any one of these does not automatically establish the others.

The guest acceptance function uses the real UmicomKernelEthernetIpv4Read entry point. Its fixed capture vector is synthetic. Protocol 17 in the header does not make its payload a valid UDP message. No network card or receive queue is involved.

## Follow the lifetime

The function creates a bounded RAM frame and an aligned output structure. It verifies a valid capture, then asks the reader to handle every shorter prefix. Before each refused call, the output is filled with a sentinel pattern; afterward, every output byte must still match. This observes failure publication, not merely a returned status.

The padding case extends the capture to 60 bytes while keeping the IP total length unchanged. The expected payload remains 12 bytes. The unaligned case places the capture one byte after an aligned array start. The parser must read bytes rather than assume aligned wire words.

Finally, the metadata-lifetime case changes the input source address after admission. The returned address must retain the copied value. Payload offsets still refer to the original capture, so this does not grant ownership of those payload bytes. A future receive-buffer owner must keep that storage valid until its consumer finishes.

## Build, then execute

From the Kernel checkout, after the documented cross-build configuration:

~~~powershell
cmake --build build/riscv64-clang-debug --target umicom-kernel-evidence --parallel 2
ctest --test-dir build/riscv64-clang-debug -R "^kernel[.](qualification[.]identity|riscv64[.]packet_admission)$" --output-on-failure --no-tests=error
~~~

Use your configured directory if it has another name. Stop on a build error. The expected guest transcript contains packet-admission.cases=7 and UMICOM_KERNEL_PACKET_ADMISSION_READY, followed eventually by UMICOM_KERNEL_END. The CTest fixture can add a current-image build check; seven guest groups are not seven independently selected CTest entries.

## Exercise and recovery

Trace which cases should return LENGTH, CHECKSUM or UNSUPPORTED. Explain why none requires a NIC. If a case fails, retain the transcript and image identity, compare the fixed bytes with the host fixture and inspect the reported reason. Do not broaden the supported packet profile to make the fixture pass.

Normal startup returns through its established boot path before the diagnostic acceptance sequence. Confirm that separation in main.c. This work adds evidence for the bounded reader; NIC queue pressure, DMA ownership, shutdown, ARP and actual network traffic remain separate implementation and qualification tasks.

[Course contents](index.md) · [Previous lesson](104-separate-parser-evidence-from-network-readiness.md) · [Next lesson](106-require-a-complete-guest-test-transcript.md)
