# Update 20 — Device discovery, MMIO and VirtIO ownership

## Scope

This delivery changes **only** `Umicom-Bits2Banking`. It does not modify Umicom Framework, Umicom Applications, Umicom Kernel or Umicom OS. Their links in the lessons refer to existing public source and documentation.

## Delivered curriculum

Chapters 127–131 teach an FDT's structure, checked big-endian decoding, hardware descriptions versus access authority, MMIO qualification and transport feature negotiation, DMA lifetimes, split virtqueue concepts, and a source reading of the actual Umicom Kernel VirtIO driver. Episodes 42–43 provide complete narration and terminal demonstrations.

The laboratories are independent C23 programs: `labs/native/device-tree-inspector` and `labs/native/virtqueue-lifetime`. They use no Python, JavaScript, sockets or privileged hardware instructions. CMake, Markdown, YAML and SVG are retained for building and publishing the educational work.

The device-tree reader accepts a **bounded subset**: one FDT image up to 64 KiB, root `#address-cells = <2>` and `#size-cells = <2>`, one direct child advertising `virtio,mmio` and a sixteen-byte `reg` property. It checks block bounds, format versions, reservation termination, structure tokens, property names and maximum nesting. It is not a general device-tree binding validator or bus translator.

The virtqueue model is **not a wire-compatible VirtIO implementation**. It uses copied C arrays and simulated device completion/reset acknowledgement to teach source preservation, bounded queues and safe reuse. It cannot prove DMA has ceased or that a storage write is durable. The real Kernel driver owns actual transport and cleanup behaviour.

## Preservation

The delivered MkDocs configuration and catalogue indexes preserve all prior lines and add only entries for new lessons and videos. Existing manuscripts, source files, video scripts, illustrations, historical book catalogues and publishing workflows are not deleted or replaced. Existing files that do not need a change are not included.

## Validation boundary

Tests can demonstrate the behaviour of the native teaching models with the compiler and host where they run. They do not establish privileged Kernel hardware qualification. Rebuild the actual website with MkDocs, preserve the original *Islam: Blueprint for Life* navigation and inspect the rendered pages before publishing.

[Read the build, test and Git instructions](UPDATE_20_BUILD_TEST_AND_GIT.md).
