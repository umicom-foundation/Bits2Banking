<!--
Umicom Bits2Banking
File: content/lessons/06-umicom/umicom-kernel-from-scratch/139-find-a-short-device-tree-path-after-a-long-branch.md

PURPOSE:
Find a short device-tree path after a long branch

AUTHOR AND ORGANISATION:
Sammy Hegab
Umicom Foundation

LICENCE:
MIT
-->

![Umicom](../../../assets/branding/umicom-wordmark.svg) · [Umicom icon](../../../assets/branding/umicom-icon.svg) · [Windows icon](../../../assets/branding/umicom.ico)

# Find a short device-tree path after a long branch

Imagine looking for a book on a shelf. You pass a long shelf label that cannot be copied onto your small note card. You can still look for the short label on the next shelf. A path lookup in the Kernel needs the same distinction.

## 1. Follow a tree one name at a time

A **device tree** describes hardware and its settings. A **node** represents one part of the tree. Each node has a name and, except for the root, a parent. In a flattened device tree the names and relationships are encoded as bytes. The Kernel reader checks those bytes before treating them as hardware descriptions.

An absolute path starts at the root. The path `/target` means the root child named `target`. Consider this small drawing of the in-memory fixture.

~~~text
/
  first long name
    second long name
      third long name
  target
~~~

The first three names are each 86 bytes in the synthetic Umicom fixture. Writing all three names and their slashes would use 261 bytes before the final string terminator. The current reader's printable path buffer is 256 bytes. All three individual names fit the reader's own limits. The short path `/target` takes seven bytes before its terminator.

## 2. Separate lookup from writing a path

`UmicomKernelDeviceTreePath` tries to write one node's full path to a buffer. It reports `UMICOM_TREE_LIMIT` when the long path cannot be written. `UmicomKernelDeviceTreeFind` takes one exact query that fits the same space. If an unrelated candidate cannot fit, it cannot equal the query. The lookup continues to the next candidate. It still reports a structural problem such as an invalid parent link.

~~~text
CHECK that the query fits the supported path space
FOR each node in the checked tree
    ASK for the node's exact full path
    IF that candidate is too long for the same buffer, continue
    IF a structural check fails, report the error
    IF the path equals the query, return the node
REPORT that the path was absent
~~~

Here is the call shape used by a C reader that already holds a validated tree. Check the return value before using the output identifier.

~~~c
/* Use the node id only when the lookup reports a match. */
UmicomSize node = 0U;
UmicomKernelTreeStatus status = UmicomKernelDeviceTreeFind(reader, "/target", &node);
~~~

## 3. Read the host test result

The Kernel's `tests/hardware_catalogue/device_tree_tests.c` contains the synthetic lookup case. From a configured build of `tests/hardware_catalogue`, the `umicom-hardware-tests` target owns it. Set `$hardwareBuild` to that build directory.

~~~powershell
cmake --build $hardwareBuild --target umicom-hardware-tests --parallel 1
ctest --test-dir $hardwareBuild --output-on-failure -R '^hardware[.]lookup_beyond_long_branch$'
~~~

The mirror host test passed. Its positive control finds `/target`, a separate lookup reports absence, and the full-path operation still reports its size limit. Draw another root child after `target` and predict what an exact query for it should return. The fixture models discovery in memory. Physical device discovery needs separate evidence.

[Course contents](index.md) · [Previous lesson · Match ELF files to a finished Kernel build](138-match-elf-files-to-a-finished-kernel-build.md) · [Next lesson · Read a declared hardware timebase](140-read-a-declared-hardware-timebase.md) · [HTML edition](../../../courses/umicom-kernel-from-scratch/lessons/139-find-a-short-device-tree-path-after-a-long-branch.html)
