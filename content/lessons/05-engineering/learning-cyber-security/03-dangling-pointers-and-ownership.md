<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/03-dangling-pointers-and-ownership.md

PURPOSE:
Recognise dangling pointers and define ownership

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Recognise dangling pointers and define ownership

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


## What a pointer means

A pointer stores an address. It does not by itself keep the addressed object alive. A dangling pointer still contains an address after the object it referred to has stopped existing. Reading or writing through it is invalid even if old bytes appear to remain there.

An owner is responsible for releasing a resource. A borrower may use the resource only while the owner guarantees its lifetime. Consider this unsafe sketch; inspect it on paper rather than running it:

~~~text
create a temporary local array
return its address
caller reads that address after the function returns
~~~

The array's lifetime ended when the function returned. Returning the address did not copy the array. A safer design writes into caller-owned storage or returns an explicitly owned allocation with a documented release function.

## Trace Framework ownership

UmiLocalProfileStoreCreate receives a backend containing callbacks and a context pointer. On success the store owns the context. On failure the caller still owns it. Retain adds a reference; Release removes one. The last Release invokes the backend destroy callback and releases the store.

1. Read the ownership comment above UmiLocalProfileBackend.
2. Draw caller -> store -> backend context.
3. Mark the transfer only on successful creation.
4. Find FixtureStore in tests/local_profile/fixture.h. Its test context is on the test function's stack and the fixture supplies no destroy callback. The test keeps that context alive until all store references are released.

Reference counting is a lifetime protocol, not a universal thread-safety mechanism. The header says calls on the store must be serialised; only Retain and Release are thread-safe. Two simultaneous writes are not made safe by retaining twice.

## GUI exercise

Imagine a login worker finishes after its window closes. Write the sequence “start worker; close window; complete worker”. Which object may still exist? The job can own its result, but the former window pointer cannot be assumed valid. A completion handler needs an owner-lifetime check or a valid weak-reference mechanism before updating widgets.

## Summary and recovery

For each pointer ask who owns it, how long it remains valid, and which operation invalidates it. Setting one pointer to NULL after release helps prevent accidental reuse of that variable; it does not repair other aliases. If a crash disappears when a delay is added, investigate lifetime and ordering instead of treating the delay as a fix.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/security/local_profile.h).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Prevent buffer errors at an input boundary](02-buffers-and-exact-length-input.md) · [Next: Keep failed input from changing valid state](04-validate-before-publishing-state.md)
