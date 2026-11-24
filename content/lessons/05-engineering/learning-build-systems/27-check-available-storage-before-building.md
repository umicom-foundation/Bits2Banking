<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-build-systems/27-check-available-storage-before-building.md

PURPOSE:
Check available storage before building

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Check available storage before building

[Course contents](index.md)

A build can stop because it cannot write a file. Learn to measure the space available to your account in the temporary folder and the output folder before you compile. Then create one small C object without linking or running a program.

## Measure the two locations

A temporary folder holds intermediate working files. A build or output folder holds objects, libraries, executables or reports that you keep. They can be on separate volumes. A volume is an area of storage that Windows can mount. A drive letter such as C: is one way to reach it.

Open PowerShell in an existing practice folder where you are allowed to write. Run the commands below as the same account that will compile the example. The check uses the space available to that account, which can differ from the total free space when a quota limits the account.

This exercise accepts local drive-letter paths and refuses folders reached through a junction, a link or a directory-mounted volume. These can redirect a path to a different volume. Use an ordinary local practice folder for this exercise, or ask the system owner how to measure the actual destination of a redirected build path.

~~~powershell
function Get-CallerStorage {
    param([string]$Purpose, [string]$Folder)

    $directory = Get-Item -LiteralPath $Folder -Force -ErrorAction Stop
    if ($directory -isnot [IO.DirectoryInfo]) {
        throw 'Choose an existing Windows file-system folder.'
    }
    $root = [IO.Path]::GetPathRoot($directory.FullName)
    if ($root -notmatch '^[A-Za-z]:\\$') {
        throw 'This exercise requires a local drive-letter folder.'
    }

    # A mounted directory or junction can redirect the path to another volume.
    for ($part = $directory; $null -ne $part; $part = $part.Parent) {
        if ($part.Attributes -band [IO.FileAttributes]::ReparsePoint) {
            throw 'Choose a folder outside junctions, links and mounted directories.'
        }
    }
    $drive = [IO.DriveInfo]::new($root)
    if ($drive.DriveType -eq [IO.DriveType]::Network) {
        throw 'This exercise requires local storage.'
    }

    # AvailableFreeSpace is the byte count available to the current caller.
    [pscustomobject]@{
        Purpose        = $Purpose
        Folder         = $directory.FullName
        Drive          = $root
        AvailableBytes = $drive.AvailableFreeSpace
    }
}

$tempFolder = [IO.Path]::GetTempPath()
$outputFolder = (Get-Location).ProviderPath
$space = @(
    Get-CallerStorage -Purpose Temporary -Folder $tempFolder
    Get-CallerStorage -Purpose Output -Folder $outputFolder
)
$space | Format-List
if ($space.AvailableBytes -contains 0) {
    throw 'No space is available in one of the selected locations.'
}
~~~

## Read the numbers before compiling

The output has two entries showing the directory, its drive and its available bytes. If both paths are on the same volume, they share its space. Count that space once. If the drives differ, measure and budget each location independently.

The result is a snapshot. A measurement can change while other processes write files. A successful measurement also gives no estimate of a full build’s needs. Use the project’s known requirements and leave room for intermediate objects, linking, reports and concurrent jobs.

## Compile one C object

You need GCC with C23 support available as gcc.exe in this PowerShell session. The commands create a fresh practice directory under the output folder. Run the first block to get the source path and then save the C example at that path. Open the file with a text editor that saves plain UTF-8 and keeps the .c extension.

~~~powershell
$gcc = (Get-Command gcc.exe -CommandType Application -ErrorAction Stop).Source
$lab = Join-Path $outputFolder ('storage-practice-' + [Guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $lab -ErrorAction Stop | Out-Null
$source = Join-Path $lab 'storage_preflight.c'
$object = Join-Path $lab 'storage_preflight.o'

# Save the C example above as storage_preflight.c at the printed path.
$source
~~~

The example returns the remaining amount after reserving part of a practice allowance. The guard prevents unsigned subtraction from wrapping when the reserve is larger than the allowance. The exercise uses this as an ordinary small input file. It takes its real storage measurements from PowerShell.

~~~c
/*-----------------------------------------------------------------------------
 * Umicom Bits2Banking
 * File: storage_preflight.c
 *
 * PURPOSE:
 *   Demonstrate a small source file that can be compiled without linking.
 *
 * AUTHOR AND ORGANISATION:
 * Sammy Hegab
 * Umicom Foundation
 *
 * LICENCE:
 * MIT
 *---------------------------------------------------------------------------*/

/* Guard the subtraction so a practice allowance below its reserve yields zero. */
unsigned int remaining_after_reserve(unsigned int available, unsigned int reserve)
{
    return available >= reserve ? available - reserve : 0U;
}
~~~

Once the source is saved, run the second PowerShell block. It temporarily points GCC at the same folder you measured. It restores the previous environment values even if compilation fails.

~~~powershell
if (-not (Test-Path -LiteralPath $source -PathType Leaf)) {
    throw 'Save the C example at the path printed by the setup block.'
}

$oldTmpdir = $env:TMPDIR
$oldTemp = $env:TEMP
$oldTmp = $env:TMP
try {
    # Give this compiler process the same temporary location measured earlier.
    $env:TMPDIR = $tempFolder
    $env:TEMP = $tempFolder
    $env:TMP = $tempFolder
    & $gcc -std=c23 -Wall -Wextra -Werror -c $source -o $object
    if ($LASTEXITCODE -ne 0) {
        throw "Compile failed with exit code $LASTEXITCODE. Read the diagnostic."
    }
    Get-Item -LiteralPath $object -ErrorAction Stop | Select-Object Name, Length
}
finally {
    $env:TMPDIR = $oldTmpdir
    $env:TEMP = $oldTemp
    $env:TMP = $oldTmp
}
~~~

Expect a storage_preflight.o row with a length greater than zero. The -c option compiles to an object file and stops before linking. The example has no main function and produces no executable. Keep the practice source and object to inspect later.

## Recognize the failure stage

Read the earliest operation-specific error and record its path and exit status. ENOSPC means the operation could not obtain the storage it needed. Windows tools may report “There is not enough space on the disk.” Use the path from the diagnostic to decide whether to check temporary, output or report storage. Remeasure before retrying.

An “undefined reference” or “unresolved external symbol” is a linker diagnostic. Check which object or library supplies the named function and whether the link command includes it. More space by itself provides no missing implementation.

When a build fails, a test can be unable to find its executable or it can run a previously built executable. Such a test result cannot qualify the source you just changed. After a successful repair, verify that the intended target was rebuilt and run the matching tests with the artifact identity recorded.

If the selected location cannot hold the work, stop. Use an approved folder or volume with sufficient space and set the affected temporary or output path through the existing project workflow. Check both locations again. For a new output location, configure a new build directory. Preserve the existing build and logs for diagnosis.

## Check your understanding

Suppose the output drive has ample space but a write in the compiler’s temporary folder reports ENOSPC. Start by rechecking the volume that owns the temporary folder. An undefined reference in a separate build points to linker inputs. A green test from an older executable is evidence about that executable. It takes a successful rebuild and a matching new test run to qualify changed source.

[Previous: Recognize stale tests after a failed build](26-recognize-stale-tests-after-a-failed-build.md) · [Course contents](index.md)

[Next lesson · Read a Ninja progress record](28-read-a-ninja-progress-record.md)
