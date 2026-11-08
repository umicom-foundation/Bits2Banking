<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/09-share-c-policy-across-targets.md

PURPOSE:
Share one C policy across target toolchains

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Share one C policy across target toolchains

## Before starting

Complete the desktop event lab. Keep a development checkout of Framework beside Bits2Banking. Locate cmake/UmicomProfileName.cmake, src/security/profile_name.c and include/umicom/security/profile_name.h in that checkout. Reading this lesson requires no new tools; the optional build requires a C23 compiler and the matching Qt C++ kit.

## Follow the dependency

The form still calls UmiLocalProfileNameBytes. Its implementation now belongs to Umicom::profile_name, a small static C library. The account service links that same library. The older local_profile.h includes the narrow header, so existing account callers keep their function names and constant. A header describes a function; the target supplies its compiled definition. Moving only a declaration would not remove a link dependency.

~~~text
Qt form -> Umicom::profile_name -> C library string operations
Account service -> Umicom::profile_name
Account service -> credential and platform adapters
~~~

## Select a source consumer

BTB_FRAMEWORK_SOURCE opts this lab into compiling the shared source with the selected kit. It does not copy the validator into the lab. Leave the option empty for the installed desktop SDK route. Use separate build folders when the compiler, CPU or runtime changes. Do not point a WebAssembly build at an installed Windows archive.

~~~powershell
cmake -S . -B build-native-source -G Ninja -DCMAKE_BUILD_TYPE=Debug '-DCMAKE_PREFIX_PATH=C:/Qt/your-version/your-desktop-kit' '-DBTB_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework' -DBUILD_TESTING=ON
cmake --build build-native-source --parallel 2
ctest --test-dir build-native-source --output-on-failure
~~~

## Check the boundary

Replace the example Qt prefix with your actual matching kit before running. Inspect the link inputs: this source route builds profile_name.c and the view, without account database or credential code. Run Alice_7, a 49-byte name and a non-ASCII name through the form. Expect lowercase acceptance, refusal and refusal. A successful name result proves no account exists.

## Exercise and worked answer

Why is a Windows .a file unsuitable for the browser even when both use C? The archive contains target machine code and an ABI, the rules for calling functions and laying out data. C source can be portable while compiled objects are not. Rebuild the source with the target compiler. If CMake reports that the portable component is missing, use matching source or reinstall the matching SDK; do not duplicate the function in C++.

## Read the source

[labs/framework/qt-profile/CMakeLists.txt](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-profile/CMakeLists.txt). Use the matching local revision when working offline.

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Extend the view while keeping Framework authoritative](08-extend-the-view-without-duplicating-policy.md) · [Next: Build the Qt form for a browser](10-build-the-browser-application.md)
