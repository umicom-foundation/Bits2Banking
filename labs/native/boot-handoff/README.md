# Laboratory: read a boot handoff

![Umicom](../../../content/assets/branding/umicom-wordmark-on-dark.svg)

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

## Encode through the production writer

The original `boot-handoff` executable still constructs wire bytes explicitly. The second executable, `boot-handoff-write`, starts from a typed observation and calls `UmicomKernelBootHandoffWrite`. It shares the production reader's semantic checks instead of reproducing them in the lab.

After the configure and build steps above, run:

~~~powershell
& .\build\boot-handoff\boot-handoff-write.exe roundtrip
& .\build\boot-handoff\boot-handoff-write.exe small
& .\build\boot-handoff\boot-handoff-write.exe unreserved
& .\build\boot-handoff\boot-handoff-write.exe bad-text
~~~

On Linux, use `./build/boot-handoff/boot-handoff-write` with the same argument. The round-trip case should print `Encoded 158 bytes; independent reader copy retained console=serial`. The other cases should print `Refused` and explain that bytes and length are unchanged. Each deliberate refusal returns zero only when the expected status and unchanged storage are observed. A nonzero exit means the exercise did not satisfy its contract.

1. Open `write.c`. The input object owns one RAM range, one reservation and the text `console=serial`. Its addresses remain integers.
2. The destination is filled with 0xa5, a visible sentinel byte. The writer may replace only the encoded prefix after complete validation.
3. The input needs 158 bytes: 64 header bytes, 32 range bytes, 48 optional-descriptor bytes and 14 text bytes. The wire text has no zero terminator.
4. Read using the returned length. Passing all 4096 capacity bytes would correctly fail the reader's exact-length rule.
5. Clear the encoded buffer after reading. The returned observation must still contain its own command text.
6. Compare the refusal cases. A small destination is a length problem; an uncovered kernel is a memory-ownership problem; a newline is a text-policy problem. The caller receives different statuses but the same unchanged-output guarantee.

These four producer cases supplement the original reader exercise. They are authored acceptance checks; this guide does not establish that they have been executed. Run the Kernel's independent host and freestanding-link checks as described in `docs/BOOT_HANDOFF.md` before integrating a startup adapter.

## Canonical Umicom identity

Both hosted executables use Framework's `umicom_apply_application_branding` helper. It stages the canonical SVG artwork and embeds the supplied ICO and SVG resource in Windows executables. The default Framework path matches the adjacent `Umicom-Applications/framework` checkout. For another layout, add `-DUMICOM_FRAMEWORK_SOURCE=/absolute/path/to/framework` when configuring. A missing helper or artwork stops configuration with the required path.

This is a build-time identity dependency; the freestanding Kernel does not link Framework or GTK. Console text uses the terminal's selected font. The web lessons use the shared Umicom learning stylesheet and its configured installed font families. Do not substitute a drawn approximation for the supplied logo or icon.
