<!--
Umicom Bits2Banking
File: labs/native/framework-boot-media/README.md

PURPOSE:
Explain the installed Framework media lab and its evidence limits.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Build a reviewed media-copy application in C23

![Umicom](../../../content/assets/branding/umicom-logo.svg)

This small application uses installed Umicom Framework services to inspect a disk image, review a new regular-file destination, copy after explicit confirmation, and verify the bytes. It contains no disk discovery or physical-device command. Its practice image has a synthetic partition table and no operating system.

<!-- The former example selected a separate boot-media build directory. Retain that path for readers of earlier setup instructions; the active example follows the Framework debug preset.
$PracticeTool = (Resolve-Path "C:\umicom\Umicom-Applications\framework\build\boot-media\bin\umicom-media-image-example.exe").Path
-->

## Prepare the tools

Use a matching Framework development installation containing the boot_media and platform libraries, native_arguments.h and the application-branding helper. Keep the compiler, architecture, installed headers and libraries aligned. The examples below use C:/umicom/installed/framework; change that prefix if your SDK is elsewhere.

Build the existing Framework target umicom-media-image-example in your established Framework build directory. Its output is normally in that build directory's bin folder. It is a separate teaching tool, not currently a required installed SDK executable. Set the full path below to the executable you built. The CTest runner needs this path; BUILD_TESTING=OFF permits building the client alone.

Run each command separately and stop on an error. These are instructions for your own qualification, not recorded results.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
$PracticeTool = (Resolve-Path "C:\umicom\Umicom-Applications\framework\build\windows-ucrt64-debug\bin\umicom-media-image-example.exe").Path
cmake -S .\labs\native\framework-boot-media -B .\build\framework-boot-media -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON "-DUMICOM_MEDIA_PRACTICE_TOOL=$PracticeTool"
cmake --build .\build\framework-boot-media --parallel 2
ctest --test-dir .\build\framework-boot-media --output-on-failure --no-tests=error
~~~

<!-- Earlier six-case description retained; all six exercises remain supported.
The six checks cover review without creating a destination, successful copying and verification, an existing destination, an image changed after review, an incorrect confirmation, and a copy modified after transfer. Each run creates a unique scratch directory under the build tree and keeps its files for inspection. No test boots the image or opens a physical device.
-->

The twelve checks retain review, successful copy and verification, existing destination, changed source, incorrect confirmation and tampered copy. Five further cases request cancellation at recheck, write, flush, verify and finished. One case refuses an unknown phase before review. Each run keeps a unique scratch directory under the build tree. No test boots an image or opens a physical device.

On Linux, use your matching native C compiler and installed SDK prefix, and provide the Linux practice-tool path. Do not point a Linux consumer at Windows SDK archives. The laboratory's console uses your terminal font. The SDK branding helper stages approved SVG assets and embeds the supplied ICO and version metadata on Windows without adding a GTK deployment dependency.

## Try the review yourself

Create one new working directory and ordinary image. Keep the variables in the same PowerShell session.

~~~powershell
$Lab = (Resolve-Path .\build\framework-boot-media\btb-framework-boot-media.exe).Path
$Practice = Join-Path $env:USERPROFILE ("Umicom Media Lesson-" + [guid]::NewGuid().ToString("N"))
New-Item -ItemType Directory -Path $Practice | Out-Null
$Image = Join-Path $Practice "source image.img"
$Copy = Join-Path $Practice "verified copy.img"
& $PracticeTool --output $Image
& $Lab inspect $Image
& $Lab review $Image $Copy
~~~

Inspection should show 2,097,152 bytes and MBR: 1. MBR names a partition-table layout, not a working OS. Review should print Destination, Fingerprint and Confirmation while leaving the destination absent. Check that path and copy the exact fingerprint and confirmation from your own output into the following command. Keep the confirmation in quotes because it contains spaces.

~~~powershell
& $Lab copy $Image $Copy "PASTE_REVIEW_FINGERPRINT" "PASTE_REVIEW_CONFIRMATION"
& $Lab verify $Image $Copy
Get-FileHash -LiteralPath $Image, $Copy -Algorithm SHA256
~~~

A completed copy should print that it copied and verified a new regular file; the final hashes should agree. Do not silently regenerate and accept tokens if the source or destination changes. Review the new state deliberately. A second copy to the same destination must fail and retain that file.

