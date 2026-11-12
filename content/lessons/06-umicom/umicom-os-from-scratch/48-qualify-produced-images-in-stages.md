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

[Installed SDK lab and commands](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-iso-inspection/README.md) · [Course contents](../../../courses/umicom-os-from-scratch/index.html)

[Written contents](index.md) · [Previous lesson](47-interpret-uefi-boot-catalogue-counts.md)

<!-- Repository laboratory sources live outside the published content root.
Public repository links replace the former local-only routes, retained here for review:
../../../../labs/native/framework-iso-inspection/README.md
Offline source files remain available in their listed repository/learning-pack locations. -->

[Next lesson: bind device rows to inventory identity](49-bind-device-rows-to-inventory-identity.md)
