<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/48-qualify-produced-images-in-stages.md

PURPOSE:
Qualify produced images in stages

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->



# Qualify produced images in stages

![Umicom](../../../assets/branding/umicom-wordmark.svg)

[Umicom icon](../../../assets/branding/umicom.ico)

## Prepare the producer review

Return to the media-stage and media-iso workflow from lesson 43. Setup accepts supported x86-64 Linux boot-protocol inputs, copies only the reviewed files into a new tree and invokes the explicitly selected native Linux GRUB program. The process exit code reports whether that program completed successfully; it cannot prove the resulting image is structurally acceptable or boots.

After a successful producer exit, Setup now uses the same ISO inspection service as Boot Media. It requires ISO9660 and supported El Torito observations. This removes a disagreement in format rules, but does not turn two calls to the same parser into two independent implementations verifying each other.

## Keep partial output available

A producer may leave output after returning an error. It may also return zero while creating malformed output. The Setup workflow marks either unsuccessful outcome as incomplete and retains the new files for diagnosis. A later attempt should use another reviewed new directory, rather than silently overwriting evidence.

The authored Setup cases distinguish an inconsistent volume size, a missing terminator, a zero BIOS count, an out-of-range load and unsupported emulation. Their producer callback writes synthetic records. They verify the boundary around producer output without running GRUB. Linux-only producer cases may be skipped on Windows; record those skips separately.

## Describe the supported distribution route

An ISO artifact can be intended for optical boot, but copying its bytes to a USB file does not establish USB boot compatibility. A hybrid image may contain additional partition descriptions. The Boot Media service separately inspects its disk layout before a transfer review. Physical writing remains an explicitly gated backend, and there is no built-in optical burning or safe-eject workflow in this profile.

The current ISO-producing path does not accept any arbitrary Umicom Kernel executable or any RISC-V payload. A new architecture requires an explicit boot-protocol adapter, compatible producer and firmware qualification. Keep the educational hosted inspector separate from claims about a freestanding kernel.

## Record what each observation proves

Create a small evidence table before running a real image. Identify the kernel and initrd hashes, Framework revision, GRUB version, host architecture, output ISO hash, structural result, target firmware, guest or device identity and startup observation. Do not fill a cell with passed until that step was executed against those inputs.

A successful memory fixture checks parser behaviour. A successful producer run checks one tool invocation. A matching file-copy digest checks observed bytes. A guest boot checks that guest and firmware configuration. A real USB or CD boot adds a different transport and hardware observation. Preserve these outcomes individually so one success cannot hide a skipped stage.

## Practice a refusal and plan the next step

Run the installed lab endian scenario, record its status and flags, then explain why it must not be labelled a boot failure: no boot was attempted. Read the Setup media.iso_endian case and identify where completed remains false even after the producer callback succeeds.

For a real failed build, retain the producer log and partial output, compare receipt-bound inputs and isolate the first failed stage. For a structural refusal, identify the unsupported or malformed record. For a guest failure, preserve serial output and firmware identity. Only then choose the next repair or qualification step. These exercises do not authorize writing a device or releasing an image.

## Find out where an ISO came from

An ISO is a file that represents an optical disc. Provenance is the record of who made the file and how. Start with the build run you chose from the project repository. Record the reviewed Umicom OS, Framework and Buildroot commits. A commit is a saved revision of the project's files. Buildroot is the tool that assembles the small Linux system used by the Foundation guest. The OS source lists which Buildroot commit to use.

SHA-256 calculates a fingerprint from a file's bytes. Written in hexadecimal, it has 64 characters using digits 0–9 and letters A–F. If the fingerprint matches a separately reviewed checksum, it gives evidence that you have the expected bytes. A fingerprint and file from an unknown source can agree with each other. Review the origin before relying on the checksum.

The Umicom OS `tools/optical-qualification/review-candidate.cmake` tool ties together four downloads from the same selected workflow run: guest evidence, optical evidence, the Foundation bundle and the optical candidate. It compares recorded revisions, bundle and ISO hashes, and the saved direct-boot results. `UMICOM_OPTICAL_CANDIDATE_FILES 1` is the file review record. Its `firmware-boot=not-run` line describes that stage. The direct-boot runner loads the kernel itself, so an optical boot through firmware still needs its own evidence.

