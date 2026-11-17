<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/native-language-interoperability/03-call-c-from-cpp.md

PURPOSE:
Teach call c from c++ without changing ownership.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg)

# Call C from C++ without changing ownership

[Course contents](index.md) · [Previous](02-follow-the-c-contract.md) · [Next](04-call-c-from-rust.md)

## Two languages, one implementation
C++ supports objects and destructors, but it can also call C functions. A C++ compiler normally encodes extra type information into function names. The extern "C" wrapper in bridge.h asks for C language linkage. It does not convert C++ objects into a portable binary format.

## Inspect and build the existing lab
1. Read bridge.h. Notice that __cplusplus guards the extern "C" block so the same header remains valid in C.
2. Read main.cpp and test_client.cpp in the cpp-activity-client directory.
3. Inspect CMakeLists.txt. It compiles activity.c as C and the client as C++; the source extensions retain their intended languages.
4. Run the following commands with the installed SDK from lesson 1.

~~~powershell
cmake -S labs/native/cpp-activity-client -B build/cpp-activity -G Ninja -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ "-DCMAKE_PREFIX_PATH=C:/umicom/installed/framework"
cmake --build build/cpp-activity --parallel 2
ctest --test-dir build/cpp-activity --output-on-failure --no-tests=error
& .\build\cpp-activity\btb-cpp-activity.exe
~~~

Expected behaviour is the same checked progression and rejection as the C model. The existing client test is the executable check; reading a plausible console transcript is not a substitute.

## Keep the boundary narrow
Do not expose std::string, std::vector, exceptions or compiler-specific class layouts through a C header. A C caller cannot understand them. If a C++ implementation can throw, catch its exceptions inside the C++ side and translate them into the documented C result. A pointer still needs a clear owner; extern "C" does not manage memory.

## Recovery and exercise
An unresolved BtbActivityNext symbol usually means the C archive was omitted or the declaration used C++ linkage. An incompatible-object error usually points to a target or toolchain mismatch. Keep separate build directories when changing toolchains.

Explain why compiling activity.c with a C++ compiler is not the intended fix. Answer: that changes the language used for the implementation and can alter accepted syntax and linkage. Connect the two correctly compiled objects instead. Continue the existing Learning C++ course for object lifetime and file ownership.

## Read the complete source

[labs/native/cpp-activity-client/main.cpp](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/cpp-activity-client/main.cpp)
