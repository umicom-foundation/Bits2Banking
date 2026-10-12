# Driver lifecycle — C23 laboratory

An application can request a device operation, but only the owning service
should control the driver's lifetime. This laboratory uses a **fictional**
driver that builds on the existing `service-recovery` and `interrupt-ownership`
models. It never accesses interrupts, a device, privileged instructions or
Umicom Kernel internals.

## Build on Windows (PowerShell)

From `C:\umicom\Umicom-Bits2Banking`:

```powershell
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S .\labs\native\driver-lifecycle -B .\output\learning-build\driver-lifecycle -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build .\output\learning-build\driver-lifecycle --parallel 2
ctest --test-dir .\output\learning-build\driver-lifecycle --output-on-failure
```

The nested `service-recovery` and `interrupt-ownership` tests also run. The
new driver tests are named `bits2banking.driver_lifecycle.*`.

## Follow the demonstration

1. Start one driver: the existing owner model claims its fictional source.
2. Accept revision 100. The service records that revision only after the
   operation completes.
3. Start revision 101 but simulate a fault before it commits.
4. Attempt Stop. Stop refuses while the device remains faulted.
5. Review revision 101 explicitly, then retry it.
6. Stop after the source is no longer servicing an operation.

Expected console output:

```text
Driver stopped. Accepted revision: 101. Reviewed faults: 1.
```

`reviewedFaults` records decisions in memory, not signed review evidence.
The driver object must stay at the same address; copying an active controller
is invalid. Stopping never provides a new generation token or resurrects a
retired driver. Actual OS device adapters and kernel interrupt controllers
must keep their own separate, authoritative ownership policies.
