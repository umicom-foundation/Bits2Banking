<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/01-assets-and-trust-boundaries.md

PURPOSE:
Identify what an application must protect

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Identify what an application must protect

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


## The idea

Cyber security means protecting systems and information from unauthorised access, change and disruption. A vulnerability is a weakness that can make one of these outcomes possible. A bug may be a vulnerability, but a compiler warning or a crash alone does not establish how an attacker could exploit it.

An asset is something valuable: a document, a password, money, a user's time, or the availability of a service. A trust boundary is a point where data arrives from a person or component with different permissions. A text box is a boundary even in a desktop application. A local file may also contain untrusted data.

## Map the example

~~~text
input bytes -> name validation -> canonical name -> profile lookup
                                  |
                                  + does not prove identity
~~~

1. Open main.c in the lab. Find field, an array of seven bytes.
2. Find canonical. It is a separate destination with the capacity required by Framework.
3. Follow the returned status before printf. Failed validation stops this path.
4. List what is absent: password verification, a session and an authorisation decision.

For Studio, protect unsaved source, chosen paths and build commands. For Bank, protect account records and payment permissions. For Trader, protect orders and the selected broker environment. A username validator protects only one small input boundary in those larger workflows.

## Make a threat table

Write four columns: asset, entry point, unwanted result, control. One row can be “source file; imported project; unexpected overwrite; explicit destination and overwrite policy”. Another can be “order; remote quote; accidental live order; environment-aware confirmation and broker permission checks”. Controls must be implemented and tested, not merely named.

## Check your understanding

Does a lowercase username prove the user owns that account? No. It establishes a consistent spelling after syntax checks. Does hiding a payment button authorise a payment? No. The service processing the request must check permission itself.

## Troubleshooting and summary

If a diagram puts every component in one trusted box, add file imports, network messages and plugin entry points. The useful result of this lesson is a small, testable threat table, not a claim that the entire application is secure.

## Read the source

[Open the example source](../../../../labs/framework/profile-name-boundary/main.c).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Next: Prevent buffer errors at an input boundary](02-buffers-and-exact-length-input.md)
