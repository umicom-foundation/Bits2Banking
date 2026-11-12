<!--
Umicom Bits2Banking
File: labs/native/framework-gpt-inspection/README.md

PURPOSE:
Build and study a memory-only GPT client using the installed Framework service.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../content/assets/branding/umicom-logo.svg)

# Inspect partition tables through Framework

This C23 console application constructs a synthetic byte source and passes it to the installed **Umicom::gpt_image** service. It demonstrates exact reads, logical-block units, refusal without output mutation and a fresh retry. The byte source contains no executable boot code or filesystem. The lab opens no files or devices.

Start with [lesson 51](../../../content/courses/umicom-os-from-scratch/lessons/51-connect-an-owned-image-read-port.html), then follow the six lessons in order. The earlier ISO and reviewed-file-copy labs remain separate.

## Prepare the installed SDK

1. Build and install a Framework SDK that exports Umicom::gpt_image and image_inspection/gpt.h.
2. Identify the installed prefix. The commands use C:/umicom/installed/framework as an example; substitute your actual qualified prefix consistently.
3. Use a compiler, architecture and runtime compatible with that SDK. Editing source does not change installed archives.
4. Run each command separately. Stop on errors and inspect the native exit code immediately.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\framework-gpt-inspection -B .\build\framework-gpt-inspection -G Ninja -DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe -DUMICOM_EXPECTED_SDK_PREFIX=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build .\build\framework-gpt-inspection --parallel 2
ctest --test-dir .\build\framework-gpt-inspection --output-on-failure --no-tests=error
~~~

Configuration checks the package origin, SDK environment metadata and installed target layout. If a reused build directory chooses an older cached package, configure a new build directory with the intended prefix. Do not mix headers from a source checkout with another SDK's archive.

For Linux, use the same source with a separate build directory, matching compiler and absolute SDK prefix. The executable has no .exe suffix. Neither host is claimed qualified by these instructions.

## Run an observation

~~~powershell
& .\build\framework-gpt-inspection\gpt-inspection.exe valid-512
& .\build\framework-gpt-inspection\gpt-inspection.exe read-failure
& .\build\framework-gpt-inspection\gpt-inspection.exe retry
~~~

Every scenario begins with a valid synthetic table and requires one active partition. The normal printed observation includes logical-block size and usable addresses.

| Scenario | Required observation |
| --- | --- |
| valid-512 | One partition, 512-byte blocks, usable interval 34..990, four reads. |
| valid-4096 | One partition, 4096-byte blocks, usable interval 6..122, four reads. |
| reservation | Matching checksums cannot admit an undersized table reservation. |
| stride | A four-slot, 384-byte entry layout is refused despite matching checksums. |
| overlap | Two active entries sharing one endpoint block are refused. |
| backup | Different disk identifiers in otherwise consistent header copies are refused. |
| read-failure | The third exact read returns IO_ERROR and output remains unchanged. |
| retry | A malformed source is refused, then a fresh valid source is accepted. |

Expected success is exit zero after the scenario's assertions. A controlled refusal prints its status and states that the previous observation stayed unchanged. An unknown scenario or wrong argument count returns two. A failed assertion prints its source location and condition, then returns one. These are expected results to observe, not recorded execution evidence.

## Understand the boundaries

- image.c creates synthetic metadata and calculates the producer-side CRCs. It does not interpret or accept partition tables.
- port.c checks each requested byte range and implements a controlled read failure.
- main.c consumes the real Framework API and checks observations. It releases its source through one cleanup path.
- lab.h declares only the owned byte source and the lab's small adapter functions.
- CMakeLists.txt links the installed target and applies Framework application branding.

The source encoder deliberately uses four slots while reserving enough table space. This makes the reservation scenario distinct from an array-length or checksum failure. The same data can be structurally consistent without being a bootable operating system.

On Windows, Framework embeds the canonical Umicom ICO in the executable. The course uses canonical SVG artwork, SVG/ICO favicons and shared local typography. The terminal host controls its own font. No font is downloaded by this lab.

## Recover from a failure

Keep the original configure or compiler diagnostic before changing settings. A missing exported target usually means the selected installation lacks the new component; confirm its producer revision and installation path. A runtime assertion needs the scenario, compiler, source identity and exact output. Do not remove the assertion or alter the expected status just to make the program return zero.

The service checks table structures, not signatures, filesystem contents or real boot behavior. It neither repairs tables nor generates new disk identifiers for deployment. Use [QUALIFICATION.md](QUALIFICATION.md) to record actual evidence, and keep native media interfaces, device writing and firmware boot as separate qualification tasks.
