# Read-only MINIX status driver

This original C lab targets the character-driver and SEF interfaces in MINIX 3.3.0. The signatures were compared with the official v3.3.0 hello driver and sef.h. It has not been compiled or loaded in a MINIX guest.

The driver serves a fixed text response through the standard character-driver read callback. It accepts minor zero, calculates a bounded read window and uses sys_safecopyto with the caller's endpoint and grant. It owns no hardware, interrupts or persistent state. Fresh start and restart announce the service; live update is not implemented.

## Study the boundary

Read read_window.c first. When position is at or beyond length, the result is EOF. Otherwise remaining = length - position is safe, and the count is the smaller of requested and remaining. It never computes position + requested. The helper uses separate output objects and preserves them on invalid pointer arguments.

status_driver.c keeps the total response below the ssize_t limit and excludes the string terminator. A failed safecopy returns the actual error rather than a successful byte count. No native pointer is handed to the client.

## Host model qualification

From the Bits2Banking repository in PowerShell:

~~~powershell
cmake -S labs/minix/status-driver -B build/minix-read-window -G Ninja
cmake --build build/minix-read-window
ctest --test-dir build/minix-read-window --output-on-failure
~~~

<!-- The original single-helper qualification description is retained for review. The expanded host suite adds a copy-outcome boundary while preserving the original range test.
The expected test checks ordinary, zero, EOF, huge request and invalid output cases. It compiles only the portable helper, not status_driver.c. A passing host test would not prove IPC permissions, grant handling, SEF startup or guest execution.
-->

The original read-window test remains, and nineteen named read-reply cases extend it. Host compilation covers read_window.c, read_reply.c and their checks, not status_driver.c. A passing host test would not prove IPC permissions, grant handling, SEF startup or guest execution. These cases are authored; no execution result is implied by this guide.

## Guest compilation

Use an isolated MINIX 3.3.0 guest with matching source and development files. Copy this lab into a new working directory, preserving the upstream source tree. In that guest directory:

~~~sh
make
~~~

Expected build product: umi_status. The Makefile uses the guest's minix.service.mk, libchardriver and libsys; do not run it as a Windows build or substitute a modern MINIX master header set.

Installation and service launch require a reviewed guest service configuration, an available device major, a device node and permissions compatible with the chosen image. This lab does not supply an unverified fixed major or a broad hardware-access policy. Read the matching release's service manual and configuration examples before deployment. Inspect the installed command name: newer wiki examples may use minix-service where an older image differs.

## Guest acceptance plan

1. Save a powered-off copy or a supported snapshot of the disposable guest.
2. Record guest release, source revision, compiler and binary digest.
3. Compile and review the service configuration before installation.
4. Read minor zero: expect “Umicom learning status: ready” followed by a newline.
5. Read a short prefix, continue from a nonzero offset and check EOF.
6. In a controlled driver test harness, refuse an invalid grant and verify the error propagates.
7. Restart the service using its supported manager and read again.
8. Record restart separately from live update; no live-update claim is supported.

If loading fails, inspect service configuration and IPC/grant permissions before changing the range calculation. Do not grant arbitrary I/O ports or interrupts to a driver that needs none. A normal application cannot impersonate a privileged grant owner.

## Sources and licence

The original files here use MIT. MINIX source retains its own licence and attribution; it is referenced, not redistributed as Umicom code.

- [MINIX 3.3.0 hello driver](https://github.com/Stichting-MINIX-Research-Foundation/minix/blob/v3.3.0/minix/drivers/examples/hello/hello.c)
- [MINIX 3.3.0 service Makefile](https://github.com/Stichting-MINIX-Research-Foundation/minix/blob/v3.3.0/minix/drivers/examples/hello/Makefile)
- [MINIX 3.3.0 SEF declarations](https://github.com/Stichting-MINIX-Research-Foundation/minix/blob/v3.3.0/minix/include/minix/sef.h)
- [MINIX memory grants guide](https://wiki.minix3.org/doku.php?id=developersguide:memorygrants)

## Copy outcomes and retries

read_reply.h defines the new portable boundary. It reuses read_window.c and invokes
one caller-provided copy callback only for a nonempty admitted slice. Invalid
arguments preserve the reply. Every valid request publishes a fresh reply,
including EOF and copy failure. The input text and callback context are borrowed
until return; the helper retains neither and does not advance a cursor.

A callback reports complete success with zero. Any other integer is preserved as
copy_status and returns COPY_FAILED with zero acknowledged bytes. This does not
guarantee that the destination was unchanged. The fault-injection test deliberately
copies its slice before returning an error so that this distinction is visible.

status_driver.c remains the release-specific adapter. Its local context contains
only the current endpoint and grant; status_copy uses sys_safecopyto at grant offset
zero. The old inline status_read is retained in an explained disabled block.
Minor validation, fixed response text, fresh start and restart remain as before.
No new live-update or hardware capability is introduced.

The host target expects the shared Framework branding helper in the sibling
Umicom-Applications/framework checkout. To choose another source checkout:

~~~powershell
cmake -S labs/minix/status-driver -B build/minix-read-window -G Ninja -DUMICOM_FRAMEWORK_SOURCE=C:/umicom/Umicom-Applications/framework
~~~

This host-only dependency supplies canonical SVG artwork and Windows ICO resources.
It adds no Framework runtime link and does not alter the guest Makefile's service
toolchain. If the path is wrong, correct it rather than substituting new logos.

For a focused host check after a successful build:

~~~powershell
ctest --test-dir build/minix-read-window --output-on-failure --no-tests=error -R "^minix[.]learning[.]read-reply[.]"
~~~

Expect nineteen registered cases: prefix, tail, whole, eof, beyond, huge-position,
zero, empty, null-empty, huge-request, positive-failure, negative-failure, retry,
reuse-eof, null-text, null-copy, null-reply, chunked and null-context. A failed or
missing test remains a failure to investigate; it is not a guest result.

Follow lessons 09–12 in [MINIX OS Foundations](../../../content/courses/minix-os-foundations/index.html)
and complete [the evidence worksheet](QUALIFICATION.md). The worksheet separates
source review, host results, guest compilation, real grant refusal and restart.
