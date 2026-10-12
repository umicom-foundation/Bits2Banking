# Process-owned file services in C23

This laboratory extends the [VFS descriptors laboratory](../vfs-descriptors/README.md) rather than copying its storage and descriptor implementation. The **VFS owns** mount selection, open descriptions, file positions and provider calls. The **process-file adapter owns** the requesting process identity, accepted descriptor handles and a fictional 512-byte user address space.

A process cannot safely hand arbitrary virtual addresses to a kernel. The caller's offset and length are first checked against this training address space; the adapter then copies data into stable, bounded buffers and calls the existing VFS interface. The trusted process identity is selected during initialisation and is absent from the request.

## Build on Windows

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\process-file-services" -B ".\output\learning-build\process-file-services" -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe" -DBUILD_TESTING=ON
cmake --build ".\output\learning-build\process-file-services" --parallel 2
ctest --test-dir ".\output\learning-build\process-file-services" --output-on-failure
& ".\output\learning-build\process-file-services\btb-process-files-demo.exe"
```

The three tests cover complete byte copies, refusal of invalid/embedded-NUL paths, bounds checking, descriptor closure, stale-handle rejection and lifetime cleanup. The example prints `Process 11 read: Umicom Notes`.

## Inspect the contract

1. Read `process_files.h`: locate the trust boundary between offsets and pointers.
2. Find `BtbProcessSpan` in `process_files.c`. Explain why subtraction is used to check lengths.
3. Locate the exact point at which a read is copied from staging memory into user bytes.
4. Run the tests before editing. Change the transfer bound from 64 to 32 **in a disposable copy**, then predict which requests should be refused.
5. Restore the original bound and rerun the tests.

This laboratory does not issue real operating-system system calls, map arbitrary memory, or support concurrent requests. The [actual Umicom Kernel file service](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/PROCESS_FILE_SERVICES.md) has additional trust and lifetime requirements.
