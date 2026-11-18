<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/124-keep-sent-bytes-until-they-are-acknowledged.md

PURPOSE:
Keep sent bytes until they are acknowledged

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Keep sent bytes until they are acknowledged

[Course contents](index.md)

## What you will learn

A computer may prepare a network message without the other computer ever receiving it. A cable can be unplugged, a packet can be lost, or a peer can stop. This lesson builds a small ownership boundary: keep the original payload until an admitted acknowledgment says that a prefix is no longer needed. You will follow four bytes, compare a send buffer with a receive buffer, read the native C interface, and run focused checks. The component is memory storage, not a working Internet connection.


## Start with words you can picture


| Word | Meaning in this lesson |
| --- | --- |
| Byte | A small integer from 0 to 255; eight bits. We use four numbered bytes so their order is visible. |
| Payload | The useful bytes a sender wants to deliver, separate from packet headers. |
| Sequence | A 32-bit position in a byte stream, not an array index. |
| Acknowledgment | A position saying which byte is expected next; earlier positions may be released after admission. |
| Outstanding | Retained bytes that have not yet been newly acknowledged. |
| Capacity | The maximum retained payload: 1024 bytes in this component. |
| Ownership | Responsibility for keeping a copy valid and deciding when it may be reused. |


## Prerequisites and workspace

1. Read the earlier lessons about arrays, pointers, TCP sequence arithmetic and owned receive storage. Review them if a term is unfamiliar.
2. Open PowerShell in your own Umicom Kernel checkout. A checkout is the folder containing the source files and their Git history.
3. Confirm that include/umicom/kernel/tcp_send_buffer.h and tests/tcp_send_buffer/CMakeLists.txt exist. If either is missing, this lesson does not match the checkout.
4. Use the compiler setup lesson to install the C compiler, CMake and Ninja. Do not paste an arbitrary compiler path from a different computer.
5. Keep this experiment in a build directory. It never needs a physical disk, administrator access, a socket or an Internet connection.


## A timeline of four bytes


| Step | Owned interval | Owned payload | What may be reused |
| --- | --- | --- | --- |
| Init at 100 | [100,100) | empty | All 1024 internal slots are available. |
| Append 10,20,30,40 | [100,104) | 10,20,30,40 | The caller input can be reused: the buffer copied it. |
| Copy from 100 | [100,104) | 10,20,30,40 | Only the output destination changes. Internal bytes remain. |
| Accept ACK 102 | [102,104) | 30,40 | The first two internal slots are cleared and available. |
| Accept ACK 104 | [104,104) | empty | All retained payload has been released. |


## Read the interval notation

The left square bracket means the first position is included. The right round bracket means the endpoint is excluded. [100,104) contains positions 100, 101, 102 and 103: four bytes. Position 104 is the next position, not another stored byte. ACK 102 releases positions 100 and 101 because 102 is the next byte expected. It does not mean “release byte 102 too.” Write the positions on paper before doing arithmetic.


## Why the buffer copies input

Suppose an application passes a temporary array to a function and then changes that array. Retaining only its pointer would make future retry data change unexpectedly. Append copies the bytes into storage inside UmicomTcpSendBuffer. After success the caller may reuse its input, but the buffer still contains the original values. This is a deliberate memory cost with a fixed upper bound, rather than an unbounded queue or an assumption that the caller keeps data forever.


## The native contract

Place this fragment inside a function when experimenting; its return statements need a containing function. U marks an unsigned integer literal. The ampersand obtains the address of a variable so the function can write its result. Always check the returned decision before interpreting an output value.

~~~c
#include "umicom/kernel/tcp_send_buffer.h"

UmicomTcpSendBuffer sender = {0};
UmicomU8 input[4] = {10U, 20U, 30U, 40U};
UmicomU8 output[4];
UmicomU32 start = 0U, count = 0U;

if (UmicomKernelTcpSendInit(&sender, 100U) != UMICOM_TCP_SEQUENCE_ACCEPT)
    return 1;
if (UmicomKernelTcpSendAppend(&sender, input, 4U, &start) != UMICOM_TCP_SEQUENCE_ACCEPT)
    return 2;
input[0] = 99U;
if (UmicomKernelTcpSendCopy(&sender, start, output, 4U, &count) != UMICOM_TCP_SEQUENCE_ACCEPT)
    return 3;
/* output is 10,20,30,40; count is 4; start is 100. */
~~~


## One service owns sequence arithmetic

The existing UmicomTcpTransmit service already validates a bounded outstanding sequence interval. The send buffer does not invent a second set of acknowledgment rules. Append reserves on a small local candidate, copies the payload, then publishes the candidate. Acknowledge admits the new position on a candidate, clears only the released slots, then publishes the new head and sequence state. This separation keeps reusable arithmetic independent of storage and makes it possible to test each boundary.


## Copying is not consuming

Call Copy twice with the same retained sequence. Both calls should produce the same bytes and leave outstanding unchanged. A connection might use one copy for an initial packet and another for a retry. The helper does not decide whether a retry is needed and does not transmit either copy. Compare receive storage: reading received bytes consumes them because the application has accepted them. A send copy cannot make that decision for the remote peer.


## Acknowledge a prefix

A successful shorter copy leaves the unused output tail untouched. Use count, not the old array contents, to decide what belongs to the new result. Passing a future ACK or a duplicate ACK does not free anything. Real connection code must admit packet identity and protocol state before calling this arithmetic-and-storage operation.

