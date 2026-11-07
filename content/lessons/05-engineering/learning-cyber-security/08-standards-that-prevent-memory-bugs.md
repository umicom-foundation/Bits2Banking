<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/08-standards-that-prevent-memory-bugs.md

PURPOSE:
Write coding rules that can be checked

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Write coding rules that can be checked

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


## Standards and conventions

A coding convention makes code predictable to read, for example naming functions consistently. A coding standard also defines required behaviour: checking lengths, returning errors, preserving ownership and avoiding secret logging. A useful rule has a reason and a way to review it.

Use these rules when extending the lab:

| Rule | Reason | Review evidence |
| --- | --- | --- |
| Carry source length with borrowed bytes | A pointer has no allocation length | Function parameters and call site |
| State output capacity in the contract | Prevent destination overflow | Header and boundary tests |
| Publish output only after validation | Preserve state on failure | Write locations and snapshot test |
| Name the owner of every resource | Avoid leaks and dangling pointers | Create/release paths |
| Check every returned status | Avoid using an absent result | Branch before result access |
| Do not log credentials | Prevent accidental disclosure | Diagnostics review |

## Apply the rules

1. Open main.c. Explain why canonical is printed only after UMI_STATUS_OK.
2. Open test_name.c. Explain why the embedded zero is part of a byte span rather than an ordinary string.
3. Find the in-place alias case. Check that the documented overlap guarantee is exercised.
4. Read the source header: product, file, purpose, author and licence identify the file without duplicating implementation comments.

The test's REQUIRE macro returns a nonzero exit status when a condition fails. CTest uses that process result to classify the test. Printing “failed” while returning zero would mislead the test runner.

## Review exercise

A contributor proposes using strcpy(out, name) because it is shorter. List the missing guarantees: an input terminator, destination capacity, naming validation and failure preservation. The problem is not the number of lines; it is the loss of a contract.

Warnings are evidence to investigate. Do not hide an incompatible pointer warning with a cast without understanding which object type will be accessed. A void pointer can point to many objects, but converting char ** to void ** does not make writing through the resulting lvalue valid.

## Summary

Keep rules close to enforceable contracts and regression tests. Style consistency helps review; it does not replace bounds checks, lifetime design or security testing.

## Read the source

[Open the example source](../../../../labs/framework/profile-name-boundary/test_name.c).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Keep desktop, mobile and broker identity separate](07-desktop-mobile-and-broker-login.md) · [Next: Test rejection, failure and recovery](09-test-security-failure-paths.md)
