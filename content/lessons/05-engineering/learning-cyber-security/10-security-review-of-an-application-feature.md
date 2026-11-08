<!--
Umicom Bits2Banking
File: content/lessons/05-engineering/learning-cyber-security/10-security-review-of-an-application-feature.md

PURPOSE:
Review a complete feature from input to effect

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Review a complete feature from input to effect

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


## Bring the pieces together

A feature is a user-visible action such as opening a file, registering a profile or submitting a payment. Its security depends on the entire path, including input, shared services, storage and the interface's response to failure.

Use a proposed “create local profile” workflow as a paper design. It is small enough to follow but contains real ownership and failure decisions.

## Step-by-step review

1. Describe the user's goal in one sentence. Specify that this is a local application profile.
2. List input fields and their maximum lengths. Distinguish bytes from characters when text can use multiple bytes per character.
3. Map each field to a Framework contract. Do not duplicate profile-name policy in Studio, Trader and Bank.
4. Assign ownership of request buffers to a job that remains alive while verification runs.
5. On completion, check whether the interface owner still exists before updating it.
6. Present success only after the backend confirms creation. On duplicate or unavailable storage, preserve the current form and explain the next action without exposing secrets.
7. Clear temporary password storage when the job finishes, including failure paths.
8. Test closing the window while work is pending, retrying after failure and attempting duplicate registration.

## Extend the review to a payment

Authentication is only the start. A payment also needs an authorised account, amount validation, currency rules, duplicate-submission handling and an auditable outcome. A local-profile success must not bypass these checks. Use the same review method to discover which services exist and which remain to implement.

## Deliverable

Create a one-page feature map with columns “input”, “Framework API”, “owner”, “failure result”, and “test”. Mark uncertain items explicitly. For example, an unsupported secure-store platform is an unavailable capability until a real adapter is supplied.

## Further study

Continue with Safer C Programming for allocation and buffer exercises. Study the web-session lesson before implementing browser login. Use the [OWASP authentication guidance](https://cheatsheetseries.owasp.org/cheatsheets/Authentication_Cheat_Sheet.html) when designing account controls such as recovery and resistance to repeated guessing.

## Summary

Security is a set of maintained contracts across a working feature. Implement shared policy once, preserve state on failure, and connect each important claim to a review or test that can actually establish it.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/include/umicom/security/local_profile.h).

## Continue learning

[Course contents](../../../courses/learning-cyber-security/index.html) · [Previous: Test rejection, failure and recovery](09-test-security-failure-paths.md)

<!-- Course metadata owns the reading order; retain the existing lesson and add its missing continuation. -->
[Next lesson](11-read-an-identity-lifecycle.md)
