# Episode 50 — How a process opens a file safely

**Running time:** approximately 15–19 minutes  
**Companion lessons:** [147](../../lessons/05-engineering/147-process-owned-file-services.md) and [148](../../lessons/05-engineering/148-checked-file-copies-and-descriptor-lifetimes.md)  
**Source:** [process-file-services laboratory](https://github.com/umicom-foundation/Bits2Banking/tree/main/labs/native/process-file-services)

## Opening — 0:00–1:15

**On screen:** A Notes window with a filename, then a simple diagram of a process, checked adapter and VFS.

**Narration:**

> Every time we open a note, there is a chain of decisions that we usually cannot see. The application chooses a filename. The operating system checks what the application may access. The virtual filesystem identifies the storage provider. Only then can the note's contents arrive in the application.
>
> In this lesson, we will build the part between a process and a virtual filesystem. Our implementation uses ordinary C23. It does not require writing a kernel or modifying a disk, but it teaches the checks that make real file services possible.

Show the process-file-service diagram. Pause on each ownership boundary and explain how each differs from the others.

## Part 1 — 1:15–4:00: What is a process-owned descriptor?

**On screen:** Open the existing `vfs.h` and display `BtbVfsHandle`, `BtbVfsOpen` and `BtbVfsClose`.

**Narration:**

> A file descriptor is an identifier, not the address of the file or a pointer into the filesystem. The VFS can reject that identifier when it is stale, belongs to another client or lacks a required right. A descriptor can also be duplicated, in which case the two references may share one file position.
>
> We already built the VFS in the previous course. It manages the names, the open descriptions and the providers. Our new process-file service will reuse that implementation. We will not write a second filesystem just because we are adding a new application boundary.

**Demonstration:** Open `CMakeLists.txt` in the new lab and point out `add_subdirectory()` and the link to `btb_vfs`.

## Part 2 — 4:00–7:30: Check a user memory range

**On screen:** Display a fictional 512-byte memory array and highlight bytes 510 and 511.

**Narration:**

> The process is allowed to name a destination offset and the requested byte count. But a request to copy three bytes beginning at offset 510 would need byte 512. Our valid positions stop at 511.
>
> The check is not simply to add the offset and length. Adding two large unsigned numbers can overflow. Instead, check the offset first, then subtract it from the capacity and compare the remaining space with the length.

**Demonstration:** Show `BtbProcessSpan()`, then locate the boundary assertion in `test_process_files.c`.

**Question for viewers:** What should happen if the request is refused? Pause before revealing the answer: the previously accepted reply and user bytes remain unchanged.

## Part 3 — 7:30–11:30: Open and read a note

**On screen:** Open `main.c` and follow the path bytes, OPEN request and READ request.

**Narration:**

> The pathname lives inside the process's teaching buffer. The service makes a checked copy and adds the correct string terminator. If an embedded zero byte tries to conceal part of the pathname, the request is rejected.
>
> The process identity is not supplied by the request. It was selected by the trusted code that created the process-file owner. In a real kernel, identity must come from the running task context, not from any number the program chooses to write into its request.
>
> For a read, we use a small staging array. We ask the VFS to read into that array. If it accepts the operation, we copy the result to the previously checked position inside the process's buffer.

**Live terminal:**

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\process-file-services" -B ".\output\learning-build\process-file-services" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\process-file-services" --parallel 2
ctest --test-dir ".\output\learning-build\process-file-services" --output-on-failure
& ".\output\learning-build\process-file-services\btb-process-files-demo.exe"
```

**Expected screen:** `Process 11 read: Umicom Notes`.

## Part 4 — 11:30–15:45: Close without losing ownership

**On screen:** Diagram showing descriptor, open description and provider file.

**Narration:**

> Closing a descriptor does not necessarily remove a file. An open description can have other references. Likewise, removing a filename does not necessarily destroy data while a file is still open.
>
> When a process shuts down, our service closes the descriptors it owns. If a release fails, a correct service must retain the unfinished cleanup obligation. Forgetting a live descriptor would make the resource difficult to recover and might keep a filesystem mounted indefinitely.

**Demonstration:** Run the lifetime test and locate the stale-handle check. Explain why an old descriptor token may no longer name the resource that now occupies its slot.

## Closing — 15:45–19:00

**Narration:**

> Today we connected application-visible requests to a virtual filesystem without exposing provider pointers. We learnt to validate address ranges, copy pathname bytes, bind a trusted process identity and retain resources until they are properly closed.
>
> To see how these principles appear in a real research kernel, read Umicom Kernel's `kernel/user_files.c`, `kernel/user_memory.c` and `kernel/vfs.c`. Their real contracts are more demanding, but the reasons for the boundaries are the same.
>
> In the next lesson, we move from file bytes to network bytes, and build a small HTTP server in C23.

**Website reference:** [Bits2Banking lessons](https://github.com/umicom-foundation/Bits2Banking), [Umicom Kernel process-file guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/PROCESS_FILE_SERVICES.md).
