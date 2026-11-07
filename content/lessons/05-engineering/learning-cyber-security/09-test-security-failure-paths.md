<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/09-test-security-failure-paths.md

PURPOSE:
Test rejection, failure and recovery

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Test rejection, failure and recovery

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


## A test is an executable question

A positive test asks whether a valid request works. A negative test asks whether an invalid or unavailable operation is rejected correctly. Security-sensitive code needs both, including what happens to state after rejection.

Framework's profile tests use a fixture: a controllable replacement backend. It can report a read error, random-source failure, derivation failure or creation conflict. This makes rare failure paths repeatable without corrupting a real credential vault.

## Trace three cases

1. Duplicate registration: a record already exists. The test expects ALREADY_EXISTS and checks that the original record was not changed.
2. Wrong password: verification must fail and removal must leave the record present.
3. Removal conflict: another change is represented between read and remove. The operation must reject the stale comparison rather than erase the newer record.

For the new name-bytes case, inspect empty input, short input, excessive length, a non-terminated three-byte array, embedded zero, high bytes and overlapping storage. Each case asks a different question about the boundary.

## Run the consumer lab

~~~powershell
ctest --test-dir build/profile-name -R "^btb\.profile_name\." --output-on-failure --no-tests=error
~~~

Read the test names and final exit status. A zero-test result is not evidence of safety, which is why the command rejects it. If a test cannot start because its executable is missing, build the target first; do not alter an assertion to hide a missing executable.

## Record evidence

Keep source revision, compiler, platform, command, timestamp and result together. Mark skipped checks separately. If the source changes after a passing run, that run belongs to the previous source identity.

## Summary

Test failures at each boundary and inspect the resulting state. Passing a deterministic policy test does not prove the absence of all vulnerabilities or replace review of cryptographic and platform components. A useful regression test encodes the condition that caused the defect, so a later change can expose its return.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/tests/local_profile/test_local_profile.c).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Write coding rules that can be checked](08-standards-that-prevent-memory-bugs.md) · [Next: Review a complete feature from input to effect](10-security-review-of-an-application-feature.md)
