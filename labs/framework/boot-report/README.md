<!--
Umicom Bits2Banking
File: labs/framework/boot-report/README.md

PURPOSE:
Inspect a boot report through Framework

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# Inspect an OS boot report with Umicom Framework

A report is a short record written by the OS startup controller. This lab reads an explicitly selected file and prints its recorded state. It uses the installed Framework reader rather than another parser. The supplied reports are teaching fixtures, not observations from a real boot.

## Files and responsibilities

| File | Responsibility |
| --- | --- |
| main.c | Read arguments, call UmiBootReportLoad, present the accepted snapshot |
| test_report.c | Exercise the pure parser and unchanged-output contract |
| fixtures/ready.report | A synthetic completed two-check plan |
| fixtures/recovery.report | A synthetic service failure after one check |
| fixtures/invalid.report | Contradictory ready state with incomplete checks |
| CMakeLists.txt | Connect the client to Umicom::platform and register checks |

## Windows setup and commands

Install the UCRT64 compiler, CMake and Ninja and a Framework SDK built with the same toolchain. The SDK prefix below is an example. It must contain lib/cmake/UmicomFramework and the platform library. Choose your own build folder; commands do not install an OS or create a user account.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\framework\boot-report"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework" -DBUILD_TESTING=ON
cmake --build build --parallel 2
ctest --test-dir build --output-on-failure --no-tests=error
& ".\build\btb-boot-report.exe" "C:\umicom\Umicom-Bits2Banking\labs\framework\boot-report\fixtures\ready.report"
~~~

Run one line at a time. Inspect $LASTEXITCODE immediately after each native command. On success the final command prints ready, 2/2, none and the illustrative source fingerprint. Recovery is also a valid report: reading it successfully does not mean the boot succeeded.

On Linux, use a Linux-built SDK and a different build directory:

~~~bash
cmake -S . -B build-linux -G Ninja -DCMAKE_PREFIX_PATH=/work/umicom-sdk -DBUILD_TESTING=ON
cmake --build build-linux --parallel 2
ctest --test-dir build-linux --output-on-failure --no-tests=error
./build-linux/btb-boot-report "$PWD/fixtures/recovery.report"
~~~

## Read the contract before using a result

UmiBootReportLoad accepts an absolute regular-file path, an optional expected lowercase SHA-256 identity, and an output structure. Pass NULL when no expected identity is available. UMI_STATUS_OK means that loading and parsing succeeded. Look at report.state and report.reason to understand the observation. A mismatch returns an error and leaves the previous output unchanged.

The maximum report is 512 bytes. Every required field appears once. These fixtures use LF line endings, including the final newline; the grammar rejects CRLF and embedded control bytes. Git checkout settings can alter text files. If a fixture is rejected, inspect the bytes before changing the parser. A source fingerprint identifies bytes; it is not a signature or an authorization grant.

## Exercises

1. Read ready.report and predict the output before launching the client.
2. Read recovery.report and explain why a successful read has a failure reason.
3. Read invalid.report. Its completed count is smaller than planned while state says ready. Expect a nonzero status and no accepted state.
4. Supply an incorrect expected source identity. Expect rejection without interpreting that as a hardware failure.
5. Read test_report.c. Find the sentinel copy and explain why each invalid call compares the old fields.

## Troubleshooting

A missing UmicomFrameworkConfig.cmake means the SDK prefix or installation is incomplete. An unresolved UmiBootReportLoad symbol means the selected SDK may predate this reader; verify the headers and archive are from the same installation. A relative path is rejected by design. A whole console transcript is not a boot-report record. Keep the original evidence and select the correct file.

The lab is a host-side SDK consumer. Its checks do not validate PID1, QEMU boot, USB media, authentication or long-term system health.
