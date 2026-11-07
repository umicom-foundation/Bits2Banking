<!--
Umicom Bits2Banking
File: labs/languages/zig-activity/README.md

PURPOSE:
Build a Zig caller without duplicating the C activity implementation.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Zig client for the shared activity model

This lab targets **Zig 0.15.2**. Use documentation matching that version.
The Zig files explain errors and external calls; the application rule stays
in the existing C activity model.

## Setup

You need Zig 0.15.2 and a Framework source checkout containing
`include/umicom/base/status.h`. No generated SDK binary is needed by this
small model because it uses the status type and no external Framework function.
Other Framework components may require their libraries.

Start in the Bits2Banking repository. Check `zig version`. Create a build
directory if needed. These commands compile the existing C files, not a
translation of them into Zig.

## PowerShell

```powershell
New-Item -ItemType Directory -Force build
zig build-exe labs/languages/zig-activity/main.zig -I ../Umicom-Applications/framework/include -cflags -std=c23 -- labs/native/activity-adapters/bridge.c labs/native/framework-activity/activity.c -lc -femit-bin=build/zig-activity.exe
& .\build\zig-activity.exe
zig test labs/languages/zig-activity/activity.zig -I ../Umicom-Applications/framework/include -cflags -std=c23 -- labs/native/activity-adapters/bridge.c labs/native/framework-activity/activity.c -lc
```

## Bash

```bash
mkdir -p build
zig build-exe labs/languages/zig-activity/main.zig -I ../Umicom-Applications/framework/include -cflags -std=c23 -- labs/native/activity-adapters/bridge.c labs/native/framework-activity/activity.c -lc -femit-bin=build/zig-activity
./build/zig-activity
zig test labs/languages/zig-activity/activity.zig -I ../Umicom-Applications/framework/include -cflags -std=c23 -- labs/native/activity-adapters/bridge.c labs/native/framework-activity/activity.c -lc
```

Stop after any failed command. Adjust the include path if the Framework checkout
is elsewhere. The example compiles for the host; these commands do not create
an Android, iPhone or bare-metal binary.

Expected lines are `0 -> 1`, `41 -> 42`, `999 -> 1000` and
`1000 -> refused`. The example uses debug.print, which writes to standard
error. Redirecting only standard output will not capture those lines.

## Read and change the example

1. Find the external C declaration in activity.zig.
2. Compare its c_int argument and result with bridge.h.
3. Follow how a negative sentinel becomes error.Refused.
4. Find catch in main.zig. It presents a refusal and continues with another input.
5. Add 998 to the values array and predict its result before running.

The tests cover success, capacity, signed extremes and independent calls.
No result should be labelled passed until the relevant command is executed.

A missing symbol means the existing C bridge must be included in the link.
An unknown standard-library name often means a different Zig version is being
used. Consult the [versioned language reference](https://ziglang.org/documentation/0.15.2/).

