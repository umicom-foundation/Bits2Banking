# Observe selected files with Framework

This C23 lab reads explicitly selected files and prints JSON containing their paths, byte counts and SHA-256 digests. It calls the installed Framework service instead of implementing hashing or filesystem access again. The example accepts up to 64 absolute paths and chooses a one-MiB per-file limit. Selected files remain unchanged.

1. Install a C23 compiler, CMake 3.25 or later and Ninja. Install a Framework SDK containing <code>umicom/toolchain/file_observation.h</code> and its compiled toolchain library. Copying a header into an older SDK is insufficient.
2. Configure and build from this lab directory. Substitute your SDK location:

~~~powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S . -B build -G Ninja -DCMAKE_PREFIX_PATH="C:/umicom/installed/framework"
cmake --build build
ctest --test-dir build --output-on-failure --no-tests=error
~~~

3. Create exactly three bytes without an encoding marker or newline:

~~~powershell
[IO.File]::WriteAllBytes("$PWD\build\abc.bin", [byte[]](97,98,99))
.\build\file-observation.exe "$PWD\build\abc.bin"
~~~

On Linux, configure with your installed SDK prefix, then use:

~~~sh
printf abc > build/abc.bin
./build/file-observation "$PWD/build/abc.bin"
~~~

The report should contain byte count 3 and digest <code>ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad</code>. Qualification and loaded-module identity remain false. Five registered lab checks cover fixed bytes, an empty file, a Unicode path, a missing file and a relative path. Registration does not establish that they passed on your machine.

If configure cannot find the SDK, check the prefix and package components. Missing headers or unresolved symbols require a matching SDK build and installation. Stop on build errors before running an older executable. Supply a full path when a relative path is refused. Keep writable exercises separate from real tools and source files.

Read the [Framework course](../../../content/courses/umicom-development/index.html) for ownership, JSON capacity, comparison and vendor identity. The native <code>umicom observe-files --file ABSOLUTE_PATH --report NEW_ABSOLUTE_FILE</code> command saves evidence exclusively. Matching digests are not signatures, loaded-module evidence, an atomic workspace snapshot or passing test results.
