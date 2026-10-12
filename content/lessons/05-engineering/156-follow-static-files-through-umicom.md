# 156. Follow a file request through Umicom Framework and Kernel

Our local C23 web server reads a file from an ordinary operating-system directory. It demonstrates an important engineering principle: a component should ask another component to perform a service instead of reaching into its internal storage.

Umicom uses the same principle at several levels, although its production components have broader responsibilities and different security contracts.

## 1. Compare the educational layers

The lesson's call path is:

```text
Browser
  |
  v
TCP listener           tcp_server.c
  |
  v
HTTP request parser    http.c
  |
  v
Rooted file owner      static_files.c
  |
  v
Operating-system file API
  |
  v
Stored HTML/CSS/image bytes
```

This is a **hosted program**. It calls the file and socket services supplied by Windows or Linux. It does not implement a kernel, a filesystem driver or a network driver.

## 2. Locate the corresponding Umicom Framework services

Umicom Framework contains reusable web components separate from this classroom application. Read these source files in the official repository:

- [Framework static-file contract](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/static_files.h) — what a caller supplies and how file requests are constrained.
- [Framework local C web service](https://github.com/umicom-foundation/umicom-framework/blob/main/examples/web/local_service.c) — an example of HTTP routing using shared Framework services.
- [Framework web server interface](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/web/server.h) — the lifetime and transport boundary around the listener.
- [Framework's local web-service guide](https://github.com/umicom-foundation/umicom-framework/blob/main/docs/learning/local-web-service.html) — how to run the established C example.

Notice that the Framework implementation has its own limits. For example, its public static-files interface documents a small bounded preview size. The educational server in this chapter demonstrates a separate **8 KiB streaming buffer and 64 MiB per-file limit**. These are different contracts, not evidence that one automatically replaces the other.

No changes to Framework are required to complete this lesson.

## 3. Locate the corresponding Umicom Kernel services

A kernel is responsible for privileged resource management. The native Umicom Kernel research project has separate files showing filesystem and process ownership:

- [Virtual filesystem interface](https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/vfs.h) — a typed contract for paths, open descriptions and file descriptors.
- [Virtual filesystem implementation](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/vfs.c) — resolves paths and manages descriptor lifetimes.
- [RAM filesystem](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/ramfs.c) — storage behind that VFS contract.
- [Process file service](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_files.c) — associates descriptor access with the admitted task.
- [VirtIO block driver](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/virtio_block.c) — a separate device transport, not a file-based web server.

The Kernel must **not** depend on the full application Framework. Its interfaces manage lower-level machine and service lifetimes. Network-server facilities from Framework should not be copied into privileged kernel code.

## 4. Keep original Kernel research separate from the OS distribution

[Umicom OS](https://github.com/umicom-foundation/umicom-os) is a separate operating-system distribution project. The original Umicom Kernel is an independent native-kernel research implementation. The OS project's current production direction uses the GNU Linux-libre kernel; study the native Kernel source as a research and educational platform, not as evidence that the complete distribution already boots on it.

Our web-server laboratory currently runs as a Windows/Linux application. It does **not** run as a user-space server on the native Umicom Kernel.

## 5. Inspect, compare and explain

Open `labs/native/http-loopback-server/static_files.c` alongside Framework's `src/web/static_files.c`. Compare what each considers an allowed path, how it owns opened storage and how it handles a file that is too large.

Then inspect Umicom Kernel's `kernel/vfs.c` and write down the difference between a **filename**, a **node**, an **open description** and a **descriptor**. These are not interchangeable identities. A descriptor can be closed while a different descriptor still refers to the same open description.

Finally, examine the `BtbStaticRoot` and `BtbStaticFile` objects in the educational code. Who creates them? Who closes them? What goes wrong if a file handle outlives its root owner or a pending send outlives its file buffer?

## Continue learning

At this point, you can explain the path from an HTTP request to a read-only file and identify which layer owns each responsibility. The next chapter group will introduce **HTTP routing, response completion and testable service boundaries** before we extend our networking course further.
