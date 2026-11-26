<!--
Umicom Bits2Banking
File: content/wiki/framework-sdk.md

PURPOSE:
Explain how to choose and verify one Framework SDK for a native consumer.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Framework SDK

![Umicom Foundation](../assets/branding/umicom-wordmark.svg){ .umicom-wordmark .umicom-wordmark-light width="215" }
![Umicom Foundation](../assets/branding/umicom-wordmark-on-dark.svg){ .umicom-wordmark .umicom-wordmark-dark width="215" }

A Software Development Kit provides public headers and libraries that an application can use. The Framework SDK describes the supported library names in a CMake package. A consumer project chooses that package and compiles against its public interfaces.

1. Open the [venue report workshop](../simple-steps/framework-sdk-venue-report/index.md). In File Explorer, find the SDK folder from which you intend to build. Confirm that the headers and the CMake package metadata belong to the same release.
2. Set up a fresh build directory for that SDK. Reusing a previous build directory can retain an older CMake package path. Check which package the first configure used before interpreting a compile error as a problem in the SDK.
3. Build and test the unchanged example. Use the short sample input first. Record its printed totals and the test outcome so you can compare after editing.
4. Change one validated input or interface at a time. For a venue report, try a valid row at a numeric bound and one just beyond it. Look for the full accepted report in the first run and a clear refusal in the second.

An *installed SDK check* uses the published headers and libraries from one installed package. A source-tree build can also see files that were omitted from the export. Record which one you used when you report your result.

If configuration reports that the headers differ from the exported identity, [read the selected directory and the two fingerprints](sdk-header-identity.md) before trying another build.

[Develop applications with Framework](../simple-steps/course-guides/umicom-development.md) · [Contributor wiki](index.md)
