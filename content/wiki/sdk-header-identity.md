<!--
Umicom Bits2Banking
File: content/wiki/sdk-header-identity.md

PURPOSE:
Teach contributors to diagnose a configured SDK header identity mismatch.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Read an SDK header identity error

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A C header describes an interface your application can compile against. Framework records a SHA-256 fingerprint for its public header set when it exports an SDK. A fingerprint is a short string calculated from the content. CMake can compare the exported value with the value calculated from the header directory it resolves.

## 1. Find the first refusal

Open the text from the consumer project’s configure step. If you saved it as `configure.log`, run this command from the folder containing that file.

```powershell
Select-String -LiteralPath './configure.log' -SimpleMatch 'Installed headers differ from the exported SDK identity' -Context 0,3
```

The current diagnostic gives the public header directory, the exported fingerprint and the observed fingerprint. Older consumer helpers can show only the first line. If the command finds no line, read the earliest CMake error instead. It may identify a missing component or a different package.

## 2. Check the selected directory

Copy the value after `Public header directory` into the example below. The command simply opens the directory entry so you can compare the path with the intended SDK prefix.

```powershell
$HeaderDirectory = 'C:\path\to\installed\framework\include'
Get-Item -LiteralPath $HeaderDirectory
```

If the path points to an older SDK, check the package location supplied during configure. If the path is the one you intended, the two differing fingerprints tell you that the header set and export disagree. They do not identify which individual file changed.

## 3. Configure with one complete SDK

1. Choose a complete SDK from a single build and leave the previous installation available for comparison.
2. Follow the [installed SDK workshop](../simple-steps/framework-sdk-venue-report/index.md) with the new prefix. Choose a fresh build directory so CMake does not reuse an old package choice.
3. Look for `Installed Framework layout and public-header identity verified`. Continue with the workshop build and run once configure succeeds.

A successful identity check confirms that the chosen public headers agree with the CMake export. The subsequent compile and run check that your actual consumer can use that SDK.

[Framework SDK wiki](framework-sdk.md) · [Contributor wiki](index.md)
