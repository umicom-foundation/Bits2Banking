<!--
Umicom Bits2Banking
File: labs/framework/qt-profile/README.md

PURPOSE:
Build and observe the existing Qt form through a shared portable Framework C policy.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Qt profile-name laboratory

This form validates a name through Framework C. It does not create an account, collect a password or contact a broker. Qt requires a C++ adapter; the naming policy has one C implementation in Framework. The same existing controls are used for desktop, browser and mobile exercises.

## Prepare

Use CMake 3.26 or later, Ninja, a C23 compiler, a C++17 compiler and Qt 6.5 or later Widgets from a mutually compatible kit. Desktop event tests also need Qt Test. A kit is a matched compiler, runtime, target and library set. Replace the example installation paths below with actual paths. Run each command separately and stop on an error.

There are two dependency choices. An installed desktop Framework SDK must contain the profile_name component. Alternatively, BTB_FRAMEWORK_SOURCE compiles the small C target from a Framework checkout using the chosen toolchain. Cross-target exercises require this explicit source route. It does not configure the Framework root or bring account storage into the form.

## Desktop using an installed SDK

From this lab directory in a matching compiler environment:

~~~powershell
cmake -S . -B build-desktop-sdk -G Ninja -DCMAKE_BUILD_TYPE=Debug '-DCMAKE_PREFIX_PATH=C:/umicom/installed/applications;C:/Qt/your-version/your-desktop-kit' -DBUILD_TESTING=ON
cmake --build build-desktop-sdk --parallel 2
ctest --test-dir build-desktop-sdk --output-on-failure
.\build-desktop-sdk\btb-qt-profile.exe
~~~

Ensure the matching Qt and compiler runtime directories are on PATH before launch. On Linux use compatible Linux prefixes and ./build-desktop-sdk/btb-qt-profile. Keep a separate build directory for each compiler and target.

## Desktop using the shared C source

~~~powershell
cmake -S . -B build-desktop-source -G Ninja -DCMAKE_BUILD_TYPE=Debug '-DCMAKE_PREFIX_PATH=C:/Qt/your-version/your-desktop-kit' '-DBTB_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework' -DBUILD_TESTING=ON
cmake --build build-desktop-source --parallel 2
ctest --test-dir build-desktop-source --output-on-failure
.\build-desktop-source\btb-qt-profile.exe
~~~

The source mode builds Umicom::profile_name from src/security/profile_name.c. The library has no credential, database, GUI or platform-service link dependency. The same source backs the existing local-profile account API. Position-independent code allows this static library and the view to be linked into Android's application module.

## Browser and mobile targets

Follow the complete lessons rather than switching a desktop build cache to a different target:

1. [Build the browser application](../../../content/courses/learning-qt/lessons/10-build-the-browser-application.html) selects the matching Emscripten and Qt Wasm kit.
2. [Serve and observe the build](../../../content/courses/learning-qt/lessons/11-serve-and-observe-the-web-build.html) checks the generated resource set and actual browser interaction.
3. [Package for Android](../../../content/courses/learning-qt/lessons/13-package-the-android-lab.html) separates native compilation, APK packaging and device observation.
4. [Build for iOS](../../../content/courses/learning-qt/lessons/14-build-and-observe-on-ios.html) uses macOS, Xcode and a matching Qt iOS kit.

The CMake lab uses qt6_add_executable for target-specific application finalization. BUILD_TESTING is OFF in the cross-target commands. Even if it is ON, desktop offscreen CTest is not registered during cross-compilation. Device, simulator and browser runs need their own observation records. No target run is claimed by this source guide.

## Observe the same contract

1. Enter Alice_7 and choose Check name. Expect Accepted name: alice_7.
2. Enter ../../other and activate the control again. Expect refusal to replace the previous success.
3. Try 48 letters, then 49. Expect acceptance followed by refusal.
4. Try a non-ASCII name. The naming contract rejects it even though the UI can display Unicode.
5. Test Enter, paste, resize or rotation, and keyboard visibility on the actual target.
6. Close and reopen. This lab has no persistent draft or account store.

The desktop event test also checks an embedded NUL in QString, recovery after refusal and plain-text presentation. It exercises the real shared C function. Offscreen execution does not qualify native focus, touch input, screen readers, deployment or process lifetime on another target.

## Recover with evidence

A missing profile_name component usually means the installed SDK predates the narrow target. Install a matching SDK or use the explicit source route; do not copy the function into the view. An undefined symbol requires checking headers and link inputs together. A platform-plugin error concerns runtime deployment: use deployment tools from the same kit and retain the first error. A generated APK or Wasm file is not a launch result.

Record the Framework and Bits2Banking revisions, local changes, compiler, Qt kit, target, commands and actual outcomes. Preserve failed logs. If you change compilers or target systems, use a new build directory rather than silently reinterpreting an old cache.

[Learning Qt](../../../content/courses/learning-qt/index.html)

<!-- The previous desktop-only setup is preserved for engineering review. The
portable target and target-specific lessons above replace its dependency and
build-folder instructions; its original observation workflow remains supported.
# Qt profile-name laboratory

This small desktop program sends a name to the C Framework service and displays the result. It does not create an account, collect a password, or sign in to a broker. C++ is required by the Qt widget API; the validation rule is not copied into C++.

## Prepare

Install CMake 3.26 or later, Ninja, a compatible C/C++ compiler, Qt 6 Widgets and Test, and an installed Umicom Framework SDK containing the security component and UmiLocalProfileNameBytes. The compiler, architecture and runtime of all three packages must match. A MinGW UCRT Framework SDK cannot be mixed with an MSVC Qt kit. Locate the package prefixes containing lib/cmake. Replace the sample prefixes below with your actual installation paths.

## Configure and build

Run these in PowerShell from this laboratory directory. Stop when a command reports an error.

~~~powershell
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug '-DCMAKE_PREFIX_PATH=C:/umicom/installed/applications;C:/Qt/6.8.3/mingw_64' -DBUILD_TESTING=ON
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure
.\build\btb-qt-profile.exe
~~~

The Qt prefix is an example, not a required version. Ensure its bin directory and the compiler runtime DLL directory are on PATH before launching. On bash, use matching Linux installations and replace the prefix argument with '-DCMAKE_PREFIX_PATH=/opt/umicom;/opt/qt'; run ./build/btb-qt-profile. Do not reuse a Windows build directory on Linux.

## Observe

1. Type Alice_7, then click Check name. Expect Accepted name: alice_7.
2. Type ../../other and press Enter. Expect a rejection, replacing the previous result.
3. Try 48 letters, then 49. The first is accepted and the second rejected.
4. Resize the window. All controls should remain reachable; the instruction and result can wrap.
5. Close the window. The event loop should finish normally.

The authored Qt event test uses the offscreen platform; it is not evidence that native window focus, screen-reader support or deployment worked on your desktop. Repeat the manual steps on the target machine and record the SDK, compiler and Qt versions.

## Troubleshoot

If a package is missing, locate its Config.cmake and correct the prefix rather than copying headers. An undefined UmiLocalProfileNameBytes means the SDK library is older than the header. A Qt platform-plugin error concerns runtime deployment: use the deployment tools from the same Qt kit and retain the error text. Do not copy arbitrary DLLs into the program folder.

[Learning Qt](../../../content/courses/learning-qt/index.html)

-->
