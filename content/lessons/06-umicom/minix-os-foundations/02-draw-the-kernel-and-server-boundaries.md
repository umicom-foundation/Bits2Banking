# Draw the kernel and server boundaries

## A small kernel still needs a system

An operating system includes more than its kernel. MINIX separates mechanisms and services across protection boundaries. The kernel provides low-level facilities including IPC, while user-space servers perform major operating-system roles.

The [official server overview](https://wiki.minix3.org/doku.php?id=developersguide:overviewofminixservers) identifies PM for process management, VFS for the virtual filesystem, VM for virtual memory and RS for service restart. DS provides a data-store service. Verify the components actually present in your selected release rather than assuming every item in a current wiki list is installed.

## Build a source map

In the release-matched source tree, locate minix/kernel, minix/servers and minix/drivers. Draw a box for each owner. For a file read, distinguish the requesting application, VFS, a filesystem server and the device driver. Draw messages between boxes instead of drawing every function inside a single kernel.

This drawing is a reasoning aid, not an exact call trace. Read the selected operation's source before assigning a particular message number or callback.

## Worked ownership question

A driver needs to return bytes to a requester. The requester's pointer is not automatically meaningful in the driver's address space. A controlled transfer mechanism is required. That need follows from isolation and motivates the later grants lesson.

## Exercise and answer

If a user-space driver fails, must the kernel itself have crashed? Answer: no. The separation permits different failure domains. Whether recovery succeeds depends on the service, manager policy and resource state; isolation alone is not a recovery proof.

## Compare with Umicom

Umicom Kernel's own supervisor and managed-service controller also distinguish owners and lifetimes. Their functions, structures and ABI are independent. Do not rename a MINIX call to an Umicom-looking name and assume compatibility.

Before continuing, explain one benefit and one cost of a message boundary. A benefit is explicit ownership; a cost can be additional scheduling and protocol complexity. Measure those costs in a real system rather than assuming an architectural label determines performance.

[Course contents](index.md)
