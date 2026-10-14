# Chapter 285 — Inspect processes, services and logs before attempting fixes

**Bits2Banking · Engineering track · Umicom Foundation**  
**Previous material:** Chapters 264–283 and the dedicated [System Administration from Zero](../08-system-administration/index.md) course.  
**Engineering policy:** C23/Assembly first, existing Umicom Framework services before new implementations.

## Purpose and context

A service can be running and still fail its business task. A build tool can be active and appear frozen in a GUI. A successful process exit does not prove the expected output file was created. These examples teach why system administration must use independent evidence.

The safer first pass is read-only: inspect `Get-Process`, `Get-Service` and a bounded `Get-WinEvent` excerpt. On Linux use `ps`, `systemctl status` where appropriate, and `journalctl -n 10 --no-pager` if permitted. Keep the original error and timestamp rather than installing a second log-parser or deleting an inconvenient event.

For a failed Umicom build, record the configured preset, compiler path, actual CMake/Ninja failure, and CTest test name. The Framework already has build diagnostics and VCS observation contracts. A learning chapter may explain them, but application code should not introduce its own competing process or repository manager.

**Operational challenge:** explain why “the service is Running” is weaker evidence than “the user completed the expected Notes save/reopen operation and the outcome was recorded”.

## Worked example: observe before changing

On Windows, open PowerShell 7, then type the following interactive commands:

```powershell
Get-Location
$PSVersionTable.PSVersion
Get-Command git, cmake, gcc -ErrorAction SilentlyContinue | Select-Object Name, Source
```

**Expected:** the working directory, shell version and installed executable paths are printed. Missing executables simply do not appear; investigate installation separately rather than changing source. Do not invoke elevated commands as part of this example.

## Guided lab

1. Begin in a personal training directory; confirm it using `Get-Location`.
2. Identify which commands in this chapter are observations and which would modify source or computer state.
3. Read the linked course chapter for your current skill level.
4. When ready for C23, configure the standalone read-only inspector as documented in its README.
5. Record the actual CTest result and keep any failure output.
6. Connect the lesson to an existing Framework-owned API, rather than copying the teaching implementation into Studio or OS.

## Troubleshooting and common questions

**Why does a command not exist?** Confirm the shell and platform, check `Get-Command`, and read the official install instructions. A shell error is not proof the C23 source is wrong.

**Why should a test failure not be ignored?** A build only proves that the source was compiled and linked. It cannot prove a function implements the intended behaviour, especially around error handling and resource ownership.

**Can I commit directly to main?** Authorised Umicom maintainers use the established main-branch workflow after reviewing tests and staged changes. External contributors need the appropriate permissions and may use pull requests.

## Review questions

1. Explain why the command prompt is not the operating system kernel.
2. Describe one way to preserve evidence before making a change.
3. Why should an educational native C23 library not automatically become a duplicate production Framework service?
4. What information must a tester report if Windows UCRT64 has not yet been tested?

## Next steps

Continue through the [dedicated System Administration course](../08-system-administration/index.md), then complete the [practice workbook](../08-system-administration/workbook-and-assessment.md).
