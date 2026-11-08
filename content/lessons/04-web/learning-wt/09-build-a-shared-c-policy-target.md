<!--
Umicom Bits2Banking
File: content/lessons/04-web/learning-wt/09-build-a-shared-c-policy-target.md

PURPOSE:
Build one shared C policy for the web adapter

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Build one shared C policy for the web adapter

## Before starting

Read the first eight Wt lessons and open the lab CMakeLists.txt beside Framework cmake/UmicomProfileName.cmake. You need matching C23 and C++17 compilers and Wt 4 packages to run the build. Reading the dependency graph requires no running server.

## Trace one call

The form calls UmiLocalProfileNameBytes through umicom/security/profile_name.h. Its implementation belongs to Umicom::profile_name. The broader account service links the same target; it does not maintain a second copy. The view library owns Wt presentation code, while main.cpp supplies the HTTP entry point.

~~~text
HTTP main -> btb-wt-profile-view -> Umicom::profile_name
Event fixture -> btb-wt-profile-view -> Umicom::profile_name
Account service -> Umicom::profile_name
~~~

## Choose the dependency deliberately

The installed SDK route consumes a compiled archive and package metadata. BTB_FRAMEWORK_SOURCE instead compiles the small shared C source with this build. Use a separate build directory for each route. Compare the selected Framework revision and compiler before treating results from the two routes as equivalent.

~~~powershell
cmake -S . -B build-source -G Ninja -DCMAKE_BUILD_TYPE=Debug '-DCMAKE_PREFIX_PATH=C:/libraries/wt' '-DBTB_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework' -DBUILD_TESTING=ON
cmake --build build-source --parallel 2
ctest --test-dir build-source --output-on-failure -R '^btb\.wt_profile\.'
~~~

## Inspect and recover

Replace the Wt prefix with your actual compatible installation. Run from labs/framework/wt-profile and stop at the first failed command. Inspect CMakeCache.txt for the Framework source option and Wt package directory. If the SDK lacks profile_name, install the matching SDK or select its source explicitly. Do not copy the validator into the web adapter to hide a dependency error.

## Exercise and worked answer

A learner includes the new header but still links an older SDK and receives an undefined symbol. Is the declaration enough? No: the compiler has a declaration, but the linker still needs the matching definition. Record both header and library identities. Repair the dependency selection, rebuild, and retain the failed and corrected logs separately. A server that links still needs browser observation.

## Read the source

[labs/framework/wt-profile/CMakeLists.txt](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/wt-profile/CMakeLists.txt). Use the matching local revision when working offline.

## Continue learning

[Course contents](../../../courses/learning-wt/index.html) · [Previous: Share Framework services across web and desktop](08-share-framework-services-across-frontends.md) · [Next: Exercise production widget events without HTTP](10-exercise-server-events-without-http.md)
