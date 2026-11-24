<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/28-read-a-ninja-progress-record.md

PURPOSE:
Read a Ninja progress record

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Read a Ninja progress record

A build tool reports actions while it works. A progress line tells you about completed actions and planned work. A final result records whether the command succeeded. Keep both facts in your notes.

## Read the default status

Ninja's default status places two decimal counts before the command description. In `[18/29] Linking C executable sample.exe`, 18 actions have finished and 29 are planned. The description begins after the space beside the last bracket. [Ninja default status](https://ninja-build.org/manual.html#_environment_variables)

| Part | Value in the example |
| --- | --- |
| Finished actions | 18 |
| Planned actions | 29 |
| Description | Linking C executable sample.exe |
| Result of the whole build | Await the exit result |

A file can contain progress records, compiler messages and lines from the build tool. The shared Framework reader locates the numeric fields without running Ninja. It returns a byte offset and a count into the original line so a caller can retain the original description.

~~~c
#include "umicom/build/ninja_progress.h"

static const char line[] = "[18/29] Linking C executable sample.exe\r\n";
UmiBuildNinjaProgress progress;
UmiStatus status = UmiBuildNinjaProgressParse(line, sizeof line - 1U, &progress);
~~~

On `UMI_STATUS_OK`, `progress.finishedCommands` is 18 and `progress.plannedCommands` is 29. The two line-ending bytes are outside the description. The source uses `sizeof line - 1U` to leave out the C string's final zero. A counted source read can pass its own exact length.

~~~text
READ a complete line
IF the prefix matches the default progress format
    STORE the counts and description span
ELSE retain the original line for the appropriate reader
WAIT FOR the build exit result before recording success
~~~

## Compare three observations

1. Read the complete line above. Confirm that the description can be copied using only the returned offset and length.
2. Try `[29/29] Linking sample.exe`. The progress counts agree. Leave the build's final result open until you observe the exit status.
3. Try a normal `FAILED: sample.c` line or a custom progress format. Expect `UMI_STATUS_NOT_FOUND` for this reader. Preserve the raw line so a different parser can handle it.
4. Try `[30/29] Impossible counters`. Expect `UMI_STATUS_PARSE_ERROR` with the previous admitted output unchanged.
5. Use the existing progress fixture in a configured SDK checkout. With the current Framework tests built, select the data-only case in that checkout. Replace `build/hosted` with the folder containing its test files.

~~~powershell
ctest --test-dir build/hosted -R '^framework\.build_diagnostics\.ninja_progress$' --output-on-failure
~~~

If no test is listed, use `ctest --test-dir build/hosted -N` to inspect the configured names. The progress fixture checks a counted source span and numeric boundaries without running a build tool. Track the build's exit status and test results with the correct revision for your own project.

A Studio build view can retain these fields and present a clear progress update while another shared service collects diagnostics and final outcomes. Continue with the earlier saved-test lesson when comparing results after a failed build.

[Course contents](index.md) · [Previous lesson · Check available storage before building](27-check-available-storage-before-building.md) · [Related lesson · Recognize stale tests after a failed build](26-recognize-stale-tests-after-a-failed-build.md) · [HTML edition](../../../courses/learning-build-systems/lessons/28-read-a-ninja-progress-record.html)

[Next lesson · See which library Ninja will link](29-see-which-library-ninja-will-link.md)
