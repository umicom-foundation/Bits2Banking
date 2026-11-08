# Choose a release and an isolated guest

## Begin with an identifiable system

An operating-system lesson needs a reproducible target. This course studies MINIX 3.3.0 and the matching v3.3.0 source tag. It does not silently combine stable headers with later development snapshots.

The [official download page](https://minix3.org/download/) provides release media. The [tracking-current guide](https://wiki.minix3.org/doku.php?id=developersguide:trackingcurrent) explicitly describes a different development path. Follow that path only as a separate exercise.

## Prepare the environment

1. Obtain release media from the official source and retain its filename and digest.
2. Create a disposable virtual-machine directory with no personal data.
3. Read the official installation guide for your emulator.
4. Boot the live media before installing a guest disk.
5. Record the emulator version, machine settings and guest release.
6. Keep a recoverable powered-off disk copy before experimenting with services.

A virtual disk file is distinct from a host physical disk. Verify the selected destination in an installer. This course does not require repartitioning the host.

Inside the guest, inspect the system before compiling:

~~~sh
uname -a
cc --version
ls /usr/src
~~~

The compiler version option or source directory may differ in a minimal installation. A missing development tree is an environment gap to resolve, not a reason to copy arbitrary headers from another release.

## Worked comparison

Two learners use an identical driver file. One compiles against 3.3.0; the other uses a development snapshot's headers. Their different outcomes are not directly comparable until the dependency identities are recorded.

## Exercise and answer

Does saving the ISO filename prove the downloaded bytes match the publisher? Answer: no. Retain the digest and the publisher's available verification information. A locally calculated digest identifies your file; it is not independently a signature or authenticity proof.

## Reading route

Use the [official QEMU installation notes](https://wiki.minix3.org/doku.php?id=usersguide:runningonqemu) as historical setup guidance and check options against your installed emulator. No VM has been installed or launched as part of authoring this course.

[Course contents](index.md)
