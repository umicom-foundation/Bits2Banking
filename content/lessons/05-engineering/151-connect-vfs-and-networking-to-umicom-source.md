# 151. Connect file services and networking to the real Umicom projects

Our practical lessons have now built a file-service adapter and a small HTTP server. Neither exercise is a replacement for the services already being developed in the Umicom projects. They are small, testable examples of architectural ideas that appear in larger systems.

This chapter shows exactly where to continue reading the real source.

## 1. Follow file access through Umicom Kernel

Open the [Umicom Kernel repository](https://github.com/umicom-foundation/umicom-kernel) and locate these source files:

| File | Responsibility |
|---|---|
| [`include/umicom/kernel/vfs.h`](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/vfs.h) | VFS interface, descriptor records, client ownership and rights |
| [`kernel/vfs.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/vfs.c) | Checked path lookup, open descriptions and provider dispatch |
| [`kernel/ramfs.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/ramfs.c) | RAM-backed files and explicit node lifetime |
| [`kernel/fat16_provider.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/fat16_provider.c) | Checked FAT16 reads through an existing provider contract |
| [`kernel/user_files.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_files.c) | Binding file clients to admitted task lifetimes |
| [`kernel/user_memory.c`](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_memory.c) | Validating user address spans and mapping permissions |

These modules have distinct responsibilities. A VFS does not know how every filesystem stores its bytes, and a process-file service must not trust a process-supplied pointer as a kernel pointer.

## 2. Compare the two designs

Our educational `BtbProcessFiles` model uses offsets into a fixed 512-byte array. Its identity comes from the harness at initialisation. Each read copies up to 64 bytes through a local buffer.

Umicom Kernel works with actual process state and translated virtual addresses. Its file-service documentation describes copying requests through an admitted ECALL boundary, retaining a stable request, restoring the machine caller and then performing the VFS operation when the execution environment allows it.

Read [Process-owned descriptors and checked file services](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/PROCESS_FILE_SERVICES.md). Follow the sequence in its *Why the filesystem does not run inside the user trap* section.

The key point is **not** that the smaller exercise implements real syscalls. It does not. The key point is why the real design needs checks, ownership and a carefully selected execution context.

## 3. Follow the storage providers

The same VFS interface may be backed by memory or disk. Inspect the [read-only FAT16 provider guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/READ_ONLY_FILESYSTEM_PROVIDER.md) and identify the storage layers below the VFS.

```text
Application request
       |
Checked Kernel file service
       |
Virtual filesystem
       |
Filesystem provider (RAMFS or FAT16)
       |
Block transport when required (VirtIO)
       |
Device and storage
```

Each layer should own its own rules and return explicit results rather than letting an unrelated caller modify its internal state.

In particular, an ordinary read-only FAT16 provider must not silently gain write authority merely because a lower VirtIO driver supports explicit writable leases.

## 4. Follow the actual Umicom web services

Umicom Framework already has HTTP and web-service modules. Explore:

- [Framework web-server interface](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/server.h)
- [Framework static-file interface](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/static_files.h)
- [Framework local C service example](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/web/local_service.c)
- [Framework local web-service guide](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/local-web-service.html)

These Framework components provide a reusable service boundary for real Umicom applications. Their current contracts and limits should be checked against the corresponding source revision before an application relies on them.

Our `btb-http-server` is intentionally separate and narrower: only fixed local routes, no uploads or filesystem serving, no remote clients, no TLS and no application authentication. It exists so a learner can see the complete source of the network entry point.

## 5. Kernel networking is not a web server

A native operating-system kernel provides lower-level mechanisms such as address spaces, process execution, interrupts, system calls and hardware access. An HTTP server normally runs in user space above networking facilities supplied by the operating system.

Our loopback server uses Winsock on Windows or POSIX sockets on Linux. **It does not run inside Umicom Kernel.** A future native Umicom networking interface would need separate design and qualification before this exercise could use it.

The Umicom OS distribution and the original Umicom Kernel are distinct projects. The existence of a user-space Framework HTTP module does not imply that the native research Kernel already contains a production TCP/IP stack.

## 6. Explore the repository source in order

1. Read the small `BtbProcessFilesCall()` function in this course.
2. Compare its trusted identity with `kernel/user_files.c` and the process-file documentation.
3. Inspect the previous VFS lab and the real `kernel/vfs.c` contract.
4. Read `BtbHttpParse()` and explain its byte-length rules.
5. Compare those rules with the Framework HTTP request and static-file interfaces.
6. Record the source revision you inspected so you can distinguish current implementation from planned features.

Do not copy privileged Kernel code into a hosted Windows exercise. Use explicit educational implementations for learning, and preserve the production source in its authoritative repository.

## 7. Final exercise: design a Notes web view

Imagine that Umicom Notes should display one **read-only** teaching note through an HTTP route. Write down the required boundaries before writing code:

- Which component owns the note data?
- Which component chooses what the requesting client may read?
- Which component parses HTTP bytes?
- Which component checks output length and escapes text inserted into HTML?
- Which component records whether the response was complete?

The correct design does not pass a file-provider pointer directly to an untrusted HTTP request. It composes the existing services behind a checked application boundary.

**Next:** [Source-code laboratories](../../labs/index.md). In the next update, we will extend the networking course into bounded static-file routing, MIME types, streaming, and more complete failure tests while retaining the loopback security boundary.
