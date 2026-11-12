<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-os-from-scratch/51-connect-an-owned-image-read-port.md

PURPOSE:
Teach connect an owned image read port through the installed Framework GPT service.

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-logo.svg)

# Connect an owned image read port

[Course contents](index.md) · [Previous lesson](50-format-device-labels-without-splitting-utf8.md) · [Next lesson](52-keep-partition-address-units-explicit.md)

[Complete source](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-gpt-inspection/port.c) · [Build and run the lab](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-gpt-inspection/README.md) · [Qualification guide](https://github.com/umicom-foundation/Bits2Banking/blob/main/labs/native/framework-gpt-inspection/QUALIFICATION.md)

A media application has two separate responsibilities: obtaining bytes it is allowed to read, and interpreting those bytes. This lesson connects an owned memory allocation to the installed Framework parser. The small program never opens a path or a device, so its behavior can be studied without selecting a real disk.

## Before you begin

Open the installed GPT inspection lab README and confirm that its C23 compiler and Framework SDK prefix are available. Start with the valid-512 synthetic memory fixture; this chapter needs no device path. Read port.c and identify the LabImage allocation before following the borrowed callback.

## The result you will build

The lab creates a synthetic image, gives Framework an exact-read callback, and prints a structural observation. main.c chooses a scenario; image.c constructs teaching data; port.c supplies bytes. Framework remains the only partition parser. These divisions let you change the source adapter later without copying validation logic into each application.

## Own the source before borrowing it

~~~c
LabImage image = {0};
if (!LabImageCreate(&image, 512U)) return 1;
UmiGptImageInfo observation = {0};
UmiStatus status = UmiGptImageInspect(LabReadAt, &image,
    image.length, image.block, &observation);
LabImageDestroy(&image);
~~~

LabImageCreate publishes an allocated image only after construction finishes. The structure owns that allocation. UmiGptImageInspect borrows the structure through its context pointer and calls LabReadAt synchronously. The callback and the source must remain alive until inspection returns. Destroying the image in a callback would violate this ownership contract even though the function pointer itself remained valid.

## Implement an exact read

~~~c
if (offset > image->length || length > image->length - offset)
    return UMI_STATUS_IO_ERROR;
memcpy(destination, image->bytes + (size_t)offset, length);
return UMI_STATUS_OK;
~~~

The offset check comes first because subtracting an excessive unsigned offset would wrap. Once both comparisons succeed, the requested range fits inside the actual allocation, and converting its offset to size_t is justified. This adapter must not return success after copying fewer bytes. A later file adapter would need the same exact-read promise even when the operating system reports a short read.

## Observe the call boundary

Build the lab using its README, then run gpt-inspection.exe valid-512. Expected behavior is one printed synthetic-table observation and exit code zero. The program also requires exactly four callback reads for this successful fixture. That count describes this implementation profile; it is not a promise that all future inspection services use four reads.

## Exercise

Move LabImageDestroy above the inspection call in a separate scratch copy. Explain the lifetime error without executing the broken version. Then restore the order and add a comment naming which function owns the allocation and which function borrows it.

## Worked explanation

Destroying first clears the structure and releases its data. Passing a zero extent would be refused at admission, while passing stale saved pointers would refer to freed storage. Neither pattern is a valid inspection. The correct application keeps its allocation alive through the call and releases it once, afterward. A success code from unrelated earlier work cannot make stale pointers safe.

## What to record

Record the Framework SDK prefix, compiler, scenario, status and observed read count when you run the exercise. The supplied source is authored coverage, not an execution record. This lab establishes no device permission, filesystem validity or successful system boot. Continue with address units before extending the byte adapter.

[Primary GPT format reference](https://uefi.org/specs/UEFI/2.11/05_GUID_Partition_Table_Format.html)

[Standalone lesson](../../../courses/umicom-os-from-scratch/lessons/51-connect-an-owned-image-read-port.html)
