<!--
Umicom Bits2Banking
File: labs/framework/connector-lifetime/README.md

PURPOSE:
Build and inspect a Framework connector lifetime example.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->
# A database connector lifetime in C

This local C example registers an in-memory document driver with Umicom Framework. It reads two of four invented rows, destroys the registry while keeping the handle, and closes the connection through a callback that requests another close. It opens no database server or network socket. The summary interface reports counts rather than document values.

## Prepare the tools

Install Git, CMake 3.26 or later, Ninja and a C23 compiler. Install an Umicom Framework SDK built with the same compiler and architecture, including its data component and connector close-order repair. Clone Bits2Banking and locate this directory. A package is a group of headers and compiled libraries; CMake uses its configuration file to import the required target.

For Windows these commands assume the repository is at C:\umicom\Umicom-Bits2Banking and the compatible SDK at C:\umicom\installed\framework. Replace those locations when needed. Open PowerShell and run each line separately; stop at the first error.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking\labs\framework\connector-lifetime"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH=C:/umicom/installed/framework -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure --no-tests=error
& ".\build\btb-connector-lifetime.exe"
~~~

On Linux, adjust the repository and SDK locations:

~~~bash
cd ~/umicom/Umicom-Bits2Banking/labs/framework/connector-lifetime
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="$HOME/umicom/installed/framework" -DBUILD_TESTING=ON
cmake --build build
ctest --test-dir build --output-on-failure --no-tests=error
./build/btb-connector-lifetime
~~~

-S identifies source and -B identifies generated build files. The build compiles and links the example. CTest runs the registered executable and checks its exit status. The last command runs it directly.

## Expected result

~~~text
Rows: 2; more: yes
Provider releases: 1; nested close observed an empty handle.
~~~

main calls the real Framework registry and handle functions. lesson_open allocates a small object; lesson_execute obeys the requested row limit; lesson_close releases that object. The driver context remains alive until all callbacks finish. The explicit REQUIRE checks remain active in optimized builds.

## Diagnose a failure

If CMake cannot find UmicomFramework, point CMAKE_PREFIX_PATH at the compatible installed SDK. If the data component is missing, install that component before retrying. A close-state check failure with an older SDK is evidence to inspect its connector implementation. Do not remove the check to make the example pass. If headers or libraries disagree, compare their SDK source revisions and rebuild/install one consistent SDK.

The exercise demonstrates serialized ownership, not concurrent database access, network recovery, authentication or a complete MongoDB adapter. Continue with [Learning NoSQL and MongoDB](../../../content/courses/learning-nosql/index.html) or review [Learning C](../../../content/courses/learning-c/index.html).
