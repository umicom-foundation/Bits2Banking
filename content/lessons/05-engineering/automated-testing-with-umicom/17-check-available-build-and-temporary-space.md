<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/automated-testing-with-umicom/17-check-available-build-and-temporary-space.md

PURPOSE:
Check available build and temporary space

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Check available build and temporary space

A build may write program files into a build directory and use a separate **temporary directory** for intermediate work. A compiler can reach a nearly full storage volume even when another volume has room. A volume is a storage area the operating system measures as a unit.

## 1. Find the failing write

Imagine that a build reaches the middle of a long list of steps and reports `No space left on device` while opening a temporary file. Keep the first failure line and look at the path named in it. Identify the build directory from the configure command and the temporary directory from your toolchain configuration. A compiler that selects a different temporary directory can require a separate check of that explicit location.

The path-length warning in the previous lesson measures characters in a filename. This lesson measures available **bytes**, which are units of storage. Shortening a directory name changes its length. Space measurements come from the volume associated with each directory.

## 2. Read both observations

Use an existing current Framework build and choose an existing absolute build directory. The command below asks Framework to measure the temporary directory visible to the command process and the build directory you supplied.

~~~powershell
$Build = 'C:/umicom/Umicom-Applications/framework/build/windows-ucrt64-debug'
$Tool = "$Build/bin/umicom.exe"
& $Tool dev storage --process-temp --build $Build
$StorageExit = $LASTEXITCODE
$StorageExit
~~~

Look for `Temporary caller-available bytes` and `Build caller-available bytes`. Caller-available bytes are the bytes the operating system reports for this process or account. If the two directories share a volume, the rows describe the same underlying storage. Keep them as two measurements.

When the compiler has its own temporary directory, replace `--process-temp` with `--temp` followed by that existing absolute path. You can ask for your own role-specific requirements with `--min-temp-bytes` and `--min-build-bytes`. Choose each requirement from the needs of the build you are checking.

| Exit | How to read the result |
| --- | --- |
| `0` | Both measurements succeeded and all supplied requirements were met. |
| `1` | At least one directory could not be measured or a result could not be written. Read the diagnostic. |
| `2` | The command arguments were refused. Check the directory options and decimal counts. |
| `3` | At least one successful measurement was below its requested minimum. |

The measurement describes one moment. Other builds may use space afterward. Keep the observation and the actual build result in your evidence.

## 3. Express the check in C

The shared C23 Framework function can measure one existing absolute directory. This helper computes whether a caller's requirement is met after a successful observation.

~~~c
#include <stdbool.h>
#include <stddef.h>
#include "umicom/platform/storage_space.h"

static UmiStatus directory_has_room(const char *path, uint64_t minimum, bool *fits)
{
    /* Publish a decision only when the caller provides a destination. */
    if (fits == NULL)
        return UMI_STATUS_INVALID_ARGUMENT;

    /* A failed observation preserves the caller's previous decision. */
    UmiStorageSpace measurement;
    const UmiStatus status = umi_storage_space_read_directory(path, &measurement);
    if (status != UMI_STATUS_OK)
        return status;
    *fits = measurement.caller_available_bytes >= minimum;
    return UMI_STATUS_OK;
}
~~~

On paper, use a temporary measurement of 90 bytes and a build measurement of 200 bytes. Compare them with a requirement of 100 bytes for each role. The temporary role falls short by 10 bytes. The build role meets its requirement. Avoid adding both rows to decide whether a single temporary file can fit.

If a real measurement fails, check that the directory exists and that the command can inspect it. Save the diagnostic, repeat the measurement with the correct path, then compare the next build log against the same tool and source selection.

[Course contents](index.md) · [Previous lesson · Check a shorter Windows build path](16-check-a-shorter-windows-build-path.md) · [Release response bodies on every exit](../building-a-web-server-in-c/38-release-response-bodies-on-every-exit.md) · [Next lesson · Separate a skip from a test that could not start](18-separate-a-skip-from-a-test-that-could-not-start.md) · [HTML edition](../../../courses/automated-testing-with-umicom/lessons/17-check-available-build-and-temporary-space.html)
