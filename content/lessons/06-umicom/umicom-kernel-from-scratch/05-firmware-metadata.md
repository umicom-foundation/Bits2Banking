# Read firmware bytes without following their addresses

Firmware can describe hardware and reserved memory in a flattened device tree. A valid magic number does not make every offset or length inside that buffer safe. The Kernel first proves that the whole blob fits its known RAM, then passes bounded bytes to its existing strict reader.

## Find the existing owners

1. Read `device_tree.c`: this is the small physical-range check.
2. Read `device_tree_reader.c`: it validates the header, section separation, reservation list, names and tree tokens.
3. Read `device_tree_firmware.c`: it normalizes only property-padding bytes in a private copy, then asks the same strict reader to validate everything.
4. Read `device_tree_layout.c`: it projects accepted fields and reservations without adding a second grammar.

A reservation contains an address as data. The parser must never dereference that address. It decodes each big-endian integer byte by byte and checks arithmetic before adding lengths. The reader has explicit limits for bytes, nodes, properties, nesting and reservation entries.

## Build the original lab

```text
Set-Location "C:\umicom\Umicom-Bits2Banking"
cmake -S ".\labs\native\kernel-boot-metadata" -B ".\build\kernel-boot-metadata" -G Ninja -DUMICOM_KERNEL_SOURCE=C:/umicom/umicom-kernel -DBUILD_TESTING=ON
cmake --build ".\build\kernel-boot-metadata" --parallel 2
ctest --test-dir ".\build\kernel-boot-metadata" --output-on-failure --no-tests=error --output-log ".\build\kernel-boot-metadata\tests.log"
```

Use a 64-bit C23 compiler. Stop when a command fails. Expected results: the plan case succeeds and the malformed fixtures are rejected as expected. These host cases do not boot firmware or prove that a physical pointer is accessible.

## Exercise

Find the final END token in the fixture. Replace it with a NOP and predict the result. A bounded buffer without a closing token is still malformed. Then inspect the big-endian bytes encoding the reservation address and explain why casting them to a native integer would be incorrect on a little-endian machine.

Reference: [Devicetree Specification](https://devicetree-specification.readthedocs.io/en/stable/flattened-format.html). This lesson and its fixtures are original Umicom material.

## Need an earlier explanation?

[Review the foundation concepts](../../00-getting-started/07-applications-os-and-kernel.md), then use the [connected learning map](../../../courses/learning-paths.html#kernel) for the longer written chapters. For C syntax or compiler commands, use the map's first-programming route before running this lab.

---

[Read this lesson in HTML](../../../courses/umicom-kernel-from-scratch/lessons/05-firmware-metadata.html) · [Learning sequence](../../../start/learning-sequence.md)

[Previous: Never execute a damaged prefix](04-damaged-console-lines.md)

[Next: Keep firmware-owned pages out of the allocator](06-reserved-pages.md)
