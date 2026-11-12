# MINIX OS Foundations

Study MINIX 3.3.0 through source reading, isolated guest exercises and an original C character-driver lab. Compare ownership concepts with Umicom Kernel without claiming API or binary compatibility.

## MINIX 3 foundations and a read-only driver

- [Choose a release and an isolated guest](01-choose-a-release-and-isolated-guest.md)
- [Draw the kernel and server boundaries](02-draw-the-kernel-and-server-boundaries.md)
- [Follow a message and its reply](03-follow-a-message-and-a-reply.md)
- [Understand SEF startup and restart](04-understand-sef-startup-and-restart.md)
- [Keep process, filesystem and memory responsibilities clear](05-keep-pm-vfs-and-vm-responsibilities-clear.md)
- [Use grants for bounded data transfer](06-use-grants-for-bounded-data-transfer.md)
- [Build and review the read-only driver](07-build-and-review-the-read-only-driver.md)
- [Compare MINIX recovery with Umicom Kernel](08-compare-recovery-with-umicom-kernel.md)

## Bounded transfers, failures and evidence

Extend the same read-only lab with injected-copy results and explicit retry traces. Host cases are authored; guest qualification remains separate.

- [Separate read planning from copying](09-separate-read-planning-from-copying.md)
- [Preserve failed copy outcomes](10-preserve-failed-copy-outcomes.md)
- [Read in chunks and retry explicitly](11-read-in-chunks-and-retry-explicitly.md)
- [Build a driver evidence record](12-build-a-driver-evidence-record.md)
