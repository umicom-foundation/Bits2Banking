<!--
Umicom Bits2Banking
File: labs/native/creative-draft-recovery/QUALIFICATION.md

PURPOSE:
Distinguish source inspection, installed client behavior and native recovery evidence.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../content/assets/branding/umicom-logo.svg)

# Qualify the creative recovery workflow

The lab and its expected outcomes are authored examples. Record execution results against the source and SDK actually used; do not mark an unexecuted layer as passed.

## 1. Establish source and SDK identity

Record the Framework and Bits2Banking revisions, local changes, selected SDK prefix, compiler and runtime library paths. Preserve configure and build output. Stop after a failed build rather than testing an older executable as if it contained the new source.

## 2. Build and exercise the installed client

Follow README.md. List the eight tests before execution:

~~~powershell
ctest --test-dir "C:\umicom\Umicom-Bits2Banking\build\creative-draft-recovery" -N
ctest --test-dir "C:\umicom\Umicom-Bits2Banking\build\creative-draft-recovery" --output-on-failure --no-tests=error
~~~

Require all eight named scenarios and inspect each outcome. The save/open commands are separate exercises because they intentionally replace a caller-selected disposable file.

## 3. Exercise shared implementation boundaries

From the matching configured Framework build directory, inspect the selected tests, then execute them. These commands select document admission, injected file-contract behavior and native recovery separately; use the configured build directory rather than assuming a particular build-folder name.

~~~powershell
ctest -N -R "^framework[.]media_(brief|storyboard)[.]document[.]"
ctest --output-on-failure --no-tests=error -R "^framework[.]media_(brief|storyboard)[.]document[.]"
ctest -N -R "^framework[.]media_(brief|storyboard)[.]file_contract[.]"
ctest --output-on-failure --no-tests=error -R "^framework[.]media_(brief|storyboard)[.]file_contract[.]"
ctest -N -R "^framework[.]media_(brief|storyboard)[.]gtk[.]recovery[.]"
ctest --output-on-failure --no-tests=error -R "^framework[.]media_(brief|storyboard)[.]gtk[.]recovery[.]"
~~~

Injected I/O checks isolate publication and cancellation rules. They do not establish real filesystem timing. Native tests require the appropriate GTK configuration and usable host; keep missing or skipped coverage explicit.

## 4. Review the native product

1. Open the approved creation workspace in the application build that consumes the qualified Framework revision.
2. Enter incomplete source and edited prompt text. Save it at a disposable absolute path using the explicit replacement control.
3. Change the current text, select Open and review the replacement decision. Confirm the recovered fields and the unprepared handoff state.
4. Use the authored native tests for deterministic stale-result and retirement interleavings. Separately inspect actual pointer and keyboard interaction.
5. Check that edits and path changes clear one-shot approvals, busy actions cannot start a second file job, and retired views receive no late updates.
6. Inspect the canonical logo, SVG/ICO resources, readable font fallback and accessibility labels using the actual installed product.

Do not infer model submission from a recovered prompt or a prepared instruction string. Provider requests, decoded media, watermarks on rendered exports and device workflows require separate evidence.

## 5. Keep a result record

| Layer | Initial state | Evidence to retain |
| --- | --- | --- |
| Source and static inspection | Unexecuted until reviewed | File identities and findings |
| Installed-SDK configure/build | Unexecuted | Selected package, compiler and build output |
| Eight console scenarios | Unexecuted | Named results and executable identity |
| Shared document tests | Unexecuted | Selected test listing and outcomes |
| Injected file contracts | Unexecuted | Failure/cancellation case outcomes |
| Native recovery tests | Unexecuted | Host, binary identity, passes/failures/skips |
| Manual application workflow | Unexecuted | Observed fields, controls, focus and branding |
| Real disposable save/open | Unexecuted | Explicit path, returned status and recovered values |

A new adverse result should reopen the relevant investigation. Preserve earlier observations instead of replacing their history with a single green status.
