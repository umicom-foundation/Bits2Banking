# Compare captured boot reports

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

The program uses src/platform/boot_report.c from Framework directly. It does not copy the parser into this repository. Read main.c from top to bottom: two captured text records are admitted, their fields are compared, then a deliberately unterminated reason is refused.

The regression assertion checks the exact two changed fields. The final check ensures malformed input cannot overwrite a prior comparison. This is a host-side parser lab; it does not establish firmware compatibility, a successful guest boot or service health.
