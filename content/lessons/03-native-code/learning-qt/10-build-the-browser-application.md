<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-qt/10-build-the-browser-application.md

PURPOSE:
Build the Qt form for a browser

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Build the Qt form for a browser

## Before starting

Use the same profile lab and Framework source from lesson 9. Install a Qt WebAssembly kit and the Emscripten version required by that exact Qt kit. Activate that Emscripten environment and confirm em++ is the intended compiler. Choose a single-threaded kit for this first exercise. The example paths below are placeholders for installed tools, not download instructions.

## Understand the target

WebAssembly is code for a browser execution environment. Qt provides a target-specific qt-cmake wrapper; the lab uses qt6_add_executable so Qt can finalize the application for that target. The visible form and the C validator remain the existing sources. There is no HTTP account service in this exercise.

## Configure a new build folder

Run these from labs/framework/qt-profile in the activated toolchain environment. Replace your-version and the kit directory with the installed names. Stop if configuration or compilation fails.

~~~powershell
em++ --version
& 'C:/Qt/your-version/wasm_singlethread/bin/qt-cmake.bat' -S . -B build-wasm -G Ninja -DCMAKE_BUILD_TYPE=Debug '-DBTB_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework' -DBUILD_TESTING=OFF
cmake --build build-wasm --parallel 2
~~~

## Inspect what was produced

Find the generated application HTML and its JavaScript and Wasm companions in build-wasm. Keep them together. The precise companion set belongs to the chosen kit; do not make a package from a guessed filename list. Save the configure output and compiler version with your exercise notes. This build result is still separate from a browser run.

## Recover from a mismatch

An incompatible archive or compiler option often means the build reused a desktop directory or mixed toolchain versions. Inspect CMakeCache.txt for the target compiler and Qt prefix. Create a fresh, differently named build directory with the correct wrapper; preserve the failed log. Do not resolve an ABI mismatch by copying arbitrary libraries into the target directory.

## Exercise and worked answer

Can desktop ctest --output-on-failure establish that this browser build works? No. The lab deliberately leaves its desktop Qt Test executable out of cross-target registration. The next lesson runs the actual generated application. Record an unrun target as unverified, even when desktop checks pass.

## Reference

[Qt WebAssembly build and toolchain reference](https://doc.qt.io/qt-6/wasm.html). Consult the documentation for the exact kit you install.

## Read the source

[labs/framework/qt-profile/CMakeLists.txt](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/framework/qt-profile/CMakeLists.txt). Use the matching local revision when working offline.

## Continue learning

[Course contents](../../../courses/learning-qt/index.html) · [Previous: Share one C policy across target toolchains](09-share-c-policy-across-targets.md) · [Next: Serve and observe the generated web application](11-serve-and-observe-the-web-build.md)
