# Laboratory: read a boot handoff

A startup program describes memory to a kernel using a record of bytes. This laboratory builds that record and calls the production reader. The addresses are synthetic numbers and are never dereferenced.

## Prepare a small host laboratory

A terminal accepts commands as text. A compiler translates C into machine instructions. CMake describes which files form a program; Ninja executes the build steps. Use a C23-capable GCC, CMake 3.24 or later and Ninja. On Windows these commands use an existing MSYS2 UCRT64 installation. Open PowerShell, enter one command at a time, and stop if it fails. Replace the checkout paths if yours differ. No boot disk or administrator access is needed.

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S labs/native/boot-handoff -B build/boot-handoff -G Ninja -DUMICOM_KERNEL_SOURCE=C:/umicom/umicom-kernel
cmake --build build/boot-handoff --parallel 2
& .\build\boot-handoff\boot-handoff.exe
ctest --test-dir build/boot-handoff --output-on-failure --no-tests=error
```

On Linux, open a Bash terminal and use these equivalent paths:

```bash
cd ~/umicom/Umicom-Bits2Banking
cmake -S labs/native/boot-handoff -B build/boot-handoff -G Ninja -DUMICOM_KERNEL_SOURCE="$HOME/umicom/umicom-kernel"
cmake --build build/boot-handoff --parallel 2
./build/boot-handoff/boot-handoff
ctest --test-dir build/boot-handoff --output-on-failure --no-tests=error
```

The expected messages begin with `Accepted:` and `Refused:`. The latter confirms a deliberate invalid-input exercise. A nonzero exit code indicates the expected result was not obtained. If CMake cannot find the reader, check `UMICOM_KERNEL_SOURCE`; if a compiler option is unsupported, check the compiler version. These host checks do not establish that a kernel can boot.

## Follow the example

1. Open `main.c`. The zero-filled array is 144 bytes: a 64-byte header, two 16-byte spans and 48 bytes of optional descriptors.
2. `Put` writes the low byte first. Its callers pass only widths 2, 4 or 8. It is a small fixture helper, not a general serialisation API.
3. The kernel occupies addresses 0x80001000 through 0x80001fff. The reservation covers 0x80000000 through 0x80001fff.
4. The first reader call produces a complete observation. `memcpy` saves its object bytes for comparison; this hosted teaching program may use the C library.
5. Reducing the reservation to 4096 bytes leaves the kernel outside it. The second call must refuse the record and leave the earlier observation unchanged.

## Try a controlled change

Change the kernel length from 4096 to 8192 while leaving the reservation unchanged. Predict whether the first call succeeds. It should fail because the kernel extends past the reservation. Restore the original size, rebuild and obtain both expected messages again. Never replace the numbers with a pointer and read from that address.

## Where the behaviour lives

The lab links `kernel/boot_handoff.c` and `kernel/address.c` from the Kernel checkout. It does not implement its own validation. Read `docs/BOOT_HANDOFF.md` in that checkout for the complete wire format. The course continues from bytes to range checks, reservations, optional descriptors and freestanding link checks.
