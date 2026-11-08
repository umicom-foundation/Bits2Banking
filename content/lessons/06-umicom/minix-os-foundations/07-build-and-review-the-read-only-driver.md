# Build and review the read-only driver

## Two builds answer different questions

The lab contains a portable range helper and a MINIX-specific driver adapter. A host CMake build checks the helper only. A guest Makefile uses MINIX service rules and links the system's character-driver and system libraries.

The [official 3.3.0 hello Makefile](https://github.com/Stichting-MINIX-Research-Foundation/minix/blob/v3.3.0/minix/drivers/examples/hello/Makefile) establishes the release's service build convention. The Umicom lab is original code, with a distinct program name and a bounded fixed response.

## Start with the host boundary

From the Bits2Banking repository:

~~~powershell
cmake -S labs/minix/status-driver -B build/minix-read-window -G Ninja
cmake --build build/minix-read-window
ctest --test-dir build/minix-read-window --output-on-failure
~~~

Expected coverage includes a normal read window, huge request, EOF, zero length and invalid output arguments. No results are claimed until the owner executes these commands.

## Continue in the guest

Copy the lab into a separate working directory in your release-matched guest, then run make there. Expected product: umi_status. Keep the original MINIX tree and licence notices intact.

Before installation, review the guest's service configuration, an available device major and its device node. The lab does not guess a universal major number or provide a broad privilege policy. Follow the matching service manual; command names can differ between older release images and newer documentation.

## Exercise and answer

The host test passes but the guest link fails to find libchardriver. Should you change read_window.c? Answer: no. Investigate the guest's development libraries and build context. The two builds exercise different boundaries.

## Acceptance record

Record source and binary identities, guest compiler, configuration, observed read text, offset behaviour, grant refusal and restart behaviour. A loaded driver is not yet a qualified driver. A successful restart is not live update, and no live-update implementation is included in this lab.

[Course contents](index.md)
