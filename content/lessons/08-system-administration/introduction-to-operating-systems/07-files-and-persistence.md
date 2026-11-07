<!--
Umicom Bits2Banking
File: content/lessons/08-system-administration/introduction-to-operating-systems/07-files-and-persistence.md

PURPOSE:
Distinguish a file interface from durable storage

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Distinguish a file interface from durable storage

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

## A name and a sequence of bytes

A filesystem organizes named data. A path describes where a file sits in that organization. The root is the starting directory of that filesystem. A guest path such as /notes/first.txt belongs to the guest's view, not automatically to C:\umicom on the host.

RAM-backed files are kept in memory. They can be useful and fully functional during a session, while disappearing when that session ends. Durable storage survives a specified failure or restart boundary. Durability requires more than a function called save: writes, buffering, errors and recovery all matter.

## Explore the documented guest

After following the Kernel's first-session setup and diskless launch, type:

~~~text
create /notes/first.txt
write /notes/first.txt "First note"
cat /notes/first.txt
append /notes/first.txt " and more"
cat /notes/first.txt
~~~

Predict First note and more after the append. Now replace the file with write and predict only the replacement text. Keep these commands inside the guest terminal. They are not PowerShell commands.

## Follow the implementation

Read console_shell.c to find the command dispatch, then ramfs.c for the storage operation. Separate argument parsing from filesystem behaviour. A parser rejecting a damaged line should never execute its valid-looking prefix.

Shut down the diskless guest and start it again. The note is not promised to persist. Record this as expected RAM behaviour, not a failed disk save. Adding disk-backed storage later needs a different test: write, flush through the documented boundary, restart, read and compare exact bytes, including cases where a write fails partway through.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-kernel/blob/main/kernel/ramfs.c).

## Continue learning

[Course contents](../../../courses/introduction-to-operating-systems/index.html) · [Previous: Understand interrupts and device events](06-interrupts-and-device-events.md) · [Next: Locate the boundary between kernel services and Framework](08-system-calls-and-framework.md)
