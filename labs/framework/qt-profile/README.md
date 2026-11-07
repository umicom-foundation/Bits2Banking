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
