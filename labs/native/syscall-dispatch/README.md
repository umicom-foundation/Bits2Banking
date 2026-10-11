# Model a system-call service in C23

A system call is a controlled request from less-privileged code to an operating-system service. This laboratory keeps both caller and service **inside one hosted application** so you can observe request validation without privilege transitions, hardware traps or access to protected memory.

## Build on Windows

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\syscall-dispatch" -B ".\output\learning-build\syscall-dispatch" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\syscall-dispatch" --parallel 2
ctest --test-dir ".\output\learning-build\syscall-dispatch" --output-on-failure
& ".\output\learning-build\syscall-dispatch\btb-service-dispatch.exe"
```

Expect `Training service ticks: 125` and `Training events: 1; revision: 2`. The two CTest cases check permission denial, stale revision refusal, capacity limits, copied text and read-only queries.

## Follow the source

`dispatch.h` describes a request as an operation, a claimed caller, rights, a revision and a length-bounded input. `dispatch.c` validates before changing the simulated service. In a real kernel, the caller identity and rights **cannot be trusted from the request**: the kernel derives them from the scheduler's current task, a live handle and its own object tables. Likewise, a pointer from user space must be checked and copied through kernel-owned memory services.

The RISC-V `asm/ecall_riscv64.S` file is a **source-reading example only**. Its environment-call instruction is not built into the hosted programme, and it is not a callable Umicom Kernel interface until a real ABI wrapper has been designed and tested.

Read [Umicom Kernel's message service](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/message_service.c), [user-memory checks](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_memory.c) and [user IPC waiting](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_ipc.c) alongside the laboratory.