## Plan four observations of the same file

Firmware is the code that starts first and looks for something to boot. BIOS and UEFI are two ways a PC or a virtual machine can start. Umicom OS also has two guest modes. In a normal run, Foundation starts its two test services and reaches the ready state. In a forced recovery run, Foundation skips those services and reaches the recovery console. A serial log is the text the host captures from the guest's serial output.

| Firmware | Guest mode | What to look for in the serial log |
| --- | --- | --- |
| BIOS | Normal | Two services completed and Foundation reported ready. |
| BIOS | Forced recovery | Recovery was requested and no services completed. |
| UEFI | Normal | Two services completed and Foundation reported ready. |
| UEFI | Forced recovery | Recovery was requested and no services completed. |

1. Keep the original artifacts in four separate ordinary folders. Record the run reference and the reviewed ISO and bundle manifest digests. Keep notes in another folder.
2. For an authorised test, use a dedicated virtual machine with the ISO attached as optical media and no writable guest disk. Save a separate folder per run ID. In it, keep the host's firmware and attachment record, the actual emulator process exit, and the complete serial log through `UMICOM_SHUTDOWN`. Record the ISO, host record and log hashes.
3. Give the owner-reviewed evidence to `tools/optical-qualification/verify-firmware-captures.cmake`. It calls the native optical checker for the BIOS pair and the UEFI pair. The checker requires exit code zero, the matching ISO and bundle, and the expected markers in each complete log. The combined `UMICOM_OPTICAL_FIRMWARE_MATRIX 1` receipt covers the four submitted captures. The reviewer confirms the host settings and attachment from the original records.
4. If a run fails or stops early, preserve its files and label the outcome. Keep USB, physical discs, Secure Boot and installation for separate reviews with their own evidence.

Find `docs/foundation/optical-candidate-review.md` and `docs/foundation/optical-firmware-matrix.md` in the Umicom OS checkout. Start with the [native image workflow](https://github.com/umicom-foundation/umicom-os/blob/main/docs/foundation/native-image-workflow.md).

## Practise with ordinary files

Save a short text file in a scratch folder. Make a copy under a different name. In PowerShell, enter the full paths to the two files. The commands read their bytes.

~~~powershell
$FirstFile = Read-Host 'Full path to the first text file'
$SecondFile = Read-Host 'Full path to its copy'
$FirstHash = (Get-FileHash -LiteralPath $FirstFile -Algorithm SHA256 -ErrorAction Stop).Hash
$SecondHash = (Get-FileHash -LiteralPath $SecondFile -Algorithm SHA256 -ErrorAction Stop).Hash
$FirstHash -eq $SecondHash
~~~

Expect `True` for a byte-for-byte copy. Change one letter in the copy, save it, and rerun the commands. Expect `False`. Changing a filename leaves the bytes alone, while saving a changed letter changes the bytes. [PowerShell file-hash reference](https://learn.microsoft.com/en-us/powershell/module/microsoft.powershell.utility/get-filehash)

On paper, suppose your file review matches ISO A. BIOS normal has a complete log for A, BIOS recovery used ISO B, UEFI normal has a complete log for A, and UEFI recovery was never run. Mark each row in your own table. The BIOS recovery row has an ISO mismatch. The UEFI recovery row is pending. Keep both rows visible and record the matrix as incomplete. This exercise uses only ordinary files and paper.

[Installed SDK lab and commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-iso-inspection/README.md) · [Course contents](../../../courses/umicom-os-from-scratch/index.html)

[Written contents](index.md) · [Previous lesson](47-interpret-uefi-boot-catalogue-counts.md)

<!-- Repository laboratory sources live outside the published content root.
Public repository links replace the former local-only routes, retained here for review:
../../../../labs/native/framework-iso-inspection/README.md
Offline source files remain available in their listed repository/learning-pack locations. -->

[Next lesson: bind device rows to inventory identity](49-bind-device-rows-to-inventory-identity.md)
