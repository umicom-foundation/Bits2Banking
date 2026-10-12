# Bits2Banking — Update 23: Virtual Filesystems and File Ownership

## A pathname is not a file descriptor

An application starts with a pathname such as `/notes/PROJECT.TXT`. The new
VFS laboratory resolves its mount, validates the filename and asks the
selected provider to open it. A successful operation returns a
**generation-tagged descriptor token**, not a pointer into provider storage.

The VFS owns the mount table, descriptors, open-file descriptions, their
shared read/write offsets and last-reference cleanup. A provider owns node
identifiers and file contents. Provider callbacks are copied into the mount,
while the provider's context remains borrowed and must outlive the mount.

This deliberate separation teaches three distinct questions: **What object
does the name select? Who may use the resulting descriptor? When can its
backing storage be released?**

## Features of the learning model

The native `vfs-descriptors` library provides bounded path dispatch; an
in-memory Notes provider; read/write permissions; duplication with narrowing;
shared offsets; owner-bound, generation-tagged tokens; unlink that preserves
already opened nodes; busy unmount protection; and explicit retry when the
last provider release fails.

The second laboratory, `vfs-provider-composition`, uses the same `btb_vfs`
library through CMake. It adds an independent, immutable reference-document
provider. A nonexistent `write` or `unlink` callback is reported as a refusal,
not silently treated as success. No VFS state machine is reimplemented.

The bounded design is intentional: four mounts, eight shared open-file
descriptions, twelve descriptor tokens, eight Notes file slots, up to 256
bytes per Notes file and paths of the form `/mount/filename` only. The
application-provided numeric client is a test identity, not real
user authentication. The programme is serial, hosted C23, not a POSIX VFS,
filesystem driver or durable-storage implementation.

## Source and lessons

- `content/lessons/05-engineering/142-*` — mount and path dispatch.
- `143-*` — descriptors, rights narrowing, offset sharing and stale handles.
- `144-*` — provider-owned data, unlink and final reference.
- `145-*` — composing editable and read-only providers.
- `146-*` — following the real Umicom Kernel VFS and process-file boundary.
- `content/videos/scripts/48-*` and `49-*` — narrated demonstrations.
- Three SVG diagrams explain dispatch, shared positions and unlink semantics.

The authoritative Umicom Kernel implementation is maintained separately:

- https://github.com/umicom-foundation/umicom-kernel/blob/main/include/umicom/kernel/vfs.h
- https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/vfs.c
- https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/ramfs.c
- https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/user_files.c
- https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/fat16_provider.c
- https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/PROCESS_FILE_SERVICES.md

Those source references describe a native RISC-V Kernel research project,
not the Linux-libre Umicom OS distribution.

## Repository and publishing boundaries

Update 23 changes only `Umicom-Bits2Banking`. No Umicom Framework, Kernel,
OS or application repository files are supplied or modified.

The complete `mkdocs.yml`, three subject index pages and the roadmap retain
the prior Update 22 text and append new entries. The historical *Islam:
Blueprint for Life* chapters, other books and previously published course
pages are not replaced or deleted. New implementation source is C23; CMake
configures it. Markdown and SVG are authoring formats, and the existing
MkDocs publishing dependency remains in place for rendering.

## Acceptance boundaries

The Linux host acceptance comprises two GCC C23 configurations with five
CTest cases in total, plus two Clang AddressSanitizer/UndefinedBehaviourSanitizer
configurations with the same five tests. The YAML and three SVGs are checked
separately; preservation is checked against the previous Update 22 files.

Windows UCRT64 compilation, the complete MkDocs website with the actual
historical files, and live GitHub Pages remain the contributor's local and
remote publishing acceptance steps. A passing hosted teaching exercise is not
a test of privileged memory safety or filesystem durability in Umicom Kernel.