## Follow the ownership boundary

main calls UmiNativeArgumentsDispatch so Windows command-line text reaches the application as UTF-8 without a private conversion implementation. MediaLessonMain calls UmiBootMediaReviewFile and owns the returned plan. Getter strings belong to that plan. The code prints them before UmiBootMediaPlanDestroy and never retains the pointers.

The copy command constructs a new plan from current observations, then passes the earlier user-supplied fingerprint and confirmation to UmiBootMediaApply. The service checks agreement again and performs transfer verification. An application must not replace the supplied review with the new plan's tokens automatically: doing so would approve a changed operation without review.

## Recover without hiding failure

If configuration cannot find boot_media, install the matching complete development SDK. If linking cannot find native argument symbols, compare the SDK header and archive revisions. If the practice tool is missing, correct its path rather than substituting an unrelated image. An existing destination is retained; choose a different new path after review. A failed or cancelled copy may leave partial output for diagnosis. Keep it separate from completed media and do not call it a usable distribution.

A matching regular-file copy establishes byte agreement for that observation. It does not establish image provenance, firmware compatibility, successful guest startup, device durability or hardware support. Continue with the [OS media lesson sequence](../../../content/courses/umicom-os-from-scratch/lessons/39-inspect-an-image-without-booting-it.html).


## Observe cancellation without assuming rollback

The additional command is:

~~~text
btb-framework-boot-media copy-until IMAGE NEW_FILE FINGERPRINT CONFIRMATION PHASE
~~~

PHASE is exactly one of recheck, write, flush, verify or finished. An invalid
phase returns usage status 2 before review or acquisition. A requested phase may
never be reached if an earlier operation fails, so also read Requested stop
observed in the output.

1. Generate the synthetic source using the earlier setup.
2. Choose a new regular-file destination and run review.
3. Read that destination and copy its exact fingerprint and confirmation.
4. Run copy-until with those tokens and the selected phase.
5. Preserve its report, exit status and any created file before another attempt.

~~~powershell
& $Lab copy-until $Image $Copy "PASTE_REVIEW_FINGERPRINT" "PASTE_REVIEW_CONFIRMATION" write
Get-Item -LiteralPath $Copy | Select-Object FullName, Length
~~~

The write-phase exercise should return a non-success result and retain an empty
file. Its report should show output-created=1, write-started=0 and verified=0.
The recheck exercise should leave no output and all three flags zero. Use a new
destination and its own review tokens for each exercise; the previous output
occupies its name even when empty.

Later stops occur after payload writes. Cancellation at flush, verify or finished
leaves verified=0 even when the retained bytes match. The finished callback can
cancel after readback and native release have succeeded. A separate verify
command can establish a later byte-comparison result, but does not rewrite the
cancelled transfer into a success. The tests save cancellation.txt and, where
applicable, later-verification.txt separately.

The Report line appears on successful and failed media operations. returned and
status should agree. output-created records exclusive file creation; write-started
records an attempted payload write; verified records completed agreement and
required release for that operation. A close error prevents successful completion.
No code in this client retries native handles or removes partial outputs.

## Qualify the matching installed service

Use the normal owner-controlled Framework configure, build, test and install
workflow for the intended SDK prefix. The practice tool is a build-tree example:

~~~powershell
Set-Location "C:\umicom\Umicom-Applications\framework"
cmake --build --preset windows-ucrt64-debug --parallel 2 --target umicom-media-image-example
~~~

Then configure and build this consumer with the earlier commands. Record the
Framework source revision, toolchain and installed prefix alongside the consumer
revision and executable digest. The injected Framework close/error tests exercise
controlled failures; these twelve consumer cases exercise real regular files.
Both remain authored coverage until run. Device selection, optical burning,
firmware boot and OS startup require their own evidence.

The HTML lesson series begins with [Read file effects separately from status](../../../content/courses/umicom-os-from-scratch/lessons/57-read-file-effects-separately-from-status.html).
Its Markdown edition begins [here](../../../content/lessons/06-umicom/umicom-os-from-scratch/57-read-file-effects-separately-from-status.md).
The shared stylesheet provides Segoe UI and Cascadia Code fallbacks; the console
continues to use the user's terminal settings.
