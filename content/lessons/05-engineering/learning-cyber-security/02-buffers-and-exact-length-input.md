<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/02-buffers-and-exact-length-input.md

PURPOSE:
Prevent buffer errors at an input boundary

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Prevent buffer errors at an input boundary

Learn how application inputs, memory ownership and identity checks fit together. The examples use Umicom Framework and a small Bits2Banking consumer. Every chapter explains its vocabulary before the exercise.

## Start here

A source file is readable program text. A compiler turns that text into machine instructions. A library supplies reusable functions; this course calls the security library in Umicom Framework. A terminal accepts commands. You can read and trace every example without installing anything.

For the practical lab, install Git, a C23 compiler, CMake 3.26 or newer, Ninja, and a matching Framework SDK containing UmiLocalProfileNameBytes. In Windows PowerShell, open the repository with Set-Location and make the UCRT64 tools visible:

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/framework/profile-name-boundary -B build/profile-name -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework" -DBUILD_TESTING=ON
cmake --build build/profile-name
ctest --test-dir build/profile-name --output-on-failure --no-tests=error
& ".\build\profile-name\btb-profile-name.exe"
~~~

Run one command at a time and stop on an error. Change the SDK path to your installation. In bash, use cd to enter your checkout, the same three CMake/CTest commands, and ./build/profile-name/btb-profile-name to launch. The expected line is Canonical name: alice_7. A missing package means the SDK path is wrong or incomplete; a missing symbol means its header and library must be updated together. This lab does not collect credentials or write a password store. The [Learning C course](../../../courses/learning-c/index.html) explains basic syntax in more depth.


## Bytes, buffers and lengths

A byte is a small storage unit. A buffer is a region reserved for several bytes. In C, an array of 49 char elements has 49 positions, numbered 0 through 48. Accessing position 49 is outside that array. A buffer overflow writes beyond the destination; an over-read reads beyond the source. Both violate the program's memory contract.

A C string ends with a zero byte, written '\0'. A network field does not automatically have that terminator. strlen and %s expect strings, so they cannot safely discover the length of an arbitrary packet field.

## Follow the actual API

~~~c
const char field[] = {'A', 'l', 'i', 'c', 'e', '_', '7'};
char out[UMI_LOCAL_PROFILE_NAME_CAPACITY];
UmiStatus status = UmiLocalProfileNameBytes(field, sizeof(field), out);
~~~

The first argument points to readable bytes. The second says how many belong to the field. The third points to space for the complete result. sizeof(field) is seven here because field is an array in this scope. Applying sizeof to a pointer would measure the pointer, not the data it references.

1. Locate the length rejection before the loop in local_profile.c.
2. Observe that each loop iteration reads name[i] only while i is less than length.
3. Find the temporary value array. It leaves space for the trailing zero.
4. Find the final copy. It occurs only after all bytes are accepted.

A correct length cannot be guessed from an untrusted claim. The caller must compare a packet's stated length with the bytes actually received before calling this function. The validator cannot inspect the size of the allocation behind an arbitrary pointer.

## Lab and expected result

Run the boundaries test using the setup commands. Read the invalid array containing an embedded zero. The exact-length interface rejects it; it does not silently accept the prefix. Change a copy of that test to expect success and observe that the assertion should fail. Restore the test afterwards.

## Summary

Carry length and capacity separately. Validate both before access. Use string operations only after establishing a terminator within readable storage. For larger text, do not assume the small username policy is appropriate: use the contract for that data type.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/security/local_profile.h).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Identify what an application must protect](01-assets-and-trust-boundaries.md) · [Next: Recognise dangling pointers and define ownership](03-dangling-pointers-and-ownership.md)
