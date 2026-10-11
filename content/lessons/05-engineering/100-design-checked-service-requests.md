# 100. Design a checked service request in C23

Applications request services because they are not supposed to control every resource directly. A useful service interface therefore needs more than a function name. It needs a clear description of accepted input, caller authority, available capacity, results and what happens when an operation fails.

Our example is a small fictional Notes service. It supports a read-only query for a training clock and an operation that records a bounded event such as `Notes document saved`.

## 1. Separate request, service state and reply

Open the header in the [syscall-dispatch laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/syscall-dispatch):

```c
BtbServiceStatus BtbServiceDispatch(
    BtbServiceState *state,
    const BtbServiceRequest *request,
    BtbServiceReply *reply);
```

Three objects are kept separate. `state` is controlled by the service; `request` describes what the caller wants; and `reply` holds an accepted result. An operation can refuse a request without writing into the reply or changing the state.

The request includes a caller number, an operation, a claimed right, an expected revision and an optional byte span. These fields are intentionally visible for a teaching exercise.

A production kernel must **not** trust the caller number or rights fields as self-authenticating. It derives the caller from the current task and resolves live handles through its own protected records.

## 2. A read-only request

The `GET_TICKS` operation reads the fictional service clock and copies its value into the reply. It does not modify the service, so it needs no event-publishing right. In a real operating system, reading time often uses a dedicated service or shared validated interface; the details vary by platform.

Read `BtbServiceDispatch` in `dispatch.c` to see that a request containing unexpected input bytes is refused before returning the tick value.

## 3. A state-changing request

The `PUBLISH_EVENT` operation has several independent checks:

1. The request uses a recognised operation and a valid caller value.
2. The caller has the required teaching right.
3. The supplied revision still matches the service's current revision.
4. The event is 1–47 printable ASCII bytes, without a hidden newline or terminator counted as content.
5. The service has another free event slot and its revision can advance.

Only after these checks does the service copy the new event, increase the count and return the updated revision.

An operation that *changes nothing when refused* is called **failure-atomic**. The effect is not the same as a database transaction covering several machines, but the principle is valuable: validate first, publish a complete update, report what happened.

## 4. Build the example

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\syscall-dispatch" -B ".\output\learning-build\syscall-dispatch" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\syscall-dispatch" --parallel 2
ctest --test-dir ".\output\learning-build\syscall-dispatch" --output-on-failure
& ".\output\learning-build\syscall-dispatch\btb-service-dispatch.exe"
```

The demonstration prints a training tick counter and a single accepted Notes event. The tests check denials, stale versions, invalid bytes and full storage.

## 5. Understand the missing hardware boundary

The laboratory makes a **normal C function call**, not a real system call. There is no trap handler, processor privilege transition, address-space change or kernel-verified handle. Source code under `asm/ecall_riscv64.S` shows the RISC-V `ecall` instruction, but intentionally does not invent a Umicom Kernel syscall number.

A real service must additionally validate user virtual memory, copy data into kernel-owned storage and make sure the request cannot nominate another caller's identity. See the actual [Umicom Kernel message service](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/message_service.c) and [user-memory validation](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_memory.c).

## 6. Extend the laboratory

Increase the maximum number of event slots from four to six, rebuild and update the capacity test accordingly. Add an invalid call number and confirm that it does not modify either output or service state. Finally, explain why a service should not increment its revision before validating the full request.

Next: [study IPC ownership in Umicom Kernel](../06-umicom/101-follow-umicom-kernel-ipc-ownership.md).
