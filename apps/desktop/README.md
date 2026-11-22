![Umicom](../../content/assets/branding/umicom-wordmark.svg)

# Umicom Bits2Banking desktop reader

[![Umicom icon](../../content/assets/branding/umicom-icon.svg)](../../content/assets/branding/umicom.ico)

The desktop reader uses the same Umicom Framework learning catalogue as Umicom Studio IDE. Keep the complete Bits2Banking library together. Each course manifest names its resources and their checksums. Framework reads the selected local files and verifies them before displaying them.

## Build the desktop reader

1. Locate an installed Umicom Framework SDK with the `learning_catalogue_gtk4` and `platform` components, the SDK's brand resources, and its matching GTK4 runtime. Use the C23 toolchain and runtime environment required by that SDK.
2. From the Bits2Banking repository root, configure and build the application. Replace the example SDK path with the prefix you selected.

   ```powershell
   $sdk = 'C:/umicom/sdk/umicom-framework'
   cmake -S apps/desktop -B build/bits2banking-desktop -G Ninja "-DUMICOM_SDK_ROOT=$sdk" -DBUILD_TESTING=ON
   cmake --build build/bits2banking-desktop
   ctest --test-dir build/bits2banking-desktop --output-on-failure
   ```

   Expect the configure step to select the requested SDK prefix. The command tests check help and argument refusals before a window opens. Start the application separately to review window appearance and reading behaviour.
3. If CMake reports a missing component or resource, check the SDK origin, package contents and toolchain. If the executable reports a missing GTK runtime library, use the matching runtime environment supplied by the SDK. The application builds with the SDK's approved SVG and Windows ICO resources.

## Open a local course

1. Start the application from any folder. With no options, the catalogue opens and lets you choose the library and relative manifest yourself. Set the library to the folder containing `content` and `learning-packs`.
2. To dispatch the first manifest at startup, run these examples from the repository root. Each command opens its own reader window. On Linux, use the executable without `.exe`.

   ```powershell
   $library = (Get-Location).Path
   $reader = '.\build\bits2banking-desktop\bin\umicom-bits2banking.exe'
   & $reader --root $library --manifest 'learning-packs/native-statement-calculations.json'
   & $reader --root $library --manifest 'learning-packs/sql-statement-reconciliation.json'
   & $reader --root $library --manifest 'learning-packs/accessible-statement-review.json'
   & $reader --root $library --manifest 'learning-packs/go-statement-tools.json'
   ```

3. Wait for the catalogue status to show the result. Select the course guide, then follow its lesson sequence. If a lookup fails, check the absolute library path and the manifest's case and spelling. If verification reports a checksum mismatch, use the matching reviewed lesson files and manifest from the same revision.

The catalogue supports its usual search and reading controls. It presents verified course content and examples for review. Run exercises separately with their documented compiler or tool. Use the website for the published browser presentation.
