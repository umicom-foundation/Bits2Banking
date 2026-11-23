![Umicom](../../../content/assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../content/assets/branding/umicom-icon.svg) · [Windows icon](../../../content/assets/branding/umicom.ico)

# Read an ext-family header inside a partition boundary

The program supplies a small header in memory and calls the Umicom Framework SDK. You can change the advertised partition length without moving, writing or allocating a disk image.

## Build the exercise

1. Install a matching Umicom Framework SDK. The package must export `Umicom::gpt_image` and contain `umicom/image_inspection/gpt_filesystem.h`.
2. Open PowerShell in your Bits2Banking checkout. Replace `C:\SDK\UmicomFramework` with the absolute SDK directory you installed. Use a C23-capable toolchain that matches the SDK.

```powershell
cmake -S labs/native/framework-filesystem-header -B build/filesystem-header -G Ninja -DUMICOM_EXPECTED_SDK_PREFIX=C:/SDK/UmicomFramework
cmake --build build/filesystem-header
ctest --test-dir build/filesystem-header --output-on-failure --no-tests=error
```

3. Run each case from the same checkout and compare the first line and read count.

```powershell
.\build\filesystem-header\btb-filesystem-header.exe present
.\build\filesystem-header\btb-filesystem-header.exe partition-too-short
.\build\filesystem-header\btb-filesystem-header.exe unknown-signature
.\build\filesystem-header\btb-filesystem-header.exe volume-too-large
```

| Case | Expected output | Reads |
| --- | --- | --- |
| `present` | `header accepted`, then a 4096-byte filesystem block and a 16777216-byte volume | 1 |
| `partition-too-short` | `partition refused before reading the header`, then `previous observation unchanged` | 0 |
| `unknown-signature` | `header read, but ext-family signature absent`, then `previous observation unchanged` | 1 |
| `volume-too-large` | `header read, but filesystem volume exceeds partition`, then `previous observation unchanged` | 1 |

All four commands should exit with code 0. The exercise checks that the latter three operations returned the expected refusal. Code 1 means the observed status, read count or output differed from the prediction. Use `ctest --test-dir build/filesystem-header -V` to identify the scenario. If configuration reports a missing filesystem metadata header, select an SDK containing this API and configure a new build directory.

The client supplies an already described partition. A production application first inspects and validates the GPT table on its own input. A recognised header provides geometry and recorded features. Filesystem health and boot readiness require separate checks.

[Lesson](../../../content/lessons/06-umicom/umicom-os-from-scratch/65-read-a-filesystem-header-within-its-partition.md)
