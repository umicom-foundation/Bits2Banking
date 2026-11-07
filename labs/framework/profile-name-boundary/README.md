# Profile-name boundaries with Umicom Framework

This small program validates a username field. It does not register users, accept passwords, contact a server or authenticate a broker account. The shared Framework service owns the naming policy.

## Prepare

Install a Framework SDK containing UmiLocalProfileNameBytes and its security component. Use CMake 3.26 or newer, Ninja and a C23 compiler. Windows UCRT64 users can open PowerShell and add C:\msys64\ucrt64\bin to PATH. Change the example SDK directory to the one installed on this machine.

~~~powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/framework/profile-name-boundary -B build/profile-name -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework" -DBUILD_TESTING=ON
cmake --build build/profile-name
ctest --test-dir build/profile-name --output-on-failure --no-tests=error
& ".\build\profile-name\btb-profile-name.exe"
~~~

Stop at the first failed command. On Linux use the same CMake commands with the installed SDK path and run ./build/profile-name/btb-profile-name. Successful execution prints Canonical name: alice_7. Tests check exact bytes, invalid input, unchanged output and in-place validation.

If the package cannot be found, inspect its installation for lib/cmake/UmicomFramework. If the new symbol is unavailable, the installed header and library may predate this API; rebuild and install the matching Framework revision before configuring this consumer. A compiler error is not a successful test run.

## Read in order

1. main.c shows a seven-byte input and a separate output buffer.
2. local_profile.h in Framework defines the capacity and status contract.
3. test_name.c checks several boundary cases without writing a credential vault.
4. CMakeLists.txt links the installed security target rather than copying validation logic.

Continue with [Learning Cyber Security](../../../content/courses/learning-cyber-security/index.html).
