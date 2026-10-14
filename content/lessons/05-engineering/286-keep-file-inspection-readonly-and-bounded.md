# Chapter 286 — Build a bounded read-only text inspector in C23

**Bits2Banking · Engineering track · Umicom Foundation**  
**Previous material:** Chapters 264–283 and the dedicated [System Administration from Zero](../08-system-administration/index.md) course.  
**Engineering policy:** C23/Assembly first, existing Umicom Framework services before new implementations.

## Purpose and context

The new educational laboratory under `labs/native/sysadmin-readonly-text` accepts an explicitly named local text file and returns an owned summary containing byte count, logical line count and whether the file ends with LF. Its use of ISO C standard streams shows a beginner what lies below shell-level file commands. It does not claim to support arbitrary binary formats, enforce an untrusted-path security policy or supersede Framework production filesystem services.

The public header documents ownership and failure behaviour. `BtbTextInspectFile` validates pointers and the byte limit before opening the file. It uses read-only `fopen` mode, rejects an unexpected NUL byte, rejects input beyond the limit, closes the stream and replaces the caller's output only after a complete successful scan. A failed request cannot produce a misleading partial “successful” report.

The CTest cases cover LF, CRLF, missing final newline, empty input, NUL bytes, overlarge input, missing paths, invalid arguments, preserved output and 10,000 repeat inspections. These tests are deterministic; they do not create temporary files or require privileged access.

**Design question:** why does the inspector refuse an over-limit text file rather than printing a cropped byte/line count without an explicit incomplete flag? Answer: a cropped result could be mistaken for the whole file. A trustworthy diagnostic either proves completeness or clearly reports what was not inspected.

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
