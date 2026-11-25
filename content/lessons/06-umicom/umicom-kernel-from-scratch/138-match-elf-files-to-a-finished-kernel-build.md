<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/138-match-elf-files-to-a-finished-kernel-build.md

PURPOSE:
Match ELF files to a finished Kernel build

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Match ELF files to a finished Kernel build

You have two files from an Umicom Kernel build. Both are prepared for the same kind of processor. Before handing either file to the next person, check which build finished and which saved identity belongs to each file.

## 1. Read the end of the build

In the completed RISC-V Debug build, Ninja recorded all **6,173** planned build actions. The final action linked `bin/umicom-kernel.elf` and the build command returned exit code `0`. The action count describes work such as compiling and linking. The exit code is the final number the build tool gives the shell. Here it confirms that the requested build finished successfully.

## 2. Read what the two headers declare

An **ELF** is an Executable and Linkable Format file. Its header tells a tool how to read it. The entry address is where a suitable loader would hand control to the program. In the saved build, the two headers gave the same format, machine, file type, and entry address. [ELF header reference](https://gabi.xinuos.com/elf/02-eheader.html)

| Built file | Header format and machine | Type and entry | File length |
| --- | --- | --- | --- |
| `bin/umicom-kernel.elf` | `elf64-littleriscv`, `EM_RISCV` | Executable, `0x80200000` | 2,220,176 bytes |
| `bin/umicom-console.elf` | `elf64-littleriscv`, `EM_RISCV` | Executable, `0x80200000` | 2,220,184 bytes |

`elf64-littleriscv` describes 64-bit RISC-V ELF with little-endian byte order. Their different lengths already show that the files differ. A **digest** is a value calculated from all the bytes of a file. The SHA-256 digest lets you check a saved file even when two files have the same length and the same visible header fields.

## 3. Match each name to its saved digest

Draw two cards. On the Kernel card write `bin/umicom-kernel.elf` and `K`. On the console card write `bin/umicom-console.elf` and `C`. The letters stand for the two different full digests. First match both cards to this list.

~~~text
Saved image record
bin/umicom-kernel.elf  -> K
bin/umicom-console.elf -> C
~~~

Now swap the letters on your two cards. Both files can still show the expected header, and both name-to-digest comparisons fail. Put the letters back and check the cards again. In a real review, compare the full digests by filename.

The saved `qualification/identity.json` recorded a digest for the selected source inventory and individual SHA-256 values for the ELF files, including this pair. It was captured after the build. A separate host verification compared the current source and ELF identities with that saved record and reported agreement. The field `sourceStableDuringBuildVerified` was `false`, so record source stability during the build as unverified. Keep the registered `kernel.qualification.identity` CTest result and any QEMU guest result separate from this artifact check. Both are unobserved here.

## 4. Try a read-only check on an existing build

If you have a completed build and its saved identity file, open PowerShell. Replace the example folder with its location. Use `llvm-readobj` from your LLVM tools to read both headers, then compare the full digests by their two names. [LLVM object reader](https://llvm.org/docs/CommandGuide/llvm-readobj.html)

~~~powershell
$Build = (Resolve-Path 'path-to-your-completed-build').Path
$KernelElf = Join-Path $Build 'bin/umicom-kernel.elf'
$ConsoleElf = Join-Path $Build 'bin/umicom-console.elf'
llvm-readobj --file-header $KernelElf $ConsoleElf
if ($LASTEXITCODE -ne 0) { throw 'Could not read the ELF headers.' }
Get-FileHash -Algorithm SHA256 -LiteralPath $KernelElf, $ConsoleElf
$Record = Join-Path $Build 'qualification/identity.json'
$Saved = Get-Content -LiteralPath $Record -Raw -ErrorAction Stop | ConvertFrom-Json
"Saved Kernel digest $($Saved.images.'bin/umicom-kernel.elf')"
"Saved console digest $($Saved.images.'bin/umicom-console.elf')"
~~~

Match the printed digests by filename. The letters in a hexadecimal digest can be displayed in uppercase or lowercase. For the separate source and artifact check, choose the source checkout that belongs with that build. This example uses the recorded RISC-V configuration. The Kernel guide `docs/BUILD_IDENTITY.md` describes the verify mode and how to compare other configurations.

~~~powershell
$Source = (Resolve-Path 'path-to-your-kernel-source').Path
$Check = Join-Path $Source 'cmake/QualificationEvidence.cmake'
cmake "-DSOURCE=$Source" "-DBINARY=$Build" -DMODE=verify -DVERIFY_CONFIGURED_CONTEXT=ON -DARCHITECTURE=riscv64 -DABI=lp64 '-DMACHINE=virt,aclint=off' -P $Check
if ($LASTEXITCODE -ne 0) { throw 'The Kernel identity could not be verified.' }
~~~

Look for `Kernel source and ELF identities agree`. If the record is missing or different, retain it and confirm which build and source folders you selected. Record the build exit, the file comparisons, and any guest result as separate observations. For this completed build example, guest behaviour remains unobserved.

[Course contents](index.md) · [Previous lesson · Run Kernel evidence checks on the host](137-run-kernel-evidence-checks-on-the-host.md) · [Review one Kernel ELF from a partial build record](136-review-one-kernel-elf-from-a-partial-build.md) · [Check the configured Kernel platform](133-check-the-configured-kernel-platform.md) · [Next lesson · Find a short device-tree path after a long branch](139-find-a-short-device-tree-path-after-a-long-branch.md) · [HTML edition](../../../courses/umicom-kernel-from-scratch/lessons/138-match-elf-files-to-a-finished-kernel-build.html)
