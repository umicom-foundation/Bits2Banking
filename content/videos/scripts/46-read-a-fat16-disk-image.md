# Episode 46 — Read a FAT16 Disk Image

**Length:** approximately 12–16 minutes.

## Opening (0:00–1:30)

**Narrator:** When you save a Notes document, the operating system must turn a filename and its contents into bytes placed somewhere on a storage device. Today we will inspect that organisation without writing a single disk sector.

**Screen:** Show a fictional Notes document, then a drawing of boot sector, FAT, root directory and data area.

## How the volume is arranged (1:30–5:00)

**Narrator:** A sector is a numbered block of bytes. Our sample uses 512-byte sectors. The first sector describes the volume geometry. Notice that the data begins after the reserved sectors, the allocation table and the root directory. A directory entry points to a starting cluster; it is not the file's entire content.

**Screen:** Highlight BPB offsets 11, 13, 14, 16, 17, 19 and 22 in Chapter 137. Calculate the first data sector step by step.

## Read-only C23 inspector (5:00–11:00)

**Narrator:** The C23 inspector receives the complete image bytes and their length. It rejects inconsistent metadata before publishing an answer. Build the test fixture, run the inspector and identify `NOTES.TXT`.

**Screen:** Build and test commands from Chapter 138. Open `BtbFat16Open`, `BtbFat16RootNames` and `BtbFat16Follow`. Demonstrate the deliberately damaged signature on a copy of the fixture.

## Conclusion (11:00–16:00)

**Narrator:** A filesystem reader is not a filesystem repair utility. Understanding that distinction is part of safe systems engineering. Continue with Chapter 139 to follow cluster chains and Chapter 141 to inspect the real Umicom Kernel implementation.

**Screen:** Show links to Chapters 137–141, the laboratory and the Umicom Kernel repository.
