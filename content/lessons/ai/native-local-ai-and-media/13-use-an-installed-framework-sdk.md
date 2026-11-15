<!--
Umicom Bits2Banking
File: content/lessons/ai/native-local-ai-and-media/13-use-an-installed-framework-sdk.md

PURPOSE:
Teach use an installed Framework SDK in an independent application.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT for original material; cited sources retain their own terms.
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Use an installed Framework SDK in an independent application

An SDK is a development package: headers describe callable functions, libraries supply their implementations, and package metadata tells a build system how they fit together. You can keep your application in its own repository. You do not need a framework subfolder or a Git submodule when you consume a matching installed SDK.

## Prepare a producer and a consumer

1. The SDK producer configures Framework with the required optional adapters and a known compiler. Enable UMICOM_BUILD_SDK_ARCHIVE and build the umicom-sdk-package target.
2. Keep the ZIP checksum, Framework source revision, compiler version, configuration and dependency list together. The archive name alone cannot encode every ABI choice.
3. Extract into a new prefix. The actual SDK root is the named folder inside the extraction destination. Do not overlay a different configuration.
4. Create a separate CMake application that locates UmicomFramework and links exported Umicom targets. Configure, compile, test and run it as distinct qualification stages.

## Understand the build contract

```cmake
cmake_minimum_required(VERSION 3.24)
project(MyNativeApp LANGUAGES C)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
find_package(UmicomFramework 0.9 CONFIG REQUIRED COMPONENTS base)
add_executable(my-app main.c)
target_link_libraries(my-app PRIVATE Umicom::base)
```

This is a build-file fragment for your own main.c. CMAKE_PREFIX_PATH can select an SDK, while the Framework sdk_consumer example also accepts an explicit UMICOM_SDK_ROOT and checks installed paths and declared environment compatibility. Neither method adds language keywords. The compiler reads headers and the linker resolves compiled symbols.

## Static libraries and DLLs

The main Framework library targets currently specify STATIC. Their object code is linked into each consumer executable. A Windows DLL is loaded at runtime and normally needs an import library for development. A DLL distribution also needs deliberate exports, compatible calling conventions, matching runtime dependencies and clear ownership of allocated memory. BUILD_SHARED_LIBS does not override an explicitly static target.

An SDK archive can package registered shared libraries, but that mechanism does not convert the whole Framework into one DLL. External dependencies such as GTK remain separately qualified. A successful configure proves package discovery, not successful linking or execution.

## Exercise and recovery

1. Build the installed sdk_consumer example in a source folder outside the Framework checkout. Keep its configure, build and test logs.
2. Repeat with a missing prefix. Expect configuration to fail, rather than silently downloading Framework.
3. Repeat with a fresh extracted prefix containing spaces. Check imported library paths.
4. If a link fails, compare the actual library, headers and dependency versions. Do not fix a binary mismatch by copying a random header.

Read Framework docs/SELECTIVE_SDK_INSTALLATION.html for the exact archive and consumer commands. The CMake packaging behavior is described in the [CPack documentation](https://cmake.org/cmake/help/latest/module/CPack.html). No distribution or consumer execution is implied by this lesson.

[Course contents](index.md) · [Previous lesson](12-qualify-a-complete-ai-workflow.md) · [Next lesson](14-comfyui-workflows-and-local-jobs.md)
