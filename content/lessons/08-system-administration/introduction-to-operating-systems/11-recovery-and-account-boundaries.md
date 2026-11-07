<!--
Umicom Bits2Banking
File: content/lessons/08-system-administration/introduction-to-operating-systems/11-recovery-and-account-boundaries.md

PURPOSE:
Understand recovery, users and permission boundaries

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Understand recovery, users and permission boundaries

An operating system coordinates programs, memory, devices and access to resources. This course introduces each idea using a small Umicom example. It assumes no previous operating-system or C experience. Definitions and setup are repeated where a lesson can be read independently.

## Prepare this lesson

You need a text editor to read the examples. A terminal is a window in which a typed command asks a program to do something. PowerShell is the Windows terminal language used below; Bash is the Linux alternative. A path names a file or folder. Replace C:\umicom with your checkout location if it differs.

For the optional C lab, install a C23 compiler, CMake and Ninja, and a matching Umicom Framework SDK that includes the platform component. On Windows, open PowerShell and enter:

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\framework\boot-report"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake --version
gcc --version
~~~

Read the lab README before configuring it. Run commands separately and stop on a nonzero exit status. Reading a report does not boot an operating system. QEMU exercises use the separate Kernel guide linked in the relevant lesson; no physical disk is attached. You can complete the prediction and source-reading exercises without executing programs.

## Recovery has a specific job

A recovery environment provides a small set of operations when the normal path cannot complete. Keeping it independent of large application services makes it useful when those services fail. It should expose the evidence and controls it actually implements.

Umicom OS Foundation currently has a restricted recovery console. Its documented commands include help, status, services, packages and poweroff. It is not a general login shell. It does not currently contain a password database, compiler, package installer or graphical session.

## Separate three ideas

A local profile can store application preferences. Authentication verifies a claimed identity. Authorization decides which operations that identity may perform. Creating a directory with a person's name supplies none of those guarantees by itself.

1. Read the OS installation guide's account section.
2. List which commands are currently available in the guest.
3. Mark user creation, password login and application building as later platform capabilities where the guide says they are unavailable.
4. Read boot/foundation/init.c and find how the controller selects recovery.
5. Explain why a successful host GUI launch is not evidence for guest login.

## Design an extension before implementing it

A future account feature needs a threat model, credential storage policy, permission model, recovery behaviour and tests for denied operations. The shared identity service belongs in Framework where reusable, while privileged OS policy remains explicit at its system boundary.

Never teach a fabricated useradd command for this console. An honest unavailable feature is actionable: it can be planned, implemented and qualified. A guide that claims unsupported installation steps can damage user trust and make debugging impossible.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-os/blob/main/docs/foundation/installation-and-development.md).

## Continue learning

[Course contents](../../../courses/introduction-to-operating-systems/index.html) · [Previous: Build a small OS observation application](10-build-the-observer.md) · [Next: Plan the route from a learning guest to an OS release](12-from-emulator-to-release.md)
