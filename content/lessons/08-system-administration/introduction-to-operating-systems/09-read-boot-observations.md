<!--
Umicom Bits2Banking
File: content/lessons/08-system-administration/introduction-to-operating-systems/09-read-boot-observations.md

PURPOSE:
Read a boot observation without overstating its meaning

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Read a boot observation without overstating its meaning

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

## A report is evidence with a limited scope

The first line UMICOM_BOOT_REPORT 1 identifies a format and version. Each following line names one field. planned is the number of startup checks; completed is the number successfully completed so far. state describes this boot phase, while reason explains a recovery outcome.

The source field is a hexadecimal fingerprint of recorded inputs. A fingerprint helps compare bytes. It does not prove who created them or whether a machine is trustworthy. Authentication requires an additional trust mechanism.

## Inspect the three fixtures

1. Open ready.report. Find planned=2 and completed=2.
2. Open recovery.report. It records one completed check and service-exit as the reason.
3. Open invalid.report. It says ready despite incomplete checks.
4. Run the lab client against each absolute path using the README commands.
5. Record the process status and accepted fields separately.

A successfully parsed recovery report should still display recovery. Returning success from a file reader means the record was read correctly; it is not permission to display a green healthy-system badge.

## Why bounded text matters

The parser accepts at most 512 bytes and requires a final LF. It rejects duplicate and unknown fields. Those choices prevent an older reader from silently ignoring a new field that changes the meaning of the record. A changed format needs a documented version policy.

These teaching files contain an illustrative source ID. Do not publish their contents as real boot results. For a guest run, preserve the actual report, console output, process status and source identity together. They answer different questions and should not be collapsed into one pass label.

## Read the source

[Open the example source](../../../../labs/framework/boot-report/fixtures/ready.report).

## Continue learning

[Course contents](../../../courses/introduction-to-operating-systems/index.html) · [Previous: Locate the boundary between kernel services and Framework](08-system-calls-and-framework.md) · [Next: Build a small OS observation application](10-build-the-observer.md)
