# Sv39 virtual-memory translation laboratory

An operating system lets programmes use *virtual addresses*. The processor's memory-management unit (MMU) consults page tables to determine which physical memory address each virtual address refers to. This laboratory models one 4 KiB page mapping using three C23 arrays; it **does not** activate an MMU or execute privileged instructions.

## Build on Windows

Open PowerShell in `C:\umicom\Umicom-Bits2Banking`:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\sv39-address-translation" `
  -B ".\output\learning-build\sv39-address-translation" `
  -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\sv39-address-translation" --parallel 2
ctest --test-dir ".\output\learning-build\sv39-address-translation" --output-on-failure
```

## What to look for

The executable prints:

```text
Virtual address: 0x40201120
Physical address: 0x9120
```

The virtual page at `0x40201000` maps to the physical page at `0x9000`. The last three hexadecimal digits are the offset within a 4 KiB page. That offset is unchanged by translation.

Sv39 uses three virtual page numbers (VPN[2], VPN[1], VPN[0]) of nine bits each, and a 12-bit page offset. Each level has 512 entries because 2^9 = 512. The laboratory owns three arrays of 512 64-bit entries. Intermediate entries point to simulated page-table frame numbers 2 and 3; the leaf entry refers to physical frame 9.

**Try it:** Change `BTB_SV39_READ | BTB_SV39_WRITE` in `main.c` to `BTB_SV39_READ | BTB_SV39_EXEC`. Rebuild and run. Explain why the test programme's requested read still succeeds while a requested write would be denied.

This is an instructional model. Actual Umicom Kernel translation also must manage physical frames, privileged CPU state, `satp`, `sfence.vma`, TLB behaviour, PMP, traps and per-process ownership. See the [Umicom Kernel virtual-memory documentation](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/VIRTUAL_MEMORY.md) and [hardware-backed translation guide](https://github.com/umicom-foundation/umicom-kernel/blob/main/docs/HARDWARE_ADDRESS_TRANSLATION.md).
