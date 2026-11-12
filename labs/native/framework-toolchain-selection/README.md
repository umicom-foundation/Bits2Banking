![Umicom](../../../content/assets/branding/umicom-logo.svg)

# Native toolchain selection with Umicom Framework

This C23 client consumes an installed Framework SDK. It demonstrates profile storage admission, selection with an owned child environment, repeated compiler synchronization and explicit position-independent compile intent. It never launches the synthetic compiler names in its fixtures.

## Prerequisites

Use a complete SDK installation from a reviewed Framework revision that includes these public APIs:

- **umi_toolchain_profile_storage_valid**
- **umi_toolchain_catalogue_select_with_environment**
- **umi_compiler_centre_sync_toolchain**
- **umi_compiler_provider_plan**

CMake must provide **Umicom::compiler**, **Umicom::toolchain** and **umicom_apply_application_branding**. Headers and libraries must come from the same installation. A missing API or target is an SDK selection or installation issue; do not work around it by compiling Framework source files directly into this client.

Use CMake 3.25 or newer, Ninja and a C23-capable compiler. On Windows, the branding helper also needs the resource compiler and the SDK's canonical icon resources. The helper applies Umicom product identity and the Windows icon; this console client has no custom font-rendering surface. The course pages use the shared Umicom learning stylesheet, logo and SVG/ICO favicons.

## Configure, build and check

The following PowerShell example assumes the repository is **C:\training\Umicom-Bits2Banking** and the complete SDK is installed in **C:\sdk\umicom**. Substitute your actual paths. Run each command separately and stop on errors. Framework installation and platform setup are separate prerequisites.

~~~powershell
Set-Location C:\training\Umicom-Bits2Banking
cmake -S labs/native/framework-toolchain-selection -B build/toolchain-selection -G Ninja -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=C:/sdk/umicom -DBUILD_TESTING=ON
cmake --build build/toolchain-selection
ctest --test-dir build/toolchain-selection --output-on-failure
~~~

For a shared-library SDK, arrange the documented runtime search path before executing the client. **CMAKE_PREFIX_PATH** helps CMake find development packages; it does not install runtime DLLs beside the executable. This lab selects **NO_RUNTIME_DEPLOYMENT** deliberately, so a successful link is not evidence of runtime deployment.

For the single-configuration Windows example, individual scenarios can then be inspected with:

~~~powershell
.\build\toolchain-selection\btb-framework-toolchain-selection.exe storage
.\build\toolchain-selection\btb-framework-toolchain-selection.exe selection
.\build\toolchain-selection\btb-framework-toolchain-selection.exe compiler
.\build\toolchain-selection\btb-framework-toolchain-selection.exe pic
~~~

On other hosts, use the executable name and runtime library setup appropriate to that platform. A multi-configuration generator also needs a consistent configuration for building, testing and finding the executable.

## Expected checks

| Scenario | Required behavior |
| --- | --- |
| storage | FAILED remains representable metadata, conversion returns UNAVAILABLE, and the receiving profile is unchanged. Unterminated display text is rejected. |
| selection | Successful selection publishes CC and receiving process-entry pointers. A newline-bearing path refuses environment preparation and preserves selection, revision and both owners. |
| compiler | A second same-family selection updates the provider executable and profile linker driver together, with one provider and one named profile. |
| pic | A C COMPILE request maps explicit PIC intent to one -fPIC argument. CHECK with that intent returns NOT_IMPLEMENTED and preserves the previous plan. |

CTest registers four **bits2banking.toolchain-selection.** scenarios. **check.cmake** checks the complete output and exit status. Success output is produced only after each native assertion succeeds; it is an expected result, not a recorded qualification result.

## Read the ownership choices

The profile and environment matrices are large, so the serial lab uses static owners. The compiler centre is explicitly allocated and released. A product with several projects should use per-instance lifetime and synchronization instead of these lab globals.

The saved environment is only a byte snapshot for comparing failure behavior. Its copied pointer view is never passed to a process. An independently usable environment copy needs a service that rebinds pointers to the receiving arrays.

**MakeProfile** creates synthetic VALIDATED metadata and leaves **bin_directory** empty. This avoids an accidental dependency on the host's inherited PATH length. No probe has established those fake drivers or the target. The checks exercise metadata contracts only.

## Troubleshooting and extensions

1. If configuration cannot find a package or target, inspect **CMAKE_PREFIX_PATH**, the installed components and the selected package path in the configure output.
2. If linkage reports a missing function, compare the installed headers and libraries. Rebuild and reinstall the matching SDK through its normal workflow, then configure a fresh client build directory.
3. If a runtime dependency is missing, correct the platform's runtime search path or approved deployment procedure. Do not treat that as a failed semantic assertion.
4. If an assertion fails, preserve its scenario, expression, binary and SDK identities. Compare the expected service contract before changing the check.
5. After these checks pass in your environment, add a separate real-tool integration exercise and record compiler/target diagnostics. Keep that evidence distinct from this lab and from Studio GUI qualification.

Continue with [Learning Build Systems](../../../content/courses/learning-build-systems/index.html), beginning at [stored profiles and usability](../../../content/courses/learning-build-systems/lessons/18-profile-storage-and-tool-usability.html). For the complete services, inspect the Framework guides on [toolchain selection](../../../../Umicom-Applications/framework/docs/development/toolchain-selection-publication.md) and [compiler synchronization](../../../../Umicom-Applications/framework/docs/development/compiler-toolchain-synchronization.md) when the ecosystem sibling checkout is available.

Sammy Hegab · Umicom Foundation · MIT
