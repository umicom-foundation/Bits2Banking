# 118. Build a driver lifecycle from reusable C23 services

A driver is the software that communicates with a device and controls its
operations. A driver can be asked to start, process work, stop and recover
from a failure. Even a small driver therefore has a **lifecycle**: a set of
states and the rules for moving between them.

In this lesson, we will build a **fictional** driver in C23. It never accesses
real hardware or installs a kernel component. It reuses two teaching libraries
from previous chapters rather than introducing another interrupt controller.

## 1. Open the laboratory

The complete source is under:

`labs/native/driver-lifecycle/`

The project consists of `driver.h`, `driver.c`, `main.c`, `test_driver.c` and
`CMakeLists.txt`. The build imports the existing `service-recovery` library,
which already imports `interrupt-ownership`.

![The driver retains one owner through its lifetime](../../assets/diagrams/driver-lifetime-stages.svg)

### Windows: configure, build and test

In PowerShell, open the Bits2Banking repository:

```powershell
Set-Location "C:\umicom\Umicom-Bits2Banking"
$env:Path = "C:\msys64\ucrt64\bin;$env:Path"
cmake -S ".\labs\native\driver-lifecycle" `
    -B ".\output\learning-build\driver-lifecycle" `
    -G Ninja -DCMAKE_C_COMPILER="C:\msys64\ucrt64\bin\gcc.exe"
cmake --build ".\output\learning-build\driver-lifecycle" --parallel 2
ctest --test-dir ".\output\learning-build\driver-lifecycle" --output-on-failure
```

The test suite includes the earlier libraries' tests, because we compose their
actual CMake targets instead of copying their `.c` files.

Run the demonstration from the same folder:

```powershell
& ".\output\learning-build\driver-lifecycle\btb-driver-lifecycle.exe"
```

Expected output:

```text
Driver stopped. Accepted revision: 101. Reviewed faults: 1.
```

## 2. Understand the interface

The public header describes the operations a caller can request:

```c
BtbIrqStatus BtbDriverStart(BtbDriver *driver, uint32_t owner);
BtbIrqStatus BtbDriverComplete(BtbDriver *driver, uint32_t revision);
BtbIrqStatus BtbDriverFail(BtbDriver *driver, uint32_t revision);
BtbIrqStatus BtbDriverReviewAndRecover(BtbDriver *driver,
                                        uint32_t reviewedRevision);
BtbIrqStatus BtbDriverStop(BtbDriver *driver);
```

A **status value** tells the caller whether the operation was accepted.
A **revision** is the number assigned to a particular unit of work. The model
rejects an earlier or duplicate accepted revision.

`BtbDriver` owns a `BtbService`, and that service owns a `BtbIrqDomain`.
The ownership model contains a `self` pointer. Consequently, you must initialise
one zero-filled driver object at a stable address and must **not copy the live
object**. Copying the structure does not grant ownership of its internal source.

## 3. Follow a failure and retry

The demonstration begins with fictional revision 100 and completes it.
The next revision, 101, faults before the service acknowledges completion.
The committed revision therefore remains **100**. The driver refuses to stop
while it is in the faulted state.

The caller explicitly reviews revision 101, resumes the teaching service,
then tries 101 again. Only the second, successfully completed attempt advances
the committed revision to **101**.

This pattern matters for a bank-account interface or a note-saving service:
**accepted work must not be confused with attempted work**. For financial
systems, actual posting, idempotency and durable journals require additional
contracts beyond the exercise.

## 4. See where the code belongs

The laboratory's CMake configuration contains the following dependency:

```cmake
add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/../service-recovery"
    "${CMAKE_CURRENT_BINARY_DIR}/service-recovery")
target_link_libraries(btb_driver_lifecycle PUBLIC btb_service_recovery)
```

The reusable ownership behaviour remains in the earlier libraries. Our new
module only **composes** it into a higher-level lifecycle.

Umicom Framework follows the same design rule: shared behaviour belongs to
the Framework; an application or service uses its public interfaces rather than
maintaining competing copies.

## 5. Your turn

1. Run the tests and find `bits2banking.driver_lifecycle.contracts`.
2. Open `test_driver.c`. Find the test which attempts to stop a faulted driver.
3. Explain why the result must be `BTB_IRQ_WRONG_STAGE`.
4. Find the check proving that revision 101 was not committed after the fault.
5. Modify the demonstration's **fictional** revision numbers while keeping them
   strictly increasing. Build and run again.

If you try to complete revision 99 after completing revision 100, the operation
must be refused. If you stop before fault review, the old driver retains its
owned source. If you review the specific failed revision and retry, the
simulation can finish normally.

**Next:** [119. Keep diagnostic records in a bounded C23 ring](119-keep-diagnostics-in-a-bounded-ring.md).
