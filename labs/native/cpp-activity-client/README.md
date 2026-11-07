# Call a C model from C++

This small console application demonstrates a C++ caller, while the checked activity rule remains in the existing C files. It is a language-boundary exercise, not a replacement Framework implementation.

## Prepare and build

Install matching C and C++ compilers, CMake, Ninja, and an Umicom Framework SDK built for that toolchain. Read the [Framework SDK practical lab](../../../content/lessons/umicom-development/sdk-practical-lab.md) and [activity lab](../framework-activity/README.md). From this directory, in PowerShell:

~~~powershell
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework" -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure --no-tests=error
& "./build/btb-cpp-activity.exe"
~~~

Replace the SDK prefix with its actual installed location. In bash use your SDK prefix and launch `./build/btb-cpp-activity`. Expected output is `Completed exercises: 1`. These commands require execution in your environment.

## Read the boundary

`bridge.h` already surrounds its function declaration with `extern "C"` when included by a C++ compiler. This gives the declaration C language linkage. It does not translate C++ objects or make incompatible binary interfaces interchangeable.

CMake compiles the `.c` model with the C compiler and the `.cpp` caller with the C++ compiler. The model returns one integer, retaining no caller memory. The test exercises success, capacity and invalid values through the same declaration.

An unresolved BtbActivityNext symbol suggests the C library was not linked or the declaration has incorrect language linkage. A library built for a different processor or incompatible toolchain must be rebuilt appropriately; a cast cannot repair that mismatch.
