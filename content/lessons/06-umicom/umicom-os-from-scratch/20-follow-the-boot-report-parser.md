<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/20-follow-the-boot-report-parser.md

PURPOSE:
Follow the boot-report parser

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Follow the boot-report parser

Follow captured startup observations from bytes to a checked comparison. Use the real Framework parser, then inspect the OS command that consumes it.

You need a text editor, a terminal, CMake 3.24 or newer, Ninja and a C23-capable C compiler. A terminal accepts commands as text. CMake describes how a program is assembled; Ninja carries out the necessary compilation commands. A compiler translates C source into machine instructions. This lab runs on the current computer; it does not install or boot an operating system.

On Windows, install MSYS2 from its official installer, open its UCRT64 terminal and install the toolchain with the following command. Accept the package manager's prompts. If it requests a restart during a system update, complete that update first.

~~~sh
pacman -S --needed mingw-w64-ucrt-x86_64-gcc mingw-w64-ucrt-x86_64-cmake mingw-w64-ucrt-x86_64-ninja
~~~

Obtain the Bits2Banking and Framework source checkouts. In these examples they are located at C:\umicom\Umicom-Bits2Banking and C:\umicom\Umicom-Applications\framework. Adjust the paths if you use another folder. Open PowerShell and enter each line separately, stopping if a command fails:

~~~powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
Set-Location "C:\umicom\Umicom-Bits2Banking"
cmake -S labs/framework/boot-report-comparison -B build/boot-report-learning -G Ninja -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
cmake --build build/boot-report-learning --parallel 2
ctest --test-dir build/boot-report-learning --output-on-failure --no-tests=error
& .\build\boot-report-learning\bin\boot-report-learning.exe
~~~

On a Linux system with GCC, CMake and Ninja installed, place the checkouts beneath ~/umicom, open Bash, and use:

~~~sh
cd ~/umicom/Umicom-Bits2Banking
cmake -S labs/framework/boot-report-comparison -B build/boot-report-learning -G Ninja -DUMICOM_FRAMEWORK_SOURCE="$HOME/umicom/Umicom-Applications/framework"
cmake --build build/boot-report-learning --parallel 2
ctest --test-dir build/boot-report-learning --output-on-failure --no-tests=error
./build/boot-report-learning/bin/boot-report-learning
~~~

The expected output includes state: starting -> ready, completed: 1 -> 2 and Malformed report refused; previous comparison preserved. If CMake cannot find boot_report.c, check the source path. If comparison symbols are missing, the header and source must both contain the comparison API. Do not combine files from unrelated revisions. The build folder stores generated files; the labs folder contains the source you edit.

A parser turns a sequence of characters into values the program can use. Framework's UmiBootReportParse receives a pointer to the first character, a byte count and a pointer to an output structure. A structure groups related values under named fields.

The parser first checks the maximum length, exact version line and final newline. It then reads each line, finds its equals sign and recognises the field name. It records which fields have appeared. A repeated field is refused because accepting two different states would leave its meaning ambiguous.

1. Open Framework src/platform/boot_report.c.
2. Locate Number. Follow how each digit contributes to a value using result * 10U plus the next digit.
3. Locate the seen mask. Each field owns a different bit, so a duplicate can be detected before publication.
4. Locate UmiBootReportValidate near the final output assignment.

The local result begins at zero. The caller's output is replaced only after every field and relationship is valid. This is useful for a UI that must keep showing the previous accepted observation while a new file is rejected. A local variable with an uninitialised value must never be displayed after a failed call; main.c returns before using it.

**Exercise.** In a copy of the lab, change completed=2 to completed=3 while keeping planned=2. Rebuild and run. Expect a nonzero exit because more services cannot complete than were planned. Restore the record afterwards.

A parse error is evidence of an unacceptable record. It is not proof that a host was attacked. Record the actual bytes, source identity and producer version before deciding whether the cause was truncation, a wrong format, a software defect or malicious input.

## Compare observations and capture bytes

A boot report tells you what the collector recorded about startup. A file digest is a short fingerprint made from the file's bytes. If two reports contain the same observations with their fields in a different order, the parser can produce matching values while the file digests differ.

| Question | Use |
| --- | --- |
| Did the service counts, state or other fields change? | Compare the parsed reports. |
| Is this exactly the file whose digest I saved? | Compare the capture digest, including line breaks and field order. |
| Which source revision does the report claim? | Read the report's declared source ID and compare it with the expected ID. |

Try this with two synthetic files. They both report two completed services and the ready state. The second file swaps the order of the lines for mode and state. Both files have the same length. The fixture build gives both files a final line feed, even on a checkout configured to use Windows line endings.

1. Open `labs/framework/boot-report-comparison/fixtures/first.txt` and `reordered.txt` from that directory. Find the two lines whose order changes.
2. In `labs/framework/boot-report-comparison/capture_identity.c`, find `UmiBootReportInspectFile`. It reads the selected file once, then parses and hashes the same bytes. The third argument accepts the digest you expect.
3. Find `UmiBootReportCompare`. This call compares field values and returns a change mask. A zero mask means that no reported field changed.
4. Look for the retry with the earlier file's digest. When it checks the reordered file, the function refuses and the caller keeps its previously accepted snapshot.

From the Bits2Banking folder in PowerShell, reuse the compiler setup above and run:

~~~powershell
cmake -S labs/framework/boot-report-comparison -B build/boot-capture-learning -G Ninja -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework -DUMICOM_LEARNING_BOOT_CAPTURE=ON
cmake --build build/boot-capture-learning --parallel 2
ctest --test-dir build/boot-capture-learning --verbose --no-tests=error
~~~

From the Bits2Banking folder in Bash on Linux, use the matching checkout path:

~~~sh
cmake -S labs/framework/boot-report-comparison -B build/boot-capture-learning -G Ninja -DUMICOM_FRAMEWORK_SOURCE="$HOME/umicom/Umicom-Applications/framework" -DUMICOM_LEARNING_BOOT_CAPTURE=ON
cmake --build build/boot-capture-learning --parallel 2
ctest --test-dir build/boot-capture-learning --verbose --no-tests=error
~~~

Read the output of `learning.boot_report.capture_identity`. It should include these three lines.

~~~text
Parsed fields and file lengths match.
Capture digests differ.
The original digest refuses the reordered capture.
~~~

If the capture test is missing, check that `UMICOM_LEARNING_BOOT_CAPTURE` and `BUILD_TESTING` are enabled. If the compiler cannot find `UmiBootReportInspectFile`, use a Framework checkout containing both `boot_report_file.c` and its matching capture-aware header. If the fixtures fail to parse, restore the checked-in examples and reconfigure so CMake recreates the two data files.

**On paper.** Change `completed=2` to `completed=1` in the reordered example and leave the state ready. The digest changes because a byte changed. The parser refuses a ready report with unfinished work, so there is no valid change mask. Change the state to starting as well. The two fields can now be compared with the accepted ready report. Trace that same transition in the original parser lab above.

Umicom OS offers an opt-in JSON comparison that accepts an expected digest for each saved report. Gather the digests at capture time and keep them with the qualification record. The reviewed digests identify the exact input bytes. Trust in the collector and an actual boot result require their own evidence.

## Read the source

[Open the example source](https://github.com/umicom-foundation/umicom-framework/blob/main/src/platform/boot_report.c).

## Continue learning

[Course contents](../../../courses/umicom-os-from-scratch/index.html) · [Previous: Read a captured boot observation](19-read-a-captured-boot-observation.md) · [Next: Validate caller-owned report fields](21-validate-caller-owned-report-fields.md)