~~~c
if (UmicomKernelTcpSendAcknowledge(&sender, 102U, &count) != UMICOM_TCP_SEQUENCE_ACCEPT)
    return 4;
/* count is 2. Retained payload is now 30,40 at positions 102,103. */
if (UmicomKernelTcpSendCopy(&sender, 102U, output, 4U, &count) != UMICOM_TCP_SEQUENCE_ACCEPT)
    return 5;
/* count is 2. Only output[0] and output[1] were written. */
~~~


## Two different circles

TCP sequence values wrap after 4,294,967,295. The fixed array wraps after slot 1023. These circles have different sizes and different jobs. Starting at sequence 4,294,967,294 and appending four bytes gives next = 2, while those four bytes can still occupy array slots 0 through 3. Later, after many appends and acknowledgments, the array head may wrap without sequence zero being involved. Tests must cover both cases independently and together.


## Full capacity is a normal state

If 1024 bytes are outstanding, Append refuses another byte. The caller should wait for a valid acknowledgment or apply a higher-level cancellation policy. Repeated Copy calls do not create space. Silently dropping the oldest bytes would break the ability to retransmit, while silently allocating a larger array would break the memory budget. A refusal is a useful result when it preserves the current stream.


## Refusal and caller responsibilities


| Situation | Expected meaning |
| --- | --- |
| Append count zero | REJECT; no payload was admitted. |
| Append more than free capacity | REJECT before reading payload. |
| Sequence length outside supported arithmetic bounds | INVALID. |
| Copy an old position or the excluded next endpoint | REJECT; output and count retain their previous values. |
| Required pointer is null or metadata is invalid | INVALID; no state publication. |
| Pointer claims more bytes than its object owns | Caller contract violation; portable C cannot prove allocation size from the pointer. |
| Two threads mutate the same owner | Caller synchronization is missing; the helper does not make races safe. |


## Run the hosted contracts

Run one line at a time from the Kernel root and stop if it fails. Configure creates a build description. Build compiles the actual production sources and the test program. CTest executes eight hosted cases. Expected outcome is eight passes, no failures and no skips. A printed test name without a successful result is not a pass.

~~~powershell
$env:Path = "C:/msys64/ucrt64/bin;$env:Path"
cmake -S tests/tcp_send_buffer -B build/tcp-send-buffer -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe
cmake --build build/tcp-send-buffer --parallel 2
ctest --test-dir build/tcp-send-buffer --output-on-failure
~~~


## Check the freestanding boundary

If Clang and LLVM’s linker are installed at these paths, this adds two checks for ten total. They link RISC-V ELF files at optimization levels O0 and O2 without a hosted C library. O0 means unoptimized; O2 enables a common optimization set. Linking can catch an accidental memcpy dependency even when a Windows test works. It does not run the RISC-V output.

~~~powershell
cmake -S tests/tcp_send_buffer -B build/tcp-send-buffer -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_SEND_CLANG=C:/msys64/ucrt64/bin/clang.exe
cmake --build build/tcp-send-buffer --parallel 2
ctest --test-dir build/tcp-send-buffer --output-on-failure
~~~


## Execute the diagnostic guest

Use the RISC-V configuration created in the earlier Kernel setup lesson. The current-image fixture and packet diagnostic must both pass. The checker requires 67 ordered groups, including four send-buffer groups, then a successful emulator exit. QEMU has no network device in this check. A result here proves the synthetic guest contract, not a working network stack.

~~~powershell
cmake --build build/riscv64-debug --target umicom-kernel --parallel 2
ctest --test-dir build/riscv64-debug -R "^kernel.riscv64.packet_admission$" --output-on-failure
~~~


## Understand the independent model

The model test keeps a plain linear queue and shifts its remaining bytes after each accepted acknowledgment. Production uses a ring; the model does not. Across three starting sequences and 12,000 operations each, the test compares intervals, free space, suffix reads and full retained contents. This independence matters: a second copy of the same ring algorithm could reproduce the same bug and falsely agree.


## Troubleshooting and experiments

1. If CMake cannot find gcc, verify the compiler path rather than reusing a cache configured for another toolchain.
2. If the linker reports an unsupported RISC-V emulation, inspect check_freestanding.cmake and confirm -fuse-ld=lld selects LLVM’s linker.
3. If a guest marker is missing, inspect packet-admission-guest.log and confirm the current image was rebuilt. Do not accept a stale executable as proof.
4. Change a local test input after Append and explain why retained output stays unchanged.
5. Predict the bytes remaining after ACK 103 in the four-byte example, then check your prediction: only 40 remains.
6. Explain why zeroing released slots is useful but does not erase every historical copy of data.
7. List the work still needed for a real connection: packet admission, peer identity, SYN/FIN state, windows, timers, retries and congestion control.


## Where this helps Umicom

A future native connection service can use this bounded owner rather than asking every application to keep ad hoc retry arrays. Studio, Media or a web server would consume a higher-level connection interface, not manipulate ring fields themselves. The current helper belongs in the Kernel because it is freestanding stream storage; the operating-system and application layers still need their own admitted integration. The lesson teaches a general principle: publish a promise only after the bytes behind that promise have a clear owner.


[Previous: Own received bytes before advancing the stream](123-own-received-bytes-before-advancing.md)

[Next: Construct a TCP capture before transmission](125-construct-a-tcp-capture-before-transmission.md)
