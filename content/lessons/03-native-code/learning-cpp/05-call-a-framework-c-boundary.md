<!--
Umicom Bits2Banking
File: content/lessons/03-native-code/learning-cpp/05-call-a-framework-c-boundary.md

PURPOSE:
Explain the lesson: Call an existing C model from C++.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

# Call an existing C model from C++

## Share the rule

A C++ application can use a C library through a suitable interface. The boundary should describe values, ownership and errors clearly. It should not require the caller to know the model's internal widgets or storage.

This example calls BtbActivityNext, the same C adapter used by the mobile and browser exercises. The underlying activity model uses Framework status definitions. The C++ caller prints the result; it does not implement a second progress rule.

## Setup recap

Install matching C and C++ compilers, CMake, Ninja and a Framework SDK for that toolchain. Follow the [C++ activity lab](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/cpp-activity-client/README.md). Replace its SDK path with the directory where your SDK is installed. The project requests C23 for C files and C++17 for this small caller.

## Follow the call

~~~text
C++ main -> C declaration in bridge.h
         -> BtbActivityNext in bridge.c
         -> existing activity model
         -> checked integer result
~~~

The header uses `extern "C"` when a C++ compiler reads it. That specifies C language linkage for the declaration. It helps the caller and linker agree on the function's identity.

It does not make every C type available in C++, convert C++ containers into C arrays, or make different processor architectures compatible. The narrow header exposes only one integer argument and one integer result.

## Lab

1. Read the public bridge declaration.
2. Read CMakeLists.txt and identify which files compile as C.
3. Build the standalone lab.
4. Run btb-cpp-activity. Expect Completed exercises: 1.
5. Follow the negative-result branch in main.cpp.
6. Check that the caller reports printing failures as well as model failures.

The CMake target links the existing model and adapter. A declaration alone tells the compiler how a call looks; the linker still needs the implementation.

## Exercise and explanation

Would copying the model into main.cpp make the boundary easier to maintain? It would create a second rule to keep consistent. Calling the original implementation lets one model correction benefit every adapter.

## Troubleshooting

An undefined reference suggests that the implementation was not linked or the declaration's linkage differs. A wrong-machine error suggests incompatible build artifacts. Check the library architecture and toolchain instead of adding casts.

This exercise establishes the shape of a C boundary. It does not prove that an arbitrary C++ object can cross that boundary or that every Framework module has a C++-compatible public header.

## Source for this lesson

[Open the example source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/cpp-activity-client/main.cpp). Keep the source revision with your exercise notes so later changes can be compared.

[Course contents](index.md) · [Previous lesson](04-understand-append-and-repeated-save.md) · [Next lesson](06-test-a-language-boundary.md)

