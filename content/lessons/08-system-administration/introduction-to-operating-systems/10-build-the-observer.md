<!--
Umicom Bits2Banking
File: content/lessons/08-system-administration/introduction-to-operating-systems/10-build-the-observer.md

PURPOSE:
Build a small OS observation application

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Build a small OS observation application

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

## Understand the build inputs

CMake reads project declarations and creates instructions for a build tool. Ninja executes those instructions. The compiler translates C files; the linker combines compiled objects with libraries. The installed SDK supplies Framework's headers and compiled services.

The lab's CMakeLists.txt creates two executable targets. A target is a named build result with declared inputs. btb-boot-report is the application; btb-boot-report-test checks parser behaviour. Linking Umicom::platform imports the SDK's include paths and library requirements instead of guessing archive locations.

## Work one stage at a time

1. Follow the README to select a matching SDK prefix.
2. Configure into a new build folder. Stop if package discovery fails.
3. Build the targets. Keep the first compiler or linker error, not only the final failed status.
4. Run CTest from that build folder. Read skipped and failed cases separately.
5. Launch the exact application produced there with the ready fixture's absolute path.

On Windows, $LASTEXITCODE reports the last native program's status. Running the next native command before inspecting it can replace that evidence. A text log containing the word error is not itself the process result; preserve both.

## Make one controlled change

Change only the presentation sentence in a private copy of main.c. Rebuild without deleting the build directory. The build tool should update the affected object and executable according to its dependency graph. Do not regenerate all SDK libraries merely because the client text changed.

If an SDK function is unavailable, compare the installed header and archive revisions. Do not add a local imitation to make the link succeed: that would create another implementation with a potentially different contract.

## Read the source

[Open the example source](../../../../labs/framework/boot-report/CMakeLists.txt).

## Continue learning

[Course contents](../../../courses/introduction-to-operating-systems/index.html) · [Previous: Read a boot observation without overstating its meaning](09-read-boot-observations.md) · [Next: Understand recovery, users and permission boundaries](11-recovery-and-account-boundaries.md)
